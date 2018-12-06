#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdlib.h>

#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "arguments.h"
using namespace std;
//This class contains functions related to input string parse
class Parser
{
 public:
  //This function will parse the input string if it contains Pipe

  vector<string> parsePipe(string s) {
    vector<string> res;
    int n = s.size();
    int start = 0, end = 0;
    for (; end < n; end++) {
      if (s[end] == '|') {
        string tmp = s.substr(start, end - start);
        start = end + 1;
        res.push_back(tmp);
      }
    }

    // push the last one
    if (end > start) {
      string tmp = s.substr(start, end - start);
      res.push_back(tmp);
    }
    return res;
  }

  // This funtion will parser the PATH to a vector of strings
  vector<string> parseEnv(string s) {
    size_t n = s.size();
    vector<string> res;
    size_t start = 0, end = 0;
    for (; end < n; end++) {
      if (s[end] == ':') {
        string tmp = s.substr(start, end - start);
        res.push_back(tmp);
        start = end + 1;
      }
    }
    //push the last one
    if (start != end) {
      string tmp = s.substr(start, end - start);
      res.push_back(tmp);
    }
    return res;
  }

  //This function parse the input string to get the redirections and elim them
  void parseRedir(string & s, int i, Arguments * arguments) {
    // The three flags are used to check if the redirection appeared more than once
    bool in = false, out = false, err = false;

    // If we meet a '< ', a'> ', or a '2> ' put the corresponding
    // filename to the redir vector in Arguments class
    if (s[i] == '<') {
      //input 0
      if (in) {
        perror("redir format is not correct");
        exit(1);
      }
      in = true;
      s[i] = ' ';
      if (i + 1 >= (int)s.size() || s[i + 1] != ' ') {
        perror("redir format is not correct");
        exit(1);
      }
      int k = i + 2;
      for (; k < (int)s.size(); k++) {
        if (s[k] == ' ' || s[k] == '\\') {
          break;
        }
      }
      string tmp = s.substr(i + 2, k - i - 2);

      s.erase(i + 2, k - i - 2);
      arguments->redir[0] = tmp;
    }
    else if (s[i] == '2') {
      if (err) {
        perror("redir format is not correct");
        exit(1);
      }
      err = true;
      if (i + 1 < (int)s.size() && s[i + 1] == '>') {
        //stderr 2
        if (i + 2 >= (int)s.size() || s[i + 2] != ' ') {
          perror("redir format is not correct");
          exit(1);
        }
        s[i] = ' ';
        s[i + 1] = ' ';
        int k = i + 3;
        for (; k < (int)s.size(); k++) {
          if (s[k] == ' ' || s[k] == '\\') {
            break;
          }
        }
        string tmp = s.substr(i + 3, k - i - 3);

        s.erase(i + 3, k - i - 3);
        arguments->redir[2] = tmp;
      }

      //else, end of string, do nothing
    }
    else if (s[i] == '>') {
      //stdout 1
      if (out) {
        perror("redir format is not correct");
        exit(1);
      }
      out = true;
      s[i] = ' ';
      if (i + 1 >= (int)s.size() || s[i + 1] != ' ') {
        perror("redir format is not correct");
        exit(1);
      }
      int k = i + 2;
      for (; k < (int)s.size(); k++) {
        if (s[k] == ' ' || s[k] == '\\') {
          break;
        }
      }
      string tmp = s.substr(i + 2, k - i - 2);
      s.erase(i + 2, k - i - 2);
      arguments->redir[1] = tmp;
    }
  }

  // This function parse the input string for most part.
  // It will check if redirection happens, deal with multiple
  // space and '\ ' and return a corresponding vector<string>
  vector<string> parseInput(string s, map<string, string> & m, Arguments * arguments) {
    vector<string> res;
    // change all '/ 'to ' 'first
    //elim leading space
    int start = 0, end = 0;

    //first check if there are variables
    for (int i = 0; i < (int)s.size(); i++) {
      if (s[i] == '>' || s[i] == '<' || s[i] == '2') {
        parseRedir(s, i, arguments);  // copy the filename to redir vector and change >... to space
      }

      if (s[i] == '$') {
        int j = i + 1;
        while ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z') || s[j] == '_') {
          j++;
        }
        string tmp = s.substr(i + 1, j - i - 1);

        map<string, string>::const_iterator got = m.find(tmp);

        if (got == m.end()) {
          perror("This var have not been set!");
        }
        else {
          s.erase(i, j - i);
          s.insert(i, m[tmp]);
        }
        //else do nothing
      }
    }
    //cout<<"intput after transform: "<<s<<endl;
    //loop through the input string
    //split when space
    //ignore when backslashspace
    for (; end < (int)s.size(); end++) {
      if (s[end] == ' ') {
        if (start == end) {
          start++;
          continue;
        }
        if (s[end - 1] != '\\') {
          string tmp = s.substr(start, end - start);
          res.push_back(tmp);
          start = end + 1;
        }
      }
    }
    if (start != end) {
      string tmp = s.substr(start, end - start);
      res.push_back(tmp);
    }

    //remove every backslashspace with in the res vector
    for (int i = 0; i < (int)res.size(); i++) {
      for (int j = 0; j < (int)res[i].size() - 1; j++) {
        if (res[i][j] == '\\' && res[i][j + 1] == ' ') {
          res[i].erase(res[i].begin() + j);
          j--;
        }
      }
    }
    return res;
  }
};

#endif
