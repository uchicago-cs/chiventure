#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"
#include "save.h"
#include "game.h"

// attribute not quite figured out
Test(save, attribute_value)
{
    attribute_value_t *d_t;
    attribute_value_t *c_t;
    attribute_value_t *b_t;
    attribute_value_t *s_t;
    attribute_value_t *i_t;

    d_t->double_val = 2.5;
    c_t->char_val = 'T';
    b_t->bool_val = true;
    s_t->str_val = "string";
    i_t->int_val = 5;

    Attribute_value *d;
    attribute_value__init(d);
    Attribute_value *c;
    attribute_value__init(c);
    Attribute_value *b;
    attribute_value__init(b);
    Attribute_value *s;
    attribute_value__init(s);
    Attribute_value *i;
    attribute_value__init(i);

    int success;
    success = save_attribute_value(d_t, d);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(d->has_double_val, 1, "save_attribute_value failed to save has_double");
    cr_assert_eq(d->double_val, 2.5, "save_attribute_value failed to save double");

    success = save_attribute_value(c_t, c);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(c->char_val, 'T', "save_attribute_value failed to save char");
    
    success = save_attribute_value(b_t, b);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(b->has_bool_val, 1,"save_attribute_value failed to save has_bool");
    cr_assert_eq(b->bool_val, true,"save_attribute_value failed to save bool");

    success = save_attribute_value(s_t, s);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(s->str_val, "string",  "save_attribute_value failed to save string");

    success = save_attribute_value(i_t, i);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(i->has_int_val, 1,  "save_attribute_value failed to save has_int");
    cr_assert_eq(i->int_val, 5,  "save_attribute_value failed to save int");
    
}

Test(save, attribute)
{
    attribute_value_t *dv_t;
    attribute_value_t *cv_t;
    attribute_value_t *bv_t;
    attribute_value_t *sv_t;
    attribute_value_t *iv_t;

    dv_t->double_val = 2.5;
    cv_t->char_val = 'T';
    bv_t->bool_val = true;
    sv_t->str_val = "string";
    iv_t->int_val = 5;


    attribute_t *d_t;
    attribute_t *c_t;
    attribute_t *b_t;
    attribute_t *s_t;
    attribute_t *i_t;

    d_t->attribute_key = "double";
    d_t->attribute_tag = DOUBLE;
    d_t->attribute_value = dv_T;

    c_t->attribute_key = "char";
    c_t->attribute_tag = CHARACTER;
    c_t->attribute_value = cv_T;

    b_t->attribute_key = "bool";
    b_t->attribute_tag = BOOLE;
    b_t->attribute_value = bv_T;

    s_t->attribute_key = "string";
    s_t->attribute_tag = STRING;
    s_t->attribute_value = sv_T;

    i_t->attribute_key = "int";
    i_t->attribute_tag = INTEGER;
    i_t->attribute_value = iv_T;

    
    Attribute *d;
    attribute__init(d);
    Attribute *c;
    attribute__init(c);
    Attribute *b;
    attribute__init(b);
    Attribute *s;
    attribute__init(s);
    Attribute *i;
    attribute__init(i);

    int success;

    success = save_attribute(d_t, d);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(d->attribute_key, "double", "save_attribute_value failed to save attribute_key");
    cr_assert_eq(d->attribute_tag, "DOUBLE", "save_attribute_value failed to save attribute_tag");

    success = save_attribute(c_t, c);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(c->attribute_key, "char", "save_attribute_value failed to save attribute_key");
    cr_assert_eq(c->attribute_tag, "CHARACTER", "save_attribute_value failed to save attribute_tag");
    
    success = save_attribute(b_t, b);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(b->attribute_key, "bool", "save_attribute_value failed to save attribute_key");
    cr_assert_eq(b->attribute_tag, "BOOLE", "save_attribute_value failed to save attribute_tag");

    success = save_attribute(s_t, s);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(s->attribute_key, "string", "save_attribute_value failed to save attribute_key");
    cr_assert_eq(s->attribute_tag, "STRING", "save_attribute_value failed to save attribute_tag");
    
    success = save_attribute(i_t, i);
    cr_assert_eq(success, 0, "save_attribute_value failed");
    cr_assert_eq(i->attribute_key, "int", "save_attribute_value failed to save attribute_key");
    cr_assert_eq(i->attribute_tag, "INTEGER", "save_attribute_value failed to save attribute_tag");
    
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

    int success;
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

    success = save_item(candy_t, candy);
    
    cr_assert_eq(success, 0, "save_item failed");
    cr_assert_eq(candy->item_id, "1234", "save_item: saving item_id failed");
    cr_assert_eq(candy->short_desc, "salt water taffy", "save_item: saving short_desc failed");
    cr_assert_eq(candy->long_desc, "glues mouth shut", "save_item: saving long_desc failed");
    cr_asser_eq(candy->attributes_len, 5, "save_item: saving the attributes_len failed");
    // we'll test attributes when its finished
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

    Game *game
    int success = save_game(game_t, game);

    cr_assert_eq(success, 0, "save_game failed");
    cr_assert_eq(game->curr_room, "1234", "save_game: saving curr_room failed");
    cr_assert_eq(game->curr_player, "Chad", "save_game: saving curr_player failed");
    cr_asser_eq(game->players_len, 1, "save_game: saving players_len failed");
    cr_asser_eq(game->allplayers[0].player_id, "Chad",
		 "save_game: saving player_id failed");
    cr_asser_eq(game->rooms_len, 1, "save_game: saving rooms_len failed");
    cr_asser_eq(game->all_rooms[0].room_id, "5", "save_game: saving room_id failed");
    cr_asser_eq(game->all_rooms[0].short_desc, "college dorm",
		"save_game: saving room_id failed");
    cr_asser_eq(game->all_rooms[0].long_desc,
		"there are clothes and empty ramen cups everywhere",
		"save_game: saving room_id failed");
}
