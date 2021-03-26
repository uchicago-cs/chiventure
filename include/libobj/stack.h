
#ifndef INCLUDE_STACK_H
#define INCLUDE_STACK_H

#include "obj.h"

/* A stack frame to keep track of attribute prefix strings */
typedef struct stack_obj {

    //current attribute string (ex: ROOMS.0)
    char *attr_string;

    //keeps track of it is the head of a YAML sequence (list)
    int isListHead;

    //if list, keeps track of the next index to use
    int nextListIndex;

    //a pointer to the next frame
    struct stack_obj* next;
} stackobj_t;

/* A very simple stack */
typedef struct stack{
    stackobj_t *top;
} stack_t;

/* 
 * Creates a new blank stack
 *
 * Parameters: none
 *
 * Returns:
 * - A newly created stack (top initialized to NULL)
 */
stack_t *new_stack();

/* 
 * Creates a new stack frame object
 *
 * Parameters:
 * - attr_string: the attribute string
 * - isListHead: 1 if this is the header for a sequence (list), 0 if not 
 * - stack: stack to push to
 *
 * Returns:
 * - The given stack, where the top is now the newly created frame object
 */
stack_t *push(char *attr_string, int isListHead, stack_t *stack);

/* Pops top stack object
 * 
 * Parameters:
 * - stack: stack to remove element
 *
 * Returns:
 * - The popped stack object
 */ 
stackobj_t *pop(stack_t *stack);

/* Frees stack object and associated string
 * 
 * Parameters:
 * - sobj: object to free
 *
 * Returns:
 * - 0 on success, -1 if given a NULL object
 */
int stackobj_free(stackobj_t *sobj);

/* Frees stack object and associated string
 * 
 * Parameters:
 * - stack: stack to free
 *
 * Returns:
 * - 0 on success, -1 if given a NULL object
 */
int stack_free(stack_t *stack);

#endif /* INCLUDE_STACK_H */