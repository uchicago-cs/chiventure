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

/*
int main(int argc, char *argv[])
{
    if (argc < 1){
	fprintf(stderr, "did not provide a file name\n");
	exit(1);
    }


    object_t *sword, *potion, *shield, *armor, *hat;
    sword = malloc(sizeof(object_t));
    potion = malloc(sizeof(object_t));
    shield = malloc(sizeof(object_t));
    armor = malloc(sizeof(object_t));
    hat =  malloc(sizeof(object_t));

    sword->object_id = "sword";
    sword->short_desc = "long and silver";
    sword->long_desc = "silver,long and with a gold handle, with a gem embedded. however is unable to cut anything";

    potion->object_id = "potion";
    potion->short_desc = "red potion in glass bottle";
    potion->long_desc = "recovers health";

    shield->object_id = "shield";
    shield->short_desc = "circular and wooden";
    shield->long_desc = NULL;

    armor->object_id = "armor";
    armor->short_desc = "silver and covers chest";
    armor->long_desc = "protects the body from attacks";

    hat->object_id = "hat";
    hat->short_desc = "top hat";
    hat->long_desc = "received by a pengiun";
  
    player_t *player1;
    player1 = malloc(sizeof(player_t));

    player1->player_id = 1;
    player1->username = "ichigocat";
    player1->level = 9001;
    player1->health = 1;
    player1->xp = 2;

    object_t **inventory = malloc(sizeof(object_t*)*3);
    inventory[0] = shield;
    inventory[1] = sword;
    inventory[2] = potion;
    //  inventory[] = {shield, sword, potion};

    object_t **clothes = malloc(sizeof(object_t*)*2);
    clothes[0] = armor;
    clothes[1] = hat;

    player1->inventory = inventory;
    player1->inventory_len = 3;
    player1->clothes = clothes;
    player1->clothes_len = 2;

    player_t *player2;
    player2 = malloc(sizeof(player_t));

    player2->player_id = 2;
    player2->username = NULL;
    player2->level = -1;
    player2->health = -1;
    player2->xp = -2;
    player2->inventory = clothes;
    player2->inventory_len = 2;
    player2->clothes = inventory;
    player2->clothes_len = 3;

    room_t *room1, *room2;
    room1 = malloc(sizeof(room_t));
    room2 = malloc(sizeof(room_t));

    room1->room_id = "dungeon";
    room1->short_desc = "dark and ominous";
    room1->long_desc = "you probably shouldn't go in here";

    object_t **dungeon_items = malloc(sizeof(object_t*)*2);
    dungeon_items[0] = potion;
    dungeon_items[1] = potion;

    room1->objs_len = 2;
    room1->objs = dungeon_items;


    room2->room_id = "armory";
    room2->short_desc = "kind and friendly";
    room2->long_desc = "you can get armor and weapons here";

    object_t **armory_items = malloc(sizeof(object_t*)*3);
    armory_items[0] = armor;
    armory_items[1] = shield;
    armory_items[2] = sword;

    room2->objs_len = 3;
    room2->objs = armory_items;

    game_t *game = malloc(sizeof(game_t));

    player_t **players = malloc(sizeof(player_t*)*2);
    players[0] = player1;
    players[1] = player2;

    game->players = players;
    game->players_len = 2;

    room_t **rooms = malloc(sizeof(room_t*)*2);
    rooms[0] = room1;
    rooms[1] = room2;

    game->rooms = rooms;
    game->rooms_len = 2;
    game->curr_room = "dungeon";
    game->start_time = 200;

    save(game, argv[1]);
  
    return 0;
}
*/
