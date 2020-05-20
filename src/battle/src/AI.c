#include "AI.h"
#include "utlist.h"

/* see AI.h */
move_t* give_move(int difficulty, player_t* player, enemy_t* enemy)
{
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
move_t* easy_move(player_t* player, enemy_t* enemy)
{
    return find_easy(player, enemy);
}

/* see AI.h */
move_t* medium_move(player_t* player, enemy_t* enemy)
{
    int i, count, random;
    move_t *elem;

    DL_COUNT(enemy->moves, elem, count);
    random = rand() % count + 1;

    move_t* random_move = enemy->moves;
    for (i = 0; i < random; i++)
    {
        random_move = random_move->next;
    }

    return random_move;
}

/* see AI.h */
move_t* hard_move(player_t* player, enemy_t* enemy)
{
    return find_hard(player, enemy);
}

/* Given a moves list, function will find the 
 *      move dealing the least damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_easy(player_t* player, enemy_t* enemy)
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
move_t* find_hard(player_t* player, enemy_t* enemy)
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
double damage(player_t* player, move_t* move, enemy_t* enemy)
{
    double dmg = 0.0;
    stats_t *enemy_stat = enemy->stats;
    stats_t *player_stat = player->stats;

    // dmg = (((((2 * enemy_stat->level) / 5) + 2) * move->damage * (enemy_stat->strength / (player_stat->defense + player->armor->defense))) / 50) + 2;
    return dmg;
}
