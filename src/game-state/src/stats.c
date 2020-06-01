#include "game-state/stats.h"
#define MIN_STRING_LENGTH 2
#define MAX_NAME_LENGTH 50

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

    stat->val = init;
    stat->max = init;
    stat->modifier = 1;
    return SUCCESS;
}

/* See stats.h*/
stats_global_t* stats_global_new(stats_global_hash_t *gsh, char *name, double max)
{
    stats_global_t *global_stat;
    if(gsh != NULL)
    {
        HASH_FIND_STR(gsh, name, global_stat);
           if(global_stat != NULL)
            {
                return global_stat; //stat_id is already in use
            }
    }

    global_stat = malloc(sizeof(stats_global_t));
    int check = stats_global_init(global_stat, name, max);
    if(check != SUCCESS)
    {
        return NULL;
    }
    if(gsh != NULL)
    {
        HASH_ADD_KEYPTR(hh, gsh, name, strlen(name), global_stat);
    }
    return global_stat;
}

/* See stats.h */
stats_t *stats_new(stats_global_hash_t *gsh, char *name, double init)
{
    stats_global_t *global_stat;
    stats_t *new_stat;

    HASH_FIND_STR(gsh, name, global_stat);
    assert(global_stat != NULL);

    new_stat = malloc(sizeof(stats_t));

    int check = stats_init(new_stat, name, init);
    new_stat->global = global_stat;
    if(check != SUCCESS)
    {
        return NULL;
    }

    return new_stat;
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
int add_stat(stats_hash_t **sh, stats_t *s)
{
    stats_t *check;
    
    HASH_FIND(hh, *sh, s->key, strlen(s->key), check);

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
    stats_t *stat;
    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * HASH_COUNT(s));
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

int free_stats_global(stats_global_hash_t *gsh)
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
