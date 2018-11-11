#include "readFreq.h"

#include <stdio.h>

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
  uint64_t * res;
  res = (uint64_t *)malloc(257 * sizeof(*res));
  res[256] = 1;
  f = fopen(fname, "r");
  if (f == NULL)
    perror("cant open file");
  while ((c = getc(f)) != EOF) {
    res[c]++;
  }
  return res;
}
