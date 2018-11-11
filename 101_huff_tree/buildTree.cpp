#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (int i = 0; i < 257; ++i) {
    if (counts[i] != 0)
      pq.push(new Node(i, counts[i]));
  }
  while (pq.size() > 1) {
    Node * right = pq.top();
    pq.pop();
    Node * left = pq.top();
    pq.pop();
    Node * newRoot = new Node(left, right);
    pq.push(newRoot);
  }
  return pq.top();
}
