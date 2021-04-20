/*
 * functions that set up the basic skills for the classes
 */
#ifndef CLASS_SKILLS_H
#define CLASS_SKILLS_H

#include "playerclass/class.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 ranger
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_ranger(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 rogue
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_rogue(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 monk
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_monk(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 sorcerer
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_sorcerer(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 druid
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_druid(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 elementalist
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_elementalist(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 bard
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_bard(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 wizard
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_wizard(class_t* class);

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 knight
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_knight(class_t* class);


#endif