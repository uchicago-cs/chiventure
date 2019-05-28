#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load.h"
#include "game.h"

Test(load, attribute_value)
{ 
	Attribute_value *d_v;
		d_v->double_val = 2.5;
    Attribute_value *c_v;
		c_v->char_val = 'T';
		Attribute_value *b_v;
		a_v->bool_val = true;
		Attribute_value *s_v;
		s_v->str_val = "string";
		Attribute_value *i_v;
    i_v->int_val = 5;
  
		atttribute_value_t *d_t;
		int succ_d = load_attribute_value(d_v, d_t);
		cr_assert_eq(succ_d, 0, "load_attribute_value failed");
		cr_assert_eq(d_t->double_val, 2.5, "load_attribute_value failed to load double");
  
		atttribute_value_t *c_t;
		int succ_c = load_attribute_value(c_v, c_t);
		cr_assert_eq(succ_c, 0, "load_attribute_value failed");
		cr_assert_eq(c_t->char_val, 'T', "load_attribute_value failed to load char");

		atttribute_value_t *b_t;
		int succ_b = load_attribute_value(b_v, b_t);
		cr_assert_eq(succ_b, 0, "load_attribute_value failed");
		cr_assert_eq(b_t->bool_val, 2.5, "load_attribute_value failed to load bool");
 
		atttribute_value_t *s_t;
		int succ_s = load_attribute_value(s_v, s_t);
		cr_assert_eq(succ_s, 0, "load_attribute_value failed");
		cr_assert_eq(s_t->str_val, "string", "load_attribute_value failed to load string");
  
		atttribute_value_t *i_t;
		int succ_i = load_attribute_value(i_v, i_t);
		cr_assert_eq(succ_i, 0, "load_attribute_value failed");
		cr_assert_eq(i_t->int_val, 5, "load_attribute_value failed to load int");
  
}

Test(load, attribute)
{
		int success;
		attribute_t *test_t;
	Attribute *str;
		Attribute_value *strv;
		str->attribute_key = "string";
		str->attribute_tag = "STRING";
		attribute_value__init(strv);
		strv->str_val = "this is a string";
		str->attribute_value = strv;
		
		success = load_attribute(str, test_t);
		cr_asser_eq(success, 0, "load_attribute failed");
		cr_asser_eq(test->attribute_key, "string",
                "load_attribute failed to load attribute_key");
		cr_asser_eq(test->attribute_tag, STRING,
                "load_attribute failed to load attribute_tag");
		cr_asser_eq(test->attribute_value->str_val, "this is a string",
                "load_attribute failed to load sttribute_value");
  
    Attribute *d; 
		Attribute_value *dv;
		d->attribute_key = "double";
		d->attribute_tag = "DOUBLE";
		attribute_value__init(dv);
		dv->double_val = 2.5;
		d->attribute_value = dv;
		
		success = load_attribute(d, test_t);
		
		cr_asser_eq(success, 0, "load_attribute failed");
		cr_asser_eq(test->attribute_key, "double",
                "load_attribute failed to load attribute_key");
		cr_asser_eq(test->attribute_tag, DOUBLE,
                "load_attribute failed to load attribute_tag");
		cr_asser_eq(test->attribute_value->double_val, 2.5,
                "load_attribute failed to load sttribute_value");
  
		Attribute *c; 
		Attribute_value *cv;
		c->attribute_key = "character";
		c->attribute_tag = "CHARACTER";
		attribute_value__init(cv);
		cv->double_val = 'C';
		c->attribute_value = cv;
		
		success = load_attribute(c, test_t);
		
		cr_asser_eq(success, 0, "load_attribute failed");
		cr_asser_eq(test->attribute_key, "character",
                "load_attribute failed to load attribute_key");
		cr_asser_eq(test->attribute_tag, CHARACTER,
                "load_attribute failed to load attribute_tag");
		cr_asser_eq(test->attribute_value->char_val, 'C',
                "load_attribute failed to load sttribute_value");
  
		Attribute *b; 
		Attribute_value *bv;
		b->attribute_key = "boole";
		b->attribute_tag = "BOOLE";
		attribute_value__init(bv);
		bv->bool_val = true;
		b->attribute_value = bv;
		
		success = load_attribute(b, test_t);
		
		cr_asser_eq(success, 0, "load_attribute failed");
		cr_asser_eq(test->attribute_key, "boole",
                "load_attribute failed to load attribute_key");
		cr_asser_eq(test->attribute_tag, BOOLE,
                "load_attribute failed to load attribute_tag");
		cr_asser_eq(test->attribute_value->bool_val, 'C',
                "load_attribute failed to load sttribute_value");
  
		Attribute *i; 
		Attribute_value *iv;
		i->attribute_key = "integer";
		i->attribute_tag = "INTEGER";
		attribute_value__init(bv);
		iv->int_val = 1;
		i->attribute_value = iv;
		
		success = load_attribute(b, test_t);
		
		cr_asser_eq(success, 0, "load_attribute failed");
		cr_asser_eq(test->attribute_key, "integer",
                "load_attribute failed to load attribute_key");
		cr_asser_eq(test->attribute_tag, INTEGER,
                "load_attribute failed to load attribute_tag");
		cr_asser_eq(test->attribute_value->int_val, 1,
                "load_attribute failed to load sttribute_value");
}


