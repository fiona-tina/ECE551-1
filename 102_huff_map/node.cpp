#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    // a leaf
    theMap[freq] = b;
  }
  else {
    //not a leaf
    assert(left != NULL && right != NULL);
    BitString leftStr = b.plusZero();
    BitString rightStr = b.plusOne();
    left->buildMap(leftStr, theMap);
    right->buildMap(rightStr, theMap);
  }
}
