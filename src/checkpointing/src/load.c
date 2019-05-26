#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"
#include "load.h"
#define MAX_BUF_SIZE 1000000


size_t read_file(char *filename, unsigned max_length, uint8_t *out)
{
    size_t cur_len = 0;
    size_t nread;
    FILE *fp = fopen(filename, "r");
    while((nread = fread(out + cur_len, 1, max_length - cur_len, fp)) != 0) {
	cur_len += nread;
	if (cur_len == max_length) {
	    fprintf(stderr, "max message length exceed\n");
	    return max_length;
	}
    }
    fclose(fp);
    return cur_len;
}


int load_attribute_value(Attribute_value *av, attribute_value_t *av_t)
{
    if (av_t == NULL) {
	fprintf(stderr, "given null attribute_value_t struct\n");
	return -1;
    }

    if (av->double_value != NULL) {
	av_t->double_value = av->double_value;
    } else {
	av_t->double_value = NULL;
    }

    if (av->char_val != NULL) {
	av_t->char_val = av->char_val;
    } else {
	av_t->char_val = NULL;
    }

    if (av->bool_val != NULL) {
	av_t->bool_val = av->bool_val;
    } else {
	av_t->bool_val = NULL;
    }

    if (av->str_val != NULL) {
	av_t->str_val = av->str_val;
    } else {
	av_t->str_val = NULL;
    }

    if (av->int_val != NULL) {
	av_t->int_val = av->int_val;
    } else {
	av_t->int_val = NULL;
    }

    return 0;
}


int load_attribute(Attribute *a, attribute_t *a_t)
{
    if (a_t == NULL) {
	fprintf(stderr, "given null attribute_t struct\n");
	return -1;
    }

    a_t->attribute_key = a->attribute_key;

    if (strcmp(a->attribute_tag, "DOUBLE") == 0) {
	a_t->attribute_tag = DOUBLE;
    } else if (strcmp(a->attribute_tag, "BOOLE") == 0) {
	a_t->attribute_tag = BOOLE;
    } else if (strcmp(a->attribute_tag, "CHARACTER") == 0) {
	a_t->attribute_tag = CHARACTER;
    } else if (strcmp(a->attribute_tag, "STRING") == 0) {
	a_t->attribute_tag = STRING;
    } else {
	a_t->attribute_tag = INTEGER;
    }

    load_attribute_value(a->attribute_value, a_t->attribute_value);

    return 0;
}

    
int load_item(Item *i, item_t *i_t);
{
    if(i_t == NULL) {
	fprintf(stderr, "given null item_t struct\n");
	return -1;
    }

    i_t->item_id = i->item_id;
  
    if (i->short_desc != NULL) {
	i_t->short_desc = i->short_desc;
    } else {
	i_t->short_desc = NULL;
    }
  
    if (i->long_desc != NULL) {
	i_t->long_desc = i->long_desc;
    } else {
	i_t->long_desc = NULL;
    }

    // bool condition reserved for future expansion

    // repeated Attribute HERE
    //ITER_ALL_ITEMS
    return 0;
}

// won't need condition for semi-incremental saving
/*
int load_condition(Condition *c, condition_t *c_t)
{
    if (c_t == NULL) {
	fprintf(stderr, "given null condition_t struct\n");
	return -1;
    }

    if (c->item_id != NULL) {
	c_t->item->item_id = c->item_id;
    } else {
	c_t->item->item_id = NULL;
    }

    // something here? idk depends on game state

    // optional Attribute here but might change

    return 0;
    }*/


int load_path(Path *p, path_t *p_t)
{
    if (p_t == NULL) {
	fprintf(stderr, "given null path_t struct\n");
	return -1;
    }

    if (p->direction != NULL) {
	p_t->direction = p->direction;
    } else {
	p_t->direction = NULL;
    }

    // if game state changes dest to a pointer, this will need to change!
    if (p->dest != NULL) {
	p_t->dest = p->dest;
    } else {
	p_t->dest = NULL;
    }

    // repeated Condition HERE

    return 0;
}


