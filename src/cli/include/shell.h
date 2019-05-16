#ifndef _CLI_INCLUDE_SHELL_H
#define _CLI_INCLUDE_SHELL_H

/*
 * DISCLAIMER; THIS SHELL STRUCTURE IS BASED ON THE LAB 6 ADRBOOK SHELL
 * FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW 
 * (University of Chicago)
 */

/* ========================= */
/* === interface actions === */
/* ========================= */

/* 
 * Prints out a help menu that contains a list of supported commands
 * (Note that this function will be moved to operation.c)
 */
void help_text();


/*
 * Prints a greeting message when player starts the game
 * (Note that this function will be moved to operation.c)
 */
void greet();


/*
 * Prints out the history of valid command inputs in the current session
 */
void print_history();


/*
 * Prints out error messages for user errors (as opposed to bugs in code)
 */
void shell_error(char *s);


/*
 * Prints out error messages for user errors (as opposed to bugs in code)
 * - this version takes a string arg for added flexibility
 */
void shell_error_arg(char *fmt, char *s);

#endif /* _CLI_INCLUDE_SHELL_H */
