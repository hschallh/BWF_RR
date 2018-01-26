#pragma once

#define TIME_UNITS "secs"
#define MAX_NUM_OF_WARMUPS 15

typedef struct Warmup Warmup;

struct Warmup {
  char* name;
  int goal;
  char* unit;
  char* warmups[MAX_NUM_OF_WARMUPS];
  int numOfWarmups;
};

Warmup* createWarmup(char* name, int goal, char* unit);
void parseExercisesForWarmup(Warmup* warmup, char* exercisesStr);
void destroyWarmup(Warmup* warmup);
int warmupNeedsTimer(Warmup* warmup);