#include "battle/battle_ai.h"
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
double damage(combatant_t* target, move_t* move, combatant_t* source)
{
    double dmg, power, src_strength, tar_defense, src_level;
    stat_t* src_stats = source->stats;
    stat_t* tar_stats = target->stats;
    

    tar_defense = (double) tar_stats->defense;
    power = (double) move->damage;
    src_strength = (double) src_stats->strength;
    src_level = (double) src_stats->level;

    
    dmg = ((2.0 * src_level) / 5.0);
    dmg *= ((power * (src_strength / tar_defense)) / 50.0) + 2.0;

    dmg = floor(dmg);
    return dmg;
}
