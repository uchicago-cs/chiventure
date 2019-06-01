#include <stdio.h>

#include "obj.h"
#include "utlist.h"

int main()
{

    obj_t *room;
    attr_list_t *ll, *el, *tmp;

    room = obj_new("room");

    // Setting properties is done with dot notation
    // Intermediate properties that don't exist yet will be created (location and talisman)
    obj_set_str(room, "location.talisman", "a real slick talisman");

    // Intermediate properties will also have a value
    obj_set_str(room, "location", "a pedestal");

    // An object can also have multiple properties at a time
    // Each property can have whatever type you want
    obj_set_int(room, "size", 64);

    // An optional self property refers to the object itself (like in python)
    // It's not necessary when accessing child properties
    // This can also just be "." or "", but "self" would probably be best (see below)
    obj_set_char(room, "self", 'A');

    // To list the immediate properties of an object use obj_list_attr()
    // You need to free the result list
    // Freeing a result will NOT free the object
    ll = obj_list_attr(room);
    DL_FOREACH_SAFE(ll, el, tmp)
    {
        printf("An attribute of %s is %s\n", room->id, el->obj->id);
        free(el);
    }


    char room_name, *desc_talisman, *desc_pedestal;

    // Intermediate properties are NOT created when using getters
    room_name = obj_get_char(room, ".");
    desc_pedestal = obj_get_str(room, "self.location");  // optional self
    desc_talisman = obj_get_str(room, "location.talisman");

    printf("%s is on %s in room %c\n", desc_talisman, desc_pedestal, room_name);


    // Properties that are of the wrong type will also default to 0 for that type
    // Properties that don't exist will also default to 0 for that type
    // Use obj_get_type() to get the type of the object to avoid this
    int fake_num;
    char fake_char;

    fake_num = obj_get_int(room, "self");
    fake_char = obj_get_char(room, "chair");

    printf("Wrong type number: %d\nNonexistent character: %c\n", fake_num, fake_char);

    obj_free_all(room);

    return 0;
}
