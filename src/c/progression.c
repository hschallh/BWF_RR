#include "progression.h"
#include <pebble.h>
#include <stdlib.h>
#include <string.h>

// Allocates memory for a new progression. Exercises can be added later
// @param  name The name of the progression
// @param  maxNumOfExercises The amount of space to allocate for the exercise
// array
// @return The newly created progression
Progression* createProgression(char* name, int maxNumOfExercises) {
  Progression* progression = (Progression*)malloc(sizeof(Progression));
  progression->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
  progression->exercises =
      (Exercise**)malloc(maxNumOfExercises * sizeof(Exercise));

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

// Parses all the exercises from a string and adds them to a progression
// @param prog The progression to add all of the exercises to
// @param exercisesString The string to parse all of the exercises from. Should
//                        be of the form:
//                        <exercise1>#<exercise2>#...#<exerciseN>
void parseExercisesForProgression(Progression* prog, char* exercisesStr) {
  char* nextExSigLocation = strstr(exercisesStr, "#");

  for (int i = 0; i < MAX_NUM_OF_EXERCISES_IN_PROGRESSION; i++) {
    // If the location of the next exercise is null, we have reached the last
    // exercise of the progression
    if (nextExSigLocation == NULL) {
      // Parse the last exercise for the progression
      prog->exercises[prog->numOfExercises++] = parseExercise(exercisesStr);
      break;
    } else {
      // Null terminate the current exercise
      nextExSigLocation[0] = '\0';

      // Parse the currect exercise and add it to the progression
      prog->exercises[prog->numOfExercises++] = parseExercise(exercisesStr);

      // Move to the next exercise
      exercisesStr = nextExSigLocation + 1;
      nextExSigLocation = strstr(exercisesStr, "#");
    }
  }
}

// Parse a progression from a string
// @param progressionStr The string to parse. Should be of the form
//                        <progression-name>#<exercise-list>
// @return The new progression
Progression* parseProgression(char* progressionStr) {
  // Get the singifier for the start of the exercise list and numm terminate the
  // progression name
  char* exerciseSignifier = strstr(progressionStr, "#");
  exerciseSignifier[0] = '\0';

  // Create a new progression and parse the rest of the string to add its
  // exercises
  Progression* progression =
      createProgression(progressionStr, MAX_NUM_OF_EXERCISES_IN_PROGRESSION);
  parseExercisesForProgression(progression, exerciseSignifier + 1);

  return progression;
}