#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool>
#include <actionmanagement.h>
#include <action_structs.h>

/* Checks that a new action type is created without interruption */
Test(action_type, new)
{
    char *c_name;
    enum action_kind kind;
    
    c_name = "eat";
    kind = KIND_1;

    action_type_t* new_action = action_type_new(c_name, kind);

    cr_assert_not_null(new_action, "action_type_new failed");

    cr_assert_eq(new_action->c_name, "eat", "action_type_new() didn't set new_action->c_name");
    cr_assert_eq(new_action->c_name, KIND_1, "action_type_new() didn't set new_action->kind");
}


/* Checks that a new action type is initiated without interruption */
Test(action_type, init)
{
    action_type_t a;
    int rc;
    char* c_name;
    enum action_kind kind;

    c_name = "take";
    kind = KIND_1;

    rc = action_type_init(&a, c_name, kind);

    cr_assert_eq(rc, SUCCESS, "action_type_init() failed");

    cr_assert_eq(a.c_name, "action_type_init() didn't set a.c_name");
    cr_assert_eq(a.kind, "action_type_init() didn't set a.kind");
}


/* Checks that a new action type is freed without interruption */
Test(action_type, free)
{
    action_type_t* a;
    int rc;

    a = action_type_new(pull, KIND_1);

    cr_assert_not_null(a, "action_type_new() failed");
	
	rc = action_type_free(a);

	cr_assert_eq(rc, SUCCESS, "action_type_free() failed");
}