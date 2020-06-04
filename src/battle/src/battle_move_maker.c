#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_move_maker.h"
#include "../../playerclass/examples/class-list.c"

/* See battle_move_maker.h */
player_t *add_class_move(player_t *player)
{
    move_list_t *moves = move_list();

    move_list_t *tmp;

    player_t *ret_player;

    move_t *ret_move;

    char *player_class_name = player->class->name;

    LL_FOREACH(moves, tmp)
    {
        if(!(strcmp(player_class_name, tmp->c->name)))
        {
            ret_move = move_new(tmp->spell, tmp->id, NULL, true, tmp->damage, 0);
            DL_PREPEND(player->moves, ret_move);
            return player;
        }
    }
    return player;
}
