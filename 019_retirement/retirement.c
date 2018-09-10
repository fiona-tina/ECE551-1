#include <stdio.h>
#include <stdlib.h>

typedef struct retire_info_tag {
  int month;
  double contribution;
  double rate_of_return;
} retire_info_t;

void retirement(int startAge, double * initial, retire_info_t info_t) {
  int totalMonth = info_t.month;
  int year = totalMonth / 12;
  int month = totalMonth % 12;

  printf("Age %3d month %2d you have $%.2lf\n", year, month, *initial);
  *initial += *initial * info_t.rate_of_return;
  *initial += info_t.contribution;
}

int main() {
  retire_info_t working;
  retire_info_t retirementing;
  int startMonth = 327;
  double startIni = 21345;
  ;
  working.month = startMonth;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  for (int i = 0; i < 489; i++) {
    retirement(startMonth, &startIni, working);
    working.month++;
  }

  retirementing.month = working.month;
  retirementing.contribution = -4000;
  retirementing.rate_of_return = 0.01 / 12;

  for (int i = 0; i < 384; i++) {
    retirement(startMonth, &startIni, retirementing);
    retirementing.month++;
  }
  return EXIT_SUCCESS;
}
