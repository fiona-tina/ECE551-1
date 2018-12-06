#ifndef __SUPPORT_H__
#define __SUPPORT_H__
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
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Arguments.h"
#include "Environs.h"
using namespace std;

// This function is used to check if a file is contained
// in a PATH. If we found one, return the index of the
// corresponding path in the vector. Else return -1;
int findPath(Arguments * args, Environs * env) {
  struct stat buffer;
  assert(args->argValue.size() != 0);
  for (int i = 0; i < (int)env->envValue.size() - 1; i++) {
    string tmp = env->envValue[i] + "/" + args->argValue[0];
    if (stat(tmp.c_str(), &buffer) == 0) {
      return i;
    }
  }
  return -1;
}

// This function gets the curDir and return as a string
string getPrompt() {
  char * buffer = get_current_dir_name();

  //char buffer[1024];
  //getcwd(buffer, 1024);
  string part1 = "myShell:";
  string part2(buffer);
  string part3 = " $";
  string res = part1 + part2 + part3;

  free(buffer);
  return res;
}

// This function checks if the new directory is valid
bool changeDir(string newDir) {
  if ((chdir(newDir.c_str()) == 0)) {
    return 1;
  }
  return 0;
}

#endif
