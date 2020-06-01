#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_move_maker.h"
#include "battle/class_list.h"


player_t *add_class_move(player_t *player)
{
    move_list_t *moves = move_list();

    move_list_t *tmp;

    player_t *ret_player;

    move_t *ret_move;

    if(!(strcmp(player->class->name, "Bard")))
    {
        LL_FOREACH(moves, tmp)
        {
            if(strcmp(tmp->c->name, "Bard"))
            {
                ret_move->item = NULL;
                ret_move->id = tmp->id;
                ret_move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
                strncpy(ret_move->info, tmp->spell, MAX_MOVE_INFO_LEN + 1);
                ret_move->attack = true;
                ret_move->damage = tmp->damage;
                ret_move->defense = 0;
                DL_PREPEND(player->moves, ret_move);
                return player;

            }
        }
    }
    else if(!(strcmp(player->class->name, "Wizard")))
    {
        LL_FOREACH(moves, tmp)
        {
            if(strcmp(tmp->c->name, "Wizard"))
            {
                ret_move->item = NULL;
                ret_move->id = tmp->id;
                ret_move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
                strncpy(ret_move->info, tmp->spell, MAX_MOVE_INFO_LEN + 1);
                ret_move->attack = true;
                ret_move->damage = tmp->damage;
                ret_move->defense = 0;
                DL_PREPEND(player->moves, ret_move);
                return player;

            }
        }
    }
    else if(!(strcmp(player->class->name, "Knight")))
    {
        LL_FOREACH(moves, tmp)
        {
            if(strcmp(tmp->c->name, "Knight"))
            {
                ret_move->item = NULL;
                ret_move->id = tmp->id;
                ret_move->info = (char*) calloc(MAX_MOVE_INFO_LEN + 1, sizeof(char));
                strncpy(ret_move->info, tmp->spell, MAX_MOVE_INFO_LEN + 1);
                ret_move->attack = true;
                ret_move->damage = tmp->damage;
                ret_move->defense = 0;
                DL_PREPEND(player->moves, ret_move);
                return player;

            }
        }
    }
    else
    {
        return player;
    }
}
