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



/* Tests the roomlevel_new function to validate that a roomlevel
 * can be made successfully. */
Test(roomlevel, new)
{
    roomlevel_t *roomlevel = roomlevel_new("excellent_name", 4);

    cr_assert_not_null(roomlevel, "failed to create new roomlevel_t\n");
}


/* Tests the init_roomlevel function to validate that a roomlevel can
 * be initialized successfully. */
Test(roomlevel, init)
{
    roomlevel_t *roomlevel = calloc(1, sizeof(roomlevel_t));
    if (!roomlevel) { 
        printf("failed to calloc for roomlevel\n");
    }
    roomlevel->room_name = calloc(1, sizeof(roomlevel_t) * MAX_SDESC_LEN);
    if (!(roomlevel->room_name)) { 
        printf("failed to calloc for roomlevel->room_name\n");
    }

    int check = init_roomlevel(roomlevel, "excellent_name", 4);
    cr_assert_str_eq(roomlevel->room_name, "excellent_name", 
                 "failed to initialize roomlevel->room_name\n");
    cr_assert_eq(4, roomlevel->difficulty_level, 
                 "failed to initialize roomlevel->difficulty_level\n");
    cr_assert_eq(check, SUCCESS, "failed to initialize a roomlevel_t\n");
}


/* Tests the roomlevel_free func to validate that a roomlevel can be
 * freed successfully. */
Test(roomlevel, free)
{
    roomlevel_t *roomlevel = roomlevel_new("excellent_name", 4);

    cr_assert_not_null(roomlevel, "failed to create new roomlevel_t\n");

    int check = roomlevel_free(roomlevel);

    cr_assert_eq(check, SUCCESS, "failed to free a roomlevel_t\n");
}


/* Tests add_roomlevel_to_hash for
   room name = "A"
   difficulty_level = 4 */
Test(roomlevel, add_roomlevel_to_hash_one)
{
    roomlevel_hash_t *roomlevel_hash = NULL;
    char *name = "A"; 

    add_roomlevel_to_hash(&roomlevel_hash, name, 4);
    
    roomlevel_t *out;
    HASH_FIND_STR(roomlevel_hash, name, out);
    cr_assert_not_null(out, "failed to add room A\n");
}


/* Tests add_roomlevel_to_hash for
   room name = "Good"
   difficulty_level = 1 */
Test(roomlevel, add_roomlevel_to_hash_two)
{
    roomlevel_hash_t *roomlevel_hash = NULL;
    char *name = "Good"; 

    add_roomlevel_to_hash(&roomlevel_hash, name, 1);
    roomlevel_t *out;
    HASH_FIND_STR(roomlevel_hash, name, out);
    cr_assert_not_null(out, "failed to add room Good\n");
}



/* Tests the levelspec_new function to validate that 
 * a levelspec can be made successfully. */
Test(levelspec, new)
{
    int num_thresholds = 3;
    int thresholds[3] = {0, 5, 10};
    levelspec_t *levelspec = levelspec_new(num_thresholds, thresholds);

    cr_assert_not_null(levelspec, "failed to create new levelspec_t\n");
    cr_assert_eq(NULL, levelspec->roomlevels, "levelspec->roomlevels hash should be NULL\n");
}


/* Tests the init_levelspec function to validate that 
 * a levelspec can be initialized successfully. */
Test(levelspec, init)
{
    int num_thresholds = 4;
    int thresholds[4] = {0, 10, 20, 30};
    
    levelspec_t *levelspec = calloc(1, sizeof(levelspec_t));
    if (!levelspec) { 
        printf("failed to calloc for levelspec\n");
    }

    levelspec->thresholds = calloc(1, sizeof(int) * num_thresholds);
    if (!(levelspec->thresholds)) { 
        printf("failed to calloc for levelspec->thresholds\n");
    }

    int check = init_levelspec(levelspec, num_thresholds, thresholds);
    cr_assert_eq(levelspec->num_thresholds, num_thresholds,
                 "failed to initialize levelspec->num_thresholds\n");
    for (int i = 0; i < num_thresholds; i++) {
        cr_assert_eq(levelspec->thresholds[i], thresholds[i],
                     "failed to initialize levelspec->threshold[%d]\n", i);
    }
    cr_assert_eq(check, SUCCESS, "failed to initialize a levelspec_t\n");
}


/* Tests the levelspec_free func to validate that a levelspec can be
 * freed successfully. */
Test(levelspec, free)
{
    int num_thresholds = 3;
    int thresholds[3]= {0, 5, 10};
    levelspec_t *levelspec = levelspec_new(num_thresholds, thresholds);
    cr_assert_not_null(levelspec, "failed to create new levelspec_t\n");

    int check = levelspec_free(levelspec);

    cr_assert_eq(check, SUCCESS, "failed to free a levelspec_t\n");
}


/* Tests that the itemspec_new function can
   create an itemspec with given params. */
Test(itemspec, new)
{

}

/* Tests that the init_itemspec function can
   initialize a given itemspec with given params. */
Test(itemspec, init)
{
    
}

/* Tests that the itemspec_free function can 
   free a given itemspec successfully. */
Test(itemspec, free)
{
    
}

/* Tests that the itemspec_new function returns NULL
   when any param requirement is violated. */
Test(itemspec, new_fail)
{
    // 1. when max_num < min_num
    // 2. when spawn_chance < 0 or > 1 
}

/* Tests that the init_itemspec function returns FAILURE
   when any param requirement is violated. */
Test(itemspec, init_fail)
{
    // 1. when max_num < min_num
    // 2. when spawn_chance < 0 or > 1   
    // 3. when given itemspec is NULL
}
