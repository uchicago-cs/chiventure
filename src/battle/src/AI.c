#include "battle/AI.h"
#include <math.h>

/* see AI.h */
move_t* give_move(int difficulty, combatant_t* player, combatant_t* enemy)
{
    if (player->is_friendly != true)
    {
        fprintf(stderr, "Error! Player is not friendly!");
    }
    if (enemy->is_friendly != false)
    {
        fprintf(stderr, "Error! Enemy is friendly!");
    }
    if (difficulty == 1)
    {
        return easy_move(player, enemy);
    }
    else if (difficulty == 2)
    {
        return medium_move(player, enemy);
    }
    else
    {
        return hard_move(player, enemy);
    }
}

/* see AI.h */
move_t* easy_move(combatant_t* player, combatant_t* enemy)
{
    return find_easy(player, enemy);
}

/* see AI.h */
move_t* medium_move(combatant_t* player, combatant_t* enemy)
{
    int i, count, random;
    move_t *move_struct;

    DL_COUNT(enemy->moves, move_struct, count);
    random = rand() % count + 1;

    move_t* random_move = enemy->moves;
    for (i = 0; i < random; i++)
    {
        if (random_move->next == NULL)
        {
            return random_move;
        }
        random_move = random_move->next;
    }

    return random_move;
}

/* see AI.h */
move_t* hard_move(combatant_t* player, combatant_t* enemy)
{
    return find_hard(player, enemy);
}

/* see AI.h */
move_t* find_easy(combatant_t* player, combatant_t* enemy)
{
    move_t* weakest_move = enemy->moves;
    move_t *temp;
    double least_damage = 10000;

    DL_FOREACH(enemy->moves, temp)
    {
        
        double cur_damage = damage(player, temp, enemy);

        if (temp == NULL)
        {
            return weakest_move;
        }
        else if (cur_damage < least_damage)
        {
            weakest_move = temp;
            least_damage = cur_damage;
        }
    }
    return weakest_move;
}

/* see AI.h */
move_t* find_hard(combatant_t* player, combatant_t* enemy)
{
    move_t* strongest_move = enemy->moves;
    move_t *temp;
    double most_damage = 0;

    DL_FOREACH(enemy->moves, temp)
    {
        
        double cur_damage = damage(player, temp, enemy);

        if (temp == NULL)
        {
            return strongest_move;
        }
        else if (cur_damage > most_damage)
        {
            strongest_move = temp;
            most_damage = cur_damage;
        }
    }
    return strongest_move;
}

/* see AI.h */
double damage(combatant_t* player, move_t* move, combatant_t* enemy)
{
    double dmg, power, enemy_strength, defense, level;
    stat_t* e_stats = enemy->stats;
    stat_t* p_stats = player->stats;
    
    //Inquire about armor
    defense = (double) p_stats->defense;
    power = (double) move->damage;
    enemy_strength = (double) e_stats->strength;
    level = (double) e_stats->level;

    
    dmg = ((2.0 * level) / 5.0);
    dmg *= ((power * (enemy_strength / defense)) / 50.0) + 2.0;

    floor(dmg);
    return dmg;
}
