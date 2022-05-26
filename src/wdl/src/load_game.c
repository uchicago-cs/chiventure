#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "wdl/load_game.h"
#include "wdl/load_room.h"
#include "wdl/load_item.h"
#include "wdl/load_npc.h"
#include "wdl/load_class.h"
#include "wdl/validate.h"
#include "game-state/mode.h"

/* See load_game.h for documentation */
game_t *load_game(obj_t *obj_store)
{
    int rc;
    game_t *game = create_game(obj_store);

    // call functions that parse items, actions, rooms, NPCs, classes and game
    // attributes into a game pointer
    rc = add_rooms_to_game(obj_store, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error adding rooms to game.\n");
        return NULL;
    }

    rc = add_connections_to_rooms(obj_store, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error adding connections to rooms.\n");
        return NULL;
    }

    rc = load_items(obj_store, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error loading items.\n");
        return NULL;
    }

    rc = load_npcs(obj_store, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error loading NPCs.\n");
        return NULL;
    }

    rc = load_classes(obj_store, game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error loading classes.\n");
        return NULL;
    }

    rc = load_normal_mode(game);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Error loading mode.\n");
        return NULL;
    }

    obj_t *game_obj = obj_get_attr(obj_store, "GAME", false);
    char *start_room = obj_get_str(game_obj, "start");
    game->curr_room = find_room_from_game(game, start_room);
    if(game->curr_room == NULL)
    {
        fprintf(stderr, "Invalid starting room: %s\n", start_room);
        return NULL;
    }

    obj_t *end = obj_get_attr(game_obj, "end", false);
    char *end_room = obj_get_str(end, "in_room");
    room_t *final_room = find_room_from_game(game, end_room);
    game->final_room = final_room;
    if(game->final_room == NULL)
    {
        fprintf(stderr, "Invalid end room: %s\n", end_room);
        return NULL;
    }

    rc = load_quests(obj_store, game);
    if(rc != SUCCESS) {
        fprintf(stderr, "Quests not loaded properly!\n");
        return NULL;
    }

    return game;
}

game_t *create_game(obj_t *doc)
{
    obj_t *game = obj_get_attr(doc, "GAME", false);
    if (game == NULL)
    {
        fprintf(stderr, "game object not found\n");
        return NULL;
    }

    int check = game_type_check(game);
    if (check == FAILURE)
    {
        fprintf(stderr, "game object fails type checking\n");
        return NULL;
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

        item_list_t *curr_item;

        ITER_ALL_ITEMS_IN_ROOM(curr_room, curr_item)
        {
            printf("item id: %s\n", curr_item->item->item_id);
        }
    }
}
