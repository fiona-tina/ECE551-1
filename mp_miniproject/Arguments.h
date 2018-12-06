#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__
#include <assert.h>
#include <stdlib.h>

#include <cstring>
#include <string>
#include <vector>
using namespace std;
// This class is similar to Environs.
// It is used to store and convert arguments
class Arguments
{
 public:
  vector<string> argValue;

  int n;
  char ** argV;
  vector<string> redir;  // redir[0]-->stdin..
  Arguments() :
      n(0),
      argV(NULL),
      redir(3, ""){

      };

  void parseArg() {
    n = (int)argValue.size();

    argV = new char *[n + 1];
    for (int i = 0; i < n; i++) {
      const char * tmp = argValue[i].c_str();
      argV[i] = (char *)malloc(argValue[i].size() + 1);
      strcpy(argV[i], tmp);
    }
    argV[n] = NULL;
  }

  // Check if we need to search PATH
  bool searchEnv() {
    int count = argValue[0].size();
    assert(count != 0);
    for (int i = 0; i < count; i++) {
      if (argValue[0][i] == '/') {
        return false;
        //already a good path;
      }
    }
    //we need to append the path to the program;
    return true;
  }
  ~Arguments() {
    for (int i = 0; i < n; ++i)
      free(argV[i]);
    delete[] argV;
  };
};
#endif
