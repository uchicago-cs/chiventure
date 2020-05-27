#include "sample_obj_documentation.h"
#include "../../../include/common/common.h"

#ifndef INCLUDE_OBJ_STORE_H
#define INCLUDE_OBJ_STORE_H

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
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id.
 * 
 * returns:
 *   - a pointer to the requested objstore item
 */
objstore_t* find_objstore(objtype_t type, char* id);

/* 
 * add_obj: given unique object, add to obj_store hash table 
 *          (else modify existing item to point to new object)
 *
 * params:
 *   - o: object to add to hash
 * returns: SUCCESS on completion, else FAILURE
 */
int add_objstore(obj_t *o);

/*
 * free_objstore: frees a given objstore struct
 * 
 * params:
 *   - store - objstore item
 * returns: SUCCESS
 */
int free_objstore(objstore_t *store);

#endif