#include <stdio.h>
#include <stdlib.h>
#include "save.h"


int main()
{
    game_t *g_t_orig = game_new("Welcome to Chiventure");

    room_t *dorm_t;
    char *room_id = "5";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    dorm_t = room_new(room_id, short_desc, long_desc);

    item_t *ramen_t;
    char *i_item_id = "1234";
    char *i_short_desc = "cup ramen";
    char *i_long_desc = "has already been eaten";
    ramen_t = item_new(i_item_id, i_short_desc, i_long_desc);
    add_item_to_room(dorm_t, ramen_t);
    
    item_t *shirt_t;
    char *s_item_id = "5678";
    char *s_short_desc = "shirt";
    char *s_long_desc = "looks unwashed";
    shirt_t = item_new(s_item_id, s_short_desc, s_long_desc);
    add_item_to_room(dorm_t, shirt_t);
    add_room_to_game(g_t_orig, dorm_t);
    
    room_t *dungeon_t;
    char *d_room_id = "2";
    char *d_short_desc = "dungeon";
    char *d_long_desc = "there are skull and bones in all the jail cells";
    dungeon_t = room_new(d_room_id, d_short_desc, d_long_desc);

    item_t *skull_t;
    char *sk_item_id = "52";
    char *sk_short_desc = "skull";
    char *sk_long_desc = "looks pretty old";
    skull_t = item_new(sk_item_id, sk_short_desc, sk_long_desc);
    add_item_to_room(dungeon_t, skull_t);
    add_room_to_game(g_t_orig, dungeon_t);

    player_t *chad_t;
    chad_t = player_new("chad", 1);
    add_player_to_game(g_t_orig, chad_t);

    set_curr_player(g_t_orig, chad_t);

    g_t_orig->curr_room = dorm_t;

    save(g_t_orig, "save.txt");
    
    return 0;
}
