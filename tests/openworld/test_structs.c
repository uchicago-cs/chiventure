#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include <string.h>
#include "openworld/gen_structs.h"

/* Tests the gencontext_new function to validate that a gencontext
 * can be made successfully. */
Test(gencontext, new)
{

    path_t *path = path_new(NULL, "north");

    cr_assert_not_null(path, "path was NULL\n");

    gencontext_t *context = gencontext_new(path, 10, 10, NULL);

    cr_assert_not_null(context, "failed to create new gencontext_t\n");
}

/* Tests the init_gencontext function to validate that a gencontext
 * can be initialized successfully. */
Test(gencontext, init)
{

    path_t *path = path_new(NULL, "north");

    cr_assert_not_null(path, "path was NULL\n");

    gencontext_t *context = calloc(1, sizeof(gencontext_t));

    if (context == NULL) {
        fprintf(stderr, "failed to calloc for context. \n");
    }

    int check = init_gencontext(context, path, 10, 10, NULL);

    cr_assert_eq(check, SUCCESS, "failed to initialize a gencontext\n");
}

/* Tests the gencontext_free function to validate that a gencontext can
 * be freed properly */
Test(gencontext, free)
{

    path_t *path = path_new(NULL, "north");

    cr_assert_not_null(path, "path was NULL\n");

    gencontext_t *context = gencontext_new(path, 10, 10, NULL);

    cr_assert_not_null(context, "failed to create new gencontext_t\n");

    int check = gencontext_free(context);

    cr_assert_eq(check, SUCCESS, "failed to free a gencontext\n");
}

/* Tests the roomspec_new function to validate that a roomspec
 * can be made successfully. */
Test(roomspec, new1)
{

    roomspec_t *spec = roomspec_new("room_name", "short desc", "long desc", NULL);

    cr_assert_not_null(spec, "failed to create new roomspec_t\n");
}

/* Tests the init_roomspec function to validate that a roomspec
 * can be initialized successfully. */
Test(roomspec, init1)
{

    roomspec_t *spec = calloc(1, sizeof(roomspec_t));

    if (spec == NULL) {
        fprintf(stderr, "failed to calloc for spec. \n");
    }

    int check = init_roomspec(spec, "room_name", "short desc", "long desc", NULL);

    cr_assert_eq(check, SUCCESS, "failed to initialize a roomspec_t\n");
}

/* Tests the roomspec_free func to validate that a roomspec can be
 * freed successfully. */
Test(roomspec, free1)
{

    roomspec_t *spec = roomspec_new("room_name", "short desc", "long desc", NULL);

    cr_assert_not_null(spec, "failed to create new roomspec_t\n");

    int check = roomspec_free(spec);

    cr_assert_eq(check, SUCCESS, "failed to free a roomspec_t\n");
}


/* Tests the speclist_new function to validate that a speclist can
 * be made successfully. */
Test(speclist, new2)
{

    roomspec_t *spec = roomspec_new("room_name", "short desc", "long desc", NULL);

    cr_assert_not_null(spec, "failed to create new roomspec_t\n");

    speclist_t *list = speclist_new(spec);

    cr_assert_not_null(list, "failed to create new speclist_t\n");
}

/* Tests the init_speclist function to validate that a speclist can
 * be initialized successfully. */
Test(speclist, init2)
{

    roomspec_t *spec = roomspec_new("room_name", "short desc", "long desc", NULL);

    cr_assert_not_null(spec, "failed to create new roomspec_t\n");

    speclist_t *list = calloc(1, sizeof(speclist_t));

    if (list == NULL) {
        fprintf(stderr, "failed to calloc for list. \n");
    }

    int check = init_speclist(list, spec);

    cr_assert_eq(check, SUCCESS, "failed to initialize a speclist_t\n");
}

/* Tests the speclist_free function to validate that a speclist can
 * be freed successfully. */
Test(speclist, free2)
{

    roomspec_t *spec = roomspec_new("room_name", "short desc", "long desc", NULL);

    cr_assert_not_null(spec, "failed to create new roomspec_t\n");

    speclist_t *list = speclist_new(spec);

    cr_assert_not_null(list, "failed to create new speclist_t\n");

    int check = speclist_free(list);

    cr_assert_eq(check, SUCCESS, "failed to free a speclist_t\n");
}

/* Tests the free_all_speclists function to validate that it can
 * free all of the elements in the doubly linked list. */
Test(speclist, free_all)
{

    speclist_t *list = speclist_new(NULL);
    speclist_t *list1 = speclist_new(NULL);
    speclist_t *list2 = speclist_new(NULL);

    cr_assert_not_null(list, "failed to create new speclist_t\n");
    cr_assert_not_null(list1, "failed to create new speclist_t\n");
    cr_assert_not_null(list2, "failed to create new speclist_t\n");

    speclist_t *head = NULL;

    DL_APPEND(head, list);
    DL_APPEND(head, list1);
    DL_APPEND(head, list2);

    int check = speclist_free_all(list);

    cr_assert_eq(check, SUCCESS, "failed to free the entire speclist. \n");
}



