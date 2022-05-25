#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "common/uthash.h"
#include "game-state/item.h"
#include "openworld/default_items.h"
#include "openworld/default_rooms.h"

/* see default_rooms.h */
int copy_item_to_hash(item_hash_t **dst, item_hash_t *src, char *name)
{
    item_t *old_item;
    HASH_FIND_STR(src, name, old_item);
    if (old_item == NULL) {
        return FAILURE;
    }

    item_t *new_item = item_new(old_item->item_id, old_item->short_desc, old_item->long_desc);
    if (new_item == NULL) {
        return FAILURE;

    }

    add_item_to_hash(dst, new_item);
    return SUCCESS;
}

/* see default_rooms.h */
roomspec_t *make_default_room(char *bucket,
                              char *sh_desc, char *l_desc)
{

    rspec_hash_t *hash = NULL;
    int rc;

    assert(bucket != NULL);

    if ((!!strcmp(bucket, "school")) && (!!strcmp(bucket, "farmhouse"))
            && (!!strcmp(bucket, "castle"))) {
        roomspec_t *room = roomspec_new(bucket, sh_desc, l_desc, NULL);
        //now add to hash
        HASH_ADD_STR(hash, room_name, room);
    } else {

        item_hash_t *def = get_default_items();

        //CLOSET
        roomspec_t *closet = roomspec_new("closet",
                                          "A broom closet",
                                          "A small broom closet with supplies",
                                          NULL);
        copy_item_to_hash(&closet->items, def, "door");
        copy_item_to_hash(&closet->items, def, "tray");
        copy_item_to_hash(&closet->items, def, "mirror");
        copy_item_to_hash(&closet->items, def, "jug");
        copy_item_to_hash(&closet->items, def, "hat");

        //HALLWAY
        roomspec_t *hallway = roomspec_new("hallway", "A well-lit hallway",
                                           "A sterile, white hallway with no windows",
                                           NULL);
        copy_item_to_hash(&hallway->items, def, "door");
        copy_item_to_hash(&hallway->items, def, "nail");
        copy_item_to_hash(&hallway->items, def, "fruit");
        copy_item_to_hash(&hallway->items, def, "tray");
        copy_item_to_hash(&hallway->items, def, "book");

        //LIBRARY
        item_hash_t *libr_items = NULL;
        roomspec_t *library = roomspec_new("library",
                                           "This is a library room with resources",
                                           "An old, dusty library with"
                                           " skill-boosting resources like books and potions",
                                           NULL);
        copy_item_to_hash(&library->items, def, "book");
        copy_item_to_hash(&library->items, def, "quill");
        copy_item_to_hash(&library->items, def, "pencil");
        copy_item_to_hash(&library->items, def, "video");
        copy_item_to_hash(&library->items, def, "mirror");

        if (!strcmp(bucket, "school")) {
            //CAFETERIA
            roomspec_t *cafeteria = roomspec_new("cafeteria",
                                                 "A grungy cafeteria",
                                                 "A messy high school"
                                                 " cafeteria with trays and tables out",
                                                 NULL);
            copy_item_to_hash(&cafeteria->items, def, "apple");
            copy_item_to_hash(&cafeteria->items, def, "tray");
            copy_item_to_hash(&cafeteria->items, def, "ice");
            copy_item_to_hash(&cafeteria->items, def, "fruit");
            copy_item_to_hash(&cafeteria->items, def, "yam");

            //CLASSROOM
            roomspec_t *classroom = roomspec_new("classroom",
                                                 "A medium-sized classroom"
                                                 " with 30 desks",
                                                 "A geography teacher's"
                                                 " classroom with 30 desks",
                                                 NULL);
            copy_item_to_hash(&classroom->items, def, "book");
            copy_item_to_hash(&classroom->items, def, "door");
            copy_item_to_hash(&classroom->items, def, "pencil");
            copy_item_to_hash(&classroom->items, def, "watercolors");
            copy_item_to_hash(&classroom->items, def, "video");

            //now add all the roomspecs to the hash
            HASH_ADD_STR(hash, room_name, closet);
            HASH_ADD_STR(hash, room_name, library);
            HASH_ADD_STR(hash, room_name, hallway);
            HASH_ADD_STR(hash, room_name, cafeteria);
            HASH_ADD_STR(hash, room_name, classroom);
        } else if (!strcmp(bucket, "farmhouse")) {
            //BARN
            roomspec_t *barn = roomspec_new("barn", "A red barn",
                                            "A red barn with stables inside",
                                            NULL);
            copy_item_to_hash(&barn->items, def, "apple");
            copy_item_to_hash(&barn->items, def, "cow");
            copy_item_to_hash(&barn->items, def, "eagle");
            copy_item_to_hash(&barn->items, def, "rabbit");
            copy_item_to_hash(&barn->items, def, "yam");

            //OPEN FIELD
            roomspec_t *field = roomspec_new("open field",
                                             "An open field outside",
                                             "An open field with grass"
                                             " and a clear view",
                                             NULL);
            copy_item_to_hash(&field->items, def, "apple");
            copy_item_to_hash(&field->items, def, "zebra");
            copy_item_to_hash(&field->items, def, "cow");
            copy_item_to_hash(&field->items, def, "eagle");
            copy_item_to_hash(&field->items, def, "rabbit");

            //KITCHEN
            roomspec_t *kitchen = roomspec_new("kitchen",
                                               "A 60s era (outdated) kitchen",
                                               "An outdated kitchen with obvious"
                                               " wear-and-tear",
                                               NULL);
            copy_item_to_hash(&kitchen->items, def, "ice");
            copy_item_to_hash(&kitchen->items, def, "jug");
            copy_item_to_hash(&kitchen->items, def, "olive");
            copy_item_to_hash(&kitchen->items, def, "tray");
            copy_item_to_hash(&kitchen->items, def, "yam");

            //LIVING ROOM
            roomspec_t *living = roomspec_new("living room",
                                              "A living room with basic items",
                                              "A plain, unremarkable living room",
                                              NULL);
            copy_item_to_hash(&living->items, def, "watercolors");
            copy_item_to_hash(&living->items, def, "video");
            copy_item_to_hash(&living->items, def, "xylophone");
            copy_item_to_hash(&living->items, def, "hat");
            copy_item_to_hash(&living->items, def, "mirror");

            //now add to hash
            HASH_ADD_STR(hash, room_name, closet);
            HASH_ADD_STR(hash, room_name, barn);
            HASH_ADD_STR(hash, room_name, field);
            HASH_ADD_STR(hash, room_name, kitchen);
            HASH_ADD_STR(hash, room_name, living);
        } else {
            //DUNGEON
            roomspec_t *dungeon = roomspec_new("dungeon",
                                               "A dark dungeon",
                                               "A dank, dark dungeon with traps"
                                               " and enemies to battle",
                                               NULL);
            copy_item_to_hash(&dungeon->items, def, "nail");
            copy_item_to_hash(&dungeon->items, def, "book");
            copy_item_to_hash(&dungeon->items, def, "ladder");
            copy_item_to_hash(&dungeon->items, def, "gold");
            copy_item_to_hash(&dungeon->items, def, "yam");

            //THRONE ROOM
            roomspec_t *throne = roomspec_new("throne room",
                                              "This is a throne room",
                                              "A regal throne room decked out "
                                              "with lavish items",
                                              NULL);
            copy_item_to_hash(&throne->items, def, "gold");
            copy_item_to_hash(&throne->items, def, "door");
            copy_item_to_hash(&throne->items, def, "mirror");
            copy_item_to_hash(&throne->items, def, "jug");
            copy_item_to_hash(&throne->items, def, "hat");

            //Now add to hash
            HASH_ADD_STR(hash, room_name, closet);
            HASH_ADD_STR(hash, room_name, hallway);
            HASH_ADD_STR(hash, room_name, library);
            HASH_ADD_STR(hash, room_name, dungeon);
            HASH_ADD_STR(hash, room_name, throne);

        }

        item_hash_t *elem, *tmp;
        HASH_ITER(hh, def, elem, tmp) {
            HASH_DELETE(hh, def, elem); // remove from hashtable
            item_free(elem); // free the item
        }
        free(def);
    }
    return hash;
}



