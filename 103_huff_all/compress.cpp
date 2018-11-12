#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

using namespace std;

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  FILE * ifile;
  ifile = fopen(inFile, "r");
  if (ifile == NULL) {
    cout << "cant open";
    exit(1);
  }

  int c;
  while ((c = fgetc(ifile)) != EOF) {
    unsigned ch = (unsigned)c;
    if (theMap.find(ch) != theMap.end())
      bfw.writeBitString(theMap.find(ch)->second);
    else {
      cout << "char not found!";
      exit(1);
    }
  }
  bfw.writeBitString(theMap.find(256)->second);
  fclose(ifile);
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter

  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  uint64_t * freq = readFrequencies(argv[1]);
  Node * root = buildTree(freq);
  map<unsigned, BitString> mp;
  BitString b;
  root->buildMap(b, mp);
  writeCompressedOutput(argv[1], argv[2], mp);
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  delete[] freq;
  delete root;
  return EXIT_SUCCESS;
}
