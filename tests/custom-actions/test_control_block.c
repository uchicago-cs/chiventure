#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "control_block.h"

/* Checks that a new IFELSE control block is created without interruption */
Test(control_block_t, new_IFELSE)
{
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = IFELSE;

    control_block_t* new_control = control_block_new(control_type, next);

    cr_assert_not_null(new_control, "control_block_new failed");

    cr_assert_eq(new_control->next, next, "control_block_new() didn't set new_control->next");
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                "set new_control->control_type");

    control_block_free(new_control);
}

/* Checks that a new WHILEENDWHILE control block is created without interruption */
Test(control_block_t, new_WHILEENDWHILE)
{
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = WHILEENDWHILE;

    control_block_t* new_control = control_block_new(control_type, next);

    cr_assert_not_null(new_control, "control_block_new failed");

    cr_assert_eq(new_control->next, next, "control_block_new() didn't set new_control->next");
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                "set new_control->control_type");

    control_block_free(new_control);
}

/* Checks that a new FORENDFOR control block is created without interruption */
Test(control_block_t, new_FORENDFOR)
{
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = FORENDFOR;

    control_block_t* new_control = control_block_new(control_type, next);

    cr_assert_not_null(new_control, "control_block_new failed");

    cr_assert_eq(new_control->next, next, "control_block_new() didn't set new_control->next");
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                "set new_control->control_type");

    control_block_free(new_control);
}

/* Checks that a new IFELSE control block is initialized without interruption */
Test(control_block_t, init_IFELSE)
{
    control_block_t control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = IFELSE;

    rc = control_block_init(&control, control_type, next);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed");
    cr_assert_eq(control.next, next, "control_block_init() didn't set control.next");
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                "didn't set control.control_type");
}

/* Checks that a new WHILEENDWHILE control block is initialized without interruption */
Test(control_block_t, init_WHILEENDWHILE)
{
    control_block_t control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = WHILEENDWHILE;

    rc = control_block_init(&control, control_type, next);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed");
    cr_assert_eq(control.next, next, "control_block_init() didn't set control.next");
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                "didn't set control.control_type");
}

/* Checks that a new FORENDFOR control block is initialized without interruption */
Test(control_block_t, init_FORENDFOR)
{
    control_block_t control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = FORENDFOR;

    rc = control_block_init(&control, control_type, next);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed");
    cr_assert_eq(control.next, next, "control_block_init() didn't set control.next");
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                "didn't set control.control_type");
}


/* Checks that a new IFELSE control block is freed without interruption */
Test(control_block_t, free_IFELSE)
{
    control_block_t *control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);

    control = control_block_new(IFELSE, next);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}

/* Checks that a new WHILEENDWHILE control block is freed without interruption */
Test(control_block_t, free_WHILEENDWHILE)
{
    control_block_t *control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);

    control = control_block_new(WHILEENDWHILE, next);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}

/* Checks that a new FORENDFOR control block is freed without interruption */
Test(control_block_t, free_FORENDFOR)
{
    control_block_t *control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);

    control = control_block_new(FORENDFOR, next);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}
