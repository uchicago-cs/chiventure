/* 
 * Basic functionality for the class struct. 
 */
#ifndef CLASS_H
#define CLASS_H

#include "libobj/obj.h"
#include "common/utlist.h"
#include "playerclass/class_structs.h"

/* 
 * Allocates memory for a new player class. Only creates a deep copies of the 
 * strings name, short description, and long description.
 * 
 * Parameters:
 *  - name, shortdesc, longdesc: Name and descriptions of the class
 *  - attr: the attributes of the class
 *  - stat: the stats of the class
 *  - skilltree: the skilltree of the class
 *  - combat: the battle/combat actions of the class
 *  - noncombat: the noncombat actions of the class
 * 
 * Returns:
 *  - a pointer to the allocated class memory
 *  - NULL on error
 */
class_t* class_new(char* name, char* shortdesc, char* longdesc,
                   obj_t* attr, stats_t* stat, skilltree_t* skilltree,
                   skill_t* combat, skill_t* noncombat);

/* 
 * Initializes values for a player class. Only creates a deep copies of the 
 * strings name, short description, and long description.
 * 
 * Parameters:
 *  - class: a pointer to the class to be initialized
 *  - name, shortdesc, longdesc: Name and descriptions of the class
 *  - attr: the attributes of the class
 *  - stat: the stats of the class
 *  - skilltree: the skilltree of the class
 *  - combat: the battle/combat actions of the class
 *  - noncombat: the noncombat actions of the class
 * 
 * Returns:
 *  - EXIT_SUCCESS on successful initialization
 *  - EXIT_FAILURE otherwise
 */
int class_init(class_t* class, char* name, char* shortdesc, char* longdesc,
               obj_t* attr, stats_t* stat, skilltree_t* skilltree,
               skill_t* combat, skill_t* noncombat);

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