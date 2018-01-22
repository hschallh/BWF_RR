#pragma once

#define TIME_UNITS "s"

typedef struct Exercise Exercise;
  
struct Exercise {
  char* name;
  int goal;
  char* unit;
};

Exercise* createExercise(char* name, int goal, char* unit);
void destroyExercise(Exercise* exercise);
int exerciseNeedsTimer(Exercise* exercise);
