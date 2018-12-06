#ifndef __SHELL_H__
#define __SHELL_H__
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Arguments.h"
#include "Environs.h"
#include "Parser.h"
#include "Support.h"
// This shell class contains functions related to execute
using namespace std;

class Shell
{
 public:
  // This function was supposed to deal with Pipe.
  // However, I could not get the pipe() working.
  // Still, I decided to leave it here for future reference.
  void executePipe(vector<string> programs, char ** _environ, Environs * env) {
    //pipefd[0] refers to the read end of the pipe.  pipefd[1] refers to the write
    //end of the pipe.
    int n = (int)programs.size();
    //cout<< " total no. for programs are:" << n<<endl;
    int ** pipefd = new int *[n - 1];
    for (int i = 0; i < n - 1; i++) {
      pipefd[i] = new int[2];
    }

    for (int i = 0; i < n - 1; ++i) {
      int * tmp = pipefd[i];
      if (pipe(tmp) == -1) {
        perror("pipe() failed");
      }
    }

    for (int i = 0; i < n; i++) {  // 0 1
      //not need to modify the first and the last
      //creat child processes
      pid_t cpid = fork();
      if (cpid == 0) {
        //child
        if (i == 0) {
          close(1);
          if (dup2(pipefd[i][1], 1) < 0) {
            perror("dup2 fail");
            exit(EXIT_FAILURE);
          }

          close(pipefd[i][0]);

          //close(pipefd[i][0]);
        }
        else if (i == n - 1) {
          //read..

          //close(0);
          close(0);
          if (dup2(pipefd[i - 1][0], 0) < 0) {
            perror("dup1 fail");
            exit(EXIT_FAILURE);
          }

          close(pipefd[i - 1][1]);

          //close(pipefd[i-1][1]);
        }
        else {
          // in the middle;
          cout << "int the middel\n";
        }
        //close all pipe before execve
        Arguments * arg = new Arguments();
        map<string, string> dummy;
        Parser psr;
        arg->argValue =
            psr.parseInput(programs[i], dummy, arg);  // convert string to vector<string>
        //cout<<"argValue[0] is "<<args -> argValue[0]<<endl;
        if (arg->searchEnv()) {
          int envpath_no = findPath(arg, env);
          if (envpath_no == -1) {
            cout << "Command " << arg->argValue[0] << " not found\n";
          }
          else {
            arg->argValue[0] = env->envValue[envpath_no] + "/" + arg->argValue[0];
            arg->parseArg();  // convert vector<string> to char** directly
            execveChild(arg, _environ);
          }
        }
        else {
          arg->parseArg();  // convert vector<string> to char** directly

          execveChild(arg, _environ);
        }

        delete arg;
      }

      pid_t wpid;
      int status = 0;
      while ((wpid = wait(&status)) > 0)  //wait all the child process
      {
        if (WIFEXITED(status)) {
          printf("Program exited with status %d\n", WEXITSTATUS(status));
        }
      }
    }

    for (int i = 0; i < n - 1; ++i) {
      delete[] pipefd[i];
    }
    delete[] pipefd;
  }

  // This function will execve a child process and also performs redirection

  void execveChild(Arguments * args, char ** _environ) {
    //redir
    for (int i = 0; i < 3; i++) {
      if (args->redir[i] != "") {  //stdin
        if (i == 0) {
          int fd = open(args->redir[i].c_str(), O_RDONLY, S_IRUSR);
          if (dup2(fd, 0) < 0) {
            perror("stdin fail");
          }
          close(fd);
        }
        else if (i == 1) {  //stdout
          int fd = open(args->redir[i].c_str(), O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
          if (dup2(fd, 1) < 0) {
            perror("stdout fail");
          }
          close(fd);
        }
        else if (i == 2) {
          int fd = open(args->redir[i].c_str(), O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
          if (dup2(fd, 2) < 0) {
            perror("stderr fail");
          }
          close(fd);
        }
      }
    }
    //cout<<args->argV[0]<<endl;
    if (execve(args->argV[0], args->argV, _environ) == -1) {
      perror("cannot execve");
      exit(1);
    }
  }

  // This function will create a child process and execute it
  void executeProg(Arguments * args, char ** _environ) {
    pid_t pid;
    pid = fork();
    if (pid == -1) {
      perror("fork!");
      exit(1);
    }

    extern int errno;
    int status;
    if (pid == 0) {
      execveChild(args, _environ);
    }

    //wait for the process to finish
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
      printf("Program exited with status %d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {  // program terminated by a signal
      printf("Program was killed by signal %d\n\n", WTERMSIG(status));
    }
  }
};

#endif
