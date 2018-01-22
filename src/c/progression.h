#pragma once

#include "exercise.h"

typedef struct Progression Progression;
  
struct Progression {
  char* name;
  Exercise** exercises;
  int numOfExercises;
};

Progression* createProgression(char* name, int maxNumOfExercises);
void destroyProgression(Progression* progression);
void addExercise(Progression* progression, char* name, int goal, char* unit);