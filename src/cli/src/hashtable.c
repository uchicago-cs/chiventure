#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

/* === hashtable helper constructors === */

void add_entry(char *command_name, operation *associated_operation, lookup_t **table)
{
    lookup_t *t = malloc(sizeof(lookup_t));
    t->name = command_name;
    t->operation_type = associated_operation;
    HASH_ADD_KEYPTR(hh, *table, t->name, strlen(t->name), t);
}

void add_action_entries(lookup_t **table)
{
    list_action_type_t *all_actions = get_supported_actions();

    while(all_actions != NULL)
    {
        action_type_t *curr_action = all_actions->act;

        if(curr_action->kind == 1)
        {
            add_entry(curr_action->c_name, type1_action_operation, table);
        }
        else if(curr_action->kind == 2)
        {
            add_entry(curr_action->c_name, type2_action_operation, table);
        }
        else if(curr_action->kind == 3)
        {
            add_entry(curr_action->c_name, type2_action_operation, table);
        }

        all_actions = all_actions->next;
    }
}

lookup_t *find_entry(char *command_name, lookup_t **table)
{
    lookup_t *t;
    HASH_FIND_STR(*table, command_name, t);
    return t;
}

operation *find_operation(char *command_name, lookup_t **table)
{
    lookup_t *t;
    if((t = find_entry(command_name, table))) 
    {
        return t->operation_type;
    }
    return NULL;
}

action_type_t *find_action(char *command_name, lookup_t **table)
{
    return find_entry(command_name, table)->action;
}

void delete_entry(char *command_name, lookup_t **table)
{
    lookup_t *t = find_entry(command_name, table);
    HASH_DEL(*table, t);
    free(t);
}

/* === hashtable constructors  === */

/* See cmd.h */
lookup_t **lookup_t_new()
{
    lookup_t **t;
    int rc;

    t = malloc(sizeof(*t));

    if(t == NULL)
    {
        return NULL;
    }

    rc = lookup_t_init(t);
    if(rc != SUCCESS)
    {
        return NULL;
    }

    return t;
}

/* See cmd.h */
int lookup_t_init(lookup_t **t)
{
    assert(t != NULL);

    add_entry("QUIT", quit_operation, t);
    add_entry("HELP", help_operation, t);
    add_entry("HIST", hist_operation, t);
    add_entry("LOOK",look_operation, t);
    add_entry("INV", inventory_operation, t);
    add_entry("SAVE", save_operation, t);
    add_action_entries(t);

    return SUCCESS;
}

/* See cmd.h */
void lookup_t_free(lookup_t **t) 
{
    lookup_t *tmp;
    lookup_t *current_user;
    HASH_ITER(hh, *t, current_user, tmp)
    {
        HASH_DEL(*t, current_user);
        free(current_user);
    }
}
