#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  char * res;
  size_t sz = 0;
  sz = strlen(inputName);

  res = malloc((sz + 8) * sizeof(res));

  memcpy(res, inputName, sz);
  memcpy(res + sz, ".counts", 8);
  return res;

  //WRITE ME
}
