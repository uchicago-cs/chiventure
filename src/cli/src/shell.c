#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/* ========================= */
/* === interface actions === */
/* ========================= */

/* See shell.h */
void help_text(chiventure_ctx_t *ctx)
{
    char p[] =
        "HERE IS A BRIEF OVERVIEW OF GAME ACTIONS (SOME NOT IMPLEMENTED)\n"
        "LOOK [OBJECT]\n"
        "	-Look at specified object\n"
        "TAKE [OBJECT]\n"
        "	-Take specified object\n"
        "go [DIRECTION]\n"
        "	-Move to the south, east, west or north\n"
        "INV\n"
        "	-Prints everything you are carrying\n"
        "GIVE [OBJECT] TO [NPC]\n"
        "	-Gives specefied object to specified non player character\n\n"

        "HERE IS A BRIEF OVERVIEW OF SYSTEM ACTIONS\n"
        "HELP\n"
        "	-Prints out help menu (duh, you just used it)\n"
        //"HIST\n"
        //"	-Prints out the history of valid command"
        //" inputs in this session\n"
        "LOAD [PATH] (NOT IMPLEMENTED)\n"
        "	-Loads a saved game from a specified location\n"
        "	 relative to the folder chiventure is running in\n"
        "SAVE [PATH] (NOT IMPLEMENTED)\n"
        "	-Saves a game to a specified location\n"
        "NAME [VALID COMMAND] [NEW COMMAND]\n"
        " -Makes the second argument a command word with the definition of the first argument\n"
        "PALETTE [\"DEFAULT\"/\"NIGHT\"/\"BRIGHT\"/\"PAIN\"]"
        " -Makes the color of the UI change to that theme!"
        "CTRL + D\n"
        "	-Quit game\n\n";
    print_to_cli(ctx, p);
}

/* See shell.h */
void greet(chiventure_ctx_t *ctx)
{
    print_to_cli(ctx, "***** Welcome to CHIVENTURE! *****\n\n");
    print_to_cli(ctx, "NOTHING USEFULL IMPLEMENTED YET !\n\n");
}

/* See shell.h */
void shell_error(char *s)
{
    fprintf(stderr,"===> ERROR! You can't: %s <===\n",s);
}

/* See shell.h */
void shell_error_arg(char *fmt, char *s)
{
    fprintf(stderr,"===> ERROR: ");
    fprintf(stderr,fmt,s);
    fprintf(stderr," <===\n");
}
