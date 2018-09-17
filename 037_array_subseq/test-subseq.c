#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);
void test(int a[], int n, size_t ans) {
  if (maxSeq(a, n) != ans)
    printf("Failed this test case!");
  return;
}

int main() {
  int a[5] = {0, 1, 2, 3, 4};
  int b[5] = {0, 1, 2, -1, 4};
  int c[0] = {};
  int d[3] = {7, 6, 5};
  int e[7] = {0, 1, 2, 2, 2, 3, 4};
  int f[5] = {-5, -4, -3, -2, -1};
  int g[3] = {0, 0, 0};
  int h[12] = {1, 2, 1, 3, 1, 2, 1, 2, 1, 2, 3, 4};
  int i[9] = {5, 4, 3, 2, 1, 2, 3, 0, 5};
  int j[10] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  test(a, 5, 5);
  test(b, 5, 3);
  test(c, 0, 0);
  test(d, 3, 1);
  test(e, 7, 3);
  test(f, 5, 5);
  test(g, 3, 1);
  test(h, 12, 4);
  test(i, 9, 3);
  test(j, 10, 4);
  exit(EXIT_SUCCESS);
}
