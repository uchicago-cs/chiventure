#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/effect.h"


/* See effect.h */
player_stat_effect_t* define_player_stat_effect(char* player_stat_effect_name, char** stat_names, double* modifications, int* durations, int num_stats, chiventure_ctx_t* ctx)
{
    if (ctx == NULL)
    {
        fprintf(stderr, "Error: Null context object passed \n");
        return NULL;
    }
    player_stat_effect_t* new_stat_effect = (player_stat_effect_t*)malloc(sizeof(player_stat_effect_t));
    if (new_stat_effect == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for new player stat effect \n");
        return NULL;
    }
    new_stat_effect->player_stat_effect_name = player_stat_effect_name;
    new_stat_effect->stats = (stats_t**)malloc(num_stats*sizeof(stats_t*));
    if (new_stat_effect->stats == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for statistics in the effect \n");
        return NULL;
    }
    stats_hash_t* sh = ctx ->game->curr_player->player_stats;
    stats_t* curr;
    for (int i = 0; i < num_stats; i++)
    {
        HASH_FIND_STR(sh, stat_names[i], curr);
        
        if (curr == NULL)
        {
            fprintf(stderr, "%s", stat_names[i]);
            fprintf(stderr, "Error: Given player statistic does not exist. \n");
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

/* See effect.h */
move_effect_t* define_move_effect(move_t* move)
{
    move_effect_t* new_move_effect = (move_effect_t*)malloc(sizeof(move_effect_t));
    new_move_effect->move = move;

    return new_move_effect;
}

/* See effect.h */
item_attr_effect_t* define_item_attr_effect(item_t* item, char* att_id, enum attribute_tag att_tag, attribute_value_t attribute_mod) 
{
    if(item == NULL)
    {
        fprintf(stderr, "Item not found \n");
        return NULL;
    }
    attribute_t* attr = get_attribute(item, att_id);
    if (attr == NULL)
    {
        fprintf(stderr, "Attribute not found \n");
        return NULL;
    }
    item_attr_effect_t* item_attr_effect = (item_attr_effect_t*)malloc(sizeof(item_attr_effect_t));
    if (item_attr_effect == NULL)
    {
        fprintf(stderr, "Malloc Failed \n");
    }
    item_attr_effect -> item = item;
    if(item_attr_effect -> item == NULL)
    {
        fprintf(stderr, "Failed to set item properly \n");
    }
    item_attr_effect -> att_id = att_id;
    item_attr_effect -> att_tag = att_tag;
    
    if (att_tag == DOUBLE)
    {
        (item_attr_effect -> attribute_mod.double_val) = attribute_mod.double_val;
    }
    if (att_tag == BOOLE)
    {
        (item_attr_effect -> attribute_mod.bool_val) = attribute_mod.bool_val;
    }
    if (att_tag == CHARACTER)
    {
        (item_attr_effect -> attribute_mod.char_val) = attribute_mod.char_val;
    }
    if (att_tag == STRING)
    {
        (item_attr_effect -> attribute_mod.str_val) = attribute_mod.str_val;
    }
    if (att_tag == INTEGER)
    {
        (item_attr_effect -> attribute_mod.int_val) = attribute_mod.int_val;
    }

    return item_attr_effect;
}

/* See effect.h */
item_stat_effect_t* define_item_stat_effect()
{
    //TODO
    return NULL;
}

/* See effect.h */
effect_t* make_player_stat_effect(player_stat_effect_t* player_stat_effect)
{
    if (player_stat_effect == NULL)
    {
        fprintf(stderr, "Error: Given NULL player stat effect");
        return NULL;
    }
    effect_t* new_effect = (effect_t*)malloc(sizeof(effect_t));
    if (new_effect == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for effect");
        return NULL;
    }
    new_effect->effect_type = PLAYER_STATISTIC_MOD;
    new_effect->data.s = player_stat_effect;
    return new_effect;
}

/* See effect.h */
effect_t* make_move_effect(move_effect_t* move_effect)
{
    if (move_effect == NULL)
    {
        fprintf(stderr, "Error: Given NULL move effect");
        return NULL;
    }
    effect_t* new_effect = (effect_t*)malloc(sizeof(effect_t));
    if (new_effect == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for effect");
        return NULL;
    }
    new_effect->effect_type = MOVE_UNLOCK;
    new_effect->data.m = move_effect;
    return new_effect;
}

/* See effect.h */
effect_t* make_item_attr_effect(item_attr_effect_t* item_attr_effect)
{
    if (item_attr_effect == NULL)
    {
        fprintf(stderr, "Error: Given NULL item attribute effect");
        return NULL;
    }
    effect_t* new_attr_effect = malloc(sizeof(effect_t));
    if (new_attr_effect == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for effect");
        return NULL;
    }
    new_attr_effect->effect_type = ITEM_ATTRIBUTE_MOD;
    new_attr_effect->data.i_a = item_attr_effect;
    return new_attr_effect;
}

/* See effect.h */
effect_t* make_item_stat_effect(item_stat_effect_t* item_stat_effect)
{
    //TODO 
    return NULL;
}

/* See effect.h */
int execute_player_stat_effect(player_stat_effect_t* player_stat_effect, chiventure_ctx_t* ctx)
{
    assert(ctx != NULL);
    effects_global_t* global_effect = global_effect_new(player_stat_effect->player_stat_effect_name);
    stat_effect_t* st_effect = stat_effect_new(global_effect);
    effects_hash_t* et = ctx->game->curr_player->player_effects;
    effects_hash_t** pointer_to_et = malloc(sizeof(effects_hash_t**));
    if (et == NULL)
    {
        fprintf(stderr, "Error: Effect hash table does not exist \n");
        return FAILURE;
    }
    if (pointer_to_et == NULL)
    {
        fprintf(stderr, "Error: Pointer to effect hash table does not exist \n");
        return FAILURE;
    }
    int check = apply_effect(pointer_to_et, st_effect, player_stat_effect->stats, player_stat_effect->modifications, player_stat_effect->durations, player_stat_effect->num_stats);
    if (check == SUCCESS)
    {
        return check;
    }
    else
    {
        fprintf(stderr, "An error occurred \n");
        return check;
    }
}

/* See effect.h */
int execute_move_effect(chiventure_ctx_t* ctx, move_effect_t* effect)
{
    assert(ctx != NULL);
    assert(effect != NULL);
    add_move(ctx->game->curr_player, effect->move); 
    return SUCCESS;
}

/* See effect.h */
int execute_item_attr_effect(item_attr_effect_t* item_attr_effect)
{
    assert(item_attr_effect != NULL);
    item_t* item = item_attr_effect -> item;
    char* attr_id = item_attr_effect -> att_id;
    enum attribute_tag att_tag = item_attr_effect -> att_tag;
    if (att_tag == DOUBLE)
    {
        double mod = item_attr_effect -> attribute_mod.double_val;
        int check = set_double_attr(item, attr_id, mod);
        if (check == FAILURE)
        {
            fprintf(stderr, "Failed to set value correctly \n");
            return FAILURE;
        }
    }
    if (att_tag == BOOLE)
    {
        bool mod = item_attr_effect -> attribute_mod.bool_val;
        int check = set_bool_attr(item, attr_id, mod);
        if (check == FAILURE)
        {
            fprintf(stderr, "Failed to set value correctly \n");
            return FAILURE;
        }
    }
    if (att_tag == CHARACTER)
    {
        char mod = item_attr_effect -> attribute_mod.char_val;
        int check = set_char_attr(item, attr_id, mod);
        if (check == FAILURE)
        {
            fprintf(stderr, "Failed to set value correctly \n");
            return FAILURE;
        }
    }
    if (att_tag == STRING)
    {
        char* mod = item_attr_effect -> attribute_mod.str_val;
        int check = set_str_attr(item, attr_id, mod);
        if (check == FAILURE)
        {
            fprintf(stderr, "Failed to set value correctly \n");
            return FAILURE;
        }
    }
    if (att_tag == INTEGER)
    {
        int mod = item_attr_effect -> attribute_mod.int_val;
        int check = set_char_attr(item, attr_id, mod);
        if (check == FAILURE)
        {
            fprintf(stderr, "Failed to set value correctly \n");
            return FAILURE;
        }
    }
    return SUCCESS;
}

/* See effect.h */
int execute_item_stat_effect(item_stat_effect_t* item_stat_effect)
{
    //TODO
    return 0;
}