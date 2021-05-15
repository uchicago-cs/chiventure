#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/effect.h"


// This code is not finalized; we're going to make more changes to implement
// it into the hash table later on

//See effect.h
stat_mod_effect_t* define_stat_mod_effect(char* stat_name, int modification, int duration)
{
    /* This is a very basic implementation that will be changed to check
     * if the stat exists in the hash table belonging to the player when
     * #898 gets merged
     */

    // TODO - Complete Implementation (Rohan)
    stat_mod_effect_t* new_stat_effect = (stat_mod_effect_t*)malloc(sizeof(stat_mod_effect_t));
    new_stat_effect->stat_name = stat_name;
    new_stat_effect->modification = modification;
    new_stat_effect->duration = duration;

    return new_stat_effect;
}

// See effect.h
move_effect_t* define_move_effect(move_t move)
{
    move_effect_t* new_move_effect = (move_effect_t*)malloc(sizeof(move_effect_t));
    new_move_effect->move = move;

    return new_move_effect;
}

// See effect.h
att_effect_t* define_att_effect(char* obj_id, char* att_id, union data mod)
{
    // TODO
    return NULL;
}

// See effect.h
effect_t* make_stat_effect(stat_mod_effect_t* stat_effect)
{
    // TODO
    return NULL;
}

// See effect.h
effect_t* make_move_effect(move_effect_t* move_effect)
{
    assert(move_effect != NULL);
    effect_t* new_effect = (effect_t*)malloc(sizeof(effect_t));
    new_effect->effect_type = MOVE_UNLOCK;
    new_effect->data.m = move_effect;
    return new_effect;
}

// See effect.h
effect_t* make_att_effect(att_effect_t* att_effect)
{
    // TODO
    return NULL;
}

// See effect.h
int execute_stat_mod_effect(stat_mod_effect_t* stat_effect)
{
    // TODO
    return 0;
}

// See effect.h
int execute_move_effect(skill_inventory_t* inventory, combatant_t* player)
{
    assert(player != NULL);
    assert(inventory != NULL);
    skill_t** skills = inventory->active;
    int size = sizeof skills / sizeof skills[0];
    for(int x = 0; x < size; x++){
        if(skills[x]->skill_effect->effect_type == MOVE_UNLOCK){
            //Waiting on pull request from battles to go through for the add_move function in include/battle/battle_move_maker.h
            add_move(player, skills[x]->skill_effect->data.m->move);
        }
    }
    return SUCCESS;
}

// See effect.h
int execute_att_effect(att_effect_t* att_effect)
{
    // TODO
    return 0;
}


