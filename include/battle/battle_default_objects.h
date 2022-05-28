#ifndef BATTLE_DEFAULT_OBJECTS_H
#define BATTLE_DEFAULT_OBJECTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_structs.h"
#include "battle/battle_moves.h"
#include "battle/battle_flow_structs.h"

/*
 * Generates a random integer between two bounds
 *
 * Parameters:
 * - min: the minimum included bound
 * - max: the maximum included bound
 * Returns:
 * - a random integer between min and max
 * Note:
 * - must include "srand(time(0));" before using 
    any of these functions in a file
 */
int randnum(int min, int max);


/* Generates a Particular battle consumable based off on description
 * 
 * Parameters:
 * - item_name: the name of the item
 * - desc: the description of the name
 * 
 * Note: This is HARD CODED right now to only be Strength UP
 * TODO: change this to include more cases that Strength Up
 */
battle_item_t *get_consumable_item(char* item_name, char* desc)

/*
 * Generates a random battle weapon from a list of previously-initialized moves
 *
 * parameters: none
 * Returns:
 * -a pointer to a default battle weapon
 */
battle_item_t *get_random_offensive_item();

/* 
 * Generates a random piece of weapon equipment from a previously-initialized 
 * list.
 *
 * Parameters: None
 * Returns:
 *  - a pointer to the weapon
 */
battle_equipment_t *get_random_equip_weapon();

/* 
 * Generates a piece of armor equipment from a previously-initialized 
 * list.
 *
 * Parameters: None
 * Returns:
 *  - a pointer to the armor
 */
battle_equipment_t *get_random_equip_armor();

/* 
 * Generates a piece of accessory equipment from a previously-initialized 
 * list.
 *
 * Parameters: None
 * Returns:
 *  - a pointer to the accessory
 */
battle_equipment_t *get_random_equip_accessory();

/*
 * Generates a random consumable item from a list of previously-initialized consumables
 *
 * Parameters: none
 * Returns:
 * - a pointer to a default item
 */
battle_item_t *get_random_default_consumable();

/*
 * Generates a random move from a list of previously-initialized moves
 *
 * Parameters: none
 * Returns:
 * - a pointer to a default move
 */
move_t *get_random_default_move();

/*
 * Generates a random stat from a list of previously-initialized stats
 *
 * Parameters: none
 * Returns:
 * - a pointer to a default stat
 */
stat_t* get_random_stat();

#endif
