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
    HASH_FIND_STR(ctx->game->curr_stats, name, global_stat);
    assert(global_stat != NULL);
    stat->global = global_stat;

    stat->val = init;
    stat->max = init;
    stat->modifier = 1;
    return SUCCESS;
}

/* See stats.h*/
stats_global_t* stats_global_new(char *name, double max)
{
    stats_global_t *global_stat;
    global_stat = HASH_FIND_STR(ctx->game->curr_stats, name, global_stat);

    if(global_stat != NULL)
    {
        return global_stat; //stat_id is already in use
    }

    global_stat = malloc(sizeof(stats_global_t));
    int check = stats_global_init(global_stat, name, max);
    if(check != SUCCESS)
    {
        return NULL;
    }
    HASH_ADD_KEYPTR(hh, ctx->game->curr_stats, name, strlen(name), global_stat);
    return global_stat;
}

/* See stats.h */
stats_t *stats_new(char *name, double init)
{
    stats_t *new_stat;
    new_stat = malloc(sizeof(stats_t));

    int check = stats_init(new_stat, name, init);
    if(check != SUCCESS)
    {
        return NULL;
    }
    return new_stat;
}

/* See stats.h */
int change_stat(stats_hash_t *sh, char *stat, double change)
{
    if (sh == NULL) {
        printf("Error: insert valid hash table");
        exit(1);
    }

    int i = 0;
    int tsize = sizeof(sh);
    stats_hash_t *curr;

    for (i = 0; i < tsize; i++) {
        if (!strcmp(sh[i].global->name, stat)) {
            curr = &sh[i];
        } 
    }

    if (curr == NULL) {
        printf("Error: no matching stat")
    }

    changed_stat = curr->stat.val + change;

    if (changed_stat > (curr->global)) {
        printf("Error: changed value exceeds global maximum");
        exit(1);
    } else {
        curr -> stat.val = changed_stat;
    }

    return 0;
}

/* See stats.h */
double get_stat_current(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        printf("Insert valid hash table");
        exit(1);
    }

    /*HASH_FIND_STR(sh, stat, curr);
    if (curr == NULL) {
        printf("Cannot find stat.");
        exit(1);
    }

    return curr.val;*/
    return 0;
}

/* See stats.h */
double get_stat_max(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        printf("Insert valid hash table");
    }

    /*return sh -> stat.max;*/
    return 0;
}



/* See stats.h */
double get_stat_mod(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        printf("Insert valid hash table");
    }

    return sh -> stat.modifier;
}

/* See stats.h */
int add_stat_player(stats_hash_t *sh, stats_t *s)
{
    
    HASH_FIND_STR(*sh, s->key, strlen(s->key));

    if (check != NULL)
    {
        return FAILURE;
    }

    HASH_ADD_KEYPTR(hh, *sh, s->key, strlen(s->key), s);
    return SUCCESS;
}

/* See stats.h */
char* display_stats(stats_hash_t *s)
{
    printf("display_stats: function not yet implemented\n");
    return "0"; // still needs to be implemented
}

/* See stats.h */
int free_stats(stats_hash_t *sh)
{
    stats_t *current, *next;
    for(current = sh->hh.next; current != NULL; current = next) 
    {
        next = current->hh.next;
        HASH_DEL(sh, current);
        free(current);
    }
    HASH_DEL(sh, sh);
    free(sh);
    return SUCCESS;
}

int free_stats_global(stats_global_hash_t* gsh)
{
    stats_global_t *current, *next;
    for(current = gsh->hh.next; current != NULL; next = current->hh.next) 
    {
        HASH_DEL(gsh, current);
        free(current);
        current = next;
    }
    HASH_DEL(gsh, gsh);
    free(gsh);
    return SUCCESS;
}
