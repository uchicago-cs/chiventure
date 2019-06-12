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
    chad_t = player_new("Chad", 100);

    if (argc == 1) {
	game_t *g_t_orig = game_new("Welcome to Chiventure");

	printf("Welcome to Chiventure\n");
	printf("Player one's name is Chad, he has 100 health.\n");
	add_room_to_game(g_t_orig, dorm_t);
	move_room(g_t_orig, dorm_t);
	printf("Chad starts in a dorm room.\n");
	printf("In the dorm room there is a shirt and cup ramen.\n"); 
	add_room_to_game(g_t_orig, dungeon_t);
	create_connection(g_t_orig, dorm_t->room_id, dungeon_t->room_id, "east");

	printf("Chad grabs a shirt from the dorm and puts it in his inventory.\n");
	add_item_to_player(chad_t, shirt_t);
	printf("Chad levels up to 9000.\n");
	change_level(chad_t, 8999);
	printf("Chad gained 578 experience.\n");
	chad_t->xp = 578;
	add_player_to_game(g_t_orig, chad_t);
	set_curr_player(g_t_orig, chad_t);
	printf("Chad goes to the dungeon from the dorm room.\n");
	move_room(g_t_orig, dungeon_t);
	printf("The game is saved in a file named save.txt\n");
	save(g_t_orig, "save.txt");
    } else {
	if (strcmp(argv[1], "save.txt") == 0) {
	    printf("file we are reading from: %s\n", argv[1]);
	    game_t *g_t_load = game_new("Welcome to Chiventure");

	    // let's pretend to load stuff from WDL

	    add_player_to_game(g_t_load, chad_t);
	    set_curr_player(g_t_load, chad_t);
	    add_room_to_game(g_t_load, dorm_t);
	    move_room(g_t_load, dorm_t);
	    add_room_to_game(g_t_load, dungeon_t);
	    create_connection(g_t_orig, dorm_t->room_id, dungeon_t->room_id, "east");
	    printf("We load the game\n");
	    load("save.txt", g_t_load);
	    printf("Loaded player;s name: %s\n",
		   g_t_load->curr_player->player_id);
	    printf("Loaded player's level: %d\n", g_t_load->curr_player->level);
	    printf("Loaded player's health: %d\n", g_t_load->curr_player->health);
	    printf("Loaded player's xp: %d\n", g_t_load->curr_player->xp);
	    printf("Loaded current room: %s\n",
		   g_t_load->curr_room->room_id);
	    printf("Loaded current room short description: %s\n",
		   g_t_load->curr_room->short_desc);
	    printf("Loaded current room long description: %s\n",
		   g_t_load->curr_room->long_desc);
	    item_list_t *inv = get_all_items_in_inventory(g_t_load->curr_player);
	    printf("%s\'s inventory\n", g_t_load->curr_player->player_id);
	    while (inv) {
		printf("Item id: %s\n", inv->item->item_id);
		printf("Item short description: %s\n", inv->item->short_desc);
		printf("Item long description: %s\n", inv->item->long_desc);
		inv = inv->next;
	    }
	    printf("These are the item(s) in the %s\n",
		   g_t_load->curr_room->short_desc);
	    item_list_t *room_items = get_all_items_in_room(g_t_load->curr_room);
	    while (room_items) {
		printf("Item ID: %s\n", room_items->item->item_id);
		printf("Short Description: %s\n", room_items->item->short_desc);
		printf("Long Description: %s\n", room_items->item->long_desc);
		room_items = room_items->next;
	    }
	    printf("Now let's save this file without changing anything in a file named: resave.txt\n");
	    save(g_t_load,"resave.txt");
	} else {
	    printf("file we are reading from: %s\n", argv[1]);
	    game_t *g_t_reload = game_new("Welcome to Chiventure");

	    // let's pretend to load stuff from WDL

	    add_player_to_game(g_t_reload, chad_t);
	    set_curr_player(g_t_reload, chad_t);
	    add_room_to_game(g_t_reload, dorm_t);
	    move_room(g_t_reload, dorm_t);
	    add_room_to_game(g_t_reload, dungeon_t);
	    create_connection(g_t_orig, dorm_t->room_id, dungeon_t->room_id, "east");
	    printf("We load the game\n");
		
	    load("resave.txt", g_t_reload);
		
	    printf("Loaded player;s name: %s\n",
		   g_t_reload->curr_player->player_id);
	    printf("Loaded player's level: %d\n", g_t_reload->curr_player->level);
	    printf("Loaded player's health: %d\n", g_t_reload->curr_player->health);
	    printf("Loaded player's xp: %d\n", g_t_reload->curr_player->xp);
	    printf("Loaded current room: %s\n",
		   g_t_reload->curr_room->room_id);
	    printf("Loaded current room short description: %s\n",
		   g_t_reload->curr_room->short_desc);
	    printf("Loaded current room long description: %s\n",
		   g_t_reload->curr_room->long_desc);
	    item_list_t *reinv = get_all_items_in_inventory(g_t_reload->curr_player);
	    printf("%s\'s inventory\n", g_t_reload->curr_player->player_id);
	    while (reinv) {
		printf("Item id: %s\n", reinv->item->item_id);
		printf("Item short description: %s\n", reinv->item->short_desc);
		printf("Item long description: %s\n", reinv->item->long_desc);
		reinv = reinv->next;
	    }
	    printf("These are the item(s) in the %s\n",
		   g_t_reload->curr_room->short_desc);
	    item_list_t *reroom_items = get_all_items_in_room(g_t_reload->curr_room);
	    while (reroom_items) {
		printf("Item ID: %s\n", reroom_items->item->item_id);
		printf("Short Description: %s\n", reroom_items->item->short_desc);
		printf("Long Description: %s\n", reroom_items->item->long_desc);
		reroom_items = reroom_items->next;
	    }
	}
    }
    return 0;
}
