#ifndef BATTLE_MOVES_H
#define BATTLE_MOVES_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "battle_structs.h"

/* defines max length of class info */
#define MAX_MOVE_INFO_LEN (100)


/* Creates a new move struct 
 * Parameters:
 * - info: a string with a short description of move 
 * - id: move id number 
 * - items: a pointer to the item struct involved with the move 
 * - attack: true if move is attack-based (vs defense), else false 
 * - damage: amount of damage the move does 
 * - defense: amount of defense the move provides 
 * returns: a pointer to the new move 
 */
move_t *move_new(char* info, int id, item_t *items, bool attack,
                 int damage, int defense);


 /* Initialize a move struct 
  * Parameters:
  * - move: a pointer to a move struct in memory
  * - info: a string with a short description of move 
  * - id: move id number 
  * - items: a pointer to the item struct involved with the move 
  * - attack: true if move is attack-based (vs defense), else false 
  * - damage: amount of damage the move does 
  * - defense: amount of defense the move provides 
  * returns:
  * - SUCCESS for successful init
  * - FAILURE for unsuccessful init
  */
int move_init(move_t *move, char* info, int id, item_t *items, bool attack,
                 int damage, int defense);


/* Frees a battle struct from memory 
 * Parameters:
 * - move: a move struct allocated with move_new();
 * Returns: 
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int move_free(move_t *move);

/* For use in testing battle code,
make a test move for each class */

move_t *test_move_bard();

move_t *test_move_cleric();

move_t *test_move_paladin();

move_t *test_move_wizard();


#endif
