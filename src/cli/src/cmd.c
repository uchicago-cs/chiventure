#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"
#include "validate.h"

/* === command constructors  === */

/* See cmd.h */
cmd *cmd_new(char *tokens[TOKEN_LIST_SIZE])
{
    cmd *c = (cmd*)malloc(sizeof(cmd));
    if (c==NULL)
    {
        fprintf(stderr,"error (cmd_tag): malloc failed\n");
        exit(1);
    }
    c->tokens=tokens;
    return c;
}

/* See cmd.h */
void cmd_free(cmd *c)
{
    if (c == NULL || c->tokens == NULL) return;
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        if (c->tokens[i] != NULL) free(c->tokens[i]);
    }
    free(c);
}

/* === command debugging === */


/* See cmd.h */
char *cmd_name_tos(cmd *c)
{
    if(c == NULL || c->tokens == NULL || c->tokens[0] == NULL) return "ERROR";
    return c->tokens[0];
}

/* See cmd.h */
void cmd_show(cmd *c)
{
    /* note: cmd_name_tos result does not need to be freed
     * since that function returns pointers to string constants
     */
    if (c == NULL || c->tokens == NULL) return;
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        if (c->tokens[i] != NULL) printf("%s\n",(c->tokens[i]));
    }
    return;
}

/* === command parsing === */

/* See cmd.h */
cmd *cmd_from_tokens(char **ts)
{
    cmd *output = assign_action(ts);

    if(output->func_of_cmd == action_error_operation)
    {
        return output;
    }
    else if(!validate_object(output))
    {
        output->func_of_cmd = object_error_operation;
        return output;
    }
    else if(!validate_prep(output))
    {
        output->func_of_cmd = prep_error_operation;
        return output;
    }
    else if(!validate_ind_objects(output))
    {
        output->func_of_cmd = ind_object_error_operation;
        return output;
    }
    return output;
}

/* See cmd.h */
cmd *cmd_from_string(char *s)
{
    char **parsed_input = parse(s);
    return cmd_from_tokens(parsed_input);
}

/* =================================== */
/* === execution of shell commands === */
/* =================================== */

/* See cmd.h */
void do_cmd(cmd *c,int *quit)
{
    char *outstring;
    /* available commands are QUIT, STATS, CHAR, LOOKUP, HELP, READ */
    if (strcmp(cmd_name_tos(c),"QUIT")==0)
    {
        *quit=0;
        (*(c->func_of_cmd))(c->tokens);
    }
    else
    {
        outstring = (*(c->func_of_cmd))(c->tokens);
        if(outstring!=NULL)
            printf("%s\n",outstring );
    }
    return;
}
