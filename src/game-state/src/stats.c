#include "game-state/stats.h"

/* See stats.h */
int stats_init(stats_t *s, stats_global_t *stats_name, double init)
{
    printf("stats_init: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
stats_t *stats_new(stats_global_t *stats_name, double init)
{
    printf("stats_new: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
int change_stat(stats_hash_t *sh, char *stat, double change)
{
    printf("change_stat: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
double get_stat_current(stats_hash_t *sh, char *stat)
{
    printf("get_stat_current: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
double get_stat_max(stats_hash_t *sh, char *stat)
{
    printf("get_stat_max: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
double get_stat_mod(stats_hash_t *sh, char *stat)
{
    printf("get_stat_mod: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
int add_stat_player(stats_hash_t **sh, stats_t *s)
{
    stats_t *check;
    
    HASH_FIND(hh, *sh, s->global, sizeof(stats_global_t), check);

    if (check != NULL)
    {
        return FAILURE;
    }

    HASH_ADD_PTR(*sh, global, s);
    return SUCCESS;
}

/* See stats.h */
char* display_stats(stats_hash_t *s)
{
    stats_t *stat;
    int size = 2 + (20 * HASH_COUNT(s));
    char list[size];
    
    stat = s;
    if (stat != NULL) 
    {
        strcpy(list, stat->global->name);
    }

    for (stat = stat->hh.next; stat != NULL; stat = stat->hh.next)
    {
        strcat(list, ", ");
        strcat(list, stat->global->name);
    }

    char *display = strdup(list);
    return display;
}

/* See stats.h */
int free_stats(stats_hash_t *s)
{
    printf("free_stats: function not yet implemented\n");
    return 0; // still needs to be implemented
}