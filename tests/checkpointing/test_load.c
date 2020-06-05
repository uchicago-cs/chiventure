#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "checkpointing/load.h"
#include "game-state/item.h"
#include "load-int.h"
#include "game.pb-c.h"


Test(load, item)
{
    Item *candy = malloc(sizeof(Item));
    candy->item_id = "1234";
    candy->short_desc = "salt water taffy";
    candy->long_desc = "glues mouth shut";

    item_t *candy_t = malloc(sizeof(item_t));

    int success = load_item(candy, candy_t);

    cr_assert_eq(success, 0, "save_item failed");
    cr_assert_str_eq(candy_t->item_id, "1234", "load_item: loading item_id failed");
    cr_assert_str_eq(candy_t->short_desc, "salt water taffy",
		 "load_item: loading short_desc failed");
    cr_assert_str_eq(candy_t->long_desc, "glues mouth shut",
		 "load_item: loading long_desc failed");
}

Test(load, room)
{
    Room *dorm = malloc(sizeof(Room));
    dorm->room_id = "5";
    dorm->short_desc = "college dorm";
    dorm->long_desc = "there are clothes and empty ramen cups everywhere";

    Item **items = malloc(sizeof(Item*) * 3);
    items[0] = malloc(sizeof(Item));
    items[0]->item_id = "1234";
    items[0]->short_desc = "cup ramen";
    items[0]->long_desc = "has already been eaten";
    items[1] = malloc(sizeof(Item));
    items[1]->item_id = "4321";
    items[1]->short_desc = "black sweatshirt";
    items[1]->long_desc = "wrinkled and probably needs to be washed";
    items[2] = malloc(sizeof(Item));
    items[2]->item_id = "5678";
    items[2]->short_desc = "salt water taffy";
    items[2]->long_desc = "glues mouth shut";
    dorm->items = items;

    item_t** all_items = malloc(sizeof(item_t*) * 3);
    int itemsucc;
    for(int i = 0; i < 3; i++){
        all_items[i] = malloc(sizeof(item_t));
        itemsucc = load_item(items[i], all_items[i]);
        cr_assert_eq(itemsucc, 0,
                     "load_item: loading item %d in load_room failed", i);
    }

    room_t room_t = {0};

    int succ = load_room(dorm, &room_t, all_items, 3);

    cr_assert_eq(succ, 0, "load_room failed");

    cr_assert_str_eq(room_t.room_id, "5", "load_room: loading room_id failed");

    cr_assert_str_eq(room_t.short_desc, "college dorm",
		 "load_room: loading short_desc failed");

    cr_assert_str_eq(room_t.long_desc,
		 "there are clothes and empty ramen cups everywhere",
		 "load_room: loading long_desc failed");

    /* We potentially need to talk to game-state about a function that let's us
     * check the contents of the item hashtable within a room.
     */

}

Test(load, player)
{
    Player *chad = malloc(sizeof(Player));
    chad->health = 1;
    chad->player_id = "Chad";
    
    Item **items = malloc(sizeof(Item*) * 2);
    items[0] = malloc(sizeof(Item));
    items[0]->item_id = "1234";
    items[0]->short_desc = "cup ramen";
    items[0]->long_desc = "has already been eaten";
    items[1] = malloc(sizeof(Item));
    items[1]->item_id = "4321";
    items[1]->short_desc = "black sweatshirt";
    items[1]->long_desc = "wrinkled and probably needs to be washed";
    items[2] = malloc(sizeof(Item));
    items[2]->item_id = "1324";
    items[2]->short_desc = "salt water taffy";
    items[2]->long_desc = "glues mouth shut";
    chad->inventory = items;

    item_t** all_items = malloc(sizeof(item_t*) * 3);
    int itemsucc;
    for(int i = 0; i < 3; i++){
        all_items[i] = malloc(sizeof(item_t));
        itemsucc = load_item(items[i], all_items[i]);
        cr_assert_eq(itemsucc, 0,
                     "load_item: loading item %d in load_player failed", i);
    }


    Item **inventory = malloc(sizeof(Item*) * 2);
    inventory[0] = malloc(sizeof(Item));
    inventory[0] = items[0];
    inventory[1] = malloc(sizeof(Item));
    inventory[1] = items[1];
    chad->inventory = inventory;

    player_t *player_t = malloc(sizeof(player_t));

    int success = load_player(chad, player_t, all_items, 3);

    cr_assert_eq(success, 0, "load_player failed");
    cr_assert_eq(player_t->health, 1, "load_player: loading health failed");
}

