// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return 4 * x - 3;
}

void printSeq1Range(int low, int high) {
  if (low >= high)
    printf("\n");
  else {
    for (int i = low; i < high; i++) {
      if (i == high - 1)
        printf("%d\n", seq1(i));
      else {
        printf("%d, ", seq1(i));
      }
    }
  }
}

int main() {
  int x[10] = {-4, -2, 0, 2, 3, 5, 6, 7, 13, 21};
  for (int i = 0; i < 10; i++) {
    printf("seq1(%d) = %d\n", x[i], seq1(x[i]));
  }

  int low[5] = {0, 0, -5, 7, -2};
  int high[5] = {0, 4, -1, 3, 6};
  for (int i = 0; i < 5; i++) {
    printf("printSeq1Range(%d, %d)\n", low[i], high[i]);
    printSeq1Range(low[i], high[i]);
  }
  return 0;
}
