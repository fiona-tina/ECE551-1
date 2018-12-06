#include <assert.h>

#include <iostream>
using namespace std;
int main(int argc, char * argv[]) {
  assert(argc == 2);
  cout << "Arguments Value 0 is " << argv[0] << endl;
  cout << "Arguments Value 1 is " << argv[1] << endl;
  return 0;
}
