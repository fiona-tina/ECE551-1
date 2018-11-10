#include <bits/stdc++.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
using namespace std;

void printFile(unordered_map<string, vector<string> > & mp) {
  //#Removing /home/ece551/test/file1 (duplicate of /home/ece551/test/dir1/file2).
  //
  // rm /home/ece551/test/file1
  //
  for (auto & it : mp) {
    vector<string> names = it.second;
    int n = names.size();
    if (n == 1)
      continue;
    for (int i = 1; i < n; ++i) {
      cout << "#Removing " << names[i] << " (duplicate of " << names[0] << ").\n";
      cout << "rm " << names[i] << endl;
    }
  }
}

mode_t checkType(const char * dir) {
  struct stat sb;
  if (stat(dir, &sb) == -1) {
    perror("cant get stat");
    exit(EXIT_FAILURE);
  }
  return sb.st_mode & S_IFMT;
}

void insertToHash(const char * dir, unordered_map<string, vector<string> > & mp) {
  string key = "";
  ifstream fin(dir);
  string s;
  while (getline(fin, s)) {
    key += s;
  }
  fin.close();
  mp[key].emplace_back(dir);
}

void findFiles(const char * dir, unordered_map<string, vector<string> > & mp) {
  //cout << "findFiles in: " << dir << endl;
  mode_t type = checkType(dir);
  if (type != S_IFDIR) {
    //not a dir
    if (type != S_IFLNK) {
      //not a symlink
      insertToHash(dir, mp);
    }
  }
  else {
    //a dir
    DIR * curDir;
    struct dirent * aFile;

    if ((curDir = opendir(dir)) == NULL) {
      cerr << "unable to open this dir";
      exit(1);
    }
    //look all the files in side it
    while ((aFile = readdir(curDir)) != NULL) {
      //      cout << aFile->d_name << endl;
      if (strcmp(aFile->d_name, ".") == 0 || strcmp(aFile->d_name, "..") == 0)
        continue;
      string fname = aFile->d_name;
      string thisDir = dir;
      string newDir = "";
      newDir = thisDir + "/" + fname;
      //cout << newDir << endl;
      //exit(0);
      findFiles(newDir.c_str(), mp);
    }
    closedir(curDir);
  }
}

int main(int argc, char ** argv) {
  if (argc <= 1) {
    cerr << "must have as least one directory!";
    exit(EXIT_FAILURE);
  }
  unordered_map<string, vector<string> > mp;
  //key is the file content and the val is the vector of name;
  for (int i = 1; i < argc; ++i) {
    findFiles(argv[i], mp);
  }

  cout << "#!/bin/bash\n";
  printFile(mp);
  return 0;
}
