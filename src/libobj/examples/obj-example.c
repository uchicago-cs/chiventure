/* Example showing how to create objects from scratch. */

#include <stdio.h>

#include "libobj/obj.h"

int main()
{
    obj_t *room = obj_new("room");

    // An object can have multiple attributes at a time
    // Each attribute can have whatever type you want
    obj_set_str(room, "name", "Example Room");
    obj_set_int(room, "size", 64);
    obj_set_bool(room, "seen", false);

    // We can get the attributes
    printf("room.name: %s\n", obj_get_str(room, "name"));
    printf("room.size: %i\n", obj_get_int(room, "size"));
    printf("room.seen: %s\n", obj_get_bool(room, "seen") ? "true" : "false");

    // You can iterate over the attributes
    obj_t *curr, *tmp;
    HASH_ITER(hh, room->data.obj.attr, curr, tmp)
    {
        printf("An attribute of %s is %s\n", room->id, curr->id);
    }

    // Setting attributes is done with dot notation
    // Intermediate attributes that don't exist yet will be created (location and talisman)
    obj_set_str(room, "location.talisman", "a real slick talisman");

    // Intermediate attributes do not have a value- the following is not allowed
    // obj_set_str(room, "location", "a pedestal");

    // We can also get the value of attributes
    char *talisman = obj_get_str(room, "location.talisman");
    printf("room.location.talisman: %s\n", talisman);

    // Attributes that are of the wrong type will default to 0 for that type
    // If the type of the object isn't known in advance, use obj_get_type()
    // to get the type of the object to avoid this.
    int wrong_type = obj_get_int(room, "name");
    printf("Wrong type: %d\n", wrong_type);

    // Attributes that don't exist will also default to 0 for that type
    char* non_existent = obj_get_str(room, "color");
    printf("Nonexistent attribute: %s\n", non_existent);

    // To free an object recursively, call obj_free_all
    obj_free_all(room);

    return 0;
}
