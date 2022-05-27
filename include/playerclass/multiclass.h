   
/*
 * Enables multiclass functionality
*/

#ifndef MULTICLASS_H
#define MULTICLASS_H

#include "libobj/obj.h"
#include "common/utlist.h"
#include "playerclass/class_structs.h"
#include "game-state/stats.h"

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
 *
 * Note:
 *  - This is not currently implemented anywhere, and is vestigial code.
 *    It may be helpful in the future, but is not currently needed.
 */
int has_component_class(class_t* class, char* name);

/* these are only here so it can be included in testing. They should be ignored
   if you are viewing this module to learn about the code */
char* multiclass_shortdesc(class_t* base_class, class_t* second_class, int *succ);
char* multiclass_longdesc(class_t* base_class, class_t* second_class, int *succ);

#endif /* MULTICLASS_H */