#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "parser.h"


/* DEBUG is 0 normally, 1 to print debugging statements */
#define DEBUG 1

/* Helper function: to print debugging statements only when debugging */
int my_print(char *string) {
    
    if (DEBUG) {
        printf("%s\n",string);
    }

    return 0;

}


int add_rooms_to_game(json_object *rooms, game_t *g) {

    //initializes json_objects for use in making room_t
    int arr_len = json_object_array_length(rooms);
    struct json_object room_obj;
    struct json_object id_obj;
    struct json_object long_desc_obj;
    struct json_object short_desc_obj;

    //if room list is empty, return 1
    if(rooms != NULL) {
        fprintf(stderr, "rooms list is empty\n");
        return FAILURE;
    }

    //for loops list of rooms, creates a new game_struct room, add room to game
    for (int i = 0; i < arr_len; i++) {

        room_obj = json_object_array_get_idx(rooms, i);

        json_object_object_get_ex(room_obj, "id", &id_obj);
        char *id = json_object_get_string(id_obj);
        
        json_object_object_get_ex(room_obj, "short_desc", &short_desc_obj);
        char *short_desc = json_object_get_string(short_desc_obj);

        json_object_object_get_ex(rooms_obj, "long_desc", &long_desc_obj);
        char *long_desc = json_object_get_string(long_desc_obj);

        room_t *room = room_new(id, short_desc, long_desc);

        add_room_to_game(g, room);

    }

    return SUCCESS;

}

game_t *parse_wdl(char* filename) {
    FILE *fp;
    char buffer[4096];
    
    /* The main json_objects for storing top level information*/
    struct json_object *game_document;
    struct json_object *game_obj;
    struct json_object *rooms_obj;
    struct json_object *items_obj;
    struct json_object *intro_obj;
    
    /* reads the input file */
    fp = fopen(filename, "r");
    assert(fp);
    fread(buffer, 4096, 1, fp);
    fclose(fp);

    game_document = json_tokener_parse(buffer);
    
    assert(game_document);
 
    json_object_object_get_ex(game_document, "GAME", &game_obj);
    json_object_object_get_ex(game_document, "ROOMS", &rooms_obj);
    json_object_object_get_ex(game_document, "ITEMS", &items_obj);

    assert(game_obj);

    //gets the intro text for the game
    json_object_object_get_ex(game, "intro", &intro_obj);
    assert(intro_text);

    char *intro = json_object_get_string(intro_obj);

    game_t *game = game_new(intro);

    add_rooms_to_game(rooms_obj,game);

    return game;

}

int main(int argc, char **argv) {

    if(argc > 1) {

         parse_wdl(argv[1]);

    }

    return 0;

}
