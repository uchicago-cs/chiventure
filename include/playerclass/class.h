/* 
 * Defines a player class struct to store base class information.
 */ 

#ifndef CLASS_H
#define CLASS_H

#include "libobj/obj.h"
#include "common/utlist.h"

// Stubbing out the playerstats object
typedef struct stats{
    obj_t* stat;
} stats_t;

/* A player class struct storing the name, descriptions, attributes, 
 * and stats */
typedef struct class {
    // Name of the class
    char* name;

    // A short description of the class
    char* shortdesc;

    // A long description of the class
    char* longdesc;

    // An object containing all the attributes of the class
    obj_t* attributes;

    // All the stats of the class
    stats_t* stats;

} class_t;

/* 
 * Allocates memory for a new player class. Does not create a deep copy.
 * 
 * Parameters:
 *  - name, shortdesc, longdesc: Name and descriptions of the class
 *  - attr: the attributes of the class
 *  - stat: the stats of the class
 * 
 * Returns:
 *  - a pointer to the allocated class memory
 *  - NULL on error
 */
class_t* class_new(char* name, char* shortdesc, char* longdesc,
                   obj_t* attr, stats_t* stat);

/* 
 * Initializes values for a player class. Does not create a deep copy.
 * 
 * Parameters:
 *  - class: a pointer to the class to be initialized
 *  - name, shortdesc, longdesc: Name and descriptions of the class
 *  - attr: the attributes of the class
 *  - stat: the stats of the class
 * 
 * Returns:
 *  - EXIT_SUCCESS on successful initialization
 *  - EXIT_FAILURE otherwise
 */
int class_init(class_t* class, char* name, char* shortdesc, char* longdesc,
               obj_t* attr, stats_t* stat);

/*
 * Frees a class created by class_new. Since class_new is not a deep copy,
 * class_free does not free the components underneath.
 * 
 * Parameters:
 *  - class: The class to free
 * 
 * Returns:
 *  - Always return EXIT_SUCCESS
 */
int class_free(class_t* class);

#endif /* CLASS_H */