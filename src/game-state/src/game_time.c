#include "include/game-state/game_time.h"

int time_init(time_t *time)
{
    time = time(NULL);
    return SUCCESS;
}

time_t time_new()
{
    time_t *time = malloc(sizeof(time_t));
    memset(time, 0, sizeof(time_t));
    int check = time_init(time);
    if (check != SUCCESS)
        return NULL;
    return time;
}

int time_dll_init(time_dll_t *prev, time_dll_t *time_dll, time_dll_t *next)
{
    time_dll->prev = prev;
    time_t currtime = time_new();
    time_dll->curr = currtime;
    time_dll->start = currtime;
    time_dll->next = next;
    return time;
}

time_dll_t *time_dll_new(time_dll_t *prev, time_dll_t *next)
{
    time_dll_t time = malloc(sizeof(time_dll_t));
    memset(time, 0, sizeof(time_dll_t));
    /* TODO */
    return NULL;
}

int time_dll_free(time_dll_t *game_time);

double time_dll_diff(time_dll_t *game_time);

