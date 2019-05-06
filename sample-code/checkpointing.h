#include <stdio.h>

enum player {BLACK, WHITE};

typedef struct game {
  int size; // Size of 2D array
  int **arr; // pointer to 2D array
  char *desc; // description of what's going on;
  enum player curr; // Black or White Turn 
} game_t;



