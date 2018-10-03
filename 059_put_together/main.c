#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * res = createCounts();
  // getline filename. value= lookupValue (kvPairs, key(from get line)),
  //value ==NULL c->unknown ++
  //else addCount(c, value)

  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "cant open %s", filename);
    exit(EXIT_FAILURE);
  }
  char * keyFromFile = NULL;
  size_t keySize = 0;
  int charNum;
  while ((charNum = getline(&keyFromFile, &keySize, f)) != -1) {
    //valuefromfile is NULL....
    if (charNum > 0 && keyFromFile[charNum - 1] == '\n')
      keyFromFile[charNum - 1] = '\0';
    char * valueFromFile = lookupValue(kvPairs, keyFromFile);
    addCount(res, valueFromFile);
  }
  free(keyFromFile);
  fclose(f);
  return res;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 2) {
    fprintf(stderr, "arguments are not enough");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kvPairs = readKVs(argv[1]);
  for (int i = 2; i < argc; i++) {
    counts_t * inputCount = countFile(argv[i], kvPairs);
    char * outputFileName = computeOutputFileName(argv[i]);
    FILE * f = fopen(outputFileName, "w");
    printCounts(inputCount, f);
    fclose(f);
    free(outputFileName);
    freeCounts(inputCount);
  }

  freeKVs(kvPairs);
  //count from 2 to argc (call the number you count i)

  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv

  return EXIT_SUCCESS;
}
