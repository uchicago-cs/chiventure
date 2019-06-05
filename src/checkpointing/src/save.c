#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"
#include "save.h"


int save_attribute(item_t *i_t, attribute_t *a_t, Attribute *a)
{
    if (a_t == NULL) {
	fprintf(stderr, "Given a NULL attribute struct in save_attribute");
	return -1;
    }
    
    a->attribute_key = a_t->attribute_key;
    
    if (a_t->attribute_tag == DOUBLE) {
	a->attribute_tag = "DOUBLE";
	a->attribute_value->double_val = get_double_attr(i_t, a_t->attribute_key);
    } else if (a_t->attribute_tag == BOOLE) {
	a->attribute_tag = "BOOLE";
	a->attribute_value->bool_val = get_bool_attr(i_t, a_t->attribute_key);
    } else if (a_t->attribute_tag == CHARACTER) {
	a->attribute_tag = "CHARACTER";
	a->attribute_value->char_val = get_char_attr(i_t, a_t->attribute_key);
    } else if (a_t->attribute_tag == STRING) {
	a->attribute_tag = "STRING";
	if (a_t->attribute_value.str_val != NULL){
	    a->attribute_value->str_val = strdup(get_str_attr(i_t, a_t->attribute_key));
	} else {
	    a->attribute_value->str_val = NULL;
	}	
    } else if (a_t->attribute_tag == INTEGER) {
	a->attribute_tag = "INTEGER";
	a->attribute_value->int_val = get_int_attr(i_t, a_t->attribute_key);	
    } else {
	a->attribute_tag = "ACTION";
	a->attribute_value->act_val->action_name =
	  strdup(a_t->attribute_value.act_val->action_name);
	a->attribute_value->act_val->action_type->c_name =
	  strdup(a_t->attribute_value.act_val->action_type->c_name);
	if (a_t->attribute_value.act_val->action_type->kind == ITEM){
	  a->attribute_value->act_val->action_type->kind = "0";
	} else if (a_t->attribute_value.act_val->action_type->kind == PATH) {
	  a->attribute_value->act_val->action_type->kind = "1";
	} else {
	  a->attribute_value->act_val->action_type->kind = "2";
	}
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

    attribute_list_t *all_attrs = get_all_attributes(i_t);
    attribute_list_t *curr_attr = all_attrs;
    
    int iter = 0; // Iterator int to track the array
    while (curr_attr != NULL){
      iter += 1;
      curr_attr = curr_attr->next;
    }
    Attribute **attrs = malloc(sizeof(Attribute*) * iter);

    // put the linked list of attributes into an array
    curr_attr = all_attrs;
    iter = 0;
    while (curr_attr != NULL){
	attrs[iter] = malloc(sizeof(Attribute));
        attribute__init(attrs[iter]);
	
        int save_attribute_success = save_attribute(i_t, curr_attr->attribute,
						    attrs[iter]);

	if (save_attribute_success != 0) {
	    fprintf(stderr, "Attribute saving for item failed \n");
	    return -1;
	}
	iter += 1;
	curr_attr = curr_attr->next;
    }
    i->attributes = attrs;    
    i->attributes_len = iter;  // Set length of array
    i->n_attributes = iter;  // Set length of array
    
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
    /*
    int count_item = 0;
    ITER_ALL_ITEMS_IN_ROOM(r_t, curr_item) {
        count_item += 1;
    }
    */
    item_list_t *all_items = get_all_items_in_room(r_t);
    item_list_t *curr_item = all_items;
    int iter =0; // Iterator int to track the array
    while (curr_item != NULL){
      iter += 1;
      curr_item = curr_item->next;
    }
    
    Item **items = malloc(sizeof(Item*) * iter);

    // Put the hashtable into the array

    // Delete after game-state pushed to master
    /*
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
    */
    // Uncomment after game-state pushed to master
    curr_item = all_items;
    iter = 0;
    while(curr_item != NULL){
	items[iter] = malloc(sizeof(Item));
	item__init(items[iter]);
	int save_item_success = save_item(curr_item->item, items[iter]);
	if (save_item_success != 0) {
	    fprintf(stderr, "Item saving for room failed \n");
	    return -1;
	}
	iter += 1;
	curr_item = curr_item->next;
    }
    //
    
    r->items = items;

    r->items_len = iter;  // Set length of array
    r->n_items = iter;  // Set length of array

    /* Path needs not be saved anymore
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
    */
    
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
    /*
    int count_item = 0;
    ITER_ALL_ITEMS_IN_INVENTORY(p_t, curr_item) {
        count_item += 1;
    }
    */
    item_list_t *all_items = get_all_items_in_inventory(p_t);
    item_list_t *curr_item = all_items;
    int iter = 0; // Iterator int to track the array
    while (curr_item != NULL) {
      iter += 1;
      curr_item = curr_item->next;
    }
    Item **items = malloc(sizeof(Item*) * iter);

    
    // Put the hashtable into the array

    // Delete after game-state pushed to master
    /*
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
    */
    // Uncomment when game-state PR
    curr_item = all_items;
    iter = 0;
    while(curr_item != NULL){
	items[iter] = malloc(sizeof(Item));
	item__init(items[iter]);
	int save_item_success = save_item(curr_item->item, items[iter]);
	if (save_item_success != 0){
	    fprintf(stderr, "Item saving for inventory failed \n");
	    return -1;
	}
	iter += 1;
	curr_item = curr_item->next;

    }
    //
    
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
    /*
    int count_player = 0;
    ITER_ALL_PLAYERS(g_t, curr_player) {
        count_player += 1;
    }
    */

    //int iter = 0; // Iterator int to track the array
    
    //Player **plyrs = malloc(sizeof(Player*) * 10);


    // Put the hashtable into the array
    /*
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
    */
    // Uncomment when game-state pushed to master
    Player **plyrs = malloc(sizeof(Player*));
    plyrs[0] = malloc(sizeof(Player));
    player__init(plyrs[0]);
    int save_plyr_success = save_player(g_t->all_players, plyrs[0]);
    if (save_plyr_success != 0){
        fprintf(stderr, "Player saving for game failed \n");
        return -1;
    }
    //

    g->all_players = plyrs;
    // g->all_players = plyrs;

    g->players_len = 1;
    g->n_all_players = 1;  // Set length of array

    
    // repeated all_rooms here!!!!!!!

    // Allocate an array of proto Player structs
    /*
    int count_room = 0;
    ITER_ALL_ROOMS(g_t, curr_room) {
        count_room += 1;
    }
    */
    room_list_t *all_rooms = get_all_rooms(g_t);
    room_list_t *curr_room = all_rooms;    
    int iter = 0; // Iterator int to track the array
    while (curr_room != NULL) {
      iter += 1;
      curr_room = curr_room->next;
    }
    Room **rooms = malloc(sizeof(Room*) * iter);


    // Put the hashtable into the array

    // Delete PR
    /*
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
    */
    // Uncomment after PR
    curr_room = all_rooms;
    iter = 0;
    while(curr_room != NULL){
	rooms[iter] = malloc(sizeof(Room));
	room__init(rooms[iter]);
	int save_room_success = save_room(curr_room->room, rooms[iter]);
	if (save_room_success != 0){
	    fprintf(stderr, "Room saving for game failed \n");
	    return -1;
	}
	iter += 1;
        curr_room = curr_room->next;
    }
    //    

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