/* Tests the room_level_new function to validate that a room_level
 * can be made successfully. */
Test(room_level, new)
{

    room_level_t *room_level = room_level_new("excellent_name", 4);

    cr_assert_not_null(room_level, "failed to create new room_level_t\n");
}


/* Tests the init_room_level function to validate that a room_level can
 * be initialized successfully. */
Test(room_level, init)
{
    room_level_t *room_level = calloc(1, sizeof(room_level_t));
    if (!room_level) { 
        printf("failed to calloc for room_level\n");
    }
    room_level->room_name = calloc(1, sizeof(room_level_t) * MAX_SDESC_LEN);
    if (!(room_level->room_name)) { 
        printf("failed to calloc for room_level->room_name\n");
    }

    int check = init_room_level(room_level, "excellent_name", 4);
    cr_assert_str_eq(room_level->room_name, "excellent_name", 
                 "failed to initialize room_level->room_name\n");
    cr_assert_eq(4, room_level->difficulty_level, 
                 "failed to initialize room_level->difficulty_level\n");
    cr_assert_eq(check, SUCCESS, "failed to initialize a room_level_t\n");
}

/* Tests the room_level_free func to validate that a room_level can be
 * freed successfully. */
Test(room_level, free)
{

    room_level_t *room_level = room_level_new("excellent_name", 4);

    cr_assert_not_null(room_level, "failed to create new room_level_t\n");

    int check = room_level_free(room_level);

    cr_assert_eq(check, SUCCESS, "failed to free a room_level_t\n");
}


/* Tests hash_room_level for
   room name = "A"
   difficulty_level = 4 */
Test(room_level, hash_room_level_A_4)
{
    room_level_t *room_level_hash = NULL;
    char *name = "A"; 

    hash_room_level(&room_level_hash, name, 4);
    
    room_level_t *out;
    HASH_FIND_STR(room_level_hash, name, out);
    cr_assert_not_null(out, "failed to add room A\n");
}

/* Tests hash_room_level for
   room name = "Good"
   difficulty_level = 1 */
Test(room_level, hash_room_level_Good_1)
{
    room_level_t *room_level_hash = NULL;
    char *name = "Good"; 

    hash_room_level(&room_level_hash, name, 1);
    room_level_t *out;
    HASH_FIND_STR(room_level_hash, name, out);
    cr_assert_not_null(out, "failed to add room Good\n");
}




/* Tests the difficulty_level_scale_new function to validate that a difficulty_level_scale
 * can be made successfully. */
Test(difficulty_level_scale, new)
{
    int thresholds[3]= {0, 5, 10};
    difficulty_level_scale_t *difficulty_level_scale = difficulty_level_scale_new(3, thresholds);
    cr_assert_not_null(difficulty_level_scale, "failed to create new difficulty_level_scale_t\n");
}


/* Tests the init_difficulty_level_scale function to validate that a difficulty_level_scale can
 * be initialized successfully. */
Test(difficulty_level_scale, init)
{
    int num_thresholds = 4;
    int thresholds[4] = {0, 10, 20, 30};
    
    difficulty_level_scale_t *difficulty_level_scale = calloc(1, sizeof(difficulty_level_scale_t));
    if (!difficulty_level_scale) { 
        printf("failed to calloc for difficulty_level_scale\n");
    }

    difficulty_level_scale->thresholds = calloc(1, sizeof(int) * num_thresholds);
    if (!(difficulty_level_scale->thresholds)) { 
        printf("failed to calloc for difficulty_level_scale->thresholds\n");
    }

    int check = init_difficulty_level_scale(difficulty_level_scale, num_thresholds, thresholds);
    cr_assert_eq(difficulty_level_scale->num_thresholds, num_thresholds,
                 "failed to initialize difficulty_level_scale->num_thresholds\n");
    for (int i = 0; i < num_thresholds; i++) {
        cr_assert_eq(difficulty_level_scale->thresholds[i], thresholds[i],
                     "failed to initialize difficulty_level_scale->threshold[%d]\n", i);
    }
    cr_assert_eq(check, SUCCESS, "failed to initialize a difficulty_level_scale_t\n");
}

/* Tests the difficulty_level_scale_free func to validate that a difficulty_level_scale can be
 * freed successfully. */

Test(difficulty_level_scale, free)
{

    int thresholds[3]= {0, 5, 10};
    difficulty_level_scale_t *difficulty_level_scale = difficulty_level_scale_new(3, thresholds);
    cr_assert_not_null(difficulty_level_scale, "failed to create new difficulty_level_scale_t\n");

    int check = difficulty_level_scale_free(difficulty_level_scale);

    cr_assert_eq(check, SUCCESS, "failed to free a difficulty_level_scale_t\n");
}
