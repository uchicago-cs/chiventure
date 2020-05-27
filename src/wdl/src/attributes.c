#include "../../../include/wdl/attributes.h"

/* See attributes.h for documentation */
attribute_t *new_attr(char *id, union attr_data d)
{
    if (id == NULL) {
        return NULL;
    }

    attribute_t *new = malloc(sizeof(attribute_t));
    memset(new, 0, sizeof(*new)); // to accommodate padding in struct

    strcpy(new->id, id);
    new->data = d;
    return new;
}

/* See attributes.h for documentation */
attribute_t *find_attr(attribute_t **attrs, char *id)
{
    attribute_t *res;
    char tmp[MAXLEN_ID];
    strcpy(tmp, id);

    HASH_FIND(hh, *attrs, &tmp, sizeof(tmp), res);

    return res;
}

/* See attributes.h for documentation */
int add_attr(attribute_t **attrs, char *id, union attr_data d)
{
    if (id == NULL) {
        return FAILURE;
    }
    attribute_t *new = find_attr(attrs, id); // see if key already exists in hash
    if (new == NULL) {
        new =  new_attr(id, d);
        if (new == NULL) return FAILURE;
        HASH_ADD(hh, *attrs, id, sizeof(id), new);
    } else {
        new->data = d;
    }
    return SUCCESS;
}

/* See attributes.h for documentation */
int free_attr(attribute_t **attrs, attribute_t *a)
{
    // HASH_DEL(attrs, a);
    free(a);
    return SUCCESS;
}