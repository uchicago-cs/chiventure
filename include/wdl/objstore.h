#include "../../src/libobj/sandbox/sample_obj_documentation.h"
#include "../common/common.h"

#ifndef INCLUDE_OBJSTORE_H
#define INCLUDE_OBJSTORE_H

/* key_t: key struct for hash table - a wrapper for id and type of obj
 * params:
 *   - id: the id of the object
 *   - type: the type of the object
 */
typedef struct objkey {
    char id[MAXLEN_ID]; // item id, e.g. "villager"
    objtype_t type; // category, e.g. "npc"
 } objkey_t;

/* objstore_t: hash table for storing objects parsed from WDL++ format
 * params:
 *   - key: key of hash, containing id and type of object
 *   - obj: pointer to object
 *   - hh: needed for hash struct
 */
typedef struct objstore {
    objkey_t key;
    obj_t *o; 
    UT_hash_handle hh;
} objstore_t; 

/* 
 * objstore_new: given type, id, and pointer to object, allocate and init objstore item
 *
 * params:
 *   - o: ptr to object
 * returns: ptr to new objstore item
 */
objstore_t *new_objstore(obj_t *o);

/*
 * find_objstore: finds objstore item containing object with given type & id
 *
 * params: 
 *   - obj_store: double ptr to hash
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id.
 * 
 * returns:
 *   - a pointer to the requested objstore item
 */
objstore_t* find_objstore(objstore_t **obj_store, char* id, objtype_t type);

/* 
 * add_obj: given unique object, add to obj_store hash table 
 *          (else modify existing item to point to new object)
 *
 * params:
 *   - obj_store: double ptr to hash
 *   - o: object to add to hash
 * returns: SUCCESS on completion
 */
int add_objstore(objstore_t **obj_store, obj_t *o);

/*
 * free_objstore: deletes & frees a given objstore struct
 * 
 * params:
 *   - store - objstore item
 * returns: SUCCESS
 */
int free_objstore(objstore_t **obj_store, objstore_t *store);

/* 
 * free_all: deletes & frees entire objectstore_t hash (including objects)
 * 
 * params:
 *   - object_store - objstore hash
 * returns: SUCCESS
 */
int free_all(objstore_t **object_store);

#endif