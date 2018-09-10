#include <stdio.h>
#include <stdlib.h>

typedef struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
} retire_info_t;

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  int totalMonth = startAge;
  int year = totalMonth / 12;
  int month = totalMonth % 12;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", year, month, initial);
    totalMonth++;
    year = totalMonth / 12;
    month = totalMonth % 12;

    initial += initial * working.rate_of_return;
    initial += working.contribution;
  }

  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", year, month, initial);
    totalMonth++;
    year = totalMonth / 12;
    month = totalMonth % 12;

    initial += initial * retired.rate_of_return;
    initial += retired.contribution;
  }
}

int main() {
  retire_info_t working;
  retire_info_t retirementing;
  int startMonth = 327;
  double startIni = 21345;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retirementing.months = 384;
  retirementing.contribution = -4000;
  retirementing.rate_of_return = 0.01 / 12;
  retirement(startMonth, startIni, working, retirementing);

  return EXIT_SUCCESS;
}
