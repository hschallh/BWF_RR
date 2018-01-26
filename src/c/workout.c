#include "workout.h"
#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create and build progressions and their exercises from a string
// @param progressions The array of progressions to build
// @param progArrayLen The length of the progressions array
// @param str Pointer to the progressions string. Should be of the
//            form <progression1>+<progression2>+...+<progression6>
void parseProgressionsForWorkout(Progression* progressions[],
                                 char* progressionsStr) {
  // Find the signifier for the next progression in the list
  char* progressionSignifier = strstr(progressionsStr, "+");
  int progressionNum = 0;

  while (progressionSignifier != NULL) {
    // Null terminate the progression string, parse and add to the
    // progression array
    progressionSignifier[0] = '\0';
    progressions[progressionNum++] = parseProgression(progressionsStr);

    // Move to the next progression
    progressionsStr = progressionSignifier + 1;
    progressionSignifier = strstr(progressionsStr, "+");
  }

  // Add the last progression to the array
  progressions[progressionNum] = parseProgression(progressionsStr);
}

// Parse and entire BWF RR from a file
void parseWorkout(Workout* workout, char* filename) {
  // Open the workout file
  FILE* workoutFile = fopen(filename, "r");
  char buf[999];

  // Read the first line and parse the Stretching Exercises
  fgets(buf, sizeof(buf), workoutFile);
  workout->stretches = createWarmup("Dynamic Stretches", 10, "reps");
  parseExercisesForWarmup(workout->stretches, buf);

  // Read the second line and parse the Bodyline Exercises
  fgets(buf, sizeof(buf), workoutFile);
  workout->bodylineDrills = createWarmup("Bodyline Drills", 60, "secs");
  parseExercisesForWarmup(workout->bodylineDrills, buf);

  // Read the third line and parse the Skill Exercises
  fgets(buf, sizeof(buf), workoutFile);
  parseProgressionsForWorkout(workout->skillProgressions, buf);

  // Read the fourth line and parse the Strength Exercises
  fgets(buf, sizeof(buf), workoutFile);
  parseProgressionsForWorkout(workout->strengthProgressions, buf);

  // Close the workout file
  fclose(workoutFile);
}

// Build a workout plan
// @param progNums An array of numbers representing where the user is in each
//                  progression
// @param filename A file containing 6 progressions and their respective
//                  exercises
// @return The newly created workout
Workout* createWorkout(int skillNums[NUM_OF_SKILL_EXERCISES],
                       int strengthNums[NUM_OF_STRENGTH_EXERCISES]) {
  // Create a Workout and parse the progressions form the workout file
  Workout* workout = (Workout*)malloc(sizeof(Workout));

  // Set the exercises the user is to do for their skill work
  for (int i = 0; i < NUM_OF_SKILL_EXERCISES; i++) {
    workout->exerciseInSkill[i] = skillNums[i];
  }

  // Set the exercises the user is to do for their strength work
  for (int i = 0; i < NUM_OF_STRENGTH_EXERCISES; i++) {
    workout->exerciseInStrength[i] = strengthNums[i];
  }

  return workout;
}

// Free all of the memory allocated to a workout
// @param wo The workout to destroy
void destroyWorkout(Workout* workout) {
  // Free all the strength progressions in this workout
  for (int i = 0; i < NUM_OF_SKILL_EXERCISES; i++) {
    destroyProgression(workout->skillProgressions[i]);
  }
  // Free all the strength progressions in this workout
  for (int i = 0; i < NUM_OF_STRENGTH_EXERCISES; i++) {
    destroyProgression(workout->strengthProgressions[i]);
  }

  destroyWarmup(workout->stretches);
  destroyWarmup(workout->bodylineDrills);

  // Free the workout
  free(workout);
}