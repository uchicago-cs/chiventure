#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"
#include "save.h"

int save_attribute_value(attribute_value_t *av_t, Attributevalue *av)
{
    if (av_t == NULL) {
	fprintf(stderr, "Given a NULL attribute_value struct in save_attribute_value");
	return -1;
    }

    if (av->has_double_val == 1){
      av->double_val = av_t->double_val;
    } else {
      av->double_val = -1.0;
    }
    av->char_val = av_t->char_val;
    
    av->bool_val = av_t->bool_val;
    
    if (av_t->str_val == NULL) {
	av->str_val = NULL;
    } else {
	av->str_val = av_t->str_val;
    }

    av->int_val = av_t->int_val;
    
    return 0;
}

int save_attribute(attribute_t *a_t, Attribute *a)
{
    if (a_t == NULL) {
	fprintf(stderr, "Given a NULL attribute struct in save_attribute");
	return -1;
    }

    a->attribute_key = a_t->attribute_key;

    if (a_t->attribute_tag == DOUBLE) {
	a->attribute_tag = "DOUBLE";
    } else if (a_t->attribute_tag == BOOLE) {
	a->attribute_tag = "BOOLE";
    } else if (a_t->attribute_tag == CHARACTER) {
	a->attribute_tag = "CHARACTER";
    } else if (a_t->attribute_tag == STRING) {
	a->attribute_tag = "STRING";
    } else {
	a->attribute_tag = "INTEGER";
    }

    save_attribute_value(&(a_t->attribute_value), a->attribute_value);

    return 0;
}


int save_item(item_t *i_t, Item *i)
{
    if (i_t == NULL) {
	fprintf(stderr, "Given a NULL item struct in save_item");
	return -1;
    }

    i->item_id = i_t->item_id;

    if (i_t->short_desc == NULL) {
	i->short_desc = NULL;
    } else {
	i->short_desc = i_t->short_desc;
    }

    if (i_t->long_desc == NULL) {
	i->long_desc = NULL;
    } else {
	i->long_desc = i_t->long_desc;
    }

    // bool condition reserved for future expansion

    // repeated Attribute HERE

    // go through array and figure out length
    // save this as i->attributes_len
    return 0;
}

int save_condition(condition_t *c_t, Condition *c)
{
    if (c_t == NULL) {
	fprintf(stderr, "Given a NULL condition struct in save_condition");
	return -1;
    }

    if (c_t->item->item_id == NULL) {
	c->item_id = NULL;
    } else {
	c->item_id = c_t->item->item_id;
    }

    // possibly expected_attribute here
    /*if (c_t->attribute == NULL) {
	c->attribute = NULL;
    } else {
	c->attribute = c_t->attribute;
	}*/

    //optional Attribute here, but might change
    return 0;
}

int save_path(path_t *p_t, Path *p)
{
    if (p_t == NULL) {
	fprintf(stderr, "Given a NULL path struct in save_path");
	return -1;
    }

    if (p_t->direction == NULL) {
	p->direction = NULL;
    } else {
	p->direction = p_t->direction;
    }

    if (p_t->dest == NULL) {
	p->dest = NULL;
    } else {
	p->dest = p_t->dest;
    }

    // repeated Condition HERE

    // go through array and figure out the length
    // save this as p->conditions_len
    return 0;
}

int save_room(room_t *r_t, Room *r)
{
    if (r_t == NULL) {
	fprintf(stderr, "Given a room_t struct that is NULL in save_room.\n");
	return -1;
    }
  
    r->room_id = r_t->room_id;
  
    if (r_t->short_desc == NULL) { 
	r->short_desc = NULL;
    } else {
	r->short_desc = r_t->short_desc;
    }
  
    if (r_t->long_desc == NULL) {
	r->long_desc = NULL;
    } else {
	r->long_desc = r_t->long_desc;
    }
    // this is a hash table and may have to be redone!!
    /*
    r->items_len = r_t->items_len;

    int len = r_t->items_len;

    Item **items;
    
    r->n_items = len;

    items = malloc(sizeof(Item*) * len); 
    for (int i = 0; i < len; ++i) {
	items[i] = malloc(sizeof(Item));
	item__init(items[i]);
	int transfer_item_success = save_item(r_t->items[i], items[i]);
    }

    r->items = items;
    */

    // path stuff here!!!
    
    return 0;
}

