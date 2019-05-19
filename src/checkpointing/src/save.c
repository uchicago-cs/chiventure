#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"
#include "save.h"

int save_object(object_t *o_t, Object *o)
{
    if (o_t == NULL){
        return -1;
    }
  
    o->object_id = o_t->object_id;
  
    if (o_t->short_desc == NULL) {
	o->short_desc = NULL;
    } else {
	o->short_desc = o_t->short_desc;
    }
  
    if (o_t->long_desc == NULL) {
	o->long_desc = NULL;
    } else {
	o->long_desc = o_t->long_desc;
    }

    return 0;
}

int save_room(room_t *r_t, Room *r)
{
    if (r_t == NULL) {
	fprintf(stderr, "Given a room_t struct that is NULL in transfer_room.\n");
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
  
    r->objs_len = r_t->objs_len;

    int len = r_t->objs_len;

    Object **objs;

    r->n_objs = len;

    objs = malloc(sizeof(Object*)*len); 
    for (int i=0; i<len; ++i) {
	objs[i] = malloc(sizeof(Object));
	object__init(objs[i]);
	int transfer_object_success = save_object(r_t->objs[i], objs[i]);
    }

    r->objs = objs;
  
    return 0;
}

int save_player(player_t *p_t, Player *p)
{
    if (p_t == NULL) {
	fprintf(stderr, "Given a player_t struct that is NULL in transfer_player.\n");
	return -1;
    }
  
    p->player_id = p_t->player_id;
  
    if (p_t->username == NULL) {
	p->username = NULL;
    } else {
	p->username = p_t->username;
    }
  
    if (p->has_level == 1) {
	p->level = p_t->level;
    } else {
	p->level = -1; 
    }
  
    if (p->has_health == 1) {
	p->health = p_t->health;
    } else {
	p->health = -1;
    }
  
    if (p->has_xp == 1) {
	p->xp = p_t->xp;
    } else {
	p->xp = -1;
    }
  
    p->inventory_len = p_t->inventory_len;

    int i_len = p_t->inventory_len;
  
    Object **inventory;
  
    p->n_inventory = i_len;

    inventory = malloc(sizeof(Object*)*i_len);
    int inventory_success = 1;
    for (int i = 0; i < i_len; i++) {
	inventory[i] = malloc(sizeof(Object));
	object__init(inventory[i]);
	inventory_success = save_object(p_t->inventory[i], inventory[i]);
    }

    p->inventory = inventory;

    p->clothes_len = p_t->clothes_len;
   
    int c_len = p_t->clothes_len;

    Object **clothes;
  
    p->n_clothes = c_len;
    
    clothes = malloc(sizeof(Object*)*c_len);
    int clothes_success = 1;
    for (int j = 0; j < c_len; j++){
	clothes[j] = malloc(sizeof(Object));
	object__init(clothes[j]);
	clothes_success = save_object(p_t->clothes[j], clothes[j]);
    }

    p->clothes = clothes;
  
    return 0;
}

int save_game(game_t *g_t, Game *g)
{
    if(g_t == NULL){
	fprintf(stderr, "Given a game_t struct that is NULL in transfer_game.\n");
	return -1;
    }
  
    g->players_len = g_t->players_len;

    int p_len = g_t->players_len;
  
    g->n_players = p_len;

    Player **players;
    players = malloc(sizeof(Player*)*p_len);
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
  
    g->rooms_len = g_t->rooms_len;
   
    int r_len = g_t->rooms_len;
  
    Room **rooms;
  
    g->n_rooms = r_len;
    
    rooms = malloc(sizeof(Room*)*r_len);
    int room_success = 1;
    for (int j = 0; j < r_len; j++){
	rooms[j] = malloc(sizeof(Room));
	room__init(rooms[j]);
	room_success = save_room(g_t->rooms[j], rooms[j]);
    }

    g->rooms = rooms;
  
    if (g_t->curr_room == NULL) {
	g->curr_room = NULL;
    } else {
	g->curr_room = g_t->curr_room;
    }
  
    if (g_t->start_time != -1) {
	g->has_start_time = 1; 
	g->start_time = g_t->start_time;
    } else {
	g->start_time = -1;
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
