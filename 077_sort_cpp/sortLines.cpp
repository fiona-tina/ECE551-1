#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char ** argv) {
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      ifstream is(argv[i]);
      vector<string> strs;
      string str;
      if (!is) {
        cerr << "wrong inputsize" << endl;
        exit(EXIT_FAILURE);
      }
      while (getline(is, str)) {
        strs.push_back(str);
      }
      sort(strs.begin(), strs.end());
      vector<string>::iterator it;
      for (it = strs.begin(); it != strs.end(); ++it) {
        cout << *it << endl;
      }
    }
  }
  else {
    vector<string> strs;
    string str;
    while (getline(cin, str)) {
      strs.push_back(str);
    }
    sort(strs.begin(), strs.end());
    vector<string>::iterator it;
    for (it = strs.begin(); it != strs.end(); ++it) {
      cout << *it << endl;
    }
  }

  return 0;
}
