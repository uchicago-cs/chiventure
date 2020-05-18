#include "AI.h"
#include "utlist.h"

/* see AI.h */
move_t* give_move(int difficulty, player_t* player, enemy_t* enemy)
{
    if (difficulty == 1)
    {
        return easy_move(player);
    }
    else if (difficulty == 2)
    {
        return medium_move(player);
    }
    else
    {
        return hard_move(player);
    }
}

/* see AI.h */
move_t* easy_move(player_t* player, enemy_t* enemy)
{
    return find_easy(player);
}

/* see AI.h */
move_t* medium_move(player_t* player, enemy_t* enemy)
{
    int i, count;
    LL_COUNT(enemy->moves, m, count);
    random = rand() % count + 1;
    move_t* random_move = enemy->moves->move;
    mlist_t *temp = enemy->moves;
    for (i = 0; i < random; i++)
    {
        temp = temp->next;
    }
    random_move = temp->move;
    return random_move;
}

/* see AI.h */
move_t* hard_move(player_t* player, enemy_t* enemy)
{
    return find_hard(player);
}

/* Given a moves list, function will find the 
 *      move dealing the least damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_easy(player_t* player, enemy_t* enemy)
{
    move_t* weakest_move = enemy->moves->move;
    mlist_t *temp;
    for (temp = enemy->moves; temp != NULL; temp = temp->next)
    {
        if (temp->next == NULL)
        {
            return weakest_move;
        }
        double damage = damage(player, temp->move, enemy);
        double next_damage = damage(player, temp->next->move, enemy);
        else if (damage > next_damage)
        {
            weakest_move = temp->next->move;
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
    move_t* hardest_move = enemy->moves->move;
    mlist_t *temp;
    for (temp = enemy->moves; temp != NULL; temp = temp->next)
    {
        if (temp->next == NULL)
        {
            return hardest_move;
        }
        double damage = damage(player, temp->move, enemy);
        double next_damage = damage(player, temp->next->move, enemy);
        else if (damage < next_damage)
        {
            hardest_move = temp->next->move;
        }
    }
    return hardest_move;
}

/* see AI.h */
double damage(player_t* player, move_t* move, enemy_t* enemy)
{
    double damage = 0.0;
    damage = (((((2 * enemy->level) / 5) + 2) * move->damage * (enemy->strength / (player->defense + player->armor->defense))) / 50) + 2;
    return damage;
}