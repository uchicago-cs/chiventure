#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_move_maker.h"
#include "../../playerclass/examples/class-list.h"

/* Integration with player_class will be amended later.*/
/* See battle_move_maker.h */
int build_moves(combatant_t *c)
{
    move_list_t *moves = move_list();
    move_list_t *tmp;
    move_t *ret_move;

    char *combatant_class_name;
    if(c->class_type != NULL)
    {
        combatant_class_name = c->class_type->name;
    }
    else
    {
        combatant_class_name = "None";
    }
    
    bool appened = false;
    DL_FOREACH(moves, tmp)
    {
        if(!(strncmp(combatant_class_name, tmp->c->name, MAX_NAME_LEN)))
        {
            appened = true;
            ret_move = move_new(tmp->id, tmp->spell, "No Description.", MAG, 
                                NO_TARGET, NO_TARGET, SINGLE, 10, NULL, 
                                tmp->damage, 100, NULL, NULL, NULL, NULL);
            DL_APPEND(c->moves, ret_move);
        }
    }
    if(appened == false)
    {
        return FAILURE;
    }
    return SUCCESS;
}
