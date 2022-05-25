#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "control_block.h"
#include "ast_block.h"

/* Checks that a new IFELSE control block is created without interruption */
Test(control_block_t, new_IFELSE)
{ 
    control_type_t control_type = IFELSE;

    control_block_t* new_control = control_block_new(control_type);

    cr_assert_not_null(new_control, "control_block_new failed");
 
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                "set new_control->control_type");

    control_block_free(new_control);
}

/* Checks that a new WHILEENDWHILE control block is created without interruption */
Test(control_block_t, new_WHILEENDWHILE)
{ 
    control_type_t control_type = WHILEENDWHILE;

    control_block_t* new_control = control_block_new(control_type);

    cr_assert_not_null(new_control, "control_block_new failed");
 
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                "set new_control->control_type");

    control_block_free(new_control);
}

/* Checks that a new FORENDFOR control block is created without interruption */
Test(control_block_t, new_FORENDFOR)
{ 
    control_type_t control_type = FORENDFOR;

    control_block_t* new_control = control_block_new(control_type);

    cr_assert_not_null(new_control, "control_block_new failed");
 
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                "set new_control->control_type");

    control_block_free(new_control);
}

/* Checks that a new AST IFELSE control block is created without interruption */
Test(control_block_t, new_AST_IFELSE)
{ 
    control_type_t control_type = IFELSE;
    block_type_t block_type = CONTROL;

    AST_block_t* new_ast = AST_control_block_new(control_type);

    cr_assert_not_null(new_ast, "AST_control_block_new failed");
 
    cr_assert_eq(new_ast->block->control_block->control_type, control_type, "AST_control_block_new() didn't "
                "set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_control_block_new() didn't "
                "set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST FORENDFOR control block is created without interruption */
Test(control_block_t, new_AST_FORENDFOR)
{ 
    control_type_t control_type = FORENDFOR;
    block_type_t block_type = CONTROL;

    AST_block_t* new_ast = AST_control_block_new(control_type);

    cr_assert_not_null(new_ast, "AST_control_block_new failed");
 
    cr_assert_eq(new_ast->block->control_block->control_type, control_type, "AST_control_block_new() didn't "
                "set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_control_block_new() didn't "
                "set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST WHILEENDWHILE control block is created without interruption */
Test(control_block_t, new_AST_WHILEENDWHILE)
{ 
    control_type_t control_type = WHILEENDWHILE;
    block_type_t block_type = CONTROL;

    AST_block_t* new_ast = AST_control_block_new(control_type);

    cr_assert_not_null(new_ast, "AST_control_block_new failed");
 
    cr_assert_eq(new_ast->block->control_block->control_type, control_type, "AST_control_block_new() didn't "
                "set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_control_block_new() didn't "
                "set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new IFELSE control block is initialized without interruption */
Test(control_block_t, init_IFELSE)
{
    control_block_t control;
    int rc;
    control_type_t control_type = IFELSE;

    rc = control_block_init(&control, control_type);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed"); 
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                "didn't set control.control_type");
}

/* Checks that a new WHILEENDWHILE control block is initialized without interruption */
Test(control_block_t, init_WHILEENDWHILE)
{
    control_block_t control;
    int rc; 
    control_type_t control_type = WHILEENDWHILE;

    rc = control_block_init(&control, control_type);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed"); 
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                "didn't set control.control_type");
}

/* Checks that a new FORENDFOR control block is initialized without interruption */
Test(control_block_t, init_FORENDFOR)
{
    control_block_t control;
    int rc; 
    control_type_t control_type = FORENDFOR;

    rc = control_block_init(&control, control_type);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed"); 
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                "didn't set control.control_type");
}


/* Checks that a new IFELSE control block is freed without interruption */
Test(control_block_t, free_IFELSE)
{
    control_block_t *control;
    control_type_t control_type = IFELSE;
    int rc; 

    control = control_block_new(control_type);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}

/* Checks that a new WHILEENDWHILE control block is freed without interruption */
Test(control_block_t, free_WHILEENDWHILE)
{
    control_block_t *control;
    control_type_t control_type = WHILEENDWHILE;
    int rc;
    
    control = control_block_new(control_type);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}

/* Checks that a new FORENDFOR control block is freed without interruption */
Test(control_block_t, free_FORENDFOR)
{
    control_block_t *control;
    control_type_t control_type = FORENDFOR;
    int rc; 

    control = control_block_new(control_type);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}
