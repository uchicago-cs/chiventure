#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
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
