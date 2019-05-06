#ifndef _CMD_H
#define _CMD_H
/*
* DISCLAIMER; THIS CODE IS BASED ON THE LAB 6 ADRBOOK SHELL
* FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW (University of Chicago)
*/

/* ======================================= */
/* === command datatype and operations === */
/* ======================================= */

// Supported command tags
enum cmd_name {
  QUIT, HELP, HIST, LOOK, TAKE, GIVE
};

// Supported prepositions 
enum preposition_name{
  NONE, WITH, TO, IN
};

// Command data type
typedef struct {
  enum cmd_name name;
  char arg1[31]; /* optional argument, more may be added, NULL means the argument is unused */
  char arg2[31]; /* Note: max argument length is 32 characters!*/
  enum preposition_name preposition;
} cmd;

/* === command constructors === */

/* cmd_new: make a new heap-allocated command with arg set to NULL */
cmd *cmd_new(enum cmd_name name);

/* === command free === */

/* cmd_free: free command struct and its string, if there is one */
void cmd_free(cmd *c);

/* === command display (for debugging, logging) === */

/* cmd_name_tos: return string constant for command name */
/* note: for debugging only; not currently used in shell */
char *cmd_name_tos(cmd *c);

/* cmd_show: print command */
/* note: for debugging only */
void cmd_show(cmd *c);

/* === command parsing === */

/* cmd_from_string: build a cmd (as defined above) from a string
 * return NULL if the parse fails
 */
cmd *cmd_from_string(char *s);

/*
 * Takes tokens and creates a command using them.
 * For the purposes of this, we will store the preposition
 * in the command, not the name.
 * Input is a list of tokens, output is a pointer to a new command.
 */
cmd *cmd_from_tokens(char **ts);

/* do_cmd: execute the given command
 * note: address_book is of type bst** so it can be modified in READ
 */
void do_cmd(cmd *c,int *quit);
#endif /* _CMD_H */
