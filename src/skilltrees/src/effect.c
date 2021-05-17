#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/effect.h"


// See effect.h
stat_mod_effect_t* define_stat_mod_effect(char* stat_mod_effect_name, char** stat_names, double* modifications, int* durations, int num_stats, chiventure_ctx_t* ctx)
{
    assert(ctx != NULL);
    stat_mod_effect_t* new_stat_effect = (stat_mod_effect_t*)malloc(sizeof(stat_mod_effect_t));
    assert(new_stat_effect != NULL);
    new_stat_effect->stat_mod_effect_name = stat_mod_effect_name;
    new_stat_effect->stats = (stat_t**)malloc(num_stats*sizeof(stat_t*));
    assert(new_stat_effect->stats != NULL);
    stats_hash_t* sh = ctx ->game->curr_player->player_stats;
    stats_t* curr;
    for(int i = 0; i < num_stats; i++)
    {
        HASH_FIND_STR(sh, stat_names[i], curr);
        
        if(curr == NULL)
        {
            printf("Given player statistic does not exist.");
            return NULL;
        }
        else
        {
            new_stat_effect->stats[i]=curr;
        }
    }
    new_stat_effect->modifications = modifications;
    new_stat_effect->durations = durations;
    new_stat_effect->num_stats=num_stats;
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
effect_t* make_stat_effect(stat_mod_effect_t* stat_mod_effect)
{
    assert(stat_mod_effect != NULL);
    effect_t* new_effect = (effect_t*)malloc(sizeof(effect_t));
    new_effect->effect_type = STATISTIC_MOD;
    new_effect->data.s = stat_mod_effect;
    return stat_mod_effect;
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
int execute_stat_mod_effect(stat_mod_effect_t* stat_mod_effect, chiventure_ctx_t* ctx)
{
    assert(ctx != NULL);
    effects_global_t* global_effect = global_effect_new(stat_mod_effect->stat_mod_effect_name);
    stat_effect_t* st_effect = stat_effect_new(global_effect);
    effects_hash_t* et = ctx->game->curr_player->player_effects;
    assert(et != NULL);
    int check = apply_effect(et, st_effect, stat_mod_effect->stats, stat_mod_effect->modifications, stat_mod_effect->durations, stat_mod_effect->num_stats);
    assert(check == SUCCESS);
    return SUCCESS;
}

// See effect.h
int execute_move_effect(chiventure_ctx_t* ctx, move_effect_t* effect)
{
    assert(ctx != NULL);
    assert(effect != NULL);
    //ctx->game->curr_player->moves currently hasn't been implemented. We are working with battles to do so.
    //add_move(ctx->game->curr_player->moves, effect->move);
    return SUCCESS;
}

// See effect.h
int execute_att_effect(att_effect_t* att_effect)
{
    // TODO
    return 0;
}