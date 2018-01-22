#include <pebble.h>
#include "workout.h"

// Create a workout from 6 exercises
// @param  A1 The first exercise in the first exercise pair
// @param  B1 The second exercise in the first exercise pair
// @param  A2 The first exercise in the second exercise pair
// @param  B2 The second exercise in the second exercise pair
// @param  A3 The first exercise in the third exercise pair
// @param  B3 The second exercise in the third exercise pair
// @return The newly created workout
Workout* createWorkout(Exercise* A1, Exercise* B1, Exercise* A2, Exercise* B2, Exercise* A3, Exercise* B3) {
  Workout* workout = malloc(sizeof(Workout));
  workout->exercises[0] = A1;
  workout->exercises[1] = B1;
  workout->exercises[2] = A2;
  workout->exercises[3] = B2;
  workout->exercises[4] = A3;
  workout->exercises[5] = B3;
  workout->currentPair = 0;
  
  return workout;
}

// Deallocates memory put aside for the workout
// @param workout The workout to destroy
void destroyWorkout(Workout* workout) {
  free(workout);
}