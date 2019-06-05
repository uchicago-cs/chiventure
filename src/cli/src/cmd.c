#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"
#include "validate.h"
/* === hashtable constructors === */

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
            add_entry(curr_action->c_name, kind1_action_operation, table);
        }
        else if(curr_action->kind == 2)
        {
            add_entry(curr_action->c_name, kind2_action_operation, table);
        }
        else if(curr_action->kind == 3)
        {
            add_entry(curr_action->c_name, kind3_action_operation, table);
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

void delete_entries(lookup_t **table)
{
    lookup_t *tmp;
    lookup_t *current_user;
    HASH_ITER(hh, *table, current_user, tmp)
    {
        HASH_DEL(*table, current_user);
        free(current_user);
    }
}

lookup_t **initialize_lookup()
{
    lookup_t **table = malloc(sizeof(*table));
    add_entry("QUIT", quit_operation, table);
    add_entry("HELP", help_operation, table);
    //add_entry("HIST", hist_operation, table);
    add_entry("LOOK",look_operation, table);
    add_entry("INV", inventory_operation, table);
    add_entry("SAVE", save_operation, table);
    add_entry("LOAD", load_operation, table);
    add_action_entries(table);
    return table;
}

/* === command constructors  === */

/* See cmd.h */
cmd *cmd_new(char *tokens[TOKEN_LIST_SIZE])
{
    cmd *c = (cmd*)malloc(sizeof(cmd));
    if(c == NULL)
    {
        fprintf(stderr,"error: malloc failed\n");
        return NULL;
    }
    c->tokens=tokens;
    return c;
}

/* See cmd.h */
void cmd_free(cmd *c)
{
    if(c == NULL || c->tokens == NULL)
    {
        return;
    }

    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        if(c->tokens[i] != NULL)
        {
            free(c->tokens[i]);
        }
    }
    free(c);
}

/* === command debugging === */


/* See cmd.h */
char *cmd_name_tos(cmd *c)
{
    if(c == NULL || c->tokens == NULL || c->tokens[0] == NULL) 
    {
        return "ERROR";
    }
    return c->tokens[0];
}

/* See cmd.h */
void cmd_show(cmd *c)
{
    /* note: cmd_name_tos result does not need to be freed
     * since that function returns pointers to string constants
     */
    if (c == NULL || c->tokens == NULL)
    {
        return;
    }

    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        if(c->tokens[i] != NULL)
        {
            printf("%s\n",(c->tokens[i]));
        }
    }
    return;
}

/* === command parsing === */

/* See cmd.h */
cmd *cmd_from_tokens(char **ts, lookup_t **table)
{
    cmd *output = assign_action(ts, table);
    return output;
}

/* See cmd.h */
cmd *cmd_from_string(char *s, lookup_t **table)
{
    char **parsed_input = parse(s);
    if(parsed_input == NULL)
    {
        return NULL;
    }
    return cmd_from_tokens(parsed_input, table);
}

/* =================================== */
/* === execution of shell commands === */
/* =================================== */

/* See cmd.h */
void do_cmd(cmd *c,int *quit, game_t *game, lookup_t **table)
{
    char *outstring;
    /* 
     * available commands are QUIT, STATS, CHAR, LOOKUP, HELP, READ
     * all other commands will segfault in the testshell, because there is no game file
     */ 
    if (strcmp(cmd_name_tos(c),"QUIT")==0)
    {
        *quit=0;
        (*(c->func_of_cmd))(c->tokens, game, table);
    }
    else
    {
        outstring = (*(c->func_of_cmd))(c->tokens, game, table);
        if(outstring!=NULL)
        {
            printf("%s\n",outstring );
        }
    }
    return;
}
