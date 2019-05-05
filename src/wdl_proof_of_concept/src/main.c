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

    // Verify game and print game arguments
    char *game_s = "GAME.0";
    char *game_i = "GAME.1";
    if (verify_game(obj, game_s, game_i)) {
        printf("\nGame is valid.\n");
        print_game(obj, game_s, game_i);
    }
    else 
        printf("\nGame is not valid.\n");

    // Verify room and print room arguments
    char *room_a = "ROOMS.0";
    char *room_b = "ROOMS.1";
    char *room_c = "ROOMS.2";
    char *rooms[3] = {room_a, room_b, room_c};
    for (int i = 0; i < 3; ++i) {
        if (verify_room(obj, rooms[i])) {
            printf("\nRoom is valid.\n");
            print_room(obj, rooms[i]);
        }
        else
            printf("\nRoom is not valid\n");
    }

    // Print item arguments
    char *item_table = "ITEMS.0";
    char *item_chair = "ITEMS.1";
    char *item_candle = "ITEMS.2";
    char *items[3] = {item_table, item_candle, item_chair};
    for (int i = 0; i < 3; ++i) {
        if (verify_item(obj, items[i])) {
            printf("\nItem is valid.\n");
            print_item(obj, items[i]);
        }
        else
            printf("\nItem is invalid.\n");
    }

    return 0;
}
