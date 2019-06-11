#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "load.h"

int main(int argc, char *argv[])
{
    // first room
    room_t *dorm_t;
    char *room_id = "dorm";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    dorm_t = room_new(room_id, short_desc, long_desc);
    
    // first room's items
    item_t *ramen_t;
    char *i_item_id = "12";
    char *i_short_desc = "cup ramen";
    char *i_long_desc = "has already been eaten";
    ramen_t = item_new(i_item_id, i_short_desc, i_long_desc);
    add_item_to_room(dorm_t, ramen_t);
    
    item_t *shirt_t;
    char *s_item_id = "34";
    char *s_short_desc = "shirt";
    char *s_long_desc = "looks unwashed";
    shirt_t = item_new(s_item_id, s_short_desc, s_long_desc);
    add_item_to_room(dorm_t, shirt_t);

    // second room
    room_t *dungeon_t;
    char *d_room_id = "56";
    char *d_short_desc = "dungeon";
    char *d_long_desc = "there are skull and bones in all the jail cells";
    dungeon_t = room_new(d_room_id, d_short_desc, d_long_desc);

    // second room's items 
    item_t *skull_t;
    char *sk_item_id = "78";
    char *sk_short_desc = "skull";
    char *sk_long_desc = "looks pretty old";
    skull_t = item_new(sk_item_id, sk_short_desc, sk_long_desc);   
    add_item_to_room(dungeon_t, skull_t);

    // one player
    player_t *chad_t;
    chad_t = player_new("chad", 100);

    if (argc == 1) {
	game_t *g_t_orig = game_new("Welcome to Chiventure");

	add_room_to_game(g_t_orig, dorm_t);
	move_room(g_t_orig, dorm_t);
	add_room_to_game(g_t_orig, dungeon_t);
	create_connection(g_t_orig, "5", "2", "east");
	
	change_level(chad_t, 8999);
	add_item_to_player(chad_t, shirt_t);
	chad_t->xp = 578;
	add_player_to_game(g_t_orig, chad_t);
	set_curr_player(g_t_orig, chad_t);
	
	move_room(g_t_orig, dungeon_t);
	
	save(g_t_orig, "save.txt");
    } else {
	printf("file we are reading from: %s\n", argv[1]);
	game_t *g_t_load = game_new("Welcome to Chiventure");

	// let's pretend to load stuff from WDL

	add_player_to_game(g_t_load, chad_t);
	set_curr_player(g_t_load, chad_t);
	add_room_to_game(g_t_load, dorm_t);
	move_room(g_t_load, dorm_t);
	add_room_to_game(g_t_load, dungeon_t);
	create_connection(g_t_load, "5", "2", "east");
       
	load("save.txt", g_t_load);
	printf("This is the current player\n");
	printf("g_t_load->curr_player->player_id: %s\n",
	       g_t_load->curr_player->player_id);
	printf("g_t_load->curr_player->level: %d\n", g_t_load->curr_player->level);
	printf("g_t_load->curr_player->health: %d\n",
	       g_t_load->curr_player->health);
	printf("g_t_load->curr_player->xp: %d\n", g_t_load->curr_player->xp);
	printf("g_t_load->curr_room->room_id: %s\n",
	       g_t_load->curr_room->room_id);
	printf("g_t_load->curr_room->short_desc: %s\n",
	       g_t_load->curr_room->short_desc);
	printf("g_t_load->curr_room->long_desc: %s\n",
	       g_t_load->curr_room->long_desc);
	item_list_t *inv = get_all_items_in_inventory(g_t_load->curr_player);
	printf("%s\'s inventory\n", g_t_load->curr_player->player_id);
	while (inv) {
	    printf("inv->item->item_id: %s\n", inv->item->item_id);
	    printf("inv->item->short_desc: %s\n", inv->item->short_desc);
	    printf("inv->item->long_desc: %s\n", inv->item->long_desc);
	    inv = inv->next;
	}
	printf("These are the item(s) in this room\n");
	item_list_t *room_items = get_all_items_in_room(g_t_load->curr_room);
	while (room_items) {
	    printf("room_items->item->item_id: %s\n", room_items->item->item_id);
	    printf("room_items->item->short_desc: %s\n", room_items->item->short_desc);
	    printf("room_items->item->long_desc: %s\n", room_items->item->long_desc);
	    room_items = room_items->next;
	}
    }
    return 0;
}
