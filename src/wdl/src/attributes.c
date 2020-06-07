#include "wdl/attributes.h"
#define MAXLEN_ID 60 // ID strings for objects


/* ---------- HASH FUNCTIONS ---------- */

/* See attributes.h for documentation */
obj_attr_t *new_attr(char *id, void *d)
{
    if (id == NULL) {
        return NULL;
    }

    obj_attr_t *new = malloc(sizeof(obj_attr_t));
    memset(new, 0, sizeof(*new)); // to accommodate padding in struct

    strcpy(new->id, id);
    new->data = d;
    new->prev = NULL;
    new->next = NULL;

    obj_attr_t *head = NULL;
    DL_APPEND(head, new);
    return head;
}

/* See attributes.h for documentation */
obj_attr_t *find_attr(obj_attr_t **attrs, char *id)
{
    obj_attr_t *res;

    HASH_FIND_STR(*attrs, id, res);

    return res;
}

/* See attributes.h for documentation */
obj_attr_t *add_attribute(obj_attr_t **attrs, char *id, void * d)
{
    if (id == NULL) {
        return NULL;
    }
    obj_attr_t *new = find_attr(attrs, id); // see if key already exists in hash
    if (new == NULL) {
        new =  new_attr(id, d);
        if (new == NULL) return NULL;
        HASH_ADD_STR(*attrs, id, new);
    } else {
        new->data = d;
    }
    return new;
}

int free_attr_hash(obj_attr_t **attrs)
{
    if (attrs == NULL) {
        return FAILURE;
    }
    obj_attr_t *curr, *tmp;
    HASH_ITER(hh, *attrs, curr, tmp)
    {
        free_attr(attrs, *attrs, curr);
    }
    return SUCCESS;
}

/* ---------- LIMBO ---------- */

/* See attributes.h for documentation */
int free_attr(obj_attr_t **attrs, obj_attr_t *head, obj_attr_t *a)
{
    if ((attrs == NULL)||(head == NULL)) {
        return FAILURE;
    }
    DL_DELETE(head, a);
    HASH_DEL(*attrs, a);
    free(a);
    return SUCCESS;
}


/* ---------- LINKED LIST FUNCTIONS ---------- */

/* See attributes.h for documentation */
obj_attr_t *append_attr(obj_attr_t *head, obj_attr_t *new)
{
    DL_CONCAT(head, new);
    return head;
}

/* See attributes.h for documentation */
int count_attr_list(obj_attr_t *head)
{
    obj_attr_t *tmp;
    int res;
    DL_COUNT(head, tmp, res);
    return res;
}

/* See attributes.h for documentation */
int free_attr_list(obj_attr_t **attrs, obj_attr_t *head)
{
    if ((attrs == NULL)|(head == NULL)) return FAILURE;
    
    obj_attr_t *elt, *tmp;
    DL_FOREACH_SAFE(head, elt, tmp) {
        //HASH_DEL(*attrs, elt);
        //DL_DELETE(head, elt);
        //free(elt);
    }
    return SUCCESS;
}


/* ---------- INTERFACE FUNCTIONS ---------- */

char *get_attr_id(obj_attr_t *attr)
{
    return attr->id;
}

void *get_attr_data(obj_attr_t *attr)
{
    return attr->data;
}

obj_attr_t *get_next_attr(obj_attr_t *attr)
{
    return attr->next;
}

obj_attr_t *get_prev_attr(obj_attr_t *attr)
{
    return attr->prev;
}
