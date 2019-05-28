#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool>
#include <actionmanagement.h>
#include <action_structs.h>

/* Checks that a new action kind, type 1 is created without interruption */
Test(action_type, new_KIND_1)
{
    char *c_name;
    enum action_kind kind;
    
    c_name = "EAT";
    kind = KIND_1;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "EAT", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->c_name, KIND_1, "action_type_new() didn't set new_action->kind");
}


/* Checks that a new action type, kind 2 is created without interruption */
Test(action_type, new_KIND_2)
{
    char *c_name;
    enum action_kind kind;
    
    c_name = "GO";
    kind = KIND_2;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "GO", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->c_name, KIND_2, "action_type_new() didn't set new_action->kind");
}



/* Checks that a new action type, kind 3 is created without interruption */
Test(action_type, new_KIND_3)
{
    char *c_name;
    enum action_kind kind;
    
    c_name = "USE_ON";
    kind = KIND_3;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "USE_ON", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->c_name, KIND_3, "action_type_new() didn't set new_action->kind");
}


/* Checks that a new action type, kind 1 is initiated without interruption */
Test(action_type, init_KIND_1)
{
    action_type_t a;
    int rc;
    char* c_name;
    enum action_kind kind;

    c_name = "TAKE";
    kind = KIND_1;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");

    cr_assert_eq(a.c_name, "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type, kind 2 is initiated without interruption */
Test(action_type, init_KIND_2)
{
    action_type_t a;
    int rc;
    char* c_name;
    enum action_kind kind;

    c_name = "GO";
    kind = KIND_2;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");

    cr_assert_eq(a.c_name, "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type, kind 3 is initiated without interruption */
Test(action_type, init_KIND_3)
{
    action_type_t a;
    int rc;
    char* c_name;
    enum action_kind kind;

    c_name = "PUT_ON";
    kind = KIND_3;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");

    cr_assert_eq(a.c_name, "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type, kind 1 is freed without interruption */
Test(action_type, free_KIND_1)
{
    action_type_t* a;
    int rc;

    a = action_type_new("PULL", KIND_1);

    cr_assert_not_null(a, "action_type_new() failed");
	
	rc = action_type_free(a);

	cr_assert_eq(rc, SUCCESS, "action_type_free() failed");
}


/* Checks that a new action type, kind 2 is freed without interruption */
Test(action_type, free_KIND_2)
{
    action_type_t* a;
    int rc;

    a = action_type_new("GO", KIND_2);

    cr_assert_not_null(a, "action_type_new() failed");
	
	rc = action_type_free(a);

	cr_assert_eq(rc, SUCCESS, "action_type_free() failed");
}


/* Checks that a new action type, kind 2 is freed without interruption */
Test(action_type, free_KIND_2)
{
    action_type_t* a;
    int rc;

    a = action_type_new("USE_ON", KIND_3);

    cr_assert_not_null(a, "action_type_new() failed");
	
	rc = action_type_free(a);

	cr_assert_eq(rc, SUCCESS, "action_type_free() failed");
}

