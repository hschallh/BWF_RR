#include <pebble.h>
#include "warmup.h"
#include <stdlib.h>
#include <string.h>


// Create a new warmup routine. Warmups are a series of exercises with 
// the same goal and unit, all to be completed every workout
// @param name The name of the warmup
// @param goal The goal for all the warmup exercises
// @param unit The units for the goal
// @return
Warmup* createWarmup(char* name, int goal, char* unit) {
  Warmup* warmup = (Warmup*)malloc(sizeof(Warmup));
  warmup->name = (char*)malloc(sizeof(char*) * (strlen(name) + 1));
  warmup->unit = (char*)malloc(sizeof(char*) * (strlen(unit) + 1));
  strcpy(warmup->name, name);
  strcpy(warmup->unit, unit);
  warmup->goal = goal;
  warmup->numOfWarmups = 0;
  return warmup;
}

// Adds a warmup to the routine. 
// @param wu The Warmup to add a warmup to
// @param name The name of the warmup to add to the Warmup
void addExerciseToWarmup(Warmup* warmup, char* name) {
  warmup->warmups[warmup->numOfWarmups] = (char*)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(warmup->warmups[warmup->numOfWarmups++], name);
}

// Parses a new warmup from a string
// @param warmup The Warmup routine to add the exercises to
// @param exerciseStr The string to parse the exercises from
void parseExercisesForWarmup(Warmup* warmup, char* exercisesStr) {
  char* exercisesSignifier = strstr(exercisesStr, "|");

  for (int i = 0; i < MAX_NUM_OF_WARMUPS; i++) {
    // If the location of the next exercise is null, we have reached the last
    // exercise of the Warmup
    if (exercisesSignifier == NULL) {
      // Add the last exercise to the warmup
      addExerciseToWarmup(warmup, exercisesStr);
      break;
    } else {
      // Null terminate the current exercise and add it to the warmup
      exercisesSignifier[0] = '\0';
      addExerciseToWarmup(warmup, exercisesStr);

      // Move to the next exercise
      exercisesStr = exercisesSignifier + 1;
      exercisesSignifier = strstr(exercisesStr, "|");
    }
  }
}

// Frees all memory created by a warmup
// @param The warmup to destroy
void destroyWarmup(Warmup* warmup) {
  for (int i = 0; i < warmup->numOfWarmups; free(warmup->warmups[i++]))
    ;
  free(warmup->warmups);
  free(warmup->name);
  free(warmup->unit);
  free(warmup);
}

// Returns true if the warmup routine is time based and false if it
// is rep based
// @param  The warmup to check
// @return Whether or not the warmup is time based
int warmupNeedsTimer(Warmup* warmup) { 
  return strcmp(warmup->unit, TIME_UNITS) == 0; 
}