#include "wdl/object.h"
#include "common/common.h"

#ifndef INCLUDE_ATTRIBUTES_H
#define INCLUDE_ATTRIBUTES_H

/* 
/* 
 * a union representing the information that can be stored in an attribute
 
union attr_data
{
    bool b;
    char c;
    char *s;
    int i;
    object_t *o;
};

/*
 * obj_attr_t: the attributes stored within an object
 
typedef struct attr
{
    //the attribute's id.
    char id[MAXLEN_ID + 1];
   
    //the information stored in the attribute
    union attr_data data;

    //next attribute in list if attribute is list of things
    struct attr *next;

    //prev attribute in list if attribute is list of things
    struct attr *prev;

    //Required uthash indentifier for making the hash table
    UT_hash_handle hh;

} obj_attr_t; 
*/

/* ---------- HASH FUNCTIONS ---------- */

/* new_attr - allocates and inits an attr_t
 *
 * params:
 *   - id: attr id
 *   - data: atrr data
 * returns: ptr to new obj_attr_t
 */
obj_attr_t *new_attr(char *id, union attr_data d);

/* find_attr - given id, find attribute in hash
 *
 * params:
 *   - attrs: obj_attr_t hash
 *   - id: attr id
 * returns: ptr to attribute if found, else NULL
 */
obj_attr_t *find_attr(obj_attr_t **attrs, char *id);

/* add_attr - if attr is unique, add new attr. else, update attr data.
 *
 * params:
 *   - attrs: obj_attr_t hash
 *   - id: attr id
 *   - data: atrr data
 * returns: SUCCESS on completion, else FAILURE
 */
int add_attr(obj_attr_t **attrs, char *id, union attr_data d);

/* append_attr - appends attr to head of attr list
 * 
 * params:
 *   - head: ptr to head of list
 *   - new: element to be appended
 */
obj_attr_t *append_attr(obj_attr_t *head, obj_attr_t *new);

/* free_attr - frees & deletes attr from hash table
 *
 * params:
 *   - attr: attribute
 * returns: SUCCESS
 */
int free_attr(obj_attr_t **attrs, obj_attr_t *a);


/* ---------- INTERFACE FUNCTIONS ---------- */

/* the following functions get elements from a given attr */
char *get_attr_id(obj_attr_t *attr);
union attr_data *get_attr_data(obj_attr_t *attr);
obj_attr_t *get_next_attr(obj_attr_t *attr);
obj_attr_t *get_prev_attr(obj_attr_t *attr);

#endif