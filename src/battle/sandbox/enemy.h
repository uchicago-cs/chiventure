#include <stdbool.h>
#include <string.h>
#include "structs.h"
#ifndef ENEMY_H
#define ENEMY_H

/* Function detemines what player goes first
 *
 *  Inputs: 
 *      difficulty: difficulty level of the game
 *  Outputs:
 *      -1 - invalid input
 *      0 - user goes first
 *      1 - enemy goes first    */
int goes_first(int difficulty);


/* Uses the item with the given ID on the player
 *
 *  Inputs: 
 *      e - the enemy using the item
 *      p - the player being attacked
 *      ID - the ID of the item
 *  Outputs:
 *      returns item used    */
int enemy_use_item(enemy_t* e, player_t* p, int ID);


/* Uses the item with the given ID on the player
 *
 *  Inputs: 
 *      name - the enemy's name
 *      inv - the enemy's inventory
 *      armor_list - the enemy's armor
 *      stats - the enemy's stats
 *  Outputs:
 *      returns item used    */
enemy_t* create_enemy_player(char* name, ilist_t* inv, alist_t* armor_list, stats_t* stats);

#endif 