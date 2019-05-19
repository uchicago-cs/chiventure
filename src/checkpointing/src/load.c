// deserializing
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../game.pb-c.h"
#include "load.h"
#define MAX_SIZE 1000000

static size_t read_file(char *filename, unsigned max_length, uint8_t *out)
{
    size_t cur_len = 0;
    size_t nread;
    FILE *fp = fopen(filename, "r");
    while((nread=fread(out+cur_len, 1, max_length - cur_len, fp)) != 0) {
	cur_len += nread;
	if (cur_len == max_length) {
	    fprintf(stderr, "max message length exceed\n");
	    exit(1);
	}
    }
    fclose(fp);
    return cur_len;
}


int load_object(Object *o, object_t *o_t)
{
    // Check if givent object_t is null
    if(o_t == NULL){
	fprintf(stderr, "given null object_t struct\n");
	return -1;
    }

    //print out object id from protofile for visual check
    //store protofile info into struct
    printf("Object ID: %s\n", o->object_id);
    o_t->object_id = o->object_id;
  
    // check if short_desc exists as it is an optional string type
    if (strcmp(o->short_desc, "has null") != 0){
	//print and store
	printf("Short Description: %s\n", o->short_desc);
	o_t->short_desc = o->short_desc;
    } else {
	// if does not exist, store as null
	o_t->short_desc = NULL;
    }
  
    //same process as short_desc above
    if (strcmp(o->long_desc, "has null") != 0){
	printf("Long Description: %s\n", o->long_desc);
	o_t->long_desc = o->long_desc;
    } else {
	o_t->long_desc = NULL;
    }

    return 0; // this means there were no errors.
}


int load_player(Player *p, player_t *p_t)
{
    //check if given is null
    if (p_t == NULL){
	fprintf(stderr, "given null player_t struct\n");
	return -1;
    }
  
    //print and store
    printf("Player ID: %d\n", p->player_id);
    p_t->player_id = p->player_id;

    // optional string type
    if (strcmp(p->username, "has null") != 0){
	printf("Username: %s\n", p->username);
	p_t->username = p->username;
    } else {
	printf("Username: %s\n", p->username);
	p_t->username = NULL;
    }
  
    // optional int type 
    //(has_ is given with protobuf-c with optional int types)
    //(in save has_ is set to 1 if it exists)
    if (p->has_level == 1){
	printf("Level: %d\n", p->level);
	p_t->level = p->level;
    } else {
	printf("Level: %d\n", p->level);
	p_t->level = -1;
    }
  
    //optional int type
    if (p->has_health == 1){
	printf("Health: %d\n", p->health);
	p_t->health = p->health;
    } else {
	printf("Health: %d\n", p->health);
	p_t->health = -1;
    }
  
    //optional int type
    if (p->has_xp == 1){
	printf("XP: %d\n", p->xp);
	p_t->xp = p->xp;
    } else {
	printf("XP: %d\n", p->xp);
	p_t->xp = -1;
    }
  
    //malloced space for a double pointer of object_t to store the protofile info
    object_t **inventory = malloc(sizeof(object_t*)*p->inventory_len);
    // loop through the array to create space for an object_t in each compontent
    // store each object into the list of object_t
    for (int i = 0; i < p->inventory_len; i++) {
	inventory[i] = malloc(sizeof(object_t));
	print_object(p->inventory[i], inventory[i]);
    }
    // stored the created array of objects into the game struct
    p_t->inventory = inventory;
  
    // print and store
    printf("Inventory length: %d\n", p->inventory_len);
    p_t->inventory_len = p->inventory_len;
  
    // same process as inventory above
    object_t **clothes = malloc(sizeof(object_t*)*p->clothes_len);

    for (int i = 0; i < p->clothes_len; i++) {
	clothes[i] = malloc(sizeof(object_t));
	print_object(p->clothes[i], clothes[i]);
    }
  
    p_t->clothes = clothes;
  
    // print and store
    printf("Clothes length: %d\n", p->clothes_len);
    p_t->clothes_len = p->clothes_len;

    return 0;
}    

