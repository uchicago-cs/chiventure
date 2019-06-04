#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load.h"
#include "game.h"

Test(load, item)
{
    Item *candy = malloc(sizeof(Item));
    candy->item_id = "1234";
    candy->short_desc = "salt water taffy";
    candy->long_desc = "glues mouth shut";

    item_t *candy_t = malloc(sizeof(item_t));

    int success = load_item(candy, candy_t);

    cr_assert_eq(success, 0, "save_item failed");
    cr_assert_eq(candy_t->item_id, "1234", "load_item: loading item_id failed");
    cr_assert_eq(candy_t->short_desc, "salt water taffy",
		 "load_item: loading short_desc failed");
    cr_assert_eq(candy_t->long_desc, "glues mouth shut",
		 "load_item: loading long_desc failed");
}

Test(load, room)
{
    Room *dorm = malloc(sizeof(Room));
    dorm->room_id = "5";
    dorm->short_desc = "college dorm";
    dorm->long_desc = "there are clothes and empty ramen cups everywhere";

    Item **items = malloc(sizeof(Item*) * 2);
    items[0] = malloc(sizeof(Item));
    items[0]->item_id = "1234";
    items[0]->short_desc = "cup ramen";
    items[0]->long_desc = "has already been eaten";
    items[1] = malloc(sizeof(Item));
    items[1]->item_id = "1234";
    items[1]->item_id = "4321";
    items[1]->short_desc = "black sweatshirt";
    items[1]->long_desc = "wrinkled and probably needs to be washed";
    dorm->items = items;

    item_t** all_items = malloc(sizeof(item_t*) * 3);
    int itemsucc;
    for(int i = 0; i < 2; i++){
        all_items[i] = malloc(sizeof(item_t));
        itemsucc = load_item(items[i], all_items[i]);
        cr_assert_eq(itemsucc, 0,
                     "load_item: loading item %d in load_room failed", i);
    }
    Item *candy = malloc(sizeof(Item));
    candy->item_id = "1234";
    candy->short_desc = "salt water taffy";
    candy->long_desc = "glues mouth shut";
    all_items[2] = malloc(sizeof(item_t));
    itemsucc = load_item(candy, all_items[2]);
    cr_assert_eq(itemsucc, 0, "load_item: loading item 2 in load_room failed");

    room_t* room_t = malloc(sizeof(room_t));
    int succ = load_room(dorm, room_t, all_items, 3);

    cr_assert_eq(succ, 0, "load_room failed");
    cr_assert_eq(room_t->room_id, "5", "load_room: loading room_id failed");
    cr_assert_eq(room_t->short_desc, "college dorm",
		 "load_room: loading short_desc failed");
    cr_assert_eq(room_t->long_desc,
		 "there are clothes and empty ramen cups everwhere",
		 "load_room: loading long_desc failed");
    /* We potentially need to talk to game-state about a function that let's us
     * check the contents of the item hashtable within a room.
     */
}

Test(load, player)
{
    Player *chad = malloc(sizeof(Player));
    chad->health = 1;

    Item **items = malloc(sizeof(Item*) * 2);
    items[0] = malloc(sizeof(Item));
    items[0]->item_id = "1234";
    items[0]->short_desc = "cup ramen";
    items[0]->long_desc = "has already been eaten";
    items[1] = malloc(sizeof(Item));
    items[1]->item_id = "1234";
    items[1]->item_id = "4321";
    items[1]->short_desc = "black sweatshirt";
    items[1]->long_desc = "wrinkled and probably needs to be washed";

    item_t** all_items = malloc(sizeof(item_t*) * 3);
    int itemsucc;
    for(int i = 0; i < 2; i++){
        all_items[i] = malloc(sizeof(item_t));
        itemsucc = load_item(items[i], all_items[i]);
        cr_assert_eq(itemsucc, 0,
                     "load_item: loading item %d in load_room failed", i);
    }
    Item *candy = malloc(sizeof(Item));
    candy->item_id = "1234";
    candy->short_desc = "salt water taffy";
    candy->long_desc = "glues mouth shut";
    all_items[2] = malloc(sizeof(item_t));
    itemsucc = load_item(candy, all_items[2]);
    cr_assert_eq(itemsucc, 0, "load_item: loading item 2 in load_room failed");

    Item **inventory = malloc(sizeof(Item*) * 1);
    inventory[0] = malloc(sizeof(Item));
    inventory[0] = candy;
    chad->inventory = inventory;

    player_t *player_t = malloc(sizeof(player_t));

    int success = load_player(chad, player_t, all_items, 3);

    cr_assert_eq(success, 0, "load_player failed");
    cr_assert_eq(player_t->health, 1, "load_player: loading health failed");
}

Test(load, game)
{
    Game *game = malloc(sizeof(Game));
    game->curr_room = "5";
    game->curr_player = "chad";

    Room **all_rooms = malloc(sizeof(Room*) *2);
    all_rooms[0] = malloc(sizeof(Room));
    all_rooms[0]->room_id = "5";
    all_rooms[0]->short_desc = "college dorm";
    all_rooms[0]->long_desc = "there are clothes and empty ramen cups everywhere";
    Item **items1 = malloc(sizeof(Item*) *1);
    items1[0] = malloc(sizeof(Item));
    items1[0]->item_id = "1234";
    items1[0]->short_desc = "cup ramen";
    items1[0]->long_desc = "has already been eaten";
    all_rooms[0]->items = items1;
    all_rooms[1] = malloc(sizeof(Room));
    all_rooms[1]->room_id = "10";
    all_rooms[1]->short_desc = "lecture hall";
    all_rooms[1]->long_desc = "where students come to sleep";
    Item **items2 = malloc(sizeof(Item*) *1);
    items2[0] = malloc(sizeof(Item));
    items2[0]->item_id = "420";
    items2[0]->short_desc = "pen";
    items2[0]->long_desc = "writes in black ink";
    all_rooms[1]->items = items2;
    game->all_rooms = all_rooms;

    game->all_players[0]->health = 1;

    game_t *g_t = malloc(sizeof(game_t));
    int success = load_game(game, g_t);

    cr_assert_eq(success, 0, "load_game failed");
    cr_assert_eq(g_t->curr_room, "5", "load_game: loading curr_room failed");
    cr_assert_eq(g_t->curr_player, "chad", "load_game: loading curr_player failed");
    // need hashtable searching options to check all_players and all_rooms
}
