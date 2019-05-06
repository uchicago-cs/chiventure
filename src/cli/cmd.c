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
cmd *cmd_new(enum cmd_name name)
{
  cmd *c = (cmd*)malloc(sizeof(cmd));
  if (c==NULL) {
    fprintf(stderr,"error (cmd_tag): malloc failed\n");
    exit(1);
  }
  c->name=name;
  c->preposition=0;
  if ((c->arg1 == NULL) || (c->arg2 == NULL)) {
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
  case LOOK:	  return "LOOK";
  case TAKE:	  return "TAKE";
  case GIVE:	  return "GIVE"; 
  }
  // this should never happen, ever 
  fprintf(stderr,"BUG (cmd_name_tos): unrecognized command name %d\n",c->name);
  exit(1);
}

static const char *prep[] = {"NONE", "WITH", "TO", "IN"};
/* cmd_show: print command */
/* note: for debugging only; */
void cmd_show(cmd *c)
{
  /* note: cmd_name_tos result does not need to be freed
   * since that function returns pointers to string constants
   */
  if (c->arg1 && strlen(c->arg2)>0)
      printf("%s %s %s %s\n",cmd_name_tos(c),c->arg1,prep[c->preposition],c->arg2);
  else if (c->arg1)
      printf("%s %s\n",cmd_name_tos(c),c->arg1);
  else
      printf("%s\n",cmd_name_tos(c));
}

/* === command parsing === */

/*
 * Set preposition (if exists) for the command
 */
void fill_preposition(cmd *c, char *token)
{
	if(token==NULL) return;
	if(strcmp((token),("WITH"))==0) c->preposition = WITH;
	if(strcmp((token),("TO"))==0) c->preposition = TO; 	
	if(strcmp((token),("IN"))==0) c->preposition = IN;
}

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
  cmd *output = NULL;
/*selectcommand(ts[0],QUIT)
  selectcommand(ts[0],HELP)
  selectcommand(ts[0],HIST)
  selectcommand(ts[0],LOOK)
  selectcommand(ts[0],TAKE)
  selectcommand(ts[0],GIVE) */
  if(strcmp(ts[0],"QUIT")==0) output = cmd_new(QUIT);
  if(strcmp(ts[0],"HELP")==0) output = cmd_new(HELP);
  if(strcmp(ts[0],"HIST")==0) output = cmd_new(HIST);
  if(strcmp(ts[0],"LOOK")==0) output = cmd_new(LOOK);
  if(strcmp(ts[0],"TAKE")==0) output = cmd_new(TAKE);
  if(strcmp(ts[0],"GIVE")==0) output = cmd_new(GIVE);
  // These are macros defined above. Essentially, just treat them as switch
  // statement cases
  // Add a new one for each new command.
  if(output == NULL) return output;
  // As above, but for prepositions.
  fill_preposition(output, ts[2]);
  if(ts[1] != NULL) strcpy(output->arg1, ts[1]);
  if(ts[3] != NULL) strcpy(output->arg2, ts[3]);
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
 * note: address_book is of type bst** so it can be modified in READ
 */
void do_cmd(cmd *c,int *quit)
{
  switch (c->name) {
  /* available commands are QUIT, STATS, CHAR, LOOKUP, HELP, READ */
  case QUIT:      *quit=0; break;
  case HELP:      help_text(); break;
  case HIST:	  print_history(); break;
  case LOOK:	  cmd_show(c); break;
  case TAKE:	  cmd_show(c); break;
  case GIVE:	  cmd_show(c); break;
  default:
    /* this shouldn't happen, ever */
    fprintf(stderr,"BUG (do_cmd): bad tag in cmd (%d)\n",c->name);
    exit(1);
  }    
}
