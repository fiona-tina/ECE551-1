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

#include "arguments.h"
#include "environs.h"
#include "parser.h"
#include "shell.h"
#include "support.h"
#include "variables.h"

using namespace std;

//This is the main function of my shell
//extern char **environ gets the environment variables
extern char ** environ;
int main(int argc, char * argv[]) {
  //create a Parser object and a Variables object.
  Parser psr;
  Variables variables;

  while (1) {
    char ** _environ = environ;

    // env will be dealing with PATH
    Environs * env = new Environs;
    char * pPath;
    pPath = getenv("PATH");
    string pPath_s(pPath);
    env->envValue = psr.parseEnv(pPath_s);

    Shell * myShell = new Shell();

    string prompt = getPrompt();
    string input_s;
    cout << prompt;

    // Get user input
    getline(cin, input_s);
    if (cin.eof()) {
      printf("\nexit myshell...\n");
      delete myShell;
      delete env;
      break;
    }
    map<string, string> m = variables.getMap();

    // Again, I tried to do the pipe part but did not finished
    vector<string> input_pipe;
    input_pipe = psr.parsePipe(input_s);

    if (input_pipe.size() == 0) {
      printf("type something\n");
    }
    else if (input_pipe.size() > 1) {
      // Should be the implementation of pipe here
    }
    else {
      // no pipe, pipeArgs.size() == 1
      Arguments * args = new Arguments();
      args->argValue = psr.parseInput(input_pipe[0], m, args);
      // convert char* to vector<string>

      // The following if-else clause will check if we are calling some
      // build-in functions including cd, set, export, inc and exit
      if (args->argValue.size() == 0) {
        printf("type something\n");
      }
      else if (args->argValue[0] == "cd") {
        if (args->argValue.size() != 2) {
          cout << "wrong size\n";
        }
        else {
          string newDir = args->argValue[1];
          if (!changeDir(newDir)) {
            cout << "Invalid directory!\n";
          }
        }
      }
      else if (args->argValue[0] == "set") {
        if (args->argValue.size() != 3) {
          cout << "wrong argc\n";
        }
        else {
          variables.setVar(args->argValue[1], args->argValue[2]);
        }
      }
      else if (args->argValue[0] == "export") {
        if (args->argValue.size() != 2) {
          cout << "wrong argc\n";
        }
        else {
          variables.exportVar(args->argValue[1]);
        }
      }
      else if (args->argValue[0] == "inc") {
        if (args->argValue.size() != 2) {
          cout << "wrong argc\n";
        }
        else {
          variables.incVar(args->argValue[1]);
        }
      }
      else if (args->argValue[0] == "exit") {
        printf("exit myshell..\n");

        delete myShell;
        delete args;
        delete env;
        break;
      }
      // try to check if argValue[0] is abslute path
      // Check if we need to search the PATH
      else if (args->searchEnv()) {
        // we have a args->: vector<string> argValue
        // we have a env: vector<string> envValue
        // concate argValue[0] with all envValue
        // is exsit, we go

        int envpath_no = findPath(args, env);
        if (envpath_no == -1) {
          cout << "Command " << args->argValue[0] << " not found\n";
        }
        else {
          args->argValue[0] = env->envValue[envpath_no] + "/" + args->argValue[0];
          args->parseArg();  // convert vector<string> to char** directly
          myShell->executeProg(args, _environ);
        }
      }
      else {
        args->parseArg();  // convert vector<string> to char** directly
        myShell->executeProg(args, _environ);
      }
      delete args;
    }

    //Clean up after each loop
    delete myShell;
    delete env;
  }
  return 0;
}
