#ifndef _GAME_TIME_H
#define _GAME_TIME_H

#include "game_state_common.h"
#include "common/common.h"

typedef struct time_dll
{
    time_t *start; // will serve as the key for searching
    double curr;
    struct time_dll *prev;
    struct time_dll *next;
} time_dll_t;

int time_init(time_t *time);

time_t *time_new();

int time_dll_init(time_dll_t *prev, time_dll_t *time_dll, time_dll_t *next);

time_dll_t *time_dll_new(time_dll_t *prev, time_dll_t *next);

int time_dll_free(time_dll_t *time_dll);

double time_dll_diff(time_dll_t *time_dll);

#endif