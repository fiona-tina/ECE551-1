#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char ** argv) {
  vector<string> strs;
  ifstream in(argv[1]);
  string str;
  while (getline(in, str)) {
    strs.push_back(str);
  }
  sort(strs.begin(), strs.end());
  vector<string>::iterator it;
  for (it = strs.begin(); it != strs.end(); ++it) {
    cout << *it << endl;
  }
  return 0;
}
