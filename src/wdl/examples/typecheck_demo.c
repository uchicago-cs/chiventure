#include "wdl/parse.h"
#include "wdl/validate.h"

int main(int argc, char* argv[])
{
    // Makes sure there are enough arguments
    if (argc <= 1) {
        printf("Err: not enough arguments");
        return 1;
    }

    // Take second element of argv as filename
    char* fname = argv[1];

    // Checks if fname exists
    if (fname == NULL) {
        printf("Err: no filename provided\n");
        return 1;
    }
    // Checks if extension is a .yaml extension
    const char *ext = strchr(fname, '.');
    const char *check = ".yaml";
   
    if (strncmp(ext, check, strlen(check)) != 0) {
        printf("Err: file does not have .yaml extension\n");
        return 1;
    }

    // Create new, malloc'ed, blank "document" object
    obj_t* doc_obj = obj_new("document");

    // Call parse_game to fill in object
    parse_game(fname, doc_obj);

    // Stream of functions to verify and print the attributes of objects parsed
    // from the YAML file

    // Extract individual objects
    obj_t *room_obj = obj_get_attr(doc_obj, "ROOMS", false);
    obj_t *item_obj = obj_get_attr(doc_obj, "ITEMS", false);
    obj_t *game_obj = obj_get_attr(doc_obj, "GAME", false);

    // Extract list of rooms and items
    attr_list_t *rooms_ls = obj_list_attr(room_obj);
    attr_list_t *items_ls = obj_list_attr(item_obj);

    // Verify game
    bool game_check = game_type_check(game_obj);
    if (game_check) {
        printf("Game successfully verified\n");
    }
    else {
        printf("Game verification unsuccessful\n"); 
    }

    // Verify rooms
    bool room_check = list_type_check(rooms_ls, room_type_check);

    if (room_check) {
        printf("Rooms successfully verified\n");
    }
    else {
        printf("Rooms verification unsuccessful\n");
    }
    // Verify items
    bool item_check = list_type_check(items_ls, item_type_check);

    if (item_check) {
        printf("Items successfully verified\n");
    }
    else {
        printf("Items verificaton unsuccessful\n");
    }

    // Print game
    printf("printing game attributes:\n");
    print_game(game_obj);

    // Print rooms
    printf("printing all rooms and their attributes:\n");
    list_print(rooms_ls, print_room);

    // Print items
    printf("printing all items and their attributes\n");
    list_print(items_ls, print_item);

    return 0;
}
