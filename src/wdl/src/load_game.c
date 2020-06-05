#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "wdl/load_wdz_internal.h"

#include "wdl/validate.h"
#include "wdl/parse.h"
#include "wdl/load_game.h"
#include "wdl/load_room.h"
#include "wdl/load_item.h"

/*
 * load_wdl, function that loads a wdl into all the game-state structs
 *
 * takes a path to a yaml file, returns a game struct
 *
 *
 */
game_t *load_wdl(char *path_to_yaml)
{
    // WDZ loading monkeypatch.
    // Intercepts chiventure if wdz file is passed in as CLI argument, 
    // and prints JSON contents for debug.
    // This is also likely the entrypoint for our final implementation.
    if (filename_extension_is("wdz", path_to_yaml))
    {
        int n_jsons = 0;
        printf("Detected wdz file. Attempting to load wdz and printing the json files...\n");
        printf("Note that loading wdz is not functional right now.\n");
        object_t *obj_store_init_obj = new_object("__empty__");
        /* commenting all this out because new_object always returns NULL for now. */
        // if (!obj_store_init_obj) 
        // {
        //     fprintf(stderr,"could not allocate dummy object for objstore\n");
        //     return NULL;
        // }
        // // ideally this should be handled by new_object itself
        // obj_store_init_obj->type = TYPE_OTHER;
        objstore_t *obj_store = new_objstore(obj_store_init_obj);

        populate_objstore_from_wdz(obj_store, &n_jsons, path_to_yaml);
        
        /* commenting this out for now because new_object always returns NULL for now. */
        //free_objstore(&obj_store, find_objstore(&obj_store, "__empty__", TYPE_OTHER));
        printf("Number of JSON files found: %d\n", n_jsons);
        return NULL;
    }

    int rc;
    obj_t *big_document = get_doc_obj(path_to_yaml);

    game_t *game = create_game(big_document);

    // call functions that parse items, actions, rooms, and game attributes
    // into a game pointer
    rc = add_rooms_to_game(big_document, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error adding rooms to game.\n");
        return NULL;
    }


    rc = add_connections_to_rooms(big_document, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error adding connections to rooms.\n");
        return NULL;
    }

    rc = load_items(big_document, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error loading items.\n");
        return NULL;
    }

    obj_t *game_document = obj_get_attr(big_document, "GAME.0", false);
    char *start_room = obj_get_str(game_document, "start");
    game->curr_room = find_room_from_game(game, start_room);
    if(game->curr_room == NULL)
    {
        fprintf(stderr, "Invalid starting room: %s\n", start_room);
        return NULL;
    }

    obj_t *end = obj_get_attr(game_document, "end.0", false);
    char *end_room = obj_get_str(end, "in_room");
    room_t *final_room = find_room_from_game(game, end_room);
    game->final_room = final_room;
    if(game->final_room == NULL)
    {
        fprintf(stderr, "Invalid end room: %s\n", end_room);
        return NULL;
    }

    return game;
}

game_t *create_game(obj_t *doc)
{
    obj_t *game = obj_get_attr(doc, "GAME.0", false);
    if (game == NULL)
    {
        fprintf(stderr, "game object not found\n");
        exit(0);
    }

    int check = game_type_check(game);
    if (check == FAILURE)
    {
        fprintf(stderr, "game object fails type checking\n");
        exit(0);
    }

    char *intro = obj_get_str(game, "intro");

    game_t *game_ret = game_new(intro);
    return game_ret;
}

void debug_print(game_t *game)
{
    room_t *curr_room;

    ITER_ALL_ROOMS(game, curr_room)
    {
        printf("room id: %s\n", curr_room->room_id);

        path_t *curr_path;

        ITER_ALL_PATHS(curr_room, curr_path)
        {
            printf("direction: %s\n", curr_path->direction);
        }

        item_t *curr_item;

        ITER_ALL_ITEMS_IN_ROOM(curr_room, curr_item)
        {
            printf("item id: %s\n", curr_item->item_id);
        }
    }
}
