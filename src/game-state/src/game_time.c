#include "include/game-state/game_time.h"

int time_init(time_t *t)
{
    time(t);
    return SUCCESS;
}

time_t *time_new()
{
    time_t *time = malloc(sizeof(time_t));
    memset(time, 0, sizeof(time_t));
    int check = time_init(time);
    if (check != SUCCESS)
        return NULL;
    return time;
}

void time_dll_update(time_dll_t *time_dll)
{
    time_t curr;
    time_dll->curr = difftime(time(&curr), *(time_dll->start));
}

int time_dll_init(time_dll_t *prev, time_dll_t *time_dll, time_dll_t *next)
{
    time_dll->prev = prev;
    time_t *start = time_new();
    time_dll->start = start;
    time_dll_update(time_dll);
    time_dll->next = next;
    return SUCCESS;
}

time_dll_t *time_dll_new(time_dll_t *prev, time_dll_t *next)
{
    time_dll_t *time = malloc(sizeof(time_dll_t));
    memset(time, 0, sizeof(time_dll_t));
    int check = time_dll_init(prev, time, next);
    assert(check == SUCCESS);
    return time;
}

int time_dll_free(time_dll_t *time_dll);