#ifndef _GAME_TIME_H
#define _GAME_TIME_H

#include "game_state_common.h"
#include "common/common.h"

typedef struct time_dll
{
    time_t *start; // will serve as the key for searching
    double since;
    struct time_dll *prev;
    struct time_dll *next;
} time_dll_t;

int time_init(time_t *time);

time_t *time_new();

void time_dll_update(time_dll_t *time_dll);

int time_dll_init(time_dll_t *prev, time_dll_t *time_dll, time_dll_t *next);

time_dll_t *time_dll_new(time_dll_t *prev, time_dll_t *next);

int single_time_dll_free(time_dll_t *time_dll);

double time_since_first_start(time_dll_t *time_dll);

#endif