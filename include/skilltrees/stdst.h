/*
 * Data structures and standard functions for chiventure's skill tree library
 */

#ifndef INCLUDE_STDST_H_
#define INCLUDE_STDST_H_

#include "common/common.h"

/* ======================== */
/* === COMMON FUNCTIONS === */
/* ======================== */
/*
 * A helper function. Adds an arbitrary array element to an array, by pointer.
 *
 * Parameters:
 *  - array: The array
 *  - array_len: The length of the array
 *  - element: The element to add to the array
 *
 * Returns:
 *  - A pointer to the updated array, NULL if an error occurs
 */
void** array_element_add(void** array, unsigned int array_len, void* element);

/*
 * A helper function. Searches a list of skills for a given skill, by sid_t.
 *
 * Parameters:
 *  - list: The skill array
 *  - list_len: The length of the skill list
 *  - sid: The skill ID of the skill to search for
 *
 * Returns:
 *  - The position of the skill in the list, -1 if the skill is not in the list
 */
int list_has_skill(skill_t** list, unsigned int list_len, sid_t sid);

#endif /* INCLUDE_STDST_H_ */