Test(load, game)
{
    Game *game = malloc(sizeof(Game));
    game__init(game);
    
    game->curr_room = "5";
    game->curr_player = "chad";

    Room **all_rooms = malloc(sizeof(Room*) *2);
    all_rooms[0] = malloc(sizeof(Room));
    room__init(all_rooms[0]);
    
    all_rooms[0]->room_id = "5";
    all_rooms[0]->short_desc = "college dorm";
    all_rooms[0]->long_desc = "there are clothes and empty ramen cups everywhere";
    Item **items1 = malloc(sizeof(Item*) * 2);
    items1[0] = malloc(sizeof(Item));
    item__init(items1[0]);
    
    items1[0]->item_id = "1234";
    items1[0]->short_desc = "cup ramen";
    items1[0]->long_desc = "has already been eaten";

    items1[1] = malloc(sizeof(Item));
    item__init(items1[1]);
    
    items1[1]->item_id = "6666";
    items1[1]->short_desc = "sword";
    items1[1]->long_desc = "blade of Jarvis";

    all_rooms[0]->items = items1;
    all_rooms[0]->items_len = 2;
    all_rooms[0]->n_items = 2;
    
    all_rooms[1] = malloc(sizeof(Room));
    room__init(all_rooms[1]);
    
    all_rooms[1]->room_id = "10";
    all_rooms[1]->short_desc = "lecture hall";
    all_rooms[1]->long_desc = "where students come to sleep";
    Item **items2 = malloc(sizeof(Item*) *1);
    items2[0] = malloc(sizeof(Item));
    item__init(items2[0]);
    
    items2[0]->item_id = "420";
    items2[0]->short_desc = "pen";
    items2[0]->long_desc = "writes in black ink";
    all_rooms[1]->items = items2;
    all_rooms[1]->items_len = 1;
    all_rooms[1]->n_items = 1;
    
    game->all_rooms = all_rooms;
    game->rooms_len = 2;
    game->n_all_rooms = 2;

    Player *player1 = malloc(sizeof(Player));

    player__init(player1);
    player1->player_id = "chad";
    player1->health = 1;
    game->all_players = &player1;
    game->players_len = 1;
    game->n_all_players = 1;


    // Start creating our game

    game_t *g_t = game_new("Welcome to my fun lair\n");

    room_t *room0 = room_new("5", "college dorm", "there are clothes and empty ramen cups everywhere");

    int success = add_room_to_game(g_t, room0);
    if (success != 0) {
      fprintf(stderr, "Failed to add room to game \n");
    }
    
    item_t *item1 = item_new("1234", "cup ramen", "ready to eat");
    item_t *item2 = item_new("6666", "sword", "blade of Sheryl");

    success = add_item_to_room(room0, item1);
    if (success != 0) {
      fprintf(stderr, "Failed to add item to room \n");
    }

    success = add_item_to_room(room0, item2);
    if (success != 0) {
      fprintf(stderr, "Failed to add item to room \n");
    }

    
    room_t *room1 = room_new("10", "lecture only", "where students party");
    
    success = add_room_to_game(g_t, room1);
    if (success != 0) {
      fprintf(stderr, "Failed to add room to game \n");
    }
    
    item_t *item3 = item_new("420", "pencil", "writes in blue ink");
    
    success = add_item_to_room(room1, item3);
    if (success != 0) {
      fprintf(stderr, "Failed to add item to room \n");
    }
    
    player_t *player1_t= player_new("chad", 1);

    success = add_player_to_game(g_t, player1_t);
    if (success != 0) {
      fprintf(stderr, "Failed to add player to game \n");
    }
    
    g_t->curr_room = room1;
    g_t->curr_player = player1_t;

    success = load_game(game, g_t);

    cr_assert_eq(success, 0, "load_game failed");
    cr_assert_str_eq(g_t->curr_room->room_id, "5", "load_game: loading curr_room failed %s", g_t->curr_room->room_id);
    cr_assert_str_eq(g_t->curr_player->player_id, "chad", "load_game: loading curr_player failed");
    // need hashtable searching options to check all_players and all_rooms
    room_list_t * all_rooms1 = get_all_rooms(g_t);
    int count_r = 0;
    for (; all_rooms1 != NULL; all_rooms1 = all_rooms1->next) {
      count_r += 1;
    }
    cr_assert_eq(count_r, 2, "load_game: wrong number of rooms %d", count_r);
    
}
