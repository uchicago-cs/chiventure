#include "obj_store.h"

objstore_t *obj_store = NULL;

/* See obj_store.h for documentation */
objstore_t* find_objstore(objtype_t type, char* id)
{
    objstore_t *res;
    objkey_t tmp;
    memset(&tmp, 0, sizeof(tmp));
    strcpy(tmp.id, id);
    tmp.type = type;

    HASH_FIND(hh, obj_store, &tmp, sizeof(objkey_t), res);

    return res;
}

/* See obj_store.h for documentation */
objstore_t *new_objstore(obj_t *o)
{
    objstore_t *new = malloc(sizeof(objstore_t));
    memset(new, 0, sizeof(*new)); // to accommodate padding in struct

    new->key.type = o->type;
    strcpy(new->key.id, o->id);
    new->o = o;
    return new;
}

/* See obj_store.h for documentation */
int add_objstore(obj_t *o)
{
    objstore_t *new = find_objstore(o->type, o->id); // see if key already exists in hash
    if (new == NULL) {
        new = new_objstore(o);
        if (new == NULL) return FAILURE;
        HASH_ADD(hh, obj_store, key, sizeof(objkey_t), new);
    } else {
        new->o = o;
    }
    return SUCCESS;
}

/* See obj_store.h for documentation */
int free_objstore(objstore_t *store)
{
    free(store);
    return SUCCESS;
}

int main() {
    return 0;
}