#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "load.h"

Test(load, attribute_value)
{

}

Test(load, attribute)
{

}

Test(load, item)
{
    item_t *candy_t;
    char *item_id = "1234";
    char *short_desc = "salt water taffy";
    char *long_desc = "glues mouth shut";
    // game-state's function
    candy_t = item_new(item_id, short_desc, long_desc);

    Item *candy;

    int success = load_item(candy, candy_t);

    cr_assert_eq(success, 0, "save_item failed");
    cr_assert_eq(candy->item_id, "1234", "save_item: saving item_id failed");
    cr_assert_eq(candy->short_desc, "salt water taffy", "save_item: saving short_desc failed");
    cr_assert_eq(candy->long_desc, "glues mouth shut", "save_item: saving long_desc failed");
    // we'll test attributes when its finished
}

Test(load, condition)
{

}

Test(load, path)
{

}

Test(load, room)
{

}

Test(load, player)
{

}

Test(load, game)
{

}
Test(save, item)
{
    item_t *candy_t;
    char *item_id = "1234";
    char *short_desc = "salt water taffy";
    char *long_desc = "glues mouth shut";
    // game-state's function
    candy_t = item_new(item_id, short_desc, long_desc);

    Item *candy;

    int success = save_item(candy_t, candy);

    cr_assert_eq(success, 0, "save_item failed");
    cr_assert_eq(candy->item_id, "1234", "save_item: saving item_id failed");
    cr_assert_eq(candy->short_desc, "salt water taffy", "save_item: saving short_desc failed");
    cr_assert_eq(candy->long_desc, "glues mouth shut", "save_item: saving long_desc failed");
    // we'll test attributes when its finished
}


Test(save, condition)
{
    condition_t *cond_t;
    char *item_id = "1234";
    cond_t->item_id = item_id;
    // expected_attribute component of condition hasn't been pushed by game-state

    Condition *cond;

    int success = save_condition(cond_t, cond);
    cr_assert_eq(success, 0, "save_condition failed");
    cr_assert_eq(cond->item_id, "1234", "save_condition: saving item_id failed");

    //

}


Test(save, path)
{
    path_t *path_t;
    char *room_id = "1234";
    path_t = path_new(room_id);

    // save.c no longer stores Condition inside a path

    Path *path;

    int success = save_path(path_t, path);

    cr_assert_eq(success, 0, "save_path failed");
    cr_assert_eq(path->room_id, "1234", "save_path: saving room_id failed");
}

Test(save, room)
{
    room_t *room_t;
    char *room_id = "5";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    room_t = room_new(room_id, short_desc, long_desc);

    item_t *ramen_t;
    char *i_item_id = "1234";
    char *i_short_desc = "cup ramen";
    char *i_long_desc = "has already been eaten";
    // game-state's function
    ramen_t = item_new(item_id, short_desc, long_desc);

    path_t *path_t;
    path_t = path_new("4")

    int item_succ = add_item_to_room(room_t, ramen_t);
    int path_succ = add_path_to_room(room_t, path_t);

    Room *dorm;
    int succ = save_room(room_t, dorm);

    cr_assert_eq(success, 0, "save_room failed");
    cr_assert_eq(dorm->room_id, "5", "save_room: saving room_id failed");
    cr_assert_eq(dorm->short_desc, "college dorm", "save_room: saving short_desc failed");
    cr_assert_eq(dorm->long_desc, "there are clothes and empty ramen cups everwhere",
                                        "save_room: saving long_desc failed");
    // will check items and paths when jarvis finishes
}

Test(save, player)
{
    player_t *player_t;
    player_t = player_new(1);

    Player *chad;

    int success = save_player(player_t, chad);

    cr_assert_eq(success, 0, "save_player failed");
    cr_assert_eq(chad->health, 1, "save_player: saving health failed");
}

Test(save, game)
{
    game_t *game_t = game_new();


    room_t *room_t;
    char *room_id = "5";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    room_t = room_new(room_id, short_desc, long_desc);
    int room_succ = add_room_to_game(game_t, room_t);

    player_t *player_t;
    player_t = player_new(1);
    player_t->player_id = "Chad";
    int player_succ = add_player_to_game(game_t, player_t);
    int player_set = set_curr_player(game_t, player_t);

    game_t->curr_room = "1234"; // no set_curr_room function
    game_t->curr_player = "Chad";
    game_t->time_start = 1234;

    Game *gama
    int success = save_game(game_t, game);

    cr_assert_eq(success, 0, "save_game failed");
    cr_assert_eq(game->curr_room, "1234", "save_game: saving curr_room failed");
    cr_assert_eq(game->curr_player, "Chad", "save_game: saving curr_player failed");

   // wait for hashtable stuff

}
