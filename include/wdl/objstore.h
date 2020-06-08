#include "wdl/object.h"
#include "common/common.h"

#ifndef INCLUDE_OBJSTORE_H
#define INCLUDE_OBJSTORE_H

/* 
 * key_t: key struct for hash table - a wrapper for id and type of obj
 */
typedef struct objkey {
    /* the id of the object, e.g. "villager" */
    char id[MAXLEN_ID];

    /* type: the type of the object */
    objtype_t type;

 } objkey_t;

/* 
 * objstore_t: hash table for storing objects parsed from WDL++ format
 */
typedef struct objstore {
    /* key of hash, containing id and type of object */
    objkey_t key;

    /* pointer to object */
    object_t *o; 

    /* required for hash struct */
    UT_hash_handle hh;

} objstore_t; 

/* 
 * objstore_new: given type, id, and pointer to object, allocate and init objstore item
 *
 * params:
 *   - o: ptr to object
 * returns: ptr to new objstore item
 */
objstore_t *new_objstore(object_t *o);

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
int add_objstore(objstore_t **obj_store, object_t *o);

/*
 * free_objstore: deletes & frees a given objstore struct
 * 
 * params:
 *   - store - objstore item
 * returns: SUCCESS
 */
int free_objstore(objstore_t **obj_store, objstore_t *store);

/* 
 * free_all_objstore: deletes & frees entire objectstore_t hash (including objects)
 * 
 * params:
 *   - object_store - objstore hash
 * returns: SUCCESS
 */
int free_all_objstore(objstore_t **object_store);

/* 
 * get_object: retrieves an object from a .wdz archive
 *
 * params:
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id
 * 
 * returns:
 *   - a pointer to the requested object as a obj_t struct member.
 */
object_t* get_object(objstore_t **ht, char* type, char* id);

#endif
