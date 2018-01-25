#pragma once

#include "exercise.h"

#define MAX_NUM_OF_EXERCISES_IN_PROGRESSION 10

typedef struct Progression Progression;
  
struct Progression {
  char* name;
  Exercise** exercises;
  int numOfExercises;
};

Progression* createProgression(char* name, int maxNumOfExercises);
Progression* parseProgression(char* progressionStr);
void destroyProgression(Progression* progression);
void addExerciseToProgression(Progression* progression, char* name, int goal, char* unit);