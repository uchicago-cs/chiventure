#include <stdio.h>
#include "parser.h"

int main(int argc, char* argv[])
{
    //Makes sure there are enough arguments
    if (argc == 1)
    {
        printf("Err: not enough arguments");
    }

    //Take second element of argv as filename
    //NOTE: must have a ".yaml" extension
    char* fname = argv[1];
    if (fname == NULL)
    {
        printf("Err: no filename provided\n");
    }

    //Create new, malloc'ed, blank "document" object
    obj_t* obj = obj_new("document");

    //Call parse_game to fill in object
    parse_game(fname, obj);


    //A few examples of getting out attributes after parsing the file "orb.yaml"
    printf("GAME.0.start: %c\n", obj_get_char(obj,"GAME.0.start"));
    printf("GAME.1.intro: %s\n",obj_get_str(obj,"GAME.1.intro"));
    printf("GAME.2.end.inventory: %s\n",obj_get_str(obj,"GAME.2.end.inventory"));
    printf("OBJECTS.0.short_desc: %s\n", obj_get_str(obj,"OBJECTS.0.short_desc"));
    printf("ROOMS.0.id: %c\n", obj_get_char(obj, "ROOMS.0.id"));

    return 0;
}
