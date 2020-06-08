#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libobj/obj.h"
#include "common/utlist.h"

/* Forward function declarations */
obj_t *obj_get_attr_single(obj_t *obj, char *id, bool create);
void obj_free_str(obj_t *obj);

/* See obj.h */
obj_t *obj_new(char *id)
{
    obj_t *obj = calloc(1, sizeof(obj_t));

    if (obj == NULL)
    {
        printf("ERROR - obj_new: Couldn't allocate memory for object.\n");

        return NULL;
    }

    if (obj->id == NULL)
    {
        printf("ERROR - obj_new: Couldn't allocate memory for object id\n");
        obj_free(obj);

        return NULL;
    }

    if (obj_init(obj, id) != EXIT_SUCCESS)
    {
        printf("ERROR - obj_new: Couldn't initialize object.\n");
        obj_free(obj);

        return NULL;
    }

    return obj;
}

/* See obj.h */
int obj_init(obj_t *obj, char *id)
{
    if (obj == NULL || id == NULL)
    {
        printf("ERROR - obj_init: Couldn't initialize object.\n");

        return EXIT_FAILURE;
    }

    strncpy(obj->id, id, MAXLEN_ID);
    obj->type = TYPE_ZERO;

    return EXIT_SUCCESS;
}

// Frees a string in an object if it exists
void obj_free_str(obj_t *obj)
{
    if (obj == NULL || obj->type != TYPE_STR
            || obj->data.s == NULL)
    {
        return;
    }

    free(obj->data.s);
    obj->type = TYPE_ZERO;
}

/* See obj.h */
int obj_free(obj_t *obj)
{

    obj_free_str(obj);

    free(obj);

    return EXIT_SUCCESS;
}


/* See obj.h */
int obj_free_all(obj_t *obj)
{

    obj_free_str(obj);

    if (obj->attr)
    {
        obj_t *el, *tmp;
        HASH_ITER(hh, obj->attr, el, tmp)
        {
            HASH_DEL(obj->attr, el);
            obj_free(el);
        }
    }

    free(obj);

    return EXIT_SUCCESS;
}


/*
 * Helper function for obj_get_attr()
 * Finds an attribute of an object
 *   - Will not recursively search
 *
 * Parameters:
 *  - obj: The object to find the attribute of
 *  - id: The id of the attribute
 *  - create: whether or not to create a new attribute if no attribute
 *      is found
 *
 * Returns:
 *  - Returns the object if it is found or created (create = true)
 *  - Returns NULL if error or not found (create = false)
 */
obj_t *obj_get_attr_single(obj_t *obj, char *id, bool create)
{
    if (obj == NULL || id == NULL)
    {
        printf("ERROR - obj_get_attr_single: Object given is NULL.\n");

        return NULL;
    }

    if (strncmp(id, "self", MAXLEN_ID) == 0)
    {
        return obj;
    }

    obj_t **ht_ptr = &obj->attr;
    obj_t *elt = NULL;

    if (obj->attr)
    {
        HASH_FIND_STR(*ht_ptr, id, elt);
    }

    if (elt == NULL && create == true)
    {
        elt = obj_new(id);

        obj_t **ht_ptr = &obj->attr;
        HASH_ADD_STR(*ht_ptr, id, elt);
    }

    return elt;
}

obj_t *obj_get_attr(obj_t *obj, char *id, bool create)
{

    char *id_imm, *head_ptr;
    char *tmp = calloc((MAXLEN_ID + 1) * MAX_DEPTH, sizeof(char));
    obj_t *attr;

    // For freeing later
    head_ptr = tmp;

    strncpy(tmp, id, (MAXLEN_ID + 1) * MAX_DEPTH - 1);
    id_imm = strtok(tmp, ".");
    attr = obj;

    while (id_imm != NULL)
    {
        attr = obj_get_attr_single(attr, id_imm, create);

        if (attr == NULL)
        {
            free(head_ptr);
            return NULL;
        }

        id_imm = strtok(NULL, ".");
    }

    free(head_ptr);

    return attr;
}

/* See obj.h */
attr_list_t *obj_list_attr(obj_t *obj)
{
    if (obj == NULL)
    {
        return NULL;
    }

    attr_list_t *ll = NULL;
    attr_list_t *append = NULL;

    if (obj->attr)
    {
        obj_t *el, *tmp;
        HASH_ITER(hh, obj->attr, el, tmp)
        {
            append = calloc(1, sizeof(attr_list_t));
            append->obj = el;

            DL_APPEND(ll, append);
        }
    }

    return ll;
}

