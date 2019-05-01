#ifndef _CMD_H
#define _CMD_H
/*
* DISCLAIMER; THIS CODE IS BASED ON THE LAB 6 ADRBOOK SHELL 
* FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW (University of Chicago)
*/

/* ======================================= */
/* === command datatype and operations === */
/* ======================================= */

//All suported commands
enum cmd_name {
  QUIT, HELP
};

//Command data type
typedef struct {
  enum cmd_name name;
  char *arg; /* optional argument, more will be added */ 
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

/* cmd_show: print command to FILE* (typically stderr) */
/* note: for debugging only; not currently used in shell */
void cmd_show(FILE *f, cmd *c);

/* === command parsing === */

/* cmd_from_string: build a cmd (as defined above) from a string;
 * return NULL if the parse fails
 */
cmd *cmd_from_string(char *s);

#endif /* _CMD_H */
