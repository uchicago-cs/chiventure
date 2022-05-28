#include "battle/battle_ai.h"
#include "battle/battle_logic.h"
#include <math.h>

/* See battle_ai.h */
move_t* give_move(combatant_t* player, combatant_t* enemy, difficulty_t difficulty)
{
    if (player->is_friendly != true)
    {
        fprintf(stderr, "Error! Player is not friendly!");
    }
    if (enemy->is_friendly != false)
    {
        fprintf(stderr, "Error! Enemy is friendly!");
    }
    switch (difficulty)
    {
    case BATTLE_AI_GREEDY:
        return (find_greedy(player, enemy));
        break;
    case BATTLE_AI_RANDOM:
        return (find_random(player, enemy));
        break;
    default:
        fprintf(stderr, "Error!");
        break;
    }
}

/* See battle_ai.h */
move_t* find_random(combatant_t* player, combatant_t* enemy)
{
    int count;
    move_t *temp;
    move_t *random_move = NULL;

    DL_COUNT(enemy->moves, temp, count);
    int index = rand() % count;

    int i = 0;
    DL_FOREACH(enemy->moves, temp)
    {
        i++;
        if (i == index)
        {
            random_move = temp;
        }
        
    }
    return random_move;
}

/* See battle_ai.h */
move_t* find_greedy(combatant_t* player, combatant_t* enemy)
{
    move_t* strongest_move = enemy->moves;
    move_t *temp;
    double most_damage = 0.0;

    DL_FOREACH(enemy->moves, temp)
    {
        
        double cur_damage = damage(player, temp, enemy);
        if (temp == NULL)
        {
            return strongest_move;
        }
        else if (cur_damage >= most_damage)
        {
            strongest_move = temp;
            most_damage = cur_damage;
        }
    }
    return strongest_move;
}

/* See battle_ai.h */
int damage(combatant_t* target, move_t* move, combatant_t* source)
{
    /* If the user does not have enough sp or the item a move requires,
     * damage will return 0 damage. Moves that do no damage will also
     * return 0 damage. */   
    if (source->stats->sp < move->sp_cost || move->dmg_type == NO_DAMAGE) 
    {
        return 0;
    }
    if (move->req_item != NULL && 
        find_battle_item(source->items, move->req_item->name) == NULL)
    {
        return 0;
    }

    /* Damage calculation values are set with the stats relevant to
     * to the move type and calculated with doubles.  */
    double dmg, base_dmg, src_lvl, src_atk, tgt_def;
    base_dmg = (double) move->damage;
    src_lvl = (double) source->stats->level;
    
    if (move->dmg_type == PHYS)
    {
        src_atk = (double) source->stats->phys_atk;
        tgt_def = (double) target->stats->phys_def;
    } 
    else 
    {
        src_atk = (double) source->stats->mag_atk;
        tgt_def = (double) target->stats->mag_def;
    }

    dmg = ((2.0 * src_lvl) / 5.0);
    dmg *= (((base_dmg * (src_atk / tgt_def)) / 50.0) + 2.0);
    dmg = round(dmg);

    return (int) dmg;
}

