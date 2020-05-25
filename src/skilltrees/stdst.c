/*
 * Data structures and standard functions for chiventure's skill tree library
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/stdst.h"

/* See helpers.h */
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

/* See helpers.h */
int array_has_sid(void** array, unsigned int alen, sid_t sid) {
    assert(array != NULL);

    unsigned int i;

    for (i = 0; i < alen; i++) {
        if (array[i]) {
            if (array[i]->sid == sid) {
                return i;
            }
        }
    }

    return -1;
}
