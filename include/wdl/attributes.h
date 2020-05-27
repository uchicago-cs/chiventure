#include "../../src/libobj/sandbox/sample_obj_documentation.h"
#include "common/common.h"

#ifndef INCLUDE_ATTRIBUTES_H
#define INCLUDE_ATTRIBUTES_H

/* typedef struct attribute
{
    //the id for the attribute
    char id[MAXLEN_ID + 1];
    
    //data stored in the attribute
    union
    {
        bool b;
        char c;
        char *s;
	    char **sl;
        int i;
        obj_t *o;
    } data;
    
    // Required uthash identifier for making the hash table
    UT_hash_handle hh;

} attribute_t; */

attribute_t *new_attr(char *id, data d);

int *add_attr(char *id, data d);

attribute_t *find_attr(char *id, data d);

attribute_t *free_attr(attribute_t *a);

#endif