#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include "validate.h"


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

    // Stream of functions to verify the attributes of objects parsed from the
    // YAML file

    // Verify rooms
    obj_t *room_obj = obj_get_attr(obj, "ROOMS", false);
    attr_list_t *rooms_ls = obj_list_attr(room_obj);
    bool roomcheck = list_type_check(rooms_ls, room_type_check);

    if (roomcheck)
        printf("Rooms successfully verified\n");

    else
        printf("Rooms unsuccessfully verified\n");

    // Print rooms
    list_print(rooms_ls, print_room);

    return 0;
}
