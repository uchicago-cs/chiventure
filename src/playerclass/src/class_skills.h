/*
 * functions that set up the basic skills for the classes
 */
#ifndef CLASS_SKILLS_H
#define CLASS_SKILLS_H

#include "playerclass/class.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"

/*
 * initializes the class's skilltree and active combat and noncombat skill lists
 *
 * Parameters:
 *  - class. the class the skilltree and lists should be placed in. The field
 *    initialized here are assumed to be empty.
 *
 * Returns:
 *  - status code
 *  - the structs in the class now contain skills.
 */
int class_skills_init(class_t* class);

#endif