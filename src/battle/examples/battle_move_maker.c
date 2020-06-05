#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "battle_move_maker.h"
#include "../../playerclass/examples/class-list.h"

/* See battle_move_maker.h */
player_t *build_moves(player_t *player)
{
    move_list_t *moves = move_list();
    move_list_t *tmp;
    player_t *ret_player;
    move_t *ret_move;
    char *player_class_name = player->class->name;

    DL_FOREACH(moves, tmp)
    {
        if(!(strncmp(player_class_name, tmp->c->name, MAX_NAME_LEN)))
        {
            ret_move = move_new(tmp->spell, tmp->id, NULL, true, tmp->damage, 0);
            DL_APPEND(player->moves, ret_move);
            return player;
        }
    }
    return player;
}
