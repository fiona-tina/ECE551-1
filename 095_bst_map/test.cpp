#include <iostream>
#include <stdexcept>
#include <string>

#include "bstmap.h"
#include "map.h"

using namespace std;

int main() {
  BstMap<int, string> bBst;
  try {
    bBst.add(5, "root");
    bBst.add(3, "left");
    bBst.add(7, "right");

    BstMap<int, string> aBst(bBst);
    cout << aBst.root->val;
    //cout << aBst.root->left->val;
    //cout << aBst.root->right->val;
    aBst.printing();
    cout << "---------\n";
    aBst.remove(5);
    aBst.printing();
    cout << aBst.lookup(5) << endl;
  }
  catch (std::invalid_argument e) {
    cerr << e.what() << endl;
    //    exit(EXIT_FAILURE);
  }

  return 0;
}
