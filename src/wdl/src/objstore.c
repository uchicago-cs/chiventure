#include "wdl/objstore.h"

/* See obj_store.h for documentation */
objstore_t *new_objstore(object_t *o)
{
    if (o == NULL) {
        return NULL;
    }
    objstore_t *new = malloc(sizeof(objstore_t));
    memset(new, 0, sizeof(*new)); // to accommodate padding in struct

    new->key.type = o->type;
    strcpy(new->key.id, o->id);
    new->o = o;
    return new;
}

/* See obj_store.h for documentation */
objstore_t* find_objstore(objstore_t **obj_store, char* id, objtype_t type)
{
    objstore_t *res;
    objkey_t tmp;
    memset(&tmp, 0, sizeof(tmp));
    strcpy(tmp.id, id);
    tmp.type = type;

    HASH_FIND(hh, *obj_store, &tmp, sizeof(objkey_t), res);

    return res;
}

/* See obj_store.h for documentation */
int add_objstore(objstore_t **obj_store, object_t *o)
{
    if (o == NULL) {
        return FAILURE;
    }
    objstore_t *new = find_objstore(obj_store, o->id, o->type); // see if key already exists in hash
    if (new == NULL) {
        new =  new_objstore(o);
        if (new == NULL) return FAILURE;
        HASH_ADD(hh, *obj_store, key, sizeof(objkey_t), new);
    } else {
        new->o = o;
    }
    return SUCCESS;
}

/* See obj_store.h for documentation */
int free_objstore(objstore_t **obj_store, objstore_t *store)
{
    HASH_DEL(*obj_store, store);
    free(store->o);
    free(store);
    return SUCCESS;
}

/* See obj_store.h for documentation */
int free_all_objstore(objstore_t **obj_store)
{
    if (obj_store == NULL) {
        return FAILURE;
    }
    objstore_t *curr, *tmp;
    HASH_ITER(hh, *obj_store, curr, tmp)
    {
        free_objstore(obj_store, curr);
    }
    return SUCCESS;
}

/*
 * Helper function for
 * get_object_wdl: retrieves an object from a .wdz archive.
 *
 * params: 
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id.
 * 
 * returns:
 *   - a pointer to the requested object as a obj_t struct member.
 */
object_t* get_object_wdl(objstore_t** ht, objtype_t type, char* id)
{
    objstore_t *objs = find_objstore(ht, id, type);

    if(objs == NULL)
    {
        return NULL;
    }

    object_t *obj = objs->o;

    return obj;
}

/* See wdl/objstore.h for documentation */
object_t* get_object(objstore_t** ht, char* type, char* id)
{
    objtype_t tp;

    tp = strToOType(type);

    return get_object_wdl(ht, tp, id);
}
