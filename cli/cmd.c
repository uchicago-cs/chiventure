#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "cmd.h"

/* === command constructors  === */

/* cmd_new: make a new heap-allocated command with arg set to NULL */
cmd *cmd_new(enum cmd_name name) 
{
  cmd *c = (cmd*)malloc(sizeof(cmd));
  if (c==NULL) {
    fprintf(stderr,"error (cmd_tag): malloc failed\n");
    exit(1);
  }
  c->name=name;
  c->arg=NULL;
  return c;
}

/* === command free === */

/* cmd_free: free command struct and its string, if there is one */
void cmd_free(cmd *c)
{
  if (c) {
    if (c->arg)
      free(c->arg);
    free(c);
  }
}

/* === command display (for debugging, logging) === */

/* cmd_name_tos: return string constant for command name */
/* note: for debugging only; not currently used in shell */
char *cmd_name_tos(cmd *c)
{
  switch (c->name) {
  case QUIT:      return "QUIT";
  case HELP:      return "HELP";
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
  if (c->arg)
    fprintf(f,"%s %s\n",cmd_name_tos(c),c->arg);
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
    }
  } 
  /* if we get this far, we couldn't parse the command string */
  return NULL;
}
