#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_move_maker.h"
#include "../../playerclass/examples/class-list.h"

/* See battle_move_maker.h */
int build_moves(combatant_t *c)
{
    move_list_t *moves = move_list();
    move_list_t *tmp;
    move_t *ret_move;

    char *combatant_class_name;
    if(c->class != NULL)
    {
        combatant_class_name = c->class->name;
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
            ret_move = move_new(tmp->spell, tmp->id, NULL, true, tmp->damage, 0);
            DL_APPEND(c->moves, ret_move);
        }
    }
    if(appened == false)
    {
        return FAILURE;
    }
    return SUCCESS;
}


/* see battle_move_maker.h */
int add_move(combatant_t *combatant, move_t *move) {
    assert(combatant != NULL);
    assert(move != NULL);

    move_t *last_move = combatant->moves;
    
    if (combatant->moves == NULL){
        combatant->moves = move;
        return SUCCESS;
    }

    while (last_move->next != NULL) {
        last_move = last_move->next;
    }
    last_move->next = move;
    return SUCCESS;
}
