#include <stdio.h>

#include "libobj/obj.h"
#include "common/utlist.h"

int main()
{

    obj_t *room;

    room = obj_new("room");

    // Setting properties is done with dot notation
    // Intermediate properties that don't exist yet will be created (location and talisman)
    obj_set_str(room, "location.talisman", "a real slick talisman");

    // Intermediate properties do not have a value- the following is not allowed
    // obj_set_str(room, "location", "a pedestal");

    // An object can also have multiple properties at a time
    // Each property can have whatever type you want
    obj_set_int(room, "size", 64);

    // An optional self property refers to the object itself (like in python)
    // It's not necessary when accessing child properties
    // This can also just be "." or ""
    obj_t *self_ex = obj_new("example_id");
    obj_set_char(self_ex, "self", 'A');

    // You can iterate over a hashtable using uthash functions
    obj_t *el, *tmp;
    HASH_ITER(hh, room, el, tmp)
    {
        printf("An attribute of %s is %s\n", room->id, el->id);
        free(el);
    }


    char *desc_talisman;

    // Intermediate properties are NOT created when using getters
    desc_talisman = obj_get_str(room, "location.talisman");

    printf("%s is in room\n", desc_talisman);


    // Properties that are of the wrong type will also default to 0 for that type
    // Properties that don't exist will also default to 0 for that type
    // Use obj_get_type() to get the type of the object to avoid this
    int fake_num;
    char fake_char;

    fake_num = obj_get_int(room, "self");
    fake_char = obj_get_char(room, "chair");

    printf("Wrong type number: %d\nNonexistent character: '%c'\n", fake_num, fake_char);

    // To free an object recursively, call obj_free_all
    obj_free_all(room);

    return 0;
}