Test(load, item)
{
		Item *candy;
		candy->item_id = "1234";
    candy->short_desc = "salt water taffy";
    candy->long_desc = "glues mouth shut";

    item_t *candy_t;

    int success = load_item(candy, candy_t);

    cr_assert_eq(success, 0, "save_item failed");
    cr_assert_eq(candy_t->item_id, "1234", "load_item: loading item_id failed");
    cr_assert_eq(candy_t->short_desc, "salt water taffy", "load_item: loading short_desc failed");
    cr_assert_eq(candy_t->long_desc, "glues mouth shut", "load_item: loading long_desc failed");
}


Test(load, room)
{
		Room *dorm;
    dorm->room_id = "5";
    dorm->short_desc = "college dorm";
    dorm->long_desc = "there are clothes and empty ramen cups everywhere";

    dorm->items[0]->item_id = "1234";
    dorm->items[0]->short_desc = "cup ramen";
    dorm->items[0]->long_desc = "has already been eaten";

    dorm->paths[0]->dest = "3";

		room_t* room_t;
    int succ = load_room(dorm, room_t);

    cr_assert_eq(success, 0, "load_room failed");
    cr_assert_eq(room_t->room_id, "5", "load_room: loading room_id failed");
    cr_assert_eq(room_t->short_desc, "college dorm", "load_room: loading short_desc failed");
    cr_assert_eq(room_t->long_desc, "there are clothes and empty ramen cups everwhere",
                                        "load_room: loading long_desc failed");
    // will check items and paths when jarvis finishes
}

Test(load, player)
{
    Player *chad;
		chad->health = 1;

		player_t *player_t;
  
    int success = load_player(chad, player_t);

    cr_assert_eq(success, 0, "load_player failed");
    cr_assert_eq(player_t->health, 1, "load_player: loading health failed");
}

Test(load, game)
{

	Game *game;
		game->curr_room = "5";
		game->curr_player = "chad";
		
    game->all_rooms[0]->room_id = "5";
    game->all_rooms[0]->short_desc = "college dorm";
		game->all_rooms[0]->long_desc = "there are clothes and empty ramen cups everywhere";
    game->all_rooms[0]->items[0]->item_id = "1234";
    game->all_rooms[0]->items[0]->short_desc = "cup ramen";
    game->all_rooms[0]->items[0]->long_desc = "has already been eaten";
	game->all_rooms[0]->paths[0]->dest = "3";
  
    game->all_players[0]->health = 1;

    game_t *g_t;
    int success = load_game(game, g_t);

    cr_assert_eq(success, 0, "load_game failed");
    cr_assert_eq(g_t->curr_room, "5", "load_game: loading curr_room failed");
    cr_assert_eq(g_t->curr_player, "chad", "load_game: loading curr_player failed");
   // need hashtable searching options to check all_players and all_rooms
}

 
