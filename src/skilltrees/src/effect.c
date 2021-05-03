#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/effect.h"

//See effect.h
stat_effect_t* define_stat_effect(char* stat_name, int mod, int duration)
{
    stat_effect_t* new_stat_effect = (stat_effect_t*)malloc(sizeof(stat_effect_t));
    new_stat_effect->stat_name = stat_name;
    new_stat_effect->mod = mod;
    new_stat_effect->duration = duration;

    return new_stat_effect;
}

//See effect.h
damage_effect_t* define_damage_effect(int mod)
{
    damage_effect_t* new_damage_effect = (damage_effect_t*)malloc(sizeof(damage_effect_t));
    new_damage_effect->mod = mod;

    return new_damage_effect;
}

//See effect.h
att_effect_t* define_att_effect(char* obj_id, char* att_id, union data mod)
{
    //TODO
}

//See effect.h
effect_t* make_stat_effect(stat_effect_t* stat_effect)
{
    //TODO
}

//See effect.h
effect_t* make_damage_effect(damage_effect_t* damage_effect)
{
    //TODO
}

//See effect.h
effect_t* make_att_effect(att_effect_t* att_effect)
{
    //TODO
}