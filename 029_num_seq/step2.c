// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  return (x + 1) * (x + 1) + x;
}

int sumSeq2(int low, int high) {
  int res = 0;
  if (low >= high)
    return res;

  for (int i = low; i < high; i++) {
    res += seq2(i);
  }
  return res;
}

int main() {
  int x[15] = {-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 14};
  for (int i = 0; i < 15; i++) {
    printf("seq2(%d) = %d\n", x[i], seq2(x[i]));
  }
  int low[5] = {0, 3, 9, -3, -6};
  int high[5] = {2, 6, 7, 2, -6};
  for (int i = 0; i < 5; i++) {
    printf("sumSeq2(%d, %d) = %d\n", low[i], high[i], sumSeq2(low[i], high[i]));
  }

  return 0;
}
