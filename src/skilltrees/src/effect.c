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
    stat_mod_effect_t* new_stat_effect = (stat_mod_effect_t*)malloc(sizeof(stat_mod_effect_t));
    new_stat_effect->stat_name = stat_name;
    new_stat_effect->modification = mod;
    new_stat_effect->duration = duration;

    return new_stat_effect;
}

// See effect.h
damage_effect_t* define_damage_effect(int mod)
{
    damage_effect_t* new_damage_effect = (damage_effect_t*)malloc(sizeof(damage_effect_t));
    new_damage_effect->damage = mod;

    return new_damage_effect;
}

// See effect.h
att_effect_t* define_att_effect(char* obj_id, char* att_id, union data mod)
{
    // TODO
}

// See effect.h
effect_t* make_stat_effect(stat_mod_effect_t* stat_effect)
{
    // TODO
}

// See effect.h
effect_t* make_damage_effect(damage_effect_t* damage_effect)
{
    // TODO
}

// See effect.h
effect_t* make_att_effect(att_effect_t* att_effect)
{
    // TODO
}

// See effect.h
int execute_stat_effect(stat_mod_effect_t* stat_effect)
{
    // TODO
}

// See effect.h
int execute_damage_effect(damage_effect_t* damage_effect)
{
    // TODO
}

// See effect.h
int execute_att_effect(att_effect_t* att_effect)
{
    // TODO
}

// See effect.h
effects_linked_list_t* init_linked_list()
{
    effects_linked_list_t* ll = (effects_linked_list_t*)malloc(sizeof(effects_linked_list_t));
    if(ll == NULL)
    {
        fprintf(stderr, "Could not allocate memory for new linked list \n");
        exit(1);
    }
    ll -> head = NULL;
    ll -> num_effects = 0;
    return ll;
}

// See effect.h
int add_node (effects_linked_list_t* ll, effect_t* effect)
{
    effect_node_t* node = (effect_node_t*)malloc(sizeof(effect_node_t));
    if(ll == NULL)
    {
        fprintf(stderr, "Could not allocate memory for new node \n");
        exit(1);
    }
    node -> data = effect;
    node -> next = NULL;
    if (ll -> head == NULL)
    {
        ll -> head = node;
        ll -> num_effects = 1;
        return 0;
    }
    effect_node_t* curr = ll -> head;
    while(curr -> next != NULL)
    curr = curr -> next;
    curr -> next = node;
    ll -> num_effects += 1;
    return 0;
}

// See effect.h
int remove_node (effects_linked_list_t* ll, effect_t* effect)
{
    // TODO
}
