#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* See stack.h */
stack_t* new_stack(){
    stack_t* stack = malloc(sizeof(stack_t));
    stack -> top = NULL;
    return stack;
}

/* See stack.h */
stack_t* push(char* attr_string, int isListHead, stack_t* stack){
    char* attr_string_deep = malloc(MAXLEN_SEARCH);
    if ((attr_string == NULL) || (stack == NULL)){
        fprintf(stderr, "Error: given null element\n");
        return NULL;
    }     
    stackobj_t* sobj = malloc(sizeof(stackobj_t));
    sobj -> isListHead = isListHead;
    sobj -> nextListIndex = isListHead ? 0 : -1;
    sobj -> attr_string = strcpy(attr_string_deep,attr_string);
    sobj -> next = (stack -> top);
    stack -> top = sobj;
    return stack;  
}

/* See stack.h */
stackobj_t* pop(stack_t* stack){
    if (stack == NULL){
        fprintf(stderr, "Error: given null element\n");
        return NULL;
    }
    stackobj_t* old_top = stack -> top;
    stack -> top = old_top -> next; 
    return old_top;  
}
