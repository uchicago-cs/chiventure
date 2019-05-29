#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"
#include "save.h"


int save_attribute(attribute_t *a_t, Attribute *a)
{
    if (a_t == NULL) {
	fprintf(stderr, "Given a NULL attribute struct in save_attribute");
	return -1;
    }

    a->attribute_key = a_t->attribute_key;

    if (a_t->attribute_tag == DOUBLE) {
	a->attribute_tag = "DOUBLE";
	a->attribute_value->double_val = a_t->attribute_value.double_val;
    } else if (a_t->attribute_tag == BOOLE) {
	a->attribute_tag = "BOOLE";
	a->attribute_value->bool_val = a_t->attribute_value.bool_val;
    } else if (a_t->attribute_tag == CHARACTER) {
	a->attribute_tag = "CHARACTER";
	a->attribute_value->char_val = a_t->attribute_value.char_val;
    } else if (a_t->attribute_tag == STRING) {
	a->attribute_tag = "STRING";
	if (a_t->attribute_value.str_val != NULL){
	    a->attribute_value->str_val = strdup(a_t->attribute_value.str_val);
	} else {
	    a->attribute_value->str_val = NULL;
	}
    } else {
	a->attribute_tag = "INTEGER";
	a->attribute_value->int_val = a_t->attribute_value.int_val;
    }

    return 0;
}


int save_item(item_t *i_t, Item *i)
{
    if (i_t == NULL) {
	fprintf(stderr, "Given a NULL item struct in save_item");
	return -1;
    }

    if (i_t->item_id != NULL){
	i->item_id = i_t->item_id;
    } else {
	i->item_id = NULL;
    }

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

    // Allocate an array of proto Attribute structs
    Attribute **attrs = malloc(sizeof(Attribute*) * (i->attributes_len));
    int iter =0; // Iterator int to track the array

    // Put the hashtable into the array
    attribute_t *curr_attr;
    ITER_ALL_ATTRIBUTES(i_t, curr_attr) {
	attrs[iter] = malloc(sizeof(Attribute));
	attribute__init(attrs[iter]);
	int save_attribute_success = save_attribute(curr_attr, attrs[iter]);
	if (save_attribute_success != 0) {
	    fprintf(stderr, "Attribute saving for item failed \n");
	    return -1;
	}
	iter += 1;
    }

    i->attributes = attrs;

    i->attributes_len = iter;  // Set length of array
    i->n_attributes = iter;  // Set length of array


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
    /* We included codes to store future expected attribute from game state,
     * the code for which has not existed in master yet, so this may change 
     * in the future. We also decided to comment the code out since from
     * our last meeting with Borja,it seems that we don't need to store 
     * the Condition structs. However, I will not delete the code completely
     * until we decide for sure that we won't need it.
     Attribute *expected_attr = malloc(sizeof(Attribute));
     int save_attribute_success =
     save_attribute(c_t->expected_attribute, expected_attr);
     if (save_attribute_success != 0) {
     fprintf(stderr, "Attribute saving failed for condition \n");
     return -1;
     };
     c->expected_attribute = expected_attr;
    */
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


    /* The code below will be commented out since it appears that we don't 
     * need to store the Condition for a path. However, I will not 
     * delete them completely until we know for sure we don't need the code.
     // repeated Condition HERE
     p->conditions_len = COUNT_CONDITIONS(p_t);  // Set length of array
     p->n_conditions = COUNT_CONDITIONS(p_t);  // Set length of array
     // Allocate an array of proto Condition structs
     Condition **conds = malloc(sizeof(Condition*) * (p->conditions_len));
     int iter =0; // Iterator int to track the array
    
     // Put the hashtable into the array
     ITER_ALL_CONDITIONS(p_t, curr_cond){
     conds[iter] = malloc(sizeof(Condition));
     condition__init(conds[iter]);
     int save_condition_success = save_condition(curr_cond, conds[iter]);
     if (save_condition_success != 0) {
     fprintf(stderr, "Condition saving for path failed \n");
     return -1;
     };
     iter += 1;
     };
     p->conditions = conds;
    
    */

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

    // Allocate an array of proto Item structs
    Item **items = malloc(sizeof(Item*) * (r->items_len));
    int iter =0; // Iterator int to track the array

    // Put the hashtable into the array
    item_t *curr_item;
    ITER_ALL_ITEMS_IN_ROOM(r_t, curr_item) {
	items[iter] = malloc(sizeof(Item));
	item__init(items[iter]);
	int save_item_success = save_item(curr_item, items[iter]);
	if (save_item_success != 0) {
	    fprintf(stderr, "Item saving for room failed \n");
	    return -1;
	}
	iter += 1;
    }

    r->items = items;

    r->items_len = iter;  // Set length of array
    r->n_items = iter;  // Set length of array

    // Allocate an array of proto Path structs
    Path **paths = malloc(sizeof(Path*) * (r->paths_len));
    iter =0; // Iterator int to track the array

    // Put the hashtable into the array

    path_t *curr_path;
    ITER_ALL_PATHS(r_t, curr_path) {
	paths[iter] = malloc(sizeof(Path));
	path__init(paths[iter]);
	int save_path_success = save_path(curr_path, paths[iter]);
	if (save_path_success != 0){
	    fprintf(stderr, "Path saving for room failed \n");
	    return -1;
	}
	iter += 1;
    }

    r->paths = paths;

    r->n_paths = iter;  // Set length of array
    r->paths_len = iter;  // Set length of array

    return 0;
}

