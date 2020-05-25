#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "common/uthash.h"
#include "openworld/default_items.h"
#include "openworld/default_rooms.h"


/* see default_rooms.h */
roomspec_t *make_default_room(char *bucket,
                              char *sh_desc, char *l_desc)
{

    roomspec_t *hash = NULL;

    assert(bucket != NULL);
    if ((!strcmp(bucket, "school")) && (!strcmp(bucket, "farmhouse"))
         && (!strcmp(bucket, "castle"))) {
        roomspec_t *room = roomspec_new(bucket, sh_desc, l_desc, NULL);

        //now add to hash
        HASH_ADD_STR(hash, room_name, room);
	return hash;

    }
 
    item_hash_t *def = get_default_items();
   
    item_t *door, *mirror, *jug, *hat, 
           *fruit, *tray, *book, *quill, *pencil,
           *video, *nail;

    //CLOSET
    item_hash_t *closet_items = NULL;
    roomspec_t *closet = roomspec_new("closet",
                                      "A broom closet",
                                      "A small broom closet with supplies",
                                      closet_items);

    HASH_FIND_STR(def, "door", door);
    HASH_ADD_STR(closet_items, item_id, door);
    HASH_FIND_STR(def, "tray", tray);
    HASH_ADD_STR(closet_items, item_id, tray);
    HASH_FIND_STR(def, "mirror", mirror);
    HASH_ADD_STR(closet_items, item_id, mirror);
    HASH_FIND_STR(def, "jug", jug);
    HASH_ADD_STR(closet_items, item_id, jug);
    HASH_FIND_STR(def, "hat", hat);
    HASH_ADD_STR(closet_items, item_id, hat);
    printf("TESTING\n");
    //HALLWAY
    item_hash_t *hall_items = NULL;
    roomspec_t *hallway = roomspec_new("hallway", "A well-lit hallway",
                                       "A sterile, white hallway with no windows",
                                       hall_items);
    HASH_ADD_STR(hall_items, item_id, door);
    HASH_FIND_STR(def, "nail", nail);
    HASH_ADD_STR(hall_items, item_id, nail);
    HASH_FIND_STR(def, "fruit", fruit);
    HASH_ADD_STR(hall_items, item_id, fruit);
    HASH_ADD_STR(hall_items, item_id, tray);
    HASH_FIND_STR(def, "book", book);
    HASH_ADD_STR(hall_items, item_id, book);
    //LIBRARY
    item_hash_t *libr_items = NULL;
    roomspec_t *library = roomspec_new("library",
                                       "This is a library room with resources",
                                       "An old, dusty library with"
                                       " skill-boosting resources like books and potions",
                                       libr_items);
    HASH_ADD_STR(libr_items, item_id, book);
    HASH_FIND_STR(def, "quill", quill);
    HASH_ADD_STR(libr_items, item_id, quill);
    HASH_FIND_STR(def, "pencil", pencil);
    HASH_ADD_STR(libr_items, item_id, pencil);
    HASH_FIND_STR(def, "video", video);
    HASH_ADD_STR(libr_items, item_id, video);
    HASH_ADD_STR(libr_items, item_id, mirror);

    if (!strcmp(bucket, "school")) {
        item_t *apple, *tray, *ice, *yam, *pencil,
               *watercolors, *video;
        item_hash_t *cafe_items = NULL, *class_items = NULL;

        //CAFETERIA
        roomspec_t *cafeteria = roomspec_new("cafeteria",
                                             "A grungy cafeteria",
                                             "A messy high school"
                                             " cafeteria with trays and tables out",
                                             cafe_items);
        HASH_FIND_STR(def, "apple", apple);
        HASH_ADD_STR(cafe_items, item_id, apple);
        HASH_ADD_STR(cafe_items, item_id, fruit);
        HASH_FIND_STR(def, "tray", tray);
        HASH_ADD_STR(cafe_items, item_id, tray);
        HASH_FIND_STR(def, "ice", ice);
        HASH_ADD_STR(cafe_items, item_id, ice);
        HASH_FIND_STR(def, "yam", yam);
        HASH_ADD_STR(cafe_items, item_id, yam);

        //CLASSROOM
        roomspec_t *classroom = roomspec_new("classroom",
                                             "A medium-sized classroom"
                                             " with 30 desks",
                                             "A geography teacher's"
                                             " classroom with 30 desks",
                                             class_items);
        HASH_ADD_STR(class_items, item_id, book);
        HASH_ADD_STR(cafe_items, item_id, door);
        HASH_ADD_STR(cafe_items, item_id, pencil);
        HASH_FIND_STR(def, "watercolors", watercolors);
        HASH_ADD_STR(class_items, item_id, watercolors);
        HASH_FIND_STR(def, "video", video);
        HASH_ADD_STR(class_items, item_id, video);

        //now add all the roomspecs to the hash
        HASH_ADD_STR(hash, room_name, closet);
        HASH_ADD_STR(hash, room_name, library);
        HASH_ADD_STR(hash, room_name, hallway);
        HASH_ADD_STR(hash, room_name, cafeteria);
        HASH_ADD_STR(hash, room_name, classroom);
    } else if (!strcmp(bucket, "farmhouse")) {
        item_t *apple, *cow, *eagle, *rabbit, *yam, *zebra,
               *olive, *ice, *watercolors, *xylophone, *video, *mirror;
        item_hash_t *barn_items = NULL, *field_items = NULL,
                     *kitch_items = NULL, *living_items = NULL;
        //BARN
        roomspec_t *barn = roomspec_new("barn", "A red barn",
                                        "A red barn with stables inside",
                                        barn_items);
        HASH_FIND_STR(def, "apple", apple);
        HASH_ADD_STR(barn_items, item_id, apple);
        HASH_FIND_STR(def, "cow", cow);
        HASH_ADD_STR(barn_items, item_id, cow);
        HASH_FIND_STR(def, "eagle", eagle);
        HASH_ADD_STR(barn_items, item_id, eagle);
        HASH_FIND_STR(def, "rabbit", rabbit);
        HASH_ADD_STR(barn_items, item_id, rabbit);
        HASH_FIND_STR(def, "yam", yam);
        HASH_ADD_STR(barn_items, item_id, yam);

        //OPEN FIELD
        roomspec_t *field = roomspec_new("open field",
                                         "An open field outside",
                                         "An open field with grass"
                                         " and a clear view",
                                         field_items);
        HASH_FIND_STR(def, "zebra", zebra);
        HASH_ADD_STR(field_items, item_id, zebra);
        HASH_ADD_STR(barn_items, item_id, cow);
        HASH_ADD_STR(barn_items, item_id, eagle);
        HASH_ADD_STR(barn_items, item_id, rabbit);
        HASH_ADD_STR(barn_items, item_id, apple);

        //KITCHEN
        roomspec_t *kitchen = roomspec_new("kitchen",
                                           "A 60s era (outdated) kitchen",
                                           "An outdated kitchen with obvious"
                                           " wear-and-tear",
                                           kitch_items);
        HASH_FIND_STR(def, "olive", olive);
        HASH_ADD_STR(kitch_items, item_id, olive);
        HASH_FIND_STR(def, "ice", ice);
        HASH_ADD_STR(kitch_items, item_id, ice);
        HASH_ADD_STR(kitch_items, item_id, jug);
        HASH_ADD_STR(kitch_items, item_id, yam);
        HASH_ADD_STR(kitch_items, item_id, tray);

        //LIVING ROOM
        roomspec_t *living = roomspec_new("living room",
                                          "A living room with basic items",
                                          "A plain, unremarkable living room",
                                          living_items);
        HASH_FIND_STR(def, "watercolors", watercolors);
        HASH_ADD_STR(living_items, item_id, watercolors);
        HASH_FIND_STR(def, "video", video);
        HASH_ADD_STR(living_items, item_id, video);
        HASH_FIND_STR(def, "xylophone", xylophone);
        HASH_ADD_STR(living_items, item_id, xylophone);
        HASH_ADD_STR(living_items, item_id, hat);
        HASH_ADD_STR(living_items, item_id, mirror);

        //now add to hash
        HASH_ADD_STR(hash, room_name, closet);
        HASH_ADD_STR(hash, room_name, barn);
        HASH_ADD_STR(hash, room_name, field);
        HASH_ADD_STR(hash, room_name, kitchen);
        HASH_ADD_STR(hash, room_name, living);

    } else {
        item_t *ladder, *gold, *yam;
        item_hash_t *dungeon_items = NULL, *throne_items = NULL;

        //DUNGEON
        roomspec_t *dungeon = roomspec_new("dungeon",
                                           "A dark dungeon",
                                           "A dank, dark dungeon with traps"
                                           " and enemies to battle",
                                           dungeon_items);
        HASH_ADD_STR(dungeon_items, item_id, nail);
        HASH_ADD_STR(dungeon_items, item_id, book);
        HASH_FIND_STR(def, "ladder", ladder);
        HASH_ADD_STR(dungeon_items, item_id, ladder);
        HASH_FIND_STR(def, "gold", gold);
        HASH_ADD_STR(dungeon_items, item_id, gold);
        HASH_FIND_STR(def, "yam", yam);
        HASH_ADD_STR(dungeon_items, item_id, yam);

        //THRONE ROOM
        roomspec_t *throne = roomspec_new("throne room",
                                          "This is a throne room",
                                          "A regal throne room decked out "
                                          "with lavish items",
                                          throne_items);
        HASH_ADD_STR(throne_items, item_id, gold);
        HASH_ADD_STR(throne_items, item_id, door);
        HASH_ADD_STR(throne_items, item_id, mirror);
        HASH_ADD_STR(throne_items, item_id, jug);
        HASH_ADD_STR(throne_items, item_id, hat);

        //Now add to hash
        HASH_ADD_STR(hash, room_name, closet);
        HASH_ADD_STR(hash, room_name, hallway);
        HASH_ADD_STR(hash, room_name, library);
        HASH_ADD_STR(hash, room_name, dungeon);
        HASH_ADD_STR(hash, room_name, throne);

    }
    return hash;
}



