#include <pebble.h>
#include <string.h>
#include <stdlib.h>
#include "exercise.h"


// Allocates memory for a new exercise and builds it
// @param  name The name of the exercise
// @param  goal The number of seconds or reps needed to progress 
// @param  unit The units the goal is in (reps or seconds)
// @return The newly created exercise
Exercise* createExercise(char* name, int goal, char* unit) {
  Exercise* exercise = malloc(sizeof(Exercise));
  exercise->name = malloc(sizeof(char) * (strlen(name) + 1));
  exercise->unit = malloc(sizeof(char) * (strlen(unit) + 1));
  strcpy(exercise->name, name);  
  strcpy(exercise->unit, unit);
  exercise->goal = goal;
  
  return exercise;
};

// Frees all memory from exercise creation
// @param exercise The exercise to delete
void destroyExercise(Exercise* exercise) {
  free(exercise->name);
  free(exercise->unit);
  free(exercise);
}

// Returns true if the exercise is a time based exercise and false if it
// is rep based
// @param  The exercise to check
// @return Whether or not the exercise is time based
int exerciseNeedsTimer(Exercise* exercise) {
  return strcmp(exercise->unit, TIME_UNITS) == 0;
}

// Parses an exercise from a string and adds it to a progression
// @param exerciseString The string to parse should be of the form:
//                        <name>|<goal>|<unit>
Exercise* parseExercise(char* exerciseStr) {
  // Find the locations of the separaters and null terminate them
  char *goalSigLocation = strstr(exerciseStr, "|"),
       *unitSigLocation = strstr(goalSigLocation + 1, "|");
  goalSigLocation[0] = '\0';
  unitSigLocation[0] = '\0';

  // Set the name, unit, and convert the goal
  char *name = exerciseStr, *unit = unitSigLocation + 1;
  int goal;
  sscanf(goalSigLocation + 1, "%i", &goal);

  // Return a new Exercise
  return createExercise(name, goal, unit);
}