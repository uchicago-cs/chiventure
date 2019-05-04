#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "cmd.h"
#define selectcommand(token,name) if(strcmp((token),("name"))==0) output = cmd_new((name));
#define selectpreposition(token,name) if(strcmp((token),("name"))==0) output = cmd_new((name));

/* === command constructors  === */

/* cmd_new: make a new heap-allocated command with arg set to NULL
 * and preposition set to 0, which is the symbol for no preposition.
 */

cmd *cmd_new(enum cmd_name name)
{
  cmd *c = (cmd*)malloc(sizeof(cmd));
  if (c==NULL) {
    fprintf(stderr,"error (cmd_tag): malloc failed\n");
    exit(1);
  }
  c->name=name;
  //c->arg1=malloc(sizeof(char)*32);
  //c->arg2=malloc(sizeof(char)*32);
  c->preposition=0;
  if ((c->arg1 ==NULL) || (c->arg2 ==NULL)) {
    fprintf(stderr,"error (cmd_tag): malloc failed\n");
    exit(1);
  }
  return c;
}

/* === command free === */

/* cmd_free: free command struct and its string, if there is one */
void cmd_free(cmd *c)
{
  if (c) {
    if (c->arg1)
      free(c->arg1);
    if (c->arg2)
      free(c->arg2);
    if (c->preposition)
      free(c->preposition);
    free(c);
  }
}

/* === command display (for debugging, logging) === */

/* cmd_name_tos: return string constant for command name */
char *cmd_name_tos(cmd *c)
{
  switch (c->name) {
  case QUIT:      return "QUIT";
  case HELP:      return "HELP";
  case HIST:	  return "HIST";
  }
  /* this should never happen, ever */
  fprintf(stderr,"BUG (cmd_name_tos): unrecognized command name %d\n",c->name);
  exit(1);
}

/* cmd_show: print command to FILE* (typically stderr) */
/* note: for debugging only; not currently used in shell */
void cmd_show(FILE *f, cmd *c)
{
  /* note: cmd_name_tos result does not need to be freed
   * since that function returns pointers to string constants
   */
  if (c->arg1)
    fprintf(f,"%s %s\n",cmd_name_tos(c),c->arg1);
  else
    fprintf(f,"%s\n",cmd_name_tos(c));
  if (c->arg2)
      fprintf(f,"%s %s\n",cmd_name_tos(c),c->arg2);
  else
      fprintf(f,"%s\n",cmd_name_tos(c));
}

/* === command parsing === */

/* cmd_from_string: build a cmd (as defined above) from a string;
 * return NULL if the parse fails
 */
cmd *cmd_from_string(char *s)
{
  char cmdbuf[2];
  char argbuf[99];
  memset(cmdbuf,0,2);
  memset(argbuf,0,99);
  sscanf(s,"%s %s",cmdbuf,argbuf);
  if (strlen(cmdbuf)==1) {
    switch (cmdbuf[0]) {
    case 'q' : return cmd_new(QUIT);
    case 'h' : return cmd_new(HELP);
    case 'H' : return cmd_new(HIST);
    }
  }
  /* if we get this far, we couldn't parse the command string */
  return NULL;
}
cmd *cmd_from_tokens(char **ts){
  cmd * output = NULL;
  selectcommand(ts[0],QUIT)
  selectcommand(ts[0],HELP)
  selectcommand(ts[0],HIST)
  // These are macros defined above. Essentially, just treat them as switch
  // statement cases
  // Add a new one for each new command.
  if(output == NULL) return output;
  // As above, but for prepositions.
  selectpreposition(ts[2],WITH)
  selectpreposition(ts[2],TO)
  selectpreposition(ts[2],IN)
  if(output->arg1 != NULL) strcpy(output->arg1, ts[1]);
  if(output->arg2 != NULL) strcpy(output->arg2, ts[3]);
  return output;
}
/*
 * Takes tokens and creates a command using them.
 * For the purposes of this, we will store the preposition
 * in the command, not the name.
 * Input is a list of tokens, output is a pointer to a new command.
 * If the command is not valid, (the first word), then it outputs a NULL pointer.
 * otherwise, it ignores bad prepositions, and keeps all other bits.
 * Also, if malloc fails for a string
 */
