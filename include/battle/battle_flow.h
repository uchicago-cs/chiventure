#ifndef BATTLE_FLOW_H
#define BATTLE_FLOW_H

#include "battle_structs.h"
#include "battle_state.h"
#include "common/utlist.h"
#include "common/common.h"
#include <stdbool.h>
#include <string.h>

/*
 * Allocates a new point in the heap.
 *
 * Parameters:
 *  - x,y: The coordinates of the point
 *
 * Returns:
 *  - A pointer to the point, or NULL if a point
 *    cannot be allocated
 */
int battle_setup();

/*
 * Allocates a new point in the heap.
 *
 * Parameters:
 *  - x,y: The coordinates of the point
 *
 * Returns:
 *  - A pointer to the point, or NULL if a point
 *    cannot be allocated
 */
int set_combatants();

/*
 * Allocates a new point in the heap.
 *
 * Parameters:
 *  - x,y: The coordinates of the point
 *
 * Returns:
 *  - A pointer to the point, or NULL if a point
 *    cannot be allocated
 */
int set_battle();

/*
 * Allocates a new point in the heap.
 *
 * Parameters:
 *  - x,y: The coordinates of the point
 *
 * Returns:
 *  - A pointer to the point, or NULL if a point
 *    cannot be allocated
 */
int run_battle();

/*
 * Allocates a new point in the heap.
 *
 * Parameters:
 *  - x,y: The coordinates of the point
 *
 * Returns:
 *  - A pointer to the point, or NULL if a point
 *    cannot be allocated
 */
int battle_turn();

