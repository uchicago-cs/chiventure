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
 * Initializes values for a player class,
 * created by combining two existing classes to form a multiclass.
 * 
 * Requires btoh classes to be already implemented.
 * Can be used multiple times to create more complicated multiclasses.
 *
 * Paramaters:
 *  - base_class: the character's base class (their current class).
 *    this class will be used to determine base stats.
 *  - second_class: the class being added to the original class.
 *  - name: the name of the multiclass.
 *
 * Returns:
 *  - a pointer to the allocated class memory
 *  - NULL on error
 */
class_t* multiclass(class_t* base_class, class_t* second_class, char* name);

/* 
 * Checks to see if a class has a component class.
 * This ensures that effects targeting a class will affect
 * multiclasses that have that target class as a component.
 *
 * Parameters:
 *  - class: the class being checked for components.
 *  - name: the name of the potential component class.
 *
 * Returns
 *  - 1 if the class has or is the target component, 0 if not.
 */
int has_component_class (class_t* class, char* name);

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
