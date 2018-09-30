#include "election.h"

#include <stdio.h>
#include <string.h>
//include any other headers you need here...
void errorHappened(int place) {
  fprintf(stderr, "somethings is wrong I can feel it @%d", place);
  exit(EXIT_FAILURE);
}
state_t parseLine(const char * line) {
  state_t curState;
  curState.population = 0;
  curState.electoralVotes = 0;
  const char *markStart, *p;
  p = line;
  markStart = line;
  size_t length = 0;
  while (*p != ':') {
    if (*p == '\0')
      errorHappened(0);
    p++;
    length++;
  }
  if (length > MAX_STATE_NAME_LENGTH)
    errorHappened(1);
  memcpy(curState.name, markStart, length);
  curState.name[length] = '\0';

  //printf("%s\n", curState.name);
  //printf("%c\n", *p);
  p++;

  //population
  while (*p >= '0' && *p <= '9') {
    curState.population *= 10;
    curState.population += (uint64_t)(*p - '0');
    p++;
  }
  //printf("%d\n", population);
  if (*p != ':')
    errorHappened(2);
  p++;

  while (*p >= '0' && *p <= '9') {
    curState.electoralVotes *= 10;
    curState.electoralVotes += (uint64_t)(*p - '0');
    p++;
  }

  p++;
  if (*p != '\0')
    errorHappened(3);

  return curState;

  //STEP 1: write me
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int res = 0;
  if (stateData == NULL || voteCounts == NULL)
    errorHappened(5);
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > stateData[i].population / 2)
      res += stateData->electoralVotes;
  }
  return res;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  if (stateData == NULL || voteCounts == NULL)
    errorHappened(6);
  for (size_t i = 0; i < nStates; i++) {
    double percentage = (double)voteCounts[i] / stateData[i].population;
    // printf("%f  ", percentage);
    if (percentage >= 0.495 && percentage <= 0.505)
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percentage * 100.0);
  }

  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  if (stateData == NULL || voteCounts == NULL)
    errorHappened(7);
  double max = 0;
  size_t stateNo = 0;
  for (size_t i = 0; i < nStates; i++) {
    double temp = (double)voteCounts[i] / stateData[i].population;
    if (temp > max) {
      stateNo = i;
      max = temp;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[stateNo].name, max * 100.0);
}
