#pragma once

#include "exercise.h"

#define MAX_NUM_OF_EXERCISES_IN_PROGRESSION 10

typedef struct Progression Progression;

struct Progression {
  char* name;
  Exercise** exercises;
  int numOfExercises;
};

Progression* parseProgression(char* progressionStr);
void destroyProgression(Progression* progression);