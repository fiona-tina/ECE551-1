#include <stdio.h>
#include <stdlib.h>

typedef struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
} retire_info_t;

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  int totalMonth = working.months;
  int year = totalMonth / 12;
  int month = totalMonth % 12;

  printf("Age %3d month %2d you have $%.2lf\n", year, month, initial);
  initial += initial * working.rate_of_return;
  initial += working.contribution;
}

int main() {
  retire_info_t working;
  retire_info_t retirementing;
  int startMonth = 327;
  double startIni = 21345;
  ;
  working.months = startMonth;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  for (int i = 0; i < 489; i++) {
    retirement(startMonth, startIni, working, working);
    working.months++;
    startIni += startIni * working.rate_of_return;
    startIni += working.contribution;
  }

  retirementing.months = working.months;
  retirementing.contribution = -4000;
  retirementing.rate_of_return = 0.01 / 12;

  for (int i = 0; i < 384; i++) {
    retirement(startMonth, startIni, retirementing, working);
    retirementing.months++;
    startIni += startIni * retirementing.rate_of_return;
    startIni += retirementing.contribution;
  }
  return EXIT_SUCCESS;
}