int load_room(Room *r, room_t *r_t)
{
    if (r_t == NULL) {
	fprintf(stderr, "given null room_t struct\n");
	return -1;
    }

    r_t->room_id = r->room_id;
  
    if (r->short_desc != NULL) {
	r_t->short_desc = r->short_desc;
    } else {
	r_t->short_desc = NULL;
    }
  
    if (r->long_desc != NULL) {
	r_t->long_desc = r->long_desc;
    } else {
	r_t->short_desc = NULL;
    }

    // hash table stuff
    // note that object is now called item
    
    /* object_t **objs = malloc(sizeof(object_t*) * r->objs_len);

    for (int i = 0; i < r->objs_len; i++) {
	objs[i] = malloc(sizeof(object_t));
	load_object(r->objs[i], objs[i]);
    }
  
    r_t->objs = objs;

    // path stuff here

    */
    return 0;
}


int load_player(Player *p, player_t *p_t)
{
    if (p_t == NULL) {
	fprintf(stderr, "given null player_t struct\n");
	return -1;
    }
  
    p_t->player_id = p->player_id;

    if (p->level != NULL) {
	p_t->level = p->level;
    } else {
	p_t->level = NULL;
    }
  
    if (p->health != NULL) {
	p_t->health = p->health;
    } else {
	p_t->health = NULL;
    }
  
    if (p->xp != NULL) {
	p_t->xp = p->xp;
    } else {
	p_t->xp = NULL;
    }

    // hash table stuff for inventory
    /*
    object_t **inventory = malloc(sizeof(object_t*) * p->inventory_len);

    for (int i = 0; i < p->inventory_len; i++) {
	inventory[i] = malloc(sizeof(object_t));
	load_object(p->inventory[i], inventory[i]);
    }
    p_t->inventory = inventory;
	
    p_t->inventory_len = p->inventory_len;
  
    */
    return 0;
}    


int load_game(Game *g, game_t *g_t)
{
    if (g_t == NULL) {
	fprintf(stderr, "given null game_t struct\n");
	return -1;
    }

    // repeated all_players
    /*
    player_t **players = malloc(sizeof(player_t*) * g->players_len);
    for (int i = 0; i < g->players_len; i++) {
	players[i] = malloc(sizeof(player_t));
	load_player(g->players[i], players[i]);
    }

    g_t->players = players;
  
    g_t->players_len = g->players_len;
  
    // repeated all_rooms

    room_t **rooms = malloc(sizeof(room_t*) * g->rooms_len); 
    for (int j = 0; j < g->rooms_len; j++) {
	rooms[j] = malloc(sizeof(room_t));
	load_room(g->rooms[j], rooms[j]);
    }

    g_t->rooms = rooms;
  
    g_t->rooms_len = g->rooms_len;  
    */


    if(g->curr_room != -1) {
	ITER_ALL_ROOMS(g_t, curr_r) {
	    if (curr_r->room_id == g->curr_room) {
		g_t->curr_room = curr_r;
	    }
	}
    } else {
	g_t->curr_room = NULL;
    }

    if (g->curr_player != -1) {
	ITER_ALL_PLAYERS(g_t, curr_p) {
	    if (curr_p->player_id == g->curr_player) {
		g_t->curr_player = curr_p;
	    }
	}
    } else {
	g_t->curr_player = NULL;
    }
    
    return 0;
}

int load(char *filename, Game *g, game_t *g_t)
{
    uint8_t buffer[MAX_BUF_SIZE];
    size_t game_len = read_file(filename, MAX_BUF_SIZE, buffer);
	
    printf("game_len: %ld\n", game_len);
  
    g = game__unpack(NULL, game_len, buffer);
	
    if (g == NULL) {
	fprintf(stderr, "error unpacking incoming game\n");
	exit(1);
    }

    load_game(g, g_t);

    game__free_unpacked(g, NULL);
  
    return 0;
}
