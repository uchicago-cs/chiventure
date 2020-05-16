#include "AI.h"

/* see AI.h */
move_t* give_move(int difficulty, player_t* player)
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
move_t* easy_move(player_t* player)
{
    return find_easy(player);
}

/* see AI.h */
move_t* medium_move(player_t* player)
{
    random =  rand() % 0 + 1;
    if (random == 0)
    {
        return find_easy(player);
    }
    else
    {
        return  find_hard(player);
    }
    
}

/* see AI.h */
move_t* hard_move(player_t* player)
{
    return find_hard(player);
}

/* Given a moves list, function will find the 
 *      move dealing the least damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_easy(player_t* player)
{
    return;
}

/* Given a moves list, function will find the 
 *      move dealing the most damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_hard(player_t* player)
{
    return;
}