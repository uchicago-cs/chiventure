/* 
 * Basic functionality for the class struct. 
 */
#ifndef CLASS_H
#define CLASS_H

#include "libobj/obj.h"
#include "common/utlist.h"
#include "playerclass/class_structs.h"
#include "game-state/stats.h"
#include "playerclass/multiclass.h"

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
 *  - starting_skills: pointer to a skill inventory for a class's initial skills.
 *  - skilltree: pointer to a skill tree for the class.
 *  - NOTE: The skill related fields may be NULL, if those feautres are
 *          disabled. However, we recommend that they be filled with empty 
 *          allocated structs instead. 
 * Returns:
 *  - EXIT_SUCCESS on successful initialization (As of now, this always occurs; the function is not finished).
 *  - EXIT_FAILURE otherwise.
 */
int class_add_skills(class_t* class, skill_inventory_t* starting_skills, 
                     skill_tree_t* skilltree); 

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


/* Functions for manipulating a class hash table. These more or less wrap the 
 * UTHASH macros into a safer and more convenient form. 
 *
 * These functions take in a class_hash_t**, since UTHASH macros may modify the
 * pointer to the actual hashtable (ie, the class_hash_t*). I recommend simply
 * using the reference operator (&) in calls to these functions. */


/*
 * Add a class_t to a class_hash_t.
 * 
 * Parameters:
 *  - hashtable: A pointer to a possibly NULL class hashtable pointer.
 *  - class: The class being added to the hashtable.
 * 
 * Returns:
 *  - FAILURE if the class or its name field were NULL, or if the class's name
 *    matched one in the hashtable (the names must be unique).
 *  - SUCCESS on successful addition to the hashtable.
 */
int add_class(class_hash_t** hashtable, class_t* class);

/*
 * Replaces a class in a hashtable, adding a new one if no old class (one with
 * the same name) is found.
 * 
 * Parameters:
 *  - hashtable: A pointer to a possibly NULL class hashtable pointer.
 *  - class: The class being added to the hashtable.
 * 
 * Returns: 
 *  - FAILURE if the class or its name field were NULL.
 *  - SUCCESS on successful addition or replacement.
 */
int set_class(class_hash_t** hashtable, class_t* class);

/*
 * Finds and returns a class in a class hash table.
 * 
 * Parameters:
 *  - hashtable: A pointer to a class hashtable pointer. 
 *  - name: The name of the class being searched for.
 * 
 * Returns:
 *  - A pointer to a the class that matches the provided name.
 *  - NULL if no class was found, or if either parameter was NULL.
 */
class_t* find_class(class_hash_t** hashtable, char* name);

/*
 * Removes a class from a hashtable and frees it.
 * 
 * Parameters:
 *  - hashtable: A pointer to a class hashtable pointer.
 *  - name: The name of the class to be deleted.
 * 
 * Returns:
 *  - SUCCESS if the class was found and deleted.
 *  - FAILURE if one of the parameters was NULL, or the class could not be
 *    found.
 */
int delete_class(class_hash_t** hashtable, char* name);

/* 
 * Returns the number of classes in a class hashtable.
 *
 * Parameters:
 *  - hashtable: A pointer to a class hashtable pointer.
 * 
 * Returns:
 *  - The number of classes in the hashtable.
 *  - 0 if the hashtable is NULL.
 */
int count_classes(class_hash_t** hashtable);


/* It is infeasible to provide a function for iterating over a hashtable. 
 * If iteration is needed, one should use UTHASH's HASH_ITER macro, or the 
 * class->hh.next and class->hh.prev pointers. See tests for examples. */

#endif /* CLASS_H */
