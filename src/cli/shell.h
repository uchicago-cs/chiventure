#ifndef _SHELL_H
#define _SHELL_H

/*
* DISCLAIMER; THIS SHELL IS BASED ON THE LAB 6 ADRBOOK SHELL 
* FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW (University of Chicago)
*/

/* ========================= */
/* === interface actions === */
/* ========================= */

/*
*    Function that prints out a message with suggested actions
*/

void help_text();

/*
*    Function that prints out a prompt
*/

void shell_prompt();

/*
*    Function that prints out a message when player runs the game
*/

void greet();

/*
 *  Prints the history of commands
 */
void print_history();

/* shell_error: this is for user errors (as opposed to bugs in code) */
/* (gives all such errors a uniform appearance) */
void shell_error(char *s);

/* shell_error_arg: this is for user errors (as opposed to bugs)
 * - this version takes a string arg for added flexibility
 */
void shell_error_arg(char *fmt, char *s);

#endif /* _SHELL_H */
