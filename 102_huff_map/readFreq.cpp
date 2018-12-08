#include "readFreq.h"

#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <fstream>

using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  FILE * f;
  int c;
  uint64_t * res = new uint64_t[257];
  //memset(res, 0, 257);
  for (int i = 0; i < 257; ++i) {
    res[i] = 0;
  }
  res[256] = 1;
  f = fopen(fname, "r");
  if (f == NULL)
    perror("cant open file");
  while ((c = fgetc(f)) != EOF) {
    res[c]++;
  }
  fclose(f);
  return res;
}
