/*
 * Data structures and standard functions for chiventure's skill tree library
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/stdst.h"

/* See stdst.h */
int array_element_add(void** array, unsigned int alen, void* element) {
    assert(array != NULL && element != NULL);

    unsigned int i;

    for (i = 0; i < alen; i++) {
        if (array[i] == NULL) {
            array[i] = element;
            return SUCCESS;
        }
    }

    fprintf(stderr, "array_element_add: failed to add array element\n");
    return FAILURE;
}

/* See stdst.h */
int list_has_skill(skill_t** list, unsigned int llen, sid_t sid) {
    assert(list != NULL);

    unsigned int i;

    for (i = 0; i < llen; i++) {
        if (list[i]) {
            if (list[i]->sid == sid) {
                return i;
            }
        }
    }

    return -1;
}
