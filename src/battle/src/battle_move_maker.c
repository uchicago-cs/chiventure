#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


player_t *add_class_move(player_t *player)
{
    move_list_t *moves = move_list();

    move_list_t *tmp;

    player_t *ret_player;

    move_t *ret_move;

    if(!(strcmp(player->class, "Bard")
    {
        DL_FOREACH(moves, tmp)
        {
            if(strcmp(tmp->c, "bard")
            {
                ret_move->item = NULL;
                ret_move->id = tmp->id;
                strncpy(ret_move->info, tmp->spell, MAX_MOVE_INFO_LEN + 1);
                ret_move->attack = true;
                ret_move->damage = tmp->damage;
                ret_move->defense = 0;
                DL_PREPEND(player->moves, ret_move);
                return player;

            }
        }
    }
    else if(!(strcmp(player->class, "Wizard")
    {
        DL_FOREACH(moves, tmp)
        {
            if(strcmp(tmp->c, "wizard")
            {
                ret_move->item = NULL;
                ret_move->id = tmp->id;
                strncpy(ret_move->info, tmp->spell, MAX_MOVE_INFO_LEN + 1);
                ret_move->attack = true;
                ret_move->damage = tmp->damage;
                ret_move->defense = 0;
                DL_PREPEND(player->moves, ret_move);
                return player;

            }
        }
    }
    else if(!(strcmp(player->class, "Knight")
    {
        DL_FOREACH(moves, tmp)
        {
            if(strcmp(tmp->c, "knight")
            {
                ret_move->item = NULL;
                ret_move->id = tmp->id;
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
