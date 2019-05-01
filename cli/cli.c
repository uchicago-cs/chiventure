/*
* DISCLAIMER; THIS SHELL IS BASED ON THE LAB 6 ADRBOOK SHELL 
* FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW (University of Chicago)
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "cli.h"
#include "cmd.h"

#define BUFFER_SIZE 256

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
  default:
    /* this shouldn't happen, ever */
    fprintf(stderr,"BUG (do_cmd): bad tag in cmd (%d)\n",c->name);
    exit(1);
  }    
}

/* ===================================== */
/* ==== run the chiventure  shell  ===== */
/* ===================================== */

/* trim_newline: duplicate the string and replace the newline 
 * at the end with '\0' if it exists. 
 */
char *trim_newline(char *s)
{
  int n = strlen(s);
  char *t = strdup(s);
  if (s[n-1]=='\n')
    t[n-1] = '\0';
  return t;
}

int main()
{
  int quit=1;
  char *cmd_string;
  char user_input[BUFFER_SIZE];
  memset(user_input,'\0',BUFFER_SIZE);
  
  /* say hello*/
  greet();

  while (quit) {
    shell_prompt();
    //read user input
    fgets(user_input, BUFFER_SIZE, stdin);
    //format user input
    cmd_string = trim_newline(user_input);
    putchar('\n');
    //check whether user input is empty
    if (!strcmp(cmd_string,""))
      continue;
    cmd *c = cmd_from_string(cmd_string);
    if (!c) {
      shell_error_arg("unrecognized or malformed command: \"%s\"", cmd_string);
      putchar('\n');
    } else
      do_cmd(c,&quit);
    if (cmd_string)
      free(cmd_string);
    cmd_free(c);
  }

  /* clean up and exit */
  return 0;
}

/* A note to coders who have read this code with interest:
 * one typically doesn't reinvent the wheel to write a shell
 * from scratch like you see here. For more information, please
 * investigate the Command Line Editor Library (libedit). -ams
 */
