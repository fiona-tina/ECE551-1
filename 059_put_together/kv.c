#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open %s\n", fname);
    exit(EXIT_FAILURE);
  }
  kvpair_t * pairs = NULL;
  kvarray_t * res;  // = malloc(sizeof(res));
  size_t size_pairs = 0;
  size_t line_size = 0;

  char * line = NULL;

  while (getline(&line, &line_size, f) != -1) {
    //keyPart = strtok(line, "=");
    //valPart = strtok(NULL, "\n");
    char * p = line;
    int len = 0;
    while (*p != '=') {
      p++;
      len++;
    }
    char * keyPart = malloc((len + 1) * sizeof(*keyPart));
    memcpy(keyPart, line, len + 1);
    keyPart[len] = '\0';

    p++;
    char * q = p;
    int len1 = 0;
    while (*q != '\n') {
      q++;
      len1++;
    }
    char * valPart = malloc((len1 + 1) * sizeof(*valPart));
    memcpy(valPart, p, len1 + 1);
    valPart[len1] = '\0';

    //printf("key: %s, val: %s\n", keyPart, valPart);
    //free(line);
    pairs = realloc(pairs, (size_pairs + 1) * sizeof(*pairs));
    //size_pairs++;
    if (pairs == NULL) {
      fprintf(stderr, "cannot realloc");
      exit(EXIT_FAILURE);
    }
    pairs[size_pairs].key = malloc(len + 1);
    pairs[size_pairs].value = malloc(len1 + 1);

    strcpy(pairs[size_pairs].key, keyPart);
    strcpy(pairs[size_pairs].value, valPart);
    size_pairs++;
    free(valPart);
    free(keyPart);
  }
  free(line);
  fclose(f);
  res = malloc(sizeof(*res));
  if (res == NULL) {
    exit(EXIT_FAILURE);
  }
  res->length = size_pairs;
  res->pairs = pairs;
  return res;
}

void freeKVs(kvarray_t * pairs) {
  size_t size = pairs->length;
  for (size_t i = 0; i < size; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t size = pairs->length;
  for (size_t i = 0; i < size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t size = pairs->length;
  for (size_t i = 0; i < size; i++) {
    if (!strcmp(key, pairs->pairs[i].key)) {
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
