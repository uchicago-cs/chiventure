#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"

/* Checks that a new action kind, type 1 is created without interruption */
Test(action_type, new_ITEM)
{
    char *c_name;
    enum action_kind kind;
    
    c_name = "EAT";
    kind = ITEM;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "EAT", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->c_name, ITEM, "action_type_new() didn't set new_action->kind");
}


/* Checks that a new action type, kind 2 is created without interruption */
Test(action_type, new_PATH)
{
    char *c_name;
    enum action_kind kind;
    
    c_name = "GO";
    kind = PATH;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "GO", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->c_name, PATH, "action_type_new() didn't set new_action->kind");
}



/* Checks that a new action type, kind 3 is created without interruption */
Test(action_type, new_ITEM_ITEM)
{
    char *c_name;
    enum action_kind kind;
    
    c_name = "USE_ON";
    kind = ITEM_ITEM;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "USE_ON", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->c_name, ITEM_ITEM, "action_type_new() didn't set new_action->kind");
}


/* Checks that a new action type, kind 1 is initiated without interruption */
Test(action_type, init_ITEM)
{
    action_type_t a;
    int rc;
    char* c_name;
    enum action_kind kind;

    c_name = "TAKE";
    kind = ITEM;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");

    cr_assert_eq(a.c_name, "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type, kind 2 is initiated without interruption */
Test(action_type, init_PATH)
{
    action_type_t a;
    int rc;
    char* c_name;
    enum action_kind kind;

    c_name = "GO";
    kind = PATH;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");

    cr_assert_eq(a.c_name, "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type, kind 3 is initiated without interruption */
Test(action_type, init_ITEM_ITEM)
{
    action_type_t a;
    int rc;
    char* c_name;
    enum action_kind kind;

    c_name = "PUT_ON";
    kind = ITEM_ITEM;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");

    cr_assert_eq(a.c_name, "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, "action_type_init() didn't set a.kind");
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

    a = action_type_new("GO", PATH);

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

