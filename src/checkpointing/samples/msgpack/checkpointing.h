#include <stdio.h>

enum player {BLACK, WHITE};

typedef struct game {
  int col; // size of col array
  int row; // size of row array
  int **arr; // pointer to 2D array
  char *desc; // description of what's going on;
  enum player curr; // Black or White Turn 
} game_t;