int save_player(player_t *p_t, Player *p)
{
    if (p_t == NULL) {
	fprintf(stderr, "Given a player_t struct that is NULL in save_player.\n");
	return -1;
    }

    if (p_t->player_id != NULL) {
	p->player_id = p_t->player_id;
    } else {
	p->player_id = NULL;
    }

    p->level = p_t->level;

    p->health = p_t->health;

    p->xp = p_t->xp;

    // Allocate an array of proto Item structs
    Item **items = malloc(sizeof(Item*) * (p->inventory_len));
    int iter =0; // Iterator int to track the array

    // Put the hashtable into the array
    item_t *curr_item;
    ITER_ALL_ITEMS_IN_INVENTORY(p_t, curr_item) {
	items[iter] = malloc(sizeof(Item));
	item__init(items[iter]);
	int save_item_success = save_item(curr_item, items[iter]);
	if (save_item_success != 0){
	    fprintf(stderr, "Item saving for inventory failed \n");
	    return -1;
	}
	iter += 1;
    }

    p->inventory = items;

    p->inventory_len = iter;  // Set length of array
    p->n_inventory = iter;  // Set length of array

    return 0;
}

int save_game(game_t *g_t, Game *g)
{
    if(g_t == NULL){
	fprintf(stderr, "Given a game_t struct that is NULL in save_game.\n");
	return -1;
    }

    // Allocate an array of proto Player structs
    Player **plyrs = malloc(sizeof(Player*) * (g->players_len));
    int iter =0; // Iterator int to track the array

    // Put the hashtable into the array
    player_t *curr_player;
    ITER_ALL_PLAYERS(g_t, curr_player) {
	plyrs[iter] = malloc(sizeof(Player));
	player__init(plyrs[iter]);
	int save_plyr_success = save_player(curr_player, plyrs[iter]);
	if (save_plyr_success != 0){
	    fprintf(stderr, "Player saving for game failed \n");
	    return -1;
	}
	iter += 1;
    }

    g->all_players = plyrs;

    g->players_len = iter;
    g->n_all_players = iter;  // Set length of array


    // repeated all_rooms here!!!!!!!

    // Allocate an array of proto Player structs
    Room **rooms = malloc(sizeof(Room*) * (g->rooms_len));
    iter =0; // Iterator int to track the array

    // Put the hashtable into the array
    room_t *curr_room;
    ITER_ALL_ROOMS(g_t, curr_room) {
	rooms[iter] = malloc(sizeof(Room));
	room__init(rooms[iter]);
	int save_room_success = save_room(curr_room, rooms[iter]);
	if (save_room_success != 0){
	    fprintf(stderr, "Room saving for game failed \n");
	    return -1;
	}
	iter += 1;
    }

    g->all_rooms = rooms;

    g->rooms_len = iter;
    g->n_all_rooms = iter;


    // Save all the other attributes
    if (g_t->curr_room == NULL) {
	g->curr_room = NULL;
    } else {
	g->curr_room = g_t->curr_room->room_id;
    }

    if (g_t->curr_player == NULL) {
	g->curr_player = NULL;
    } else {
	g->curr_player = g_t->curr_player->player_id;
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
