#ifndef __VARIABLES_H__
#define __VARIABLES_H__
#include <stdlib.h>

#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;
// This class is used to save the variables.
// An map<string, string> is used to save a key-value pair.
// The key is variable and the value is a string

class Variables
{
 private:
  map<string, string> vars;

 public:
  Variables() {}
  Variables(Variables & rhs) { vars = rhs.vars; }

  //check if the variable name is valid
  bool validVar(string s) {
    for (int i = 0; i < (int)s.size(); i++) {
      if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
        continue;
      else
        return false;
    }
    return true;
  }

  // Set a new variable - value pair
  void setVar(string var, string value) {
    if (validVar(var))
      vars[var] = value;
    else {
      cout << "Variable should only contains a-zA-Zand_\n";
    }
  }

  // This function Inc a variable
  void incVar(string var) {
    bool allDigi = true;
    ;
    if (findVar(var)) {
      //dont support out of range INTMAX
      for (int i = 0; i < (int)vars[var].size(); i++) {
        if (!isdigit(vars[var][i])) {
          allDigi = false;
          break;
        }
      }
      if (allDigi) {
        int num;
        sscanf(vars[var].c_str(), "%d", &num);
        num++;
        ostringstream s;
        s << num;
        vars[var] = s.str();
        return;
      }
      else {
        setVar(var, "1");
        return;
      }
    }
    // If we do not have this var or var's value is not a number
    setVar(var, "1");
    return;
  }
  // This function export a key-value pair to the environment variable
  void exportVar(string var) {
    if (findVar(var)) {
      setenv(var.c_str(), vars[var].c_str(), 1);  //overwrite
    }
    else {
      cout << "set the var before export!\n";
    }
  }

  // This function returns the
  string getVar(string var) {
    if (findVar(var)) {
      return vars[var];
    }
    else {
      return "";
    }
  }
  // This function returns if the var exists
  bool findVar(string var) {
    map<string, string>::const_iterator got = vars.find(var);

    if (got == vars.end())
      return false;
    else
      return true;
  }
  // This function returns the map
  map<string, string> getMap() { return vars; }
};

#endif
