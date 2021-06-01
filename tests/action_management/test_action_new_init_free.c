#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_management/actionmanagement.h"
#include "action_management/action_structs.h"

/* Checks that a new action kind, type 1 is created without interruption */
Test(action_type, new_ITEM)
{
    char *c_name = "EAT";
    enum action_kind kind = ITEM;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "EAT", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->kind, ITEM, "action_type_new() didn't set new_action->kind");

    action_type_free(new_action);
}


/* Checks that a new action type, kind 2 is created without interruption */
Test(action_type, new_PATH)
{
    char *c_name = "GO";
    enum action_kind kind = PATH;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "GO", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->kind, PATH, "action_type_new() didn't set new_action->kind");

    action_type_free(new_action);
}



/* Checks that a new action type, kind 3 is created without interruption */
Test(action_type, new_ITEM_ITEM)
{
    char *c_name = "USE_ON";
    enum action_kind kind = ITEM_ITEM;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "USE_ON", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->kind, ITEM_ITEM, "action_type_new() didn't set new_action->kind");

    action_type_free(new_action);
}

/* Checks that a new action type, kind 1 is initialized without interruption */
Test(action_type, init_ITEM)
{
    action_type_t a;
    int rc;
    char* c_name = "TAKE";
    enum action_kind kind = ITEM;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");
    cr_assert_eq(a.c_name, "TAKE", "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, ITEM, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type, kind 2 is initialized without interruption */
Test(action_type, init_PATH)
{
    action_type_t a;
    int rc;
    char* c_name = "GO";
    enum action_kind kind = PATH;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");
    cr_assert_eq(a.c_name, "GO", "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, PATH, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type, kind 3 is initialized without interruption */
Test(action_type, init_ITEM_ITEM)
{
    action_type_t a;
    int rc;
    char* c_name = "PUT_ON";
    enum action_kind kind = ITEM_ITEM;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");
    cr_assert_eq(a.c_name, "PUT_ON", "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, ITEM_ITEM, "action_type_init() didn't set a.kind");
}

/* Checks that a new action type, kind 1 is freed without interruption */
Test(action_type, free_ITEM)
{
    action_type_t* a;
    int rc;

    a = action_type_new("PULL", ITEM);

    cr_assert_not_null(a, "action_type_new() failed");

    rc = action_type_free(a);

    cr_assert_eq(rc, SUCCESS, "action_type_free() failed");
}


/* Checks that a new action type, kind 2 is freed without interruption */
Test(action_type, free_PATH)
{
    action_type_t* a;
    int rc;

    a = action_type_new("go", PATH);

    cr_assert_not_null(a, "action_type_new() failed");

    rc = action_type_free(a);

    cr_assert_eq(rc, SUCCESS, "action_type_free() failed");
}


/* Checks that a new action type, kind 2 is freed without interruption */
Test(action_type, free_ITEM_ITEM)
{
    action_type_t* a;
    int rc;

    a = action_type_new("USE_ON", ITEM_ITEM);

    cr_assert_not_null(a, "action_type_new() failed");

    rc = action_type_free(a);

    cr_assert_eq(rc, SUCCESS, "action_type_free() failed");
}


/* Checks that room and direction are initialized in ation_type_t struct */
Test(action_type, init_room_dir)
{
    action_type_t *a;
    int rc;
    room_t *new_room = room_new("test_room", "room for testing",
    "room to test path_new()");

    a = action_type_new("USE_ON", ITEM_ITEM);

    cr_assert_not_null(a, "action_type_new() failed");

    rc = action_type_init_room_dir(a, new_room, "west");

    cr_assert_eq(rc, SUCCESS, "action_type_init_room_dir() failed");
    cr_assert_not_null(a->room, "room was not initialized");
    cr_assert_not_null(a->direction, "direction was not initialized");

    room_free(new_room);
    action_type_free(a);
}
