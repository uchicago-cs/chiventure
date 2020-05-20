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
attribute_t* attribute_new(attribute_value_t value, enum attribute_tag
attribute_tag, char *name)
{
    attribute_t *attribute;
    int new_attribute;

    attribute = malloc(sizeof(attribute_t));

    if (attribute == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }

    new_attribute = attribute_init(attribute, value, attribute_tag, name);
    if (new_attribute != SUCCESS) 
    {
        error("Could not initialize attribute");
        return NULL;
    }

    return attribute;
}

/* See attribute_functions.h */
int attribute_init(attribute_t *attribute, attribute_value_t value, enum 
attribute_tag attribute_tag, char *name)
{
    assert(attribute != NULL);
    assert(value != NULL);
    assert(attribute_tag != NULL);
    assert(name != NULL);

    attribute->value = value;
    attribute->attribute_tag = attribute_tag;
    attribute->name = name;

    return SUCCESS;
}
