#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include "shell.h"

/* ========================= */
/* === interface actions === */
/* ========================= */

/* See shell.h */
void help_text()
{
  char p[] = 
    "HERE IS A BRIEF OVERVIEW OF GAME ACTIONS (NOT IMPLEMENTED)\n"
    "LOOK [OBJECT]  // look at specefied object\n"
    "TAKE [OBJECT] // take specefied object\n"
    "go [DIRECTION] // Move to the south, east, west or north\n"
    "inv   // prints everything you are carrying\n"
    "GIVE [OBJECT] TO [NPC] //gives specefied object to specefied non player character\n"
    
    "HERE IS A BRIEF OVERVIEW OF SYSTEM ACTIONS\n"
    
    "HELP        // help (duh, you just used it)\n"
    "load [PATH] (NOT IMPLEMENTED) // will load a saved game located at the specefied path relative to the folder chiventure is running in\n"
    "save [PATH] (NOT IMPLEMENTED) // will save a game at specefied path\n"
    "QUIT        // quit\n\n"
    "HIST		// prints out history of commands\n";
  printf("%s",p);
}

/* See shell.h */
void greet()
{
  printf("***** Welcome to CHIVENTURE! *****\n\n");
  printf("NOTHING USEFULL IMPLEMENTED YET !\n\n");
}

/* See shell.h */
void print_history()
{
	int offset_start = history_base,
 	    offset_end = history_length;
	int i, j=1;
	for (i = offset_start; i <= offset_end; i++)
	{
		printf("Entry %d: %s\n", j, history_get(i)->line);
		j++;
	}
}

/* See shell.h */
void shell_error(char *s)
{
  fprintf(stderr,"===> ERROR: %s <===\n",s);
}

/* See shell.h */
void shell_error_arg(char *fmt, char *s)
{
  fprintf(stderr,"===> ERROR: ");
  fprintf(stderr,fmt,s);
  fprintf(stderr," <===\n");
}
