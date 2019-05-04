#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

int main(int argc, char* argv[])
{
    // Makes sure there are enough arguments
    if (argc <= 1)
    {
        printf("Err: not enough arguments");
        return 1;
    }

    // Take second element of argv as filename
    char* fname = argv[1];

    // Checks if fname exists
    if (fname == NULL)
    {
        printf("Err: no filename provided\n");
        return 1;
    }
    // Checks if extension is a .yaml extension
    const char *ext = strchr(fname, '.');
    const char *check = ".yaml";
    if (strcmp(ext, check) != 0)
    {
        printf("Err: file does not have .yaml extension\n");
        return 1;
    }

    // Create new, malloc'ed, blank "document" object
    obj_t* obj = obj_new("document");

    // Call parse_game to fill in object
    parse_game(fname, obj);

    // Print game arguments
    char *game_s = "GAME.0";
    char *game_i = "GAME.1";
    print_game(obj, game_s, game_i);
}
