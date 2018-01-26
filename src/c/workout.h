#pragma once

#include <stdlib.h>
#include "progression.h"
#include "warmup.h"

#define NUM_OF_STRETCHES 9
#define NUM_OF_BODYLINE_DRILLS 6
#define NUM_OF_STRENGTH_EXERCISES 6
#define NUM_OF_SKILL_EXERCISES 3

typedef struct Workout Workout;

struct Workout {
  Warmup* stretches;
  Warmup* bodylineDrills;
  int exerciseInSkill[NUM_OF_SKILL_EXERCISES];
  Progression* skillProgressions[NUM_OF_SKILL_EXERCISES];
  int exerciseInStrength[NUM_OF_STRENGTH_EXERCISES];
  Progression* strengthProgressions[NUM_OF_STRENGTH_EXERCISES];
};

Workout* createWorkout(int skillNums[NUM_OF_SKILL_EXERCISES],
                       int strengthNums[NUM_OF_STRENGTH_EXERCISES]);
void parseWorkout(Workout* workout, char* filename);
void destroyWorkout(Workout* workout);