int load_room(Room *r, room_t *r_t)
{
    // check if given room_t is null
    if (r_t == NULL){
	fprintf(stderr, "given null room_t struct\n");
	return -1;
    }

    //print and store
    printf("Room ID: %s\n", r->room_id);
    r_t->room_id = r->room_id;
  
    // optional string type
    if (strcmp(r->short_desc, "has null") != 0){
	printf("Short Description: %s\n", r->short_desc);
	r_t->short_desc = r->short_desc;
    } else {
	printf("Short Description: %s\n", r->short_desc);
	r_t->short_desc = NULL;
    }
  
    //optional string type
    if (strcmp(r->long_desc, "has null") != 0){
	printf("Long Description: %s\n", r->long_desc);
	r_t->long_desc = r->long_desc;
    } else {
	printf("Long Description: %s\n", r->long_desc);
	r_t->short_desc = NULL;
    }
  
    //print and store a list of objects
    object_t **objs = malloc(sizeof(object_t*)*r->objs_len);

    for (int i = 0; i < r->objs_len; i++) {
	objs[i] = malloc(sizeof(object_t));
	print_object(r->objs[i], objs[i]);
    }
  
    r_t->objs = objs;
  
    return 0;

}

int load_game(Game *g, game_t *g_t)
{
    //check if given game_t is null
    if (g_t == NULL){
	fprintf(stderr, "given null game_t struct\n");
	return -1;
    }
  
    //print and store list of players
    player_t **players = malloc(sizeof(player_t*)*g->players_len);
    for (int i = 0; i < g->players_len; i++){
	players[i] = malloc(sizeof(player_t));
	print_player(g->players[i], players[i]);
    }

    g_t->players = players;
  
    //print and store
    printf("Players length: %d\n", g->players_len);
    g_t->players_len = g->players_len;
  
    //print and store list of rooms
    room_t **rooms = malloc(sizeof(room_t*)*g->rooms_len); 
    for (int j = 0; j < g->rooms_len; j++){
	rooms[j] = malloc(sizeof(room_t));
	print_room(g->rooms[j], rooms[j]);
    }

    g_t->rooms = rooms;
  
    //print and store
    printf("Room length: %d\n", g->rooms_len);
    g_t->rooms_len = g->rooms_len;  

    //optional string type
    if(strcmp(g->curr_room, "has null") != 0){
	printf("Current Room: %s\n", g->curr_room);
	g_t->curr_room = g->curr_room;
    } else {
	printf("Current Room: %s\n", g->curr_room);
	g_t->curr_room = NULL;
    }
        
    //optional int type
    if(g->has_start_time == 1){
	printf("Start Time: %d\n", g->start_time);
	g_t->start_time = g->start_time;
    } else {
	printf("Start Time: %d\n", g->start_time);
	g_t->start_time = -1;
    }
    return 0;
}

int load(char *filename, Game *g, game_t *g_t)
{
    uint8_t buffer[MAX_SIZE];
    size_t game_len = read_file(filename, MAX_SIZE, buffer);
	
    printf("game_len: %ld\n", game_len);
  
    // deserialize serialized code into proto structs
    g = game__unpack(NULL, game_len, buffer);
	
    //check if game unpacked
    if (g == NULL){
	fprintf(stderr, "error unpacking incoming game\n");
	exit(1);
    }

    //transfer proto structs to game structs
    print_game(g, g_t);

    //result of unpacking is freed
    game__free_unpacked(g, NULL);
  
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 1) {
	fprintf(stderr, "no filename provided\n");
	exit(1);
    }
	
    Game *g = malloc(sizeof(Game));
    game_t *g_t = malloc(sizeof(game_t));
  
    load(argv[1], g, g_t);

    return 0;
}
