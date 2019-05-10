#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"
//#define selectcommand(token,name) if(strcmp(token,"name")==0) output = cmd_new(name);

/* === command constructors  === */

/* cmd_new: make a new heap-allocated command with arg set to NULL
 * and preposition set to 0, which is the symbol for no preposition.
 */
cmd *cmd_new(char *  tokens[TOKEN_LIST_SIZE])
{
  cmd *c = (cmd*)malloc(sizeof(cmd));
  if (c==NULL) {
    fprintf(stderr,"error (cmd_tag): malloc failed\n");
    exit(1);
  }
  c->tokens=tokens;
  return c;
}

/* === command free === */

/* cmd_free: free command struct and its string, if there is one */
void cmd_free(cmd *c)
{
  if (c == NULL || c->tokens == NULL) return;
  for(int i = 0; i < TOKEN_LIST_SIZE; i++) {
      if (c->tokens[i] != NULL) free(c->tokens[i]);
  }
    free(c);
}

/* === command display (for debugging, logging) === */

/* cmd_name_tos: return string constant for command name */
char *cmd_name_tos(cmd *c)
{
  if(c == NULL || c->tokens == NULL || c->tokens[0] == NULL) return "ERROR";
  return c->tokens[0];
}

/* cmd_show: print command */
/* note: for debugging only; */
void cmd_show(cmd *c)
{
  /* note: cmd_name_tos result does not need to be freed
   * since that function returns pointers to string constants
   */
   if (c == NULL || c->tokens == NULL) return;
   for(int i = 0; i < TOKEN_LIST_SIZE; i++) {
       if (c->tokens[i] != NULL) printf("%s\n",(c->tokens[i]));
   }
   return;
}

/* === command parsing === */


/*
 * Takes tokens (parsed command) and creates a command using them.
 * For the purposes of this, we will store the preposition
 * in the command, not the name.
 * Input is a list of tokens, output is a pointer to a new command.
 * If the command is not valid, (the first word), then it outputs a NULL pointer.
 * otherwise, it ignores bad prepositions, and keeps all other bits.
 * Also, if malloc fails for a string
 */
cmd *cmd_from_tokens(char **ts){
  cmd *output = cmd_new(ts);
/*selectcommand(ts[0],QUIT)
  selectcommand(ts[0],HELP)
  selectcommand(ts[0],HIST)
  selectcommand(ts[0],LOOK)
  selectcommand(ts[0],TAKE)
  selectcommand(ts[0],GIVE) */
  if(strcmp(ts[0],"QUIT")==0) output->functionofcommand = quit_operation;
  else if(strcmp(ts[0],"HELP")==0) output->functionofcommand = help_operation;
  else if(strcmp(ts[0],"HIST")==0) output->functionofcommand = hist_operation;
  else if(strcmp(ts[0],"LOOK")==0) output->functionofcommand = state_operation;
  else if(strcmp(ts[0],"TAKE")==0) output->functionofcommand = action_operation;
  else if(strcmp(ts[0],"GIVE")==0) output->functionofcommand = action_operation;
  // These are macros defined above. Essentially, just treat them as switch
  // statement cases
  // Add a new one for each new command.
  else {
    output->functionofcommand = action_error_operation;
    }
  //HERE WE VALIDATE THE COMMANDS

  return output;

}

/* cmd_from_string: build a cmd (as defined in the cmd.h) from a string;
 * return NULL if the parse fails
 */
cmd *cmd_from_string(char *s)
{
  char **parsed_input = parse(s);
  return cmd_from_tokens(parsed_input);
}

/* =================================== */
/* === execution of shell commands === */
/* =================================== */

/* do_cmd: execute the given command
 */
void do_cmd(cmd *c,int *quit)
{
  char * outstring;
  /* available commands are QUIT, STATS, CHAR, LOOKUP, HELP, READ */
  if (strcmp(cmd_name_tos(c),"QUIT")==0){
      *quit=0;
      (*(c->functionofcommand))(c->tokens);
    }
  else{
    outstring = (*(c->functionofcommand))(c->tokens);
    if(outstring!=NULL)
    printf("%s\n",outstring );
  }
  // else if (strcmp(cmd_name_tos(c),"HELP")==0)  help_text();
  // else if (strcmp(cmd_name_tos(c),"HIST")==0)	print_history();
  // else if (strcmp(cmd_name_tos(c),"LOOK")==0)	cmd_show(c);
  // else if (strcmp(cmd_name_tos(c),"TAKE")==0)	  cmd_show(c);
  // else if (strcmp(cmd_name_tos(c),"GIVE")==0)	  cmd_show(c);
  // else {
  //   /* this shouldn't happen, ever */
  //   fprintf(stderr,"BUG (do_cmd): bad tag in cmd (%s)\n",cmd_name_tos(c));
  //   exit(1);
  // }
  return;
}
