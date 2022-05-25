#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libobj/obj.h"

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
    obj->type = TYPE_NONE;

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
    obj->type = TYPE_NONE;
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

    if (obj->type == TYPE_OBJ && obj->data.obj.attr != NULL)
    {
        obj_t *el, *tmp;
        HASH_ITER(hh, obj->data.obj.attr, el, tmp)
        {
            HASH_DEL(obj->data.obj.attr, el);
            obj_free_all(el);
        }
    }
    else if (obj->type == TYPE_LIST && obj->data.lst != NULL)
    {
        obj_t *el, *tmp;
        DL_FOREACH_SAFE(obj->data.obj.attr, el, tmp)
        {
            DL_DELETE(obj->data.obj.attr, el);
            obj_free_all(el);
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
        printf("ERROR - obj_get_attr_single: Object or id given is NULL.\n");

        return NULL;
    }

    if (strncmp(id, "self", MAXLEN_ID) == 0)
    {
        return obj;
    }

    if (obj->type != TYPE_OBJ && create == true)
    {
        printf("ERROR - obj_get_attr_single: Object cannot have children.\n");
        return NULL;
    }

    obj_t *el = NULL;

    // Try to find the object in the existing hash table
    if (obj->data.obj.attr)
    {
        HASH_FIND_STR(obj->data.obj.attr, id, el);
    }

    if (el == NULL && create == true)
    {
        el = obj_new(id);
        HASH_ADD_STR(obj->data.obj.attr, id, el);
    }

    return el;
}

/* See obj.h */
obj_t *obj_get_attr(obj_t *obj, char *id, bool create)
{
    if (obj == NULL || id == NULL)
    {
        printf("ERROR - obj_get_attr_single: Object or id given is NULL.\n");

        return NULL;
    }

    char *id_imm, *free_me;
    char *tmp = calloc((MAXLEN_ID + 1) * MAX_DEPTH, sizeof(char));
    char *saveptr;
    obj_t *attr;

    // For freeing later
    free_me = tmp;

    strncpy(tmp, id, (MAXLEN_ID + 1) * MAX_DEPTH - 1);
    id_imm = strtok_r(tmp, ".", &saveptr);
    attr = obj;

    while (id_imm != NULL)
    {
        if (create == true && attr->type == TYPE_NONE)
        {
            attr->type = TYPE_OBJ;
        }

        attr = obj_get_attr_single(attr, id_imm, create);

        if (attr == NULL)
        {
            free(free_me);
            return NULL;
        }

        id_imm = strtok_r(NULL, ".", &saveptr);
    }

    free(free_me);

    return attr;
}

/* See obj.h */
obj_t *obj_get(obj_t *obj, char *id)
{
    return obj_get_attr(obj, id, false);
}

/* See obj.h */
int obj_add_attr(obj_t *obj, char *id, obj_t *attr)
{
    if (obj == NULL || attr == NULL)
    {
        printf("ERROR - obj_add_attr: Object given is NULL.\n");

        return EXIT_FAILURE;
    }

    // Make the path to the object if necessary
    obj_t *parent = obj_get_attr(obj, id, true);

    if (parent == NULL)
    {
        return EXIT_FAILURE;
    }
    
    if (parent->type == TYPE_NONE)
    {
        parent->type = TYPE_OBJ;
    }
    if (parent->type != TYPE_OBJ)
    {
        return EXIT_FAILURE;
    }
    
    HASH_ADD_STR(parent->data.obj.attr, id, attr);

    return EXIT_SUCCESS;
}

