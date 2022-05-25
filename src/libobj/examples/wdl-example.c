/* Example showing how to access information loaded from a WDL file
 * into an object store.
 *
 * This example needs to be run with the connected_rooms.wdl file */

#include <stdio.h>
#include "libobj/load.h"

int main(int argc, char* argv[])
{
    //Makes sure there are enough arguments
    if (argc == 1)
    {
        printf("Err: not enough arguments\n");
        exit(1);
    }

    //Take second element of argv as filename
    char* fname = argv[1];
    if (fname == NULL)
    {
        printf("Err: no filename provided\n");
        exit(1);
    }

    /* Load object store */
    obj_t *obj_store = load_obj_store(argv[1]);;

    /* Access individual values via their identifiers */
    printf("GAME.start: %s\n", obj_get_str(obj_store,"GAME.start"));
    printf("GAME.intro: %s\n",obj_get_str(obj_store,"GAME.intro"));
    printf("GAME.end.in_room: %s\n",obj_get_str(obj_store,"GAME.end.in_room"));
    printf("ITEMS.CHAIR.short_desc: %s\n", obj_get_str(obj_store,"ITEMS.CHAIR.short_desc"));

    /* A more circuitous way of fetching one of the above values */
    obj_t *short_desc_obj = obj_get(obj_store,"ITEMS.CHAIR.short_desc");
    assert(short_desc_obj->type == TYPE_STR);
    printf("ITEMS.CHAIR.short_desc: %s\n", short_desc_obj->data.s);


    /* Iterate over attributes of an object (e.g., rooms in "ROOMS") */
    obj_t *rooms_obj = obj_get(obj_store, "ROOMS");

    /* The attributes of the "ROOMS" object are the rooms themselves */
    obj_t *curr, *tmp;
    printf("\nRooms:\n");
    HASH_ITER(hh, rooms_obj->data.obj.attr, curr, tmp)
    {
        char *id = curr->id;
        char *short_desc = obj_get_str(curr, "short_desc");

        printf("- %s: %s\n", id, short_desc);
    }

    /* Iterate over a list (e.g., actions in ITEMS.CHAIR.actions) */
    printf("\nActions in ITEMS.CHAIR.actions:\n");
    obj_list_t *actions = obj_get_list(obj_store, "ITEMS.CHAIR.actions");
    DL_FOREACH(actions, curr)
    {
        char *action = obj_get_str(curr, "action");
        printf("- %s\n", action);
    }

    return 0;
}
