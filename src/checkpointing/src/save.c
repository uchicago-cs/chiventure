#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../game.pb-c.h"
#include "save.h"

// Object
int transfer_object(Object *o, object_t *o_t){
  if (o_t == NULL){
    return -1;
  }
  
  o->object_id = o_t->object_id; // gives the object_id to proto file
  
  if (o_t->short_desc == NULL)
    o->short_desc = "has null"; // tells proto file this is a null string
  else
    o->short_desc = o_t->short_desc; // gives the short_desc in struct to proto file
  
  if (o_t->long_desc == NULL)
    o->long_desc = "has null";  // tells proto file this is a null string 
  else
    o->long_desc = o_t->long_desc; // gives the long_desc in struct to proto file
  
  return 0;
}

// Room
int transfer_room(Room *r, room_t *r_t) {
  if (r_t == NULL) {
    return -1;
  }
  
  r->room_id = r_t->room_id; // gives proto file the room id
  
  if (r_t->short_desc == NULL) 
    r->short_desc = "has null"; // tells proto file this is a null string 
  else
    r->short_desc = r_t->short_desc; // gives the short_desc in struct to proto file
  
  if (r_t->long_desc == NULL) 
    r->long_desc = "has null"; // tells proto file this is a null string 
  else
    r->long_desc = r_t->long_desc; // gives the long_desc in struct to proto file
  
  r->objs_len = r_t->objs_len; // gives the len of array  protfile 

  int len = r_t->objs_len;

  Object **objs; // array we want to pack

  r->n_objs = len; // IMPORTANT: tells protofile that we want to pack array of size n

  /* puts the objects of the room into the allocated array */
  objs = malloc (sizeof(Object*)*len); 
  for (int i=0; i<len; ++i){
    objs[i] = malloc (sizeof (Object));
    object__init(objs[i]);
    int transfer_object_success = transfer_object(objs[i], r_t->objs[i]);
  }

  r->objs = objs; // puts the array into proto file
  
  return 0;
}

// Player
int transfer_player(Player *p, player_t *p_t, int level, int health, int xp){
  if(p_t == NULL){
    fprintf(stderr, "given a player_t struct that is NULL.\n");
    return -1;
  }
  
  p->player_id = p_t->player_id; // gives proto file the player id
  
  if (p_t->username == NULL) 
    p->username = "has null"; // tells proto file this is a null string 
  else
    p->username = p_t->username; // gives the username in struct to proto file
  
  if (level == 1)
    p->level = p_t->level; // gives the level to the proto file
  else
    p->level = -1; // tells proto file that this field is not used
  
  if (health == 1)
    p->health = p_t->health; // gives the health to the proto file
  else
    p->health = -1; // tells proto file that this field is not used
  
  if (xp == 1)
    p->xp = p_t->xp; // gives the xp to the proto file
  else
    p->xp = -1; // tels proto file that this field is not used
  
  p->inventory_len = p_t->inventory_len; // gives the inventory_len to proto file

  int i_len = p_t->inventory_len;
  
  Object **inventory; // array we want to pack
  
  p->n_inventory = i_len; // IMPORTANT: tells protofile that we want to
  // pack array of size n

  /* puts the objects of the inventory into the allocated array */
  inventory = malloc(sizeof(Object*)*i_len);
  int inventory_success = 1;
  for (int i = 0; i < i_len; i++){
    inventory[i] = malloc(sizeof(Object));
    object__init(inventory[i]);
    inventory_success = transfer_object(inventory[i], p_t->inventory[i]);
  }

  p->inventory = inventory; // gives array to proto file

  p->clothes_len = p_t->clothes_len; // gives clothes_len to proto file
   
  int c_len = p_t->clothes_len;

  Object **clothes;  // array we want to pack
  
  p->n_clothes = c_len; // IMPORTANT: tells protofile that we want to
  // pack array of size n

  /* puts the objects of the clothes into the allocated array */
  clothes = malloc(sizeof(Object*)*c_len);
  int clothes_success = 1;
  for (int j = 0; j < c_len; j++){
    clothes[j] = malloc(sizeof(Object));
    object__init(clothes[j]);
    clothes_success = transfer_object(clothes[j], p_t->clothes[j]);
  }

  p->clothes = clothes; // gives array to proto file
  
  return 0;
}

// Game
int transfer_game(Game *g, game_t *g_t)
{
  if(g_t == NULL){
    fprintf(stderr, "given a g_t struct that is NULL.\n");
    return -1;
  }
  
  g->players_len = g_t->players_len; // gives the inventory_len to proto file

  int p_len = g_t->players_len; // length of array
  
  g->n_players = p_len; // IMPORTANT: tells protofile that we want to                 
  // pack array of size n
  
  int username = 0, health = 0, level = 0, xp = 0; // flags to let proto file know
  // if we have these fields in use or not

  /* puts all players into the allocated array */
  Player **players;
  players = malloc(sizeof(Player*)*p_len);
  int player_success = 1;
  for (int i = 0; i < p_len; i++){
    players[i] = malloc(sizeof(Player));
    player__init(players[i]);

    if (g_t->players[i]->level != -1){
      level = 1; // flags that this field is in use
      players[i]->has_level = 1;
    }
    
    if (g_t->players[i]->health != -1){
      health = 1; // flags that this field is in use
      players[i]->has_health = 1;
    }
    
    if (g_t->players[i]->xp != -1){
      xp = 1; // flags that this field is in use
      players[i]->has_xp = 1;
    }
    
    player_success = transfer_player(players[i], g_t->players[i], level, health, xp);
  }
  
  g->players = players; // gives array to proto file 
  
  g->rooms_len = g_t->rooms_len; // gives rooms_len to proto file 
   
  int r_len = g_t->rooms_len;
  
  Room **rooms; // array we want to pack
  
  g->n_rooms = r_len;// IMPORTANT: tells protofile that we want to
  // pack array of size n 

  /* puts all the rooms into the allocated array */
  rooms = malloc(sizeof(Room*)*r_len);
  int room_success = 1;
  for (int j = 0; j < r_len; j++){
    rooms[j] = malloc(sizeof(Room));
    room__init(rooms[j]);
    room_success = transfer_room(rooms[j], g_t->rooms[j]);
  }

  g->rooms = rooms; // gives array to proto file
  
  if (g_t->curr_room == NULL)
    g->curr_room = "has null"; // tells proto file this is a null string 
  else
    g->curr_room = g_t->curr_room; // gives current room to proto_file
  
  if (g_t->start_time != -1){
    g->has_start_time = 1; // tells proto file this field is in use
    g->start_time = g_t->start_time;
  } else {
    g->start_time = -1; // tells proto file this field is not in use
  }
  
  return 0;
}

int write_to_file(char *filename, uint8_t *buffer, unsigned len)
{
  int res = 0;
  FILE *fp = fopen(filename, "w");
  fwrite(buffer, len, 1,fp); // writes serialized buffer into file
  fclose(fp);
  return res;
}

int save (game_t *g_t, char *filename)
{
  Game g = GAME__INIT;
  void *buf;
  size_t len;
  int success;

  /* packs the game in the proto file */
  success = transfer_game(&g, g_t);
  len = game__get_packed_size(&g);
  buf = malloc(len);
  game__pack(&g, buf);

  fprintf(stderr, "Writing %ld serialized bytes\n", len);    

  write_to_file(filename, buf, len);
    
  free(buf);
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc < 1){
    fprintf(stderr, "did not provide a file name\n");
    exit(1);
  }

  /* Dummy Game Implementation */
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
