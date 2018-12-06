#include <errno.h>
#include <stdio.h>

#include <iostream>
using namespace std;
int main(int argc, char * argv[]) {
  string s;
  cin >> s;
  cout << "you have just STDIN a string :" << s << endl;
  perror("error happens..");
  return 0;
}
