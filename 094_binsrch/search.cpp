#include <math.h>

#include <iostream>

#include "function.h"
using namespace std;
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high) {
    exit(EXIT_FAILURE);
  }
  if (low == high)
    return low;
  while (low < high - 1) {
    int mid = low - (low - high) / 2;
    int val = f->invoke(mid);
    if (val > 0)
      high = mid;

    else  //<=0
      low = mid;
  }
  return low;
}
