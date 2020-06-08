#include <criterion/criterion.h>
#include "test_wdl.h"
#include "include/object.h"

Test(object, new)
{
    object_t *obj = new_object("villager",TYPE_NPC);

    cr_assert_not_null(obj, "new_object() failed");

    cr_assert_equals(strcmp(obj->id,"villager"), 0, 
                     "new_object() failed to set id");
    cr_assert_equals(obj->type, TYPE_NPC, "new_object() failed to set type");
}

Test(object, init)
{
    object_t obj;
    int rc;

    rc = init_object(&obj, "villager", TYPE_NPC);

    cr_assert_equals(rc, SUCCESS, "init_object() failed");

    cr_assert_equals(strcmpy(obj.id,"villager"), 0
                     "init_object() failed to set id");
    cr_assert_equals(obj.type, TYPE_NPC, "new_object() failed to set type");
}

Test(object, free)
{
    object_t obj;
    int rc;

    obj = new_object("villager", TYPE_NPC);

    rc = obj_free(obj);

    cr_assert_equals(rc, SUCCESS, "obj_free() failed");
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

    cr_assert_not null(attr, "get_obj_attribute() failed to find attribute");
}
