#pragma once

#define TIME_UNITS "secs"

typedef struct Exercise Exercise;
  
struct Exercise {
  char* name;
  int goal;
  char* unit;
};

Exercise* createExercise(char* name, int goal, char* unit);
Exercise* parseExercise(char* exerciseString);
void destroyExercise(Exercise* exercise);
int exerciseNeedsTimer(Exercise* exercise);
