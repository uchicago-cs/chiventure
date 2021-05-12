/* 
 * Basic functionality for the class struct. 
 */
#ifndef CLASS_H
#define CLASS_H

#include "libobj/obj.h"
#include "common/utlist.h"
#include "playerclass/class_structs.h"
#include "game-state/stats.h"

/* 
 * Allocates memory for a new player class. Only creates a deep copies of the 
 * strings name, short description, and long description.
 * 
 * Parameters:
 *  - name, shortdesc, longdesc: Name and descriptions of the class
 *  - attr: the attributes of the class
 *  - stat: the stats of the class
 *  - effect: temporary stats of the class
 * 
 * Returns:
 *  - a pointer to the allocated class memory
 *  - NULL on error
 */
class_t* class_new(char* name, char* shortdesc, char* longdesc,
                   obj_t* attr, stats_hash_t* stat, effects_hash_t* effect);

/* 
 * Initializes values for a player class. Only creates a deep copies of the 
 * strings name, short description, and long description.
 * 
 * Does not initialize fields related to skills and skill trees. If those
 * features are enabled, call class_add_skills() as well.
 * 
 * Parameters:
 *  - class: a pointer to the class to be initialized
 *  - name, shortdesc, longdesc: Name and descriptions of the class
 *  - attr: the attributes of the class
 *  - stat: the stats of the class
 *  - effect: temporary stats of the class
 * 
 * Returns:
 *  - EXIT_SUCCESS on successful initialization
 *  - EXIT_FAILURE otherwise
 */
int class_init(class_t* class, char* name, char* shortdesc, char* longdesc,
               obj_t* attr, stats_hash_t* stat, effects_hash_t* effect);

/*
 * Adds skill inventories and a skill tree to a pre existing player class. If a
 * game does not have class skill feautres enabled, do not call this function.
 * 
 * Parameters:
 *  - class: pointer to a class where skills are to be added.
 *  - combat: pointer to a skill inventory for combat skills.
 *  - non-combat: pointer to a skill inventory for non-combat skills.
 *  - skilltree: pointer to a skill tree for the class.
 *  - NOTE: The skill related fields may be NULL, if those feautres are
 *          disabled. However, we recommend that they be filled with empty 
 *          allocated structs instead. 
 * Returns:
 *  - EXIT_SUCCESS on successful initialization (As of now, this always occurs; the function is not finished).
 *  - EXIT_FAILURE otherwise.
 */
int class_add_skills(class_t* class, skill_inventory_t* combat, 
                     skill_inventory_t *noncombat, skill_tree_t* skilltree);

/*
 * Frees a class and strings created by class_new.
 * 
 * Parameters:
 *  - class: The class to free
 * 
 * Returns:
 *  - Always return EXIT_SUCCESS
 */
int class_free(class_t* class);

#endif /* CLASS_H */