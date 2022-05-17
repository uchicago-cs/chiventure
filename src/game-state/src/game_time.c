#include "game-state/game_time.h"

/* See game_time.h */
int time_init(time_t *t)
{
    time(t);
    return SUCCESS;
}

/* See game_time.h */
time_t *time_new()
{
    time_t *time = malloc(sizeof(time_t));
    memset(time, 0, sizeof(time_t));
    int check = time_init(time);
    if (check != SUCCESS)
        return NULL;
    return time;
}

/* See game_time.h */
void time_dll_update(time_dll_t *time_dll)
{
    time_t curr;
    time_dll->since = difftime(time(&curr), *(time_dll->start));
}

/* See game_time.h */
int time_dll_init(time_dll_t *prev, time_dll_t *time_dll, time_dll_t *next)
{
    time_dll->prev = prev;
    time_t *start = time_new();
    time_dll->start = start;
    time_dll_update(time_dll);
    time_dll->next = next;
    return SUCCESS;
}

/* See game_time.h */
time_dll_t *time_dll_new(time_dll_t *prev, time_dll_t *next)
{
    time_dll_t *time = malloc(sizeof(time_dll_t));
    memset(time, 0, sizeof(time_dll_t));
    int check = time_dll_init(prev, time, next);
    assert(check == SUCCESS);
    return time;
}

/* See game_time.h */
int single_time_dll_free(time_dll_t *time_dll)
{
    free(time_dll->start);
    free(time_dll);
    if (time_dll == NULL)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

/* See game_time.h for an overview.
 * Just wanted to say real quickly that although it looks awkward, using two
 * separate while loops here was intentional, so that the `tmp->since` that's
 * constantly being updated by the current game is the one added to `rc` last,
 * so the returned value has the highest probability of including the most
 * recent time update (since running from different processes)
 */
double time_since_first_start(time_dll_t *time_dll)
{
    time_dll_t *tmp = time_dll;
    int counter = 0;
    while (tmp->prev != NULL)
    {
        tmp = tmp->prev;
        counter++;
    }
    double rc = tmp->since;
    while(counter != 0)
    {
        tmp = tmp->next;
        rc += tmp->since;
        counter--;
    }
    return rc;
}