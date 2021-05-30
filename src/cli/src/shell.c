#include <stdio.h>

#include "cli/shell.h"
#include "ui/print_functions.h"

/* ========================= */
/* === interface actions === */
/* ========================= */

/* See shell.h */
void help_text(chiventure_ctx_t *ctx)
{
    char p[] =

        "HERE IS A BRIEF OVERVIEW OF GAME ACTIONS\n"
        "LOOK\n"
        "   -Look around the room\n"
        "GO [DIRECTION]\n"
        "	-Move to the south, east, west or north\n"
        "INV\n"
        "	-Prints everything you are carrying\n"
        "OTHER COMMANDS:\n"
        "   -LOOK [OBJ]\n"
        "   -OPEN [OBJ]\n"
        "   -CLOSE [OBJ]\n"
        "   -PUSH [OBJ]\n"
        "   -PULL [OBJ]\n"
        "   -TALK TO [NPC]\n"
        "   -TURNON [OBJ]\n"
        "   -TURNOFF [OBJ]\n"
        "   -TAKE [OBJ]\n"
        "   -PICKUP [OBJ]\n"
        "   -DROP [OBJ]\n"
        "   -CONSUME [OBJ]\n"
        "   -USE [OBJ]\n"
        "   -EAT [OBJ]\n"
        "   -DRINK [OBJ]\n"
        "   -USE [OBJ] ON [OBJ]\n"
        "   -PUT [OBJ] ON [OBJ]\n"
        "HERE IS A BRIEF OVERVIEW OF SYSTEM ACTIONS\n"
        "HELP\n"
        "	-Prints out help menu (duh, you just used it)\n"
        "MAP\n"
        "   -Shows the map. Type 'map' again to hide the map\n"
        "SWITCH\n"
        "   -Switches the position of the main window and the CLI. Type 'switch' again to switch it back\n"
        "LOAD [PATH] (NOT IMPLEMENTED)\n"
        "	-Loads a saved game from a specified location\n"
        "	 relative to the folder chiventure is running in\n"
        "SAVE [PATH] (NOT IMPLEMENTED)\n"
        "	-Saves a game to a specified location\n"
        "NAME [VALID COMMAND] [NEW COMMAND]\n"
        " -Makes the second argument a command word with the definition of the first argument\n"
        "PALETTE [\"DEFAULT\"/\"NIGHT\"/\"BRIGHT\"/\"PAIN\"]\n"
        " -Makes the color of the UI change to that theme!\n"
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