int save_player(player_t *p_t, Player *p)
{
    if (p_t == NULL) {
	fprintf(stderr, "Given a player_t struct that is NULL in save_player.\n");
	return -1;
    }
  
    p->player_id = p_t->player_id;
  
    if (p_t->level == NULL) {
	p->level = NULL;
    } else {
	p->level = p_t->level;
    }
  
    if (p_t->health == NULL) {
	p->health = NULL;
    } else {
	p->health = p_t->health;
    }

    if (p_t->xp == NULL) {
	p->xp = NULL;
    } else {
	p->xp = p_t->xp;
    }

    // inventory is a has table; this may been to be redone!!

    /*    p->inventory_len = p_t->inventory_len;

    int i_len = p_t->inventory_len;

    Object **inventory;
  
    p->n_inventory = i_len;

    inventory = malloc(sizeof(Object*) * i_len);
    int inventory_success = 1;
    for (int i = 0; i < i_len; i++) {
	inventory[i] = malloc(sizeof(Object));
	object__init(inventory[i]);
	inventory_success = save_object(p_t->inventory[i], inventory[i]);
    }

    p->inventory = inventory;
    */
    return 0;
}

int save_game(game_t *g_t, Game *g)
{
    if(g_t == NULL){
	fprintf(stderr, "Given a game_t struct that is NULL in save_game.\n");
	return -1;
    }
    
    g->players_len = g_t->players_len;

    // repeated all_players here!!!!!    
    /*
    int p_len = g_t->players_len;
  
    g->n_players = p_len;

    Player **players;
    players = malloc(sizeof(Player*) * p_len);
    int player_success = 1;
    for (int i = 0; i < p_len; i++){
	players[i] = malloc(sizeof(Player));
	player__init(players[i]);

	if (g_t->players[i]->level != -1){
	    players[i]->has_level = 1;
	}
    
	if (g_t->players[i]->health != -1){
	    players[i]->has_health = 1;
	}
    
	if (g_t->players[i]->xp != -1){
	    players[i]->has_xp = 1;
	}
    
	player_success = save_player(g_t->players[i], players[i]);
    }
  
    g->players = players;
    */
    // repeated all_rooms here!!!!!!!

    g->rooms_len = g_t->rooms_len;
    /*
    int r_len = g_t->rooms_len;
  
    Room **rooms;
  
    g->n_rooms = r_len;
    
    rooms = malloc(sizeof(Room*) * r_len);
    int room_success = 1;
    for (int j = 0; j < r_len; j++){
	rooms[j] = malloc(sizeof(Room));
	room__init(rooms[j]);
	room_success = save_room(g_t->rooms[j], rooms[j]);
    }

    g->rooms = rooms;
    */
    if (g_t->curr_room == NULL) {
	g->curr_room = NULL;
    } else {
	g->curr_room = g_t->curr_room;
    }
  
    if (g_t->curr_player == NULL) {
	g->curr_player = NULL;
    } else {
	g->curr_player = g_t->curr_player;
    }
    
    return 0;
}

int write_to_file(char *filename, uint8_t *buffer, unsigned len)
{
    int res = 0;
    FILE *fp = fopen(filename, "w");
    fwrite(buffer, len, 1,fp);
    fclose(fp);
    return res;
}

int save(game_t *g_t, char *filename)
{
    Game g = GAME__INIT;
    void *buf;
    size_t len;
    int success;

    success = save_game(g_t, &g);
    len = game__get_packed_size(&g);
    buf = malloc(len);
    game__pack(&g, buf);

    fprintf(stderr, "Writing %ld serialized bytes\n", len);    

    write_to_file(filename, buf, len);
    
    free(buf);
    return 0;
}
