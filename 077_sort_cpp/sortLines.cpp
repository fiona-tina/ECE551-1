#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char ** argv) {
  vector<string> strs;
  string str;
  if (argc > 2) {
    cerr << "wrong inputsize" << endl;
    exit(EXIT_FAILURE);
  }
  else if (argc == 2) {
    ifstream is(argv[1]);
    if (!is) {
      cerr << "wrong inputsize" << endl;
      exit(EXIT_FAILURE);
    }
    while (getline(is, str)) {
      strs.push_back(str);
    }
  }
  else {
    while (cin >> str) {
      strs.push_back(str);
    }
  }
  sort(strs.begin(), strs.end());
  vector<string>::iterator it;
  for (it = strs.begin(); it != strs.end(); ++it) {
    cout << *it << endl;
  }
  return 0;
}
