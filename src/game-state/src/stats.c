#include "game-state/stats.h"

/* See stats.h*/
int stats_global_init(stats_global_t *s, char *name, double max)
{
    printf("stats_global_init: function net yet implemented\n");
    return 0;// still needs to be implemented
}



/* See stats.h */
int stats_init(stats_t *s, stats_global_t *stat, double init)
{
    printf("stats_init: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h*/
stats_global_t* stats_global_new(char *name, double max)
{
    printf("stats_global_new: function net yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
stats_t *stats_new(stats_global_t *stat, double init)
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
int add_stat_player(stats_hash_t *sh, stats_t *s)
{
    printf("add_stat: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
char* display_stats(stats_hash_t *s)
{
    printf("display_stats: function not yet implemented\n");
    return "0"; // still needs to be implemented
}

/* See stats.h */
int free_stats(stats_hash_t *s)
{
    printf("free_stats: function not yet implemented\n");
    return 0; // still needs to be implemented
}

int free_stats_global(stats_global_hash_t* gsh)
{
    printf("free_stats_global: function not yet implemented\n");
    return 0; // still needs to be implemented
}
