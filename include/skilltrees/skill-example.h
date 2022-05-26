/*
 * Skill examples for battle demo
 */

#ifndef INCLUDE_SKILL_EXAMPLE_H_
#define INCLUDE_SKILL_EXAMPLE_H_
#include "skilltrees/inventory.h"


/* ============================== */
/* == EXAMPLE EFFECT FUNCTIONS == */
/* ============================== */
/*
 * Skill functions for attacks
 *
 * Parameters:
 *  - args: user inputted args
 *
 * Returns:
 *  - A string representing damage dealt
 */


/* Diss Track skill effect deals 8 damage */
char* effect_diss_track(char* args);


/* Fireball skill effect deals 10 damage */
char* effect_fireball(char* args);


/* Sword Slash skill effect deals 9 damage */
char* effect_sword_slash(char* args);


/* =============================== */
/* == EXAMPLE CLASS INVENTORIES == */
/* =============================== */

/* 
 * Generates an example skill inventory for a Bard 
 *
 * Returns:
 *  - A skill inventory containing Diss Track.
 */
skill_inventory_t* bard_inventory();

/* 
 * Generates an example skill inventory for a Wizard 
 *
 * Returns:
 *  - A skill inventory containing Fireball.
 */
skill_inventory_t* wizard_inventory();

/* 
 * Generates an example skill inventory for a Knight 
 *
 * Returns:
 *  - A skill inventory containing Sword Slash.
/*
skill_inventory_t* knight_inventory();

/*
* adds a combined skill to the player
* takes in: CTX
* Puts out: VOID
*/

void combined_skill(chiventure_ctx_t* ctx);


/*
* adds a sequential skill to the player
* takes in: CTX
* Puts out: VOID
*/
void sequential_skill(chiventure_ctx_t* ctx);


/*
* adds a conditional skill to the player
* takes in: CTX
* Puts out: VOID
*/
void conditional_skill(chiventure_ctx_t* ctx)


#endif /* INCLUDE_SKILL_EXAMPLE_H_ */