/* See obj.h */
int obj_add_attr(obj_t *obj, char *id, obj_t *attr)
{
    if (obj == NULL || attr == NULL)
    {
        printf("ERROR - obj_add_attr: Object given is NULL.\n");

        return EXIT_FAILURE;
    }

    obj_t *addee;

    addee = obj_get_attr(obj, id, true);
    if (addee == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_t **ht_ptr = &obj->attr;
    HASH_ADD_STR(*ht_ptr, id, attr);

    return EXIT_SUCCESS;
}

/* See obj.h */
int obj_remove_attr(obj_t *obj, char *id)
{
    if (obj == NULL)
    {
        printf("ERROR - obj_remove_attr: Object given is NULL.\n");

        return EXIT_FAILURE;
    }

    obj_t *attr;

    attr = obj_get_attr(obj, id, false);
    if (attr == NULL)
    {
        return EXIT_FAILURE;
    }

    HASH_DEL(obj->attr, attr);

    return EXIT_SUCCESS;
}

datatype_t obj_get_type(obj_t *obj, char *id)
{
    if (obj == NULL || id == NULL)
    {
        printf("ERROR - obj_get_type: Object/id given is NULL.\n");

        return TYPE_ERROR;
    }

    obj_t *target = obj_get_attr(obj, id, false);

    if (target == NULL)
    {
        return TYPE_ERROR;
    }

    return target->type;
}

/* See obj.h */
bool obj_get_bool(obj_t *obj, char *id)
{
    if (obj == NULL || id == NULL)
    {
        return false;
    }

    obj_t *attr = obj_get_attr(obj, id, false);

    if (attr == NULL || attr->type != TYPE_BOOL)
    {
        return false;
    }

    return attr->data.b;
}

/* See obj.h */
int obj_set_bool(obj_t *obj, char *id, bool value)
{
    if (obj == NULL || id == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_t *attr = obj_get_attr(obj, id, true);

    if (attr == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_free_str(attr);

    attr->data.b = value;
    attr->type = TYPE_BOOL;

    return EXIT_SUCCESS;
}

/* See obj.h */
char obj_get_char(obj_t *obj, char *id)
{
    if (obj == NULL || id == NULL)
    {
        return '\0';
    }

    obj_t *attr = obj_get_attr(obj, id, false);

    if (attr == NULL || attr->type != TYPE_CHAR)
    {
        return '\0';
    }

    return attr->data.c;
}

/* See obj.h */
int obj_set_char(obj_t *obj, char *id, char value)
{
    if (obj == NULL || id == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_t *attr = obj_get_attr(obj, id, true);

    if (attr == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_free_str(attr);

    attr->data.c = value;
    attr->type = TYPE_CHAR;

    return EXIT_SUCCESS;
}

/* See obj.h */
int obj_get_int(obj_t *obj, char *id)
{
    if (obj == NULL || id == NULL)
    {
        return 0;
    }

    obj_t *attr = obj_get_attr(obj, id, false);

    if (attr == NULL || attr->type != TYPE_INT)
    {
        return 0;
    }

    return attr->data.i;
}

/* See obj.h */
int obj_set_int(obj_t *obj, char *id, int value)
{
    if (obj == NULL || id == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_t *attr = obj_get_attr(obj, id, true);

    if (attr == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_free_str(attr);

    attr->data.i = value;
    attr->type = TYPE_INT;

    return EXIT_SUCCESS;
}

/* See obj.h */
char *obj_get_str(obj_t *obj, char *id)
{
    if (obj == NULL || id == NULL)
    {
        return NULL;
    }

    obj_t *attr = obj_get_attr(obj, id, false);

    if (attr == NULL || attr->type != TYPE_STR)
    {
        return NULL;
    }

    return attr->data.s;
}

/* See obj.h */
int obj_set_str(obj_t *obj, char *id, char *value)
{
    if (obj == NULL || id == NULL || value == NULL)
    {
        return EXIT_FAILURE;
    }

    obj_t *attr = obj_get_attr(obj, id, true);

    if (attr == NULL)
    {
        return EXIT_FAILURE;
    }

    int len = strnlen(value, MAXLEN_DATA);

    obj_free_str(attr);

    attr->data.s = calloc(len + 1, sizeof(char));
    strncpy(attr->data.s, value, len);
    attr->type = TYPE_STR;

    return EXIT_SUCCESS;
}
