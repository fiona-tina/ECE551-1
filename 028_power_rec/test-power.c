#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) == expected_ans) {
    return;
  }
  else
    exit(EXIT_FAILURE);
}
int main() {
  run_check(3, 4, 81);
  run_check(1, 5, 1);
  run_check(0, 177, 0);
  run_check(2, 4, 16);
  run_check(-1, 3, -1);
  run_check(-2, 4, 16);
  // run_check(1.5, 2, 2.25);
  run_check(0, 0, 1);
  run_check(3, 0, 1);
  run_check(10000, 2, 100000000);
  exit(EXIT_SUCCESS);
}
