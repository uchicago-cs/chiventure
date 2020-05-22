#include "AI.h"
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

/* Given a moves list, function will find the 
 *      move dealing the least damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_easy(combatant_t* player, combatant_t* enemy)
{
    move_t* weakest_move = enemy->moves;
    move_t *temp;

    DL_FOREACH(enemy->moves, temp)
    {
        double least_damage = 0;
        double cur_damage = damage(player, temp, enemy);

        if (temp->next == NULL)
        {
            return weakest_move;
        }
        else if (cur_damage < least_damage)
        {
            weakest_move = temp;
        }
    }
    return weakest_move;
}

/* Given a moves list, function will find the 
 *      move dealing the most damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_hard(combatant_t* player, combatant_t* enemy)
{
    move_t* strongest_move = enemy->moves;
    move_t *temp;

    DL_FOREACH(enemy->moves, temp)
    {
        double most_damage = 0;
        double cur_damage = damage(player, temp, enemy);

        if (temp->next == NULL)
        {
            return strongest_move;
        }
        else if (cur_damage > most_damage)
        {
            strongest_move = temp;
        }
    }
    return strongest_move;
}

/* see AI.h */
double damage(combatant_t* player, move_t* move, combatant_t* enemy)
{
    double dmg, power, enemy_strength, defense;
    stat_t* e_stats = enemy->stats;
    stat_t* p_stats = player->stats;
    
    //Inquire about armor
    defense = (double) p_stats->defense + (double) player->armor->defense;
    power = (double) move->damage;

    
    dmg = ((2.0 * (double) e_stats->level) / 5.0) + 2.0;
    dmg *= ((power * ((double) e_stats->strength / defense)) / 50.0) + 2.0;

    return dmg;
}
