#include <pebble.h>
#include <string.h>
#include <stdlib.h>
#include "progression.h"

// Allocates memory for a new progression. Exercises can be added later
// @param  name The name of the progression
// @param  maxNumOfExercises The amount of space to allocate for the exercise array
// @return The newly created progression
Progression* createProgression(char* name, int maxNumOfExercises) {
  Progression* progression = malloc(sizeof(Progression));
  progression->name = malloc(sizeof(char) * (strlen(name) + 1));
  progression->exercises = malloc(sizeof(Exercise) * maxNumOfExercises);
  strcpy(progression->name, name);
  progression->numOfExercises = 0;
  
  return progression;
}

// Deallocates all memory allocated to the progression
// @param  progression The progression to destroy
void destroyProgression(Progression* progression) {
  while (progression->numOfExercises > 0) {
    destroyExercise(progression->exercises[--progression->numOfExercises]);
  }
  free(progression->name);
  free(progression->exercises);
  free(progression);
}

// Creates and adds an exercise to a progression. Exercises will be stored in
// added order, with the first in position 0 and the last in position numOfExercises
// @param progression The progression to add the new exercise to
// @param  name The name of the exercise to create
// @param  goal The number of seconds or reps needed to progress in the exercise
// @param  unit The units the goal is in (reps or seconds)
void addExercise(Progression* progression, char* name, int goal, char* unit) {
  progression->exercises[progression->numOfExercises++] = createExercise(name, goal, unit);
}