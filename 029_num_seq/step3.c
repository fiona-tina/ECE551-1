// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return x * (y - 3) + 2 * y;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int res = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0)
        res++;
    }
  }
  return res;
}

int main() {
  int x[5] = {-5, -4, -1, 0, 4};
  int y[5] = {-3, -4, 0, 3, 5};
  for (int i = 0; i < 5; i++) {
    printf("seq3(%d, %d) = %d\n", x[i], y[i], seq3(x[i], y[i]));
  }

  int xLow[5] = {5, -1, 0, 7, 2};
  int xHi[5] = {2, 4, 2, 10, 2};
  int yLow[5] = {-1, 4, 0, -4, 2};
  int yHi[5] = {6, 6, 3, -6, 2};

  for (int i = 0; i < 5; i++) {
    printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
           xLow[i],
           xHi[i],
           yLow[i],
           yHi[i],
           countEvenInSeq3Range(xLow[i], xHi[i], yLow[i], yHi[i]));
  }

  return 0;
}
