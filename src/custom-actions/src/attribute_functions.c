/* 
 * Basic functions for attributes to be used in custom-actions implementation. 
 *
 * Please see "attribute_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/struct.h"
#include "game-state/item.h"
#include "custom-actions/attribute_functions.h"

/* See attribute_functions.h */
attribute_t* attribute_new(UT_hash_handle hh, char *attribute_key, enum attribute_tag
attribute_tag, attribute_value_t attribute_value)
{
    attribute_t *attribute;
    int new_attribute;

    attribute = malloc(sizeof(attribute_t));

    if (attribute == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }

    new_attribute = attribute_init(attribute, hh, attribute_key, attribute_tag, 
    attribute_value);
    if (new_attribute != SUCCESS) 
    {
        error("Could not initialize attribute");
        return NULL;
    }

    return attribute;
}

/* See attribute_functions.h */
int attribute_init(attribute_t *attribute, UT_hash_handle hh, char *attribute_key, 
enum attribute_tag attribute_tag, attribute_value_t attribute_value)
{
    assert(attribute != NULL);
    assert(hh != NULL);
    assert(attribute_key != NULL);
    assert(attribute_tag != NULL);
    assert(attribute_value != NULL);

    attribute->hh = hh;
    attribute->attribute_key = attribute_key;
    attribute->attribute_tag = attribute_tag;
    attribute->attribute_value = attribute_value;

    return SUCCESS;
}
