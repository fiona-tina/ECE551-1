#include <stddef.h>

size_t maxSeq(int * a, size_t n) {
  size_t res = 1;
  size_t tmp = 1;
  if (n == 0)
    return 0;
  if (n == 1)
    return tmp;
  for (size_t i = 1; i < n; i++) {
    if (a[i] > a[i - 1]) {
      tmp++;
      if (tmp > res)
        res = tmp;
    }
    else {
      tmp = 1;
    }
  }
  return res;
}
