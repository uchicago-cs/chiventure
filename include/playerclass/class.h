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
 * features are enabled, call class_init_skills() as well.
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
 * Initializes skill and skilltree related values for a player class.  Currently
 * only works for classes that match the name of one of our prefab classes.
 * 
 * Parameters:
 *  - class: a pointer to the class to be initialized.
 *  - max_skills_in_tree: the maximum number of skills in the class skilltree.
 *  - max_combat_skills: the maximum number of combat skills the class may have.
 *  - max_noncombat_skills: the maximum number of noncombat skills the class may
 *    have.
 * 
 * Returns:
 *  - EXIT_SUCCESS on successful initializtion.
 *  - EXIT_FAILURE otherwise.
 */
int class_init_skills(class_t* class, int max_skills_in_tree, 
                      int max_active_skills, int max_passive_skills); 

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