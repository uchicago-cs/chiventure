#include "game-state/stats.h"

/* See stats.h*/
int stats_global_init(stats_global_t *s, char *name, double max)
{
    assert(s != NULL);
    strncpy(s->name, name, strlen(name));
    s->max = max;
    return SUCCESS;
}

/* See stats.h */
int stats_init(stats_t *stat, char *name, double init)
{
    assert(stat != NULL);
    
    stats_global_t *global_stat;
    HASH_FIND(ctx->game->curr_stats, &name, global_stat);
    assert(global_stat != NULL)
    stat->global = global_stat

    stat->val = init
    stat->max = init;
    stat->modifier = 1;
    return SUCCESS;
}

/* See stats.h*/
stats_global_t* stats_global_new(char *nm, double max)
{
    stats_global_t *global_stat;
    global_stat = HASH_FIND(ctx->game->curr_stats, &nm, global_stat);

    if(global_stat != NULL)
    {
        return global_stat; //stat_id is already in use
    }

    global_stat = malloc(sizeof(global_stat));
    int check = stats_global_init(global_stat, name, max);
    if(check != SUCCESS)
    {
        return NULL;
    }

    HASH_ADD(ctx->game->curr_stats, name, global_stat);
    return global_stat;
}

/* See stats.h */
stats_t *stats_new(char *name, double init)
{
    stats_global_t *global_stat;
    global_stat = HASH_FIND(ctx->game->curr_stats, &nm, global_stat);

    if(global_stat != NULL)
    {
        return global_stat; //stat_id is already in use
    }

    global_stat = malloc(sizeof(global_stat));
    int check = stats_global_init(global_stat, name, max);
    if(check != SUCCESS)
    {
        return NULL;
    }

    HASH_ADD(ctx->game->curr_stats, name, global_stat);
    return global_stat;
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