/* See obj.h */
int obj_remove_attr(obj_t *obj, char *id, bool do_free)
{
    if (obj == NULL)
    {
        printf("ERROR - obj_remove_attr: Object given is NULL.\n");

        return EXIT_FAILURE;
    }

    int parent_path_len = 0;
    if (strrchr(id, '.') != 0)
    {
        parent_path_len = strrchr(id, '.') - id + 1;
    }

    char *parent_path = calloc((MAXLEN_ID + 1) * MAX_DEPTH, sizeof(char));
    strncpy(parent_path, id, parent_path_len);
    parent_path[parent_path_len] = '\0';

    obj_t *parent = obj_get_attr(obj, parent_path, false);
    free(parent_path);

    if (parent == NULL)
    {
        return EXIT_FAILURE;
    }
    if (parent->type != TYPE_OBJ)
    {
        printf("obj_remove_attr: parent is not TYPE_OBJ");
        return EXIT_FAILURE;
    }

    obj_t *to_del;
    char *child_id = id + parent_path_len;
    HASH_FIND_STR(parent->data.obj.attr, child_id, to_del);

    if (to_del != NULL)
    {
        HASH_DEL(parent->data.obj.attr, to_del);
        
        if (do_free == true)
        {
            obj_free_all(to_del);
        }
    }

    return EXIT_SUCCESS;
}

type_t obj_get_type(obj_t *obj, char *id)
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

    if (attr == NULL)
    {
        printf("obj_get_bool: obj '%s' does not have an attribute '%s'\n", obj->id, id);
        return false;
    }
    else if (attr->type != TYPE_BOOL)
    {
        printf("obj_get_bool: This obj has incorrect type: %d\n", attr->type);
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

    if (attr == NULL)
    {
        printf("obj_get_char: obj '%s' does not have an attribute '%s'\n", obj->id, id);
        return '\0';
    }
    else if (attr->type != TYPE_CHAR)
    {
        printf("obj_get_char: This obj has incorrect type: %d\n", attr->type);
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

    if (attr == NULL)
    {
        printf("obj_get_int: obj '%s' does not have an attribute '%s'\n", obj->id, id);
        return 0;
    }
    else if (attr->type != TYPE_INT)
    {
        printf("obj_get_int: This obj has incorrect type: %d\n", attr->type);
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

    if (attr == NULL)
    {
        printf("obj_get_str: obj '%s' does not have an attribute '%s'\n", obj->id, id);
        return NULL;
    }
    else if (attr->type != TYPE_STR)
    {
        printf("obj_get_str: This obj has incorrect type: %d\n", attr->type);
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

/* See obj.h */
obj_list_t *obj_get_list(obj_t *obj, char *id)
{
    if (obj == NULL || id == NULL)
    {
        return 0;
    }

    obj_t *attr = obj_get_attr(obj, id, false);

    if (attr == NULL)
    {
        printf("obj_get_list: obj '%s' does not have an attribute '%s'\n", obj->id, id);
        return NULL;
    }
    else if (attr->type != TYPE_LIST)
    {
        printf("obj_get_list: This obj has incorrect type: %d\n", attr->type);
        return NULL;
    }

    return attr->data.lst;
}

/* See obj.h */
int obj_set_list(obj_t *obj, char *id, obj_list_t *value)
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

    attr->data.lst = value;
    attr->type = TYPE_LIST;

    return EXIT_SUCCESS;
}

/* Helper for dump_obj */
void _dump_obj(obj_t *obj, int depth)
{
    obj_t *curr, *tmp;
    if (obj->type == TYPE_OBJ)
    {
        HASH_ITER(hh, obj->data.obj.attr, curr, tmp)
        {
            for (int i = 0; i < depth; i++)
            {
                printf("  ");
            }
            printf("- %s\n", curr->id);
            _dump_obj(curr, depth + 1);
        }
    }
    else if (obj->type == TYPE_LIST)
    {
        int i = 0;
        DL_FOREACH(obj->data.lst, curr)
        {
            for (int i = 0; i < depth; i++)
            {
                printf("  ");
            }
            printf("[%d] %s\n", i, curr->id);
            _dump_obj(curr, depth + 1);
            i++;
        }
    }
}

/* See obj.h */
void dump_obj(obj_t *obj)
{
    printf("- %s\n", obj->id);
    _dump_obj(obj, 1);
}
