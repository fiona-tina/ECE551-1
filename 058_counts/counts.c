#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void someErr(void) {
  fprintf(stderr, "someError");
  exit(EXIT_FAILURE);
}

counts_t * createCounts(void) {
  counts_t * res;
  res = malloc(sizeof(counts_t));
  if (res == 0) {
    someErr();
  }
  res->sz = 0;
  res->strInfos = NULL;
  res->unknowSize = 0;
  return res;
  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknowSize++;
    return;
  }
  one_count_t * oneCount;
  //already exist
  for (size_t i = 0; i < c->sz; i++) {
    oneCount = &c->strInfos[i];
    if (strcmp(name, oneCount->aStr) == 0) {
      oneCount->freq++;
      return;
    }
  }
  //new
  c->strInfos = realloc(c->strInfos, (c->sz + 1) * sizeof(*c->strInfos));
  if (c->strInfos == NULL) {
    someErr();
  }

  oneCount = &c->strInfos[c->sz];
  c->sz++;
  oneCount->aStr = malloc(strlen(name) + 1);
  strcpy(oneCount->aStr, name);
  if (oneCount->aStr == NULL) {
    someErr();
  }
  oneCount->freq = 1;

  //WRITE ME
}
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->sz; i++) {
    one_count_t * oneCount = &c->strInfos[i];
    fprintf(outFile, "%s: %d\n", oneCount->aStr, oneCount->freq);
  }
  if (c->unknowSize != 0) {
    fprintf(outFile, "<unknown>: %d\n", c->unknowSize);
  }
  return;
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->sz; i++) {
    free(c->strInfos[i].aStr);
  }
  free(c->strInfos);
  free(c);
}
