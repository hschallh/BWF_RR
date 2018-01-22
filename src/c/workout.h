#pragma once

#include "progression.h"
#include <stdlib.h>

typedef struct Workout Workout;
  
struct Workout {
  Exercise* exercises[6];
  int currentPair;
};

Workout* buildWorkout();
Workout* createWorkout(Exercise* A1, Exercise* B1, Exercise* A2, Exercise* B2, Exercise* A3, Exercise* B3);
void destroyWorkout(Workout* workout);