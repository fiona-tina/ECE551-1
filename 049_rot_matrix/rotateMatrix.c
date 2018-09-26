#include <stdio.h>
#include <stdlib.h>

void read_line(char line[], FILE * f) {
  int i;
  int ch;

  i = 0;
  while (1) {
    ch = fgetc(f);
    if (ch == '\n') {
      if (i == 10) {
        line[10] = '\0';
        return;
        //finished a line
      }
      else {
        fprintf(stderr, "%s\n", "line too short");
        exit(EXIT_FAILURE);
      }
      break;
    }
    else if (ch == EOF) {
      if (i == 10) {
        fprintf(stderr, "%s\n", "unexpected EOF");
        exit(EXIT_FAILURE);
      }
      else {
        fprintf(stderr, "%s\n", "line too short");
        exit(EXIT_FAILURE);
      }
      break;
    }
    else {
      if (i < 10) {
        line[i] = (char)ch;
        i++;
      }
      else {
        fprintf(stderr, "%s\n", "line too long");
        exit(EXIT_FAILURE);
      }
      //break;
    }
  }
}

void rot_matrix(char m[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", m[9 - j][i]);
    }
    printf("\n");
  }
}

int main(int argc, char * argv[]) {
  char m[10][10];
  FILE * f;
  int ch, i;

  if (argc != 2) {  //too many arg
    fprintf(stderr, "Usage: rotateMatrix input\n");
    exit(EXIT_FAILURE);
  }
  if ((f = fopen(argv[1], "r")) == 0) {  //c
    fprintf(stderr, "Cannot open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < 10; i++) {
    read_line(m[i], f);
  }
  ch = fgetc(f);
  ch = fgetc(f);

  if (ch != EOF) {
    fprintf(stderr, "Too long\n");
    exit(EXIT_FAILURE);
  }

  fclose(f);

  rot_matrix(m);

  return 0;
}
