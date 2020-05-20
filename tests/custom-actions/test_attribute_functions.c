#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "game-state/item.h"
#include "custom-actions/struct.h"
#include "custom-actions/attribute_functions.h"

/* Checks that a new attribute with type DOUBLE is created without interruption */
Test(attribute_t, new_DOUBLE)
{
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute";
    enum attribute_tag attribute_tag = DOUBLE;
    attribute_value_t attribute_value = 0;

    attribute_t new_attribute = attribute_new(hh, attribute_key, 
    attribute_tag, attribute_value);

    cr_assert_not_null(new_attribute, "attribute_new failed");

    cr_assert_eq(new_attribute->hh, hh, "attribute_new() didn't set new_attribute->hh");
    cr_assert_eq(new_attribute->attribute_key, attribute_key, "attribute_new() didn't "
                 "set new_attribute->attribute_key");
    cr_assert_eq(new_attribute->attribute_tag, attribute_tag, "attribute_new() didn't "
                 "set new_attribute->attribute_tag");
    cr_assert_eq(new_attribute->attribute_value, attribute_value, "attribute_new() didn't "
                 "set new_attribute->attribute_value");

    attribute_free(new_attribute);
}

/* Checks that a new attribute with type CHARACTER is created without interruption */
Test(attribute_t, new_CHARACTER)
{   
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute"; 
    enum attribute_tag attribute_tag = CHARACTER;
    attribute_value_t attribute_value = "s";
    
    attribute_t new_attribute = attribute_new(hh, attribute_key,
    attribute_tag, attribute_value);
    
    cr_assert_not_null(new_attribute, "attribute_new failed");
    
    cr_assert_eq(new_attribute->hh, hh, "attribute_new() didn't set new_attribute->hh");
    cr_assert_eq(new_attribute->attribute_key, attribute_key, "attribute_new() didn't "
                 "set new_attribute->attribute_key");
    cr_assert_eq(new_attribute->attribute_tag, attribute_tag, "attribute_new() didn't "
                 "set new_attribute->attribute_tag");
    cr_assert_eq(new_attribute->attribute_value, attribute_value, "attribute_new() didn't "
                 "set new_attribute->attribute_value");
    
    attribute_free(new_attribute);
}

/* Checks that a new attribute with type BOOLE is created without interruption */
Test(attribute_t, new_BOOLE)
{   
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute"; 
    enum attribute_tag attribute_tag = BOOLE;
    attribute_value_t attribute_value = 0;
    
    attribute_t new_attribute = attribute_new(hh, attribute_key,
    attribute_tag, attribute_value);
    
    cr_assert_not_null(new_attribute, "attribute_new failed");
    
    cr_assert_eq(new_attribute->hh, hh, "attribute_new() didn't set new_attribute->hh");
    cr_assert_eq(new_attribute->attribute_key, attribute_key, "attribute_new() didn't "
                 "set new_attribute->attribute_key");
    cr_assert_eq(new_attribute->attribute_tag, attribute_tag, "attribute_new() didn't "
                 "set new_attribute->attribute_tag");
    cr_assert_eq(new_attribute->attribute_value, attribute_value, "attribute_new() didn't "
                 "set new_attribute->attribute_value");
    
    attribute_free(new_attribute);
}

/* Checks that a new attribute with type STRING is created without interruption */
Test(attribute_t, new_STRING)
{   
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute"; 
    enum attribute_tag attribute_tag = STRING;
    attribute_value_t attribute_value = "string";
    
    attribute_t new_attribute = attribute_new(hh, attribute_key,
    attribute_tag, attribute_value);
    
    cr_assert_not_null(new_attribute, "attribute_new failed");
    
    cr_assert_eq(new_attribute->hh, hh, "attribute_new() didn't set new_attribute->hh");
    cr_assert_eq(new_attribute->attribute_key, attribute_key, "attribute_new() didn't "
                 "set new_attribute->attribute_key");
    cr_assert_eq(new_attribute->attribute_tag, attribute_tag, "attribute_new() didn't "
                 "set new_attribute->attribute_tag");
    cr_assert_eq(new_attribute->attribute_value, attribute_value, "attribute_new() didn't "
                 "set new_attribute->attribute_value");
    
    attribute_free(new_attribute);
}

/* Checks that a new attribute with type INTEGER is created without interruption */
Test(attribute_t, new_INTEGER)
{   
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute"; 
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value = 0;
    
    attribute_t new_attribute = attribute_new(hh, attribute_key,
    attribute_tag, attribute_value);
    
    cr_assert_not_null(new_attribute, "attribute_new failed");
    
    cr_assert_eq(new_attribute->hh, hh, "attribute_new() didn't set new_attribute->hh");
    cr_assert_eq(new_attribute->attribute_key, attribute_key, "attribute_new() didn't "
                 "set new_attribute->attribute_key");
    cr_assert_eq(new_attribute->attribute_tag, attribute_tag, "attribute_new() didn't "
                 "set new_attribute->attribute_tag");
    cr_assert_eq(new_attribute->attribute_value, attribute_value, "attribute_new() didn't "
                 "set new_attribute->attribute_value");
    
    attribute_free(new_attribute);
}

/* Checks that a new attribute with type DOUBLE is intialized without interruption */
Test(attribute_t, init_DOUBLE)
{
    attribute_t attribute;
    int rc
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute";
    enum attribute_tag attribute_tag = DOUBLE;
    attribute_value_t attribute_value = 0;

    rc = attribute_init(&attribute, hh, attribute_key, attribute_tag, attribute_value);

    cr_assert_eq(rc, SUCCESS, "attribute_init() failed");
    cr_assert_eq(attribute.hh, hh, "attribute_init() didn't set attribute.hh");
    cr_assert_eq(attribute.attribute_key, attribute_key, "attribute_init() didn't "
                 "set attribute.attribute_key");
    cr_assert_eq(attribute.attribute_tag, attribute_tag, "attribute_init() didn't "
                 "set attribute.attribute_tag");
    cr_assert_eq(attribute.attribute_value, attribute_value, "attribute_init() didn't "
                 "set attribute.attribute_value");
}

/* Checks that a new attribute with type CHARACTER is intialized without interruption */
Test(attribute_t, init_CHARACTER)
{
    attribute_t attribute;
    int rc
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute";
    enum attribute_tag attribute_tag = CHARACTER;
    attribute_value_t attribute_value = "s";

    rc = attribute_init(&attribute, hh, attribute_key, attribute_tag, attribute_value);

    cr_assert_eq(rc, SUCCESS, "attribute_init() failed");
    cr_assert_eq(attribute.hh, hh, "attribute_init() didn't set attribute.hh");
    cr_assert_eq(attribute.attribute_key, attribute_key, "attribute_init() didn't "
                 "set attribute.attribute_key");
    cr_assert_eq(attribute.attribute_tag, attribute_tag, "attribute_init() didn't "
                 "set attribute.attribute_tag");
    cr_assert_eq(attribute.attribute_value, attribute_value, "attribute_init() didn't "
                 "set attribute.attribute_value");
}

/* Checks that a new attribute with type BOOLE is intialized without interruption */
Test(attribute_t, init_BOOLE)
{
    attribute_t attribute;
    int rc
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute";
    enum attribute_tag attribute_tag = BOOLE;
    attribute_value_t attribute_value = 0;

    rc = attribute_init(&attribute, hh, attribute_key, attribute_tag, attribute_value);

    cr_assert_eq(rc, SUCCESS, "attribute_init() failed");
    cr_assert_eq(attribute.hh, hh, "attribute_init() didn't set attribute.hh");
    cr_assert_eq(attribute.attribute_key, attribute_key, "attribute_init() didn't "
                 "set attribute.attribute_key");
    cr_assert_eq(attribute.attribute_tag, attribute_tag, "attribute_init() didn't "
                 "set attribute.attribute_tag");
    cr_assert_eq(attribute.attribute_value, attribute_value, "attribute_init() didn't "
                 "set attribute.attribute_value");
}

/* Checks that a new attribute with type STRING is intialized without interruption */
Test(attribute_t, init_STRING)
{
    attribute_t attribute;
    int rc
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute";
    enum attribute_tag attribute_tag = STRING;
    attribute_value_t attribute_value = "string";

    rc = attribute_init(&attribute, hh, attribute_key, attribute_tag, attribute_value);

    cr_assert_eq(rc, SUCCESS, "attribute_init() failed");
    cr_assert_eq(attribute.hh, hh, "attribute_init() didn't set attribute.hh");
    cr_assert_eq(attribute.attribute_key, attribute_key, "attribute_init() didn't "
                 "set attribute.attribute_key");
    cr_assert_eq(attribute.attribute_tag, attribute_tag, "attribute_init() didn't "
                 "set attribute.attribute_tag");
    cr_assert_eq(attribute.attribute_value, attribute_value, "attribute_init() didn't "
                 "set attribute.attribute_value");
}

/* Checks that a new attribute with type INTEGER is intialized without interruption */
Test(attribute_t, init_INTEGER)
{
    attribute_t attribute;
    int rc
    UT_hash_handle hh = 00;
    char *attribute_key = "attribute";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value = 0;

    rc = attribute_init(&attribute, hh, attribute_key, attribute_tag, attribute_value);

    cr_assert_eq(rc, SUCCESS, "attribute_init() failed");
    cr_assert_eq(attribute.hh, hh, "attribute_init() didn't set attribute.hh");
    cr_assert_eq(attribute.attribute_key, attribute_key, "attribute_init() didn't "
                 "set attribute.attribute_key");
    cr_assert_eq(attribute.attribute_tag, attribute_tag, "attribute_init() didn't "
                 "set attribute.attribute_tag");
    cr_assert_eq(attribute.attribute_value, attribute_value, "attribute_init() didn't "
                 "set attribute.attribute_value");
} 
