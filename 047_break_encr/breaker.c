#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int findMaxIdx(int array[], int n) {
  int mIdx = 0;

  for (int i = 0; i < n; i++) {
    if (array[i] > array[mIdx]) {
      mIdx = i;
    }
  }
  return mIdx;
}

int getkey(FILE * f) {
  int freq[26] = {0};
  int c;
  int maxIdx;

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      freq[tolower(c) - 'a']++;
    }
  }
  maxIdx = findMaxIdx(freq, 26);
  return (maxIdx + 22) % 26;
}

int main(int argc, char * argv[]) {
  FILE * f;
  int key;

  if (argc != 2) {
    fprintf(stderr, "usage %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "failed to open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  key = getkey(f);
  printf("%d\n", key);

  fclose(f);
  return 0;
}
