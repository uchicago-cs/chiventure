#include "common/common.h"
#include "common/uthash.h"
#include "common/utlist.h"

#ifndef INCLUDE_ATTRIBUTES_H
#define INCLUDE_ATTRIBUTES_H
#define MAXLEN_ID 60 // ID strings for objects

//typedef struct object_t object_t; // forward declaration so attribute_t can use

/*
 * attribute_t: the attributes stored within an object
 */
typedef struct attr
{
    /* the attribute's id. */
    char id[MAXLEN_ID + 1];
   
    /* the information stored in the attribute */
    void *data;

    /* next attribute in list if attribute is list of things */
    struct attr *next;

    /* prev attribute in list if attribute is list of things */
    struct attr *prev;

    /* Required uthash indentifier for making the hash table */
    UT_hash_handle hh;

} obj_attr_t;


/* ---------- HASH FUNCTIONS ---------- */

/* new_attr - allocates and inits an attr_t as a hash item AND a linked list
 *
 * params:
 *   - id: attr id
 *   - data: atrr data
 * returns: ptr to new obj_attr_t
 */
obj_attr_t *new_attr(char *id, void *d);

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
 * returns: pointer to new attribute or NULL
 */
obj_attr_t *add_attribute(obj_attr_t **attrs, char *id, void *d);

/* free_attr_hash - frees & deletes attr from by iterating through hash (WILL ALSO delete from linked list)
 *
 * params:
 *   - attrs: ptr to hash
 * returns: SUCCESS
 */
int free_attr_hash(obj_attr_t **attrs);


/* ---------- LINKED LIST FUNCTIONS ---------- */

/* init_attr_list - initializes given attr as head of a linked list
 * 
 * params:
 *   - new: new attribute
 * returns: head of list
 */
obj_attr_t *init_attr_list(obj_attr_t *new);

/* append_attr - appends attr to attr list
 * 
 * params:
 *   - head: ptr to head of list
 *   - new: element to be appended
 * returns: head of list
 */
obj_attr_t *append_attr(obj_attr_t *head, obj_attr_t *new);

/* count_attr_list - counts items in list
 *
 * params:
 *   - head: ptr to head of list
 * returns: number of items in list
 */
int count_attr_list(obj_attr_t *head);

/* free_attr - frees & deletes 1 item from linked list
 *
 * params:
 *   - head: head ptr
 *   - a: attr to delete
 * returns: SUCCESS
 */
int free_attr(obj_attr_t *head, obj_attr_t *a);

/* free_attr_list - frees & deletes attr 1 item from hash (including its linked elements)
 *
 * params:
 *   - attrs: ptr to hash
 *   - head: head of linked list
 * returns: SUCCESS
 */
int free_attr_list(obj_attr_t **attrs, obj_attr_t *head);


/* ---------- INTERFACE FUNCTIONS ---------- */

/* the following functions get elements from a given attr */
char *get_attr_id(obj_attr_t *attr);
void *get_attr_data(obj_attr_t *attr);
obj_attr_t *get_next_attr(obj_attr_t *attr);
obj_attr_t *get_prev_attr(obj_attr_t *attr);

#endif
