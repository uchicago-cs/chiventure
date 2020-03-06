#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "save-int.h"
#include "game.pb-c.h"
#include "checkpointing/save.h"


Test(save, item)
{
    item_t *candy_t;
    char *item_id = "1234";
    char *short_desc = "salt water taffy";
    char *long_desc = "glues mouth shut";

    // item_new is a function in game-states's item.h. It creates an item_t struct.
    candy_t = item_new(item_id, short_desc, long_desc);
    cr_assert_not_null(candy_t, "candy_t is null");
    Item *candy = malloc(sizeof(Item));

    int success;
    
    success = set_double_attr(candy_t, "double", 2.5);
    cr_assert_eq(success, 0, "set_double_attr failed");

    success = set_char_attr(candy_t, "char", 'T');
    cr_assert_eq(success, 0, "set_char_attr failed");

    success = set_bool_attr(candy_t, "boole", true);
    cr_assert_eq(success, 0, "set_bool_attr failed");

    success = set_str_attr(candy_t, "str", "string");
    cr_assert_eq(success, 0, "set_str_attr failed");

    success = set_int_attr(candy_t, "int", 1);
    cr_assert_eq(success, 0, "set_int_attr failed");

    success = save_item(candy_t, candy);

    cr_assert_eq(success, 0, "save_item failed %d", success);
    cr_assert_str_eq(candy->item_id, "1234", "save_item: saving item_id failed");
    cr_assert_str_eq(candy->short_desc, "salt water taffy",
		     "save_item: saving short_desc failed");
    cr_assert_str_eq(candy->long_desc, "glues mouth shut",
		     "save_item: saving long_desc failed");
    cr_assert_eq(candy->attributes_len, 5,
		 "save_item: saving the attributes_len failed %d", candy->attributes_len);

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
    cr_assert_not_null(room_t, "room_t is null in save_room");
    item_t *ramen_t;
    char *i_item_id = "1234";
    char *i_short_desc = "cup ramen";
    char *i_long_desc = "has already been eaten";

    // item_new is a function in game-states's item.h. It creates an item_t struct.
    ramen_t = item_new(i_item_id, i_short_desc, i_long_desc);
    cr_assert_not_null(ramen_t, "ramen_t is null in save_room");

    item_t *shirt_t;
    char *s_item_id = "5678";
    char *s_short_desc = "shirt";
    char *s_long_desc = "looks unwashed";

    // item_new is a function in game-states's item.h. It creates an item_t struct.
    shirt_t = item_new(s_item_id, s_short_desc, s_long_desc);
    cr_assert_not_null(shirt_t, "shirt_t is null in save_room");

    int succ;
    succ = add_item_to_room(room_t, ramen_t);
    cr_assert_eq(succ, 0, "save_room failed");
    succ = add_item_to_room(room_t, shirt_t);
    cr_assert_eq(succ, 0, "save_room failed");

    Room *dorm = malloc(sizeof(Room));
    succ = save_room(room_t, dorm);
    cr_assert_eq(succ, 0, "save_room failed");
    cr_assert_str_eq(dorm->room_id, "5", "save_room: saving room_id failed");
    cr_assert_str_eq(dorm->short_desc, "college dorm",
     "save_room: saving short_desc failed");
    cr_assert_str_eq(dorm->long_desc, "there are clothes and empty ramen cups everywhere",
                                   "save_room: saving long_desc failed");
    cr_assert_eq(dorm->items_len, 2,
		 "save_item: saving the items_len failed %d", dorm->items_len);

    free(dorm);
}


Test(save, player)
{
    player_t *player_t;

    /* player_new is a function in game-states's player.h. 
     * It creates a player_t struct.
     */
    player_t = player_new("Chad", 1);

    int success = change_level(player_t, 8999);
    cr_assert_eq(success, 9000, "change_level() failed %d", success);
    success = change_xp(player_t, 50);
    cr_assert_eq(success, 50, "change_xp() failed, %d", success);

    item_t *candy_t;
    char *item_id = "1234";
    char *short_desc = "salt water taffy";
    char *long_desc = "glues mouth shut";

    // item_new is a function in game-states's item.h. It creates an item_t struct.
    candy_t = item_new(item_id, short_desc, long_desc);
    cr_assert_not_null(candy_t, "candy_t is null");
    success = add_item_to_player(player_t, candy_t);
    cr_assert_eq(success, 0, "add_item_to_player() failed");

    item_t *sword_t;
    char *s_item_id = "6666";
    char *s_short_desc = "katana";
    char *s_long_desc = "the blade of Jarvis";

    // item_new is a function in game-states's item.h. It creates an item_t struct.
    sword_t = item_new(s_item_id, s_short_desc, s_long_desc);
    cr_assert_not_null(sword_t, "sword_t is null");
    success = add_item_to_player(player_t, sword_t);
    cr_assert_eq(success, 0, "add_item_to_player() failed");

    item_t *bag_t;
    char *b_item_id = "0000";
    char *b_short_desc = "backpack";
    char *b_long_desc = "empty bag with nothing in it";

    // item_new is a function in game-states's item.h. It creates an item_t struct.
    bag_t = item_new(b_item_id, b_short_desc, b_long_desc);
    cr_assert_not_null(bag_t, "bag_t is null");
    success = add_item_to_player(player_t, bag_t);
    cr_assert_eq(success, 0, "add_item_to_player() failed");

    item_t *shield_t;
    char *sh_item_id = "9999";
    char *sh_short_desc = "wooden shield";
    char *sh_long_desc = "looks worn and could break any moment";
    
    // item_new is a function in game-states's item.h. It creates an item_t struct.
    shield_t = item_new(sh_item_id, sh_short_desc, sh_long_desc);
    cr_assert_not_null(shield_t, "shield_t is null");
    success = add_item_to_player(player_t, shield_t);
    cr_assert_eq(success, 0, "add_item_to_player() failed");
    
    
    Player *chad = malloc(sizeof(Player));
    success = save_player(player_t, chad);

    item_list_t *inventory = get_all_items_in_inventory(player_t);
    item_t *item_t = inventory->item;

    cr_assert_eq(success, 0, "save_player failed");
    cr_assert_eq(chad->health, 1, "save_player: saving health failed");
    cr_assert_str_eq(chad->player_id, "Chad", "save_player: saving player_id failed");
    cr_assert_eq(chad->xp, 50, "save_player: saving xp failed");
    cr_assert_eq(chad->level, 9000, "save_player: saving level failed");
    cr_assert_eq(chad->inventory[0]->item_id, item_t->item_id, "save_player: saving item failed");
    cr_assert_eq(chad->inventory[0]->short_desc, item_t->short_desc, "save_player: saving item failed");
    cr_assert_eq(chad->inventory[0]->long_desc, item_t->long_desc, "save_player: saving item failed");
    cr_assert_eq(chad->inventory_len, 4, "save_player: saving inventory_len failed");
  
    free(chad);
}


Test(save, game)
{
    // game_new is a function in game-states's game.h. It creates a game_t struct.
    game_t *game_t = game_new("Welcome to Chiventure!");
    
    room_t *dungeon_t;
    room_t *room_t;
    char *room_id = "5";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";

    // room_new is a function in game-states's room.h. It creates a room_t struct.
    room_t = room_new(room_id, short_desc, long_desc);
    cr_assert_not_null(room_t, "room_t is null in save_game");

    char *d_room_id = "2";
    char *d_short_desc = "dungeon";
    char *d_long_desc = "there are skull and bones in all the jail cells";

    int succ;
    succ = add_room_to_game(game_t, room_t);
    cr_assert_eq(succ, 0, "add_room_to_game failed");
    
    // room_new is a function in game-states's room.h. It creates a room_t struct.
    dungeon_t = room_new(d_room_id, d_short_desc, d_long_desc);
    cr_assert_not_null(dungeon_t, "room_t is null in save_room");

    succ = add_room_to_game(game_t, dungeon_t);
    cr_assert_eq(succ, 0, "add_room_to_game failed");

    player_t *player_t;

    /* player_new is a function in game-states's player.h. 
     * It creates a player_t struct.
     */
    player_t = player_new("Chad", 1);
    cr_assert_not_null(player_t, "player_t is null in save_game");

    succ = add_player_to_game(game_t, player_t);
    cr_assert_eq(succ, 0, "add_player_to_game failed");
    
    set_curr_player(game_t, player_t);
    cr_assert_str_eq(game_t->curr_player->player_id, "Chad", "curr_player not set in game");    

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
    cr_assert_eq(game->rooms_len, 2, "save_game: saving rooms_len failed");
    cr_assert_str_eq(game->all_rooms[0]->room_id, "5",
                  "save_game: saving room_id failed");
    cr_assert_str_eq(game->all_rooms[0]->short_desc, "college dorm",
                  "save_game: saving short_desc failed");
    cr_assert_str_eq(game->all_rooms[0]->long_desc,
                  "there are clothes and empty ramen cups everywhere",
                  "save_game: saving long_desc failed");

    free(game);
}
