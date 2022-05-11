#ifndef _GAME_TIME_H
#define _GAME_TIME_H

#include "game_state_common.h"
#include "common/common.h"

typedef struct game_time
{
    time_t *start;
    time_t *current;
} game_time_t;

int game_time_init();

game_time_t *game_time_new();

int game_time_free(game_time_t *game_time);

double game_time_diff(game_time_t *game_time);

#endif