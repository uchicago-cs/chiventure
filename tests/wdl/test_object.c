#include <criterion/criterion.h>
#include <string.h>
#include "test_wdl.h"
#include "wdl/object.h"

Test(object, new)
{
    object_t *obj = new_object("villager",TYPE_NPC);

    cr_assert_not_null(obj, "new_object() failed");

    cr_assert_eq(strcmp(obj->id,"villager"), 0, 
                     "new_object() failed to set id");
    cr_assert_eq(obj->type, TYPE_NPC, "new_object() failed to set type");
    cr_assert_null(obj->attrs, "new_object() failed to set attrs");
}

Test(object, init)
{
    object_t obj;
    int rc;

    rc = init_object(&obj, "villager", TYPE_NPC);

    cr_assert_eq(rc, SUCCESS, "init_object() failed");

    cr_assert_eq(strcmp(obj.id,"villager"), 0,
                     "init_object() failed to set id");
    cr_assert_eq(obj.type, TYPE_NPC, "new_object() failed to set type");
    cr_assert_null(obj->attrs, "init_object() failed to set attrs");
}
}

Test(object, free)
{
    object_t *obj;
    int rc;

    obj = new_object("villager", TYPE_NPC);

    rc = free_object(obj);

    cr_assert_eq(rc, SUCCESS, "free_object() failed");
}

Test(object, get_obj_attr_empty_fail)
{
    object_t* obj = new_object("villager", TYPE_NPC);

    obj_attr_t* attr = get_obj_attribute(obj, "name");
  
    cr_assert_null(attr, 
                   "get_obj_attribute() failed to fail to find something");
}

Test(object, get_obj_attr_miss_fail)
{
    object_t* obj = new_object("villager", TYPE_NPC);

    int num_hats = 6;

    add_attribute(&(obj->attrs), "hats", &num_hats);

    obj_attr_t* attr = get_obj_attribute(obj, "name");

    cr_assert_null(attr, "get_obj_attribute() failed to miss finding");
}

Test(object, get_obj_attr_success)
{
    object_t* obj = new_object("villager", TYPE_NPC);

    char *name = "Alice";

    add_attribute(&(obj->attrs), "name", &name);

    obj_attr_t* attr = get_obj_attribute(obj, "name");

    cr_assert_not_null(attr, "get_obj_attribute() failed to find attribute");
}

Test(object, str_to_type)
{
    cr_assert_eq(strToOType("NONE"),0,
                            "strToOType() failed to convert to none");
    cr_assert_eq(strToOType("PLAYER"),1,
                 "strToOType() failed to convert to player");
    cr_assert_eq(strToOType("ROOM"),2,
                            "strToOType() failed to convert to room");
    cr_assert_eq(strToOType("ITEM"),3,
                            "strToOType() failed to convert to item");
    cr_assert_eq(strToOType("ACTION"),4,
                            "strToOType() failed to convert to action");
    cr_assert_eq(strToOType("GCONDITION"),5,
                            "strToOType() failed to convert to gcondition");
    cr_assert_eq(strToOType("NPC"),6,
                            "strToOType() failed to convert to npc");
    cr_assert_eq(strToOType("DIALOG"),7,
                            "strToOType() failed to convert to dialog");
    cr_assert_eq(strToOType("CHEESE"),-1,
                            "strToOType() failed to convert to error");
}
