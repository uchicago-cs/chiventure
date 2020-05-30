#include "wdl/object.h"
#include "common/common.h"

#ifndef INCLUDE_ATTRIBUTES_H
#define INCLUDE_ATTRIBUTES_H

/* 
union attr_data {
    bool b;
    char c;
    char *s;
    char **sl;
    int i;
    obj_t *o;
};

typedef struct attribute
{
    //the id for the attribute
    char id[MAXLEN_ID + 1];
    
    //data stored in the attribute
    union attr_data data;
    
    // Required uthash identifier for making the hash table
    UT_hash_handle hh;

} attribute_t; */

/* new_attr - allocates and inits an attr_t
 *
 * params:
 *   - id: attr id
 *   - data: atrr data
 * returns: ptr to new attribute_t
 */
attribute_t *new_attr(char *id, union attr_data d);

/* find_attr - given id, find attribute in hash
 *
 * params:
 *   - attrs: attribute_t hash
 *   - id: attr id
 * returns: ptr to attribute if found, else NULL
 */
attribute_t *find_attr(attribute_t **attrs, char *id);

/* add_attr - if attr is unique, add new attr. else, update attr data.
 *
 * params:
 *   - attrs: attribute_t hash
 *   - id: attr id
 *   - data: atrr data
 * returns: SUCCESS on completion, else FAILURE
 */
int add_attr(attribute_t **attrs, char *id, union attr_data d);

/* append_attr - appends attr to head of attr list
 * 
 * params:
 *   - head: ptr to head of list
 *   - new: element to be appended
 */
attribute_t *append_attr(attribute_t *head, attribute_t *new);

/* free_attr - frees & deletes attr from hash table
 *
 * params:
 *   - attr: attribute
 * returns: SUCCESS
 */
int free_attr(attribute_t **attrs, attribute_t *a);

#endif