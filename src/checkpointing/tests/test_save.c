#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game.pb-c.h"
#include "save.h"
#include "game.h"

Test(save, item)
{
    item_t *candy_t;
    char *item_id = "1234";
    char *short_desc = "salt water taffy";
    char *long_desc = "glues mouth shut";
    // item_new is a function in game-states's item.h. It creates an item_t struct.
    candy_t = item_new(item_id, short_desc, long_desc);

    Item *candy = malloc(sizeof(Item));
    
    int success;

    // functions that will be in game-states pull request
    /*
    success = create_new_double_attr(candy_t, "double", 2.5);
    cr_assert_eq(success, 0, "create_new_double_attr failed");

    success = create_new_char_attr(candy_t, "char", 'T');
    cr_assert_eq(success, 0, "create_new_char_attr failed");

    success = create_new_boole_attr(candy_t, "boole", true);
    cr_assert_eq(success, 0, "create_new_boole_attr failed");

    success = create_new_str_attr(candy_t, "str", "string");
    cr_assert_eq(success, 0, "create_new_str_attr failed");

    success = create_new_int_attr(candy_t, "int", 1);
    cr_assert_eq(success, 0, "create_new_int_attr failed");
    */

    success = save_item(candy_t, candy);
    
    cr_assert_eq(success, 0, "save_item failed %d", success);
    cr_assert_str_eq(candy->item_id, "1234", "save_item: saving item_id failed");
    cr_assert_str_eq(candy->short_desc, "salt water taffy",
		 "save_item: saving short_desc failed");
    cr_assert_str_eq(candy->long_desc, "glues mouth shut",
     "save_item: saving long_desc failed");
    cr_assert_eq(candy->attributes_len, 5,
    "save_item: saving the attributes_len failed");

    free(candy);
}

Test(save, room)
{
    room_t *room_t;
    char *room_id = "5";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    // room_new is a function in game-states's room.h. It creates a room_t struct.
    room_t = room_new(room_id, short_desc, long_desc);

    item_t *ramen_t;
    char *i_item_id = "1234";
    char *i_short_desc = "cup ramen";
    char *i_long_desc = "has already been eaten";
    // item_new is a function in game-states's item.h. It creates an item_t struct.
    ramen_t = item_new(i_item_id, i_short_desc, i_long_desc);

    path_t *path_t;
    // path_new is a function in game-states's path.h. It creates a path_t struct.
    path_t = path_new("4");

    add_item_to_room(room_t, ramen_t);
    add_path_to_room(room_t, path_t);

    Room *dorm = malloc(sizeof(Room));
    int succ = save_room(room_t, dorm);
    printf("starting room tests");
    cr_assert_eq(succ, 0, "save_room failed");
    printf("passed");
    cr_assert_str_eq(dorm->room_id, "5", "save_room: saving room_id failed");
    cr_assert_str_eq(dorm->short_desc, "college dorm",
     "save_room: saving short_desc failed");
    cr_assert_str_eq(dorm->long_desc, "there are clothes and empty ramen cups everwhere",
                                   "save_room: saving long_desc failed");
    /* There is potential changes coming regarding whether we include paths.
     * We additionally need a way to check if an item was stored in the hash.
     * This might need to be some discussion with Game-State.
     */

    free(dorm);
}

Test(save, player)
{
    player_t *player_t;
    /* player_new is a function in game-states's player.h. It creates a
     * player_t struct.
     */
    player_t = player_new(1);

    Player *chad = malloc(sizeof(Player));

    int success = save_player(player_t, chad);

    cr_assert_eq(success, 0, "save_player failed");
    cr_assert_eq(chad->health, 1, "save_player: saving health failed");

    free(chad);
}

Test(save, game)
{
    // game_new is a function in game-states's game.h. It creates a game_t struct.
    game_t *game_t = game_new();

    room_t *room_t;
    char *room_id = "5";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    // room_new is a function in game-states's room.h. It creates a room_t struct.
    room_t = room_new(room_id, short_desc, long_desc);
    add_room_to_game(game_t, room_t);

    player_t *player_t;
     /* player_new is a function in game-states's player.h. It creates a
     * player_t struct.
     */
    player_t = player_new(1);
    player_t->player_id = "Chad";
    add_player_to_game(game_t, player_t);
    set_curr_player(game_t, player_t);

    game_t->curr_room = room_t; // no set_curr_room function
    game_t->curr_player = player_t;

    Game *game = malloc(sizeof(Game));
    int success = save_game(game_t, game);

    cr_assert_eq(success, 0, "save_game failed");
    cr_assert_str_eq(game->curr_room, "5", 
                  "save_game: saving curr_room failed");
    cr_assert_str_eq(game->curr_player, "Chad", 
                  "save_game: saving curr_player failed");
    cr_assert_eq(game->players_len, 1, "save_game: saving players_len %d failed",
		 game->players_len);
    
    cr_assert_str_eq(game->all_players[0]->player_id, "Chad",
                  "save_game: saving player_id failed");
    cr_assert_eq(game->rooms_len, 1, "save_game: saving rooms_len failed");
    cr_assert_str_eq(game->all_rooms[0]->room_id, "5", 
                  "save_game: saving room_id failed");
    cr_assert_str_eq(game->all_rooms[0]->short_desc, "college dorm",
                  "save_game: saving short_desc failed");
    cr_assert_str_eq(game->all_rooms[0]->long_desc,
                  "there are clothes and empty ramen cups everywhere",
                  "save_game: saving long_desc failed");

    free(game);
}
