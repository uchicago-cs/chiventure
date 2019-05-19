// deserializing
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


int load_object(Object *o, object_t *o_t)
{
    if(o_t == NULL) {
	fprintf(stderr, "given null object_t struct\n");
	return -1;
    }

    o_t->object_id = o->object_id;
  
    if (o->short_desc != NULL) {
	o_t->short_desc = o->short_desc;
    } else {
	o_t->short_desc = NULL;
    }
  
    if (o->long_desc != NULL) {
	o_t->long_desc = o->long_desc;
    } else {
	o_t->long_desc = NULL;
    }

    return 0;
}


int load_player(Player *p, player_t *p_t)
{
    if (p_t == NULL) {
	fprintf(stderr, "given null player_t struct\n");
	return -1;
    }
  
    p_t->player_id = p->player_id;

    if (p->username !=  NULL) {
	p_t->username = p->username;
    } else {
	p_t->username = NULL;
    }
  
    if (p->has_level == 1) {
	p_t->level = p->level;
    } else {
	p_t->level = -1;
    }
  
    if (p->has_health == 1) {
	p_t->health = p->health;
    } else {
	p_t->health = -1;
    }
  
    if (p->has_xp == 1) {
	p_t->xp = p->xp;
    } else {
	p_t->xp = -1;
    }
  
    object_t **inventory = malloc(sizeof(object_t*) * p->inventory_len);

    for (int i = 0; i < p->inventory_len; i++) {
	inventory[i] = malloc(sizeof(object_t));
	load_object(p->inventory[i], inventory[i]);
    }
    p_t->inventory = inventory;
	
    p_t->inventory_len = p->inventory_len;
  
    object_t **clothes = malloc(sizeof(object_t*) * p->clothes_len);

    for (int i = 0; i < p->clothes_len; i++) {
	clothes[i] = malloc(sizeof(object_t));
	load_object(p->clothes[i], clothes[i]);
    }
  
    p_t->clothes = clothes;
  
    p_t->clothes_len = p->clothes_len;

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
  
    object_t **objs = malloc(sizeof(object_t*) * r->objs_len);

    for (int i = 0; i < r->objs_len; i++) {
	objs[i] = malloc(sizeof(object_t));
	load_object(r->objs[i], objs[i]);
    }
  
    r_t->objs = objs;
  
    return 0;

}

int load_game(Game *g, game_t *g_t)
{
    if (g_t == NULL) {
	fprintf(stderr, "given null game_t struct\n");
	return -1;
    }
  
    player_t **players = malloc(sizeof(player_t*) * g->players_len);
    for (int i = 0; i < g->players_len; i++) {
	players[i] = malloc(sizeof(player_t));
	load_player(g->players[i], players[i]);
    }

    g_t->players = players;
  
    g_t->players_len = g->players_len;
  
    room_t **rooms = malloc(sizeof(room_t*) * g->rooms_len); 
    for (int j = 0; j < g->rooms_len; j++) {
	rooms[j] = malloc(sizeof(room_t));
	load_room(g->rooms[j], rooms[j]);
    }

    g_t->rooms = rooms;
  
    g_t->rooms_len = g->rooms_len;  

    if(g->curr_room != NULL) {
	g_t->curr_room = g->curr_room;
    } else {
	g_t->curr_room = NULL;
    }
    
    if(g->has_start_time == 1) {
	g_t->start_time = g->start_time;
    } else {
	g_t->start_time = -1;
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
