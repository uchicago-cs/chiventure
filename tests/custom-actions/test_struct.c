#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom-actions/struct.h"

/* Checks that a new AST block with control type is created without interruption */
Test(AST_block_t, new_CONTROL)
{
    block_t block = control_block;
    enum block_type block_type = CONTROL;

    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, control_block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, CONTROL, "AST_block_new() didn't set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with branch type is created without interruption */
Test(AST_block_t, new_BRANCH)
{
    block_t block = branch_block;
    enum block_type block_type = BLOCK;

    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, branch_block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, BRANCH, "AST_block_new() didn't set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with action type is created without interruption */
Test(AST_block_t, new_ACTION)
{
    block_t block = action_block;
    enum block_type block_type = ACTION;

    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, action_block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, ACTION, "AST_block_new() didn't set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with conditional type is created without interruption */
Test(AST_block_t, new_CONDITIONAL)
{
    block_t block = conditional_block;
    enum block_type block_type = CONDITIONAL;

    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, conditional_block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, CONDITIONAL, "AST_block_new() didn't set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with control type is initialized without interruption */
Test(AST_block_t, init_CONTROL)
{
    AST_block_t ast;
    int rc;
    block_t block = control_block;
    enum block_type block_type = CONTROL;

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, control_block, "AST_block_init() didn't set ast.block");
    cr_assert_eq(ast.block_type, CONTROL, "AST_block_init() didn't set ast.block_type");
}

/* Checks that a new AST block with branch type is initialized without interruption */
Test(AST_block_t, init_BRANCH)
{
    AST_block_t ast;
    int rc;
    block_t block = branch_block;
    enum block_type block_type = BRANCH;

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, branch_block, "AST_block_init() didn't set ast.block");
    cr_assert_eq(ast.block_type, BRANCH, "AST_block_init() didn't set ast.block_type");
}

/* Checks that a new AST block with action type is initialized without interruption */
Test(AST_block_t, init_ACTION)
{
    AST_block_t ast;
    int rc;
    block_t block = action_block;
    enum block_type block_type = ACTION;

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, action_block, "AST_block_init() didn't set ast.block");
    cr_assert_eq(ast.block_type, ACTION, "AST_block_init() didn't set ast.block_type");
}

/* Checks that a new AST block with conditional type is initialized without interruption */
Test(AST_block_t, init_CONDITIONAL)
{
    AST_block_t ast;
    int rc;
    block_t block = conditional_block;
    enum block_type block_type = CONDITIONAL;

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, conditional_block, "AST_block_init() didn't set ast.block");
    cr_assert_eq(ast.block_type, CONDITIONAL, "AST_block_init() didn't set ast.block_type");
}

/* Checks that a new AST block with control type is freed without interruption */
Test(AST_block_t, free_CONTROL)
{
    AST_block_t* ast;
    int rc;

    ast = AST_block_new(control_block, CONTROL);

    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with branch type is freed without interruption */
Test(AST_block_t, free_BRANCH)
{
    AST_block_t* ast;
    int rc;

    ast = AST_block_new(branch_block, BRANCH);

    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with action type is freed without interruption */
Test(AST_block_t, free_ACTION)
{
    AST_block_t* ast;
    int rc;

    ast = AST_block_new(action_block, ACTION);

    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with conditional type is freed without interruption */
Test(AST_block_t, free_CONDITIONAL)
{
    AST_block_t* ast;
    int rc;

    ast = AST_block_new(conditional_block, CONDITIONAL);

    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new IF-ELSE control block is created without interruption */
Test(control_block_t, new_IF-ELSE)
{
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = IF-ELSE;

    control_block_t* new_control = control_block_new(next, control_type);

    cr_assert_not_null(new_control, "control_block_new failed");

    cr_assert_eq(new_control->next, next, "control_block_new() didn't set new_control->next");
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                "set new_control->control_type");

    control_block_free(new control);
}

/* Checks that a new WHILE-ENDWHILE control block is created without interruption */
Test(control_block_t, new_WHILE-ENDWHILE)
{
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = WHILE-ENDWHILE;

    control_block_t* new_control = control_block_new(next, control_type);

    cr_assert_not_null(new_control, "control_block_new failed");

    cr_assert_eq(new_control->next, next, "control_block_new() didn't set new_control->next");
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                 "set new_control->control_type");

    control_block_free(new control);
}

/* Checks that a new FOR-ENDFOR control block is created without interruption */
Test(control_block_t, new_FOR-ENDFOR)
{
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = FOR-ENDFOR;

    control_block_t* new_control = control_block_new(next, control_type);

    cr_assert_not_null(new_control, "control_block_new failed");

    cr_assert_eq(new_control->next, next, "control_block_new() didn't set new_control->next");
    cr_assert_eq(new_control->control_type, control_type, "control_block_new() didn't "
                 "set new_control->control_type");

    control_block_free(new control);
}

/* Checks that a new IF-ELSE control block is initialized without interruption */
Test(control_block_t, init_IF-ELSE)
{
    control_block_t control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = IF-ELSE;

    rc = control_block_init(&control, next, control_type);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed");
    cr_assert_eq(control.next, next, "control_block_init() didn't set control.next");
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                 "didn't set control.control_type");
}

/* Checks that a new WHILE-ENDWHILE control block is initialized without interruption */
Test(control_block_t, init_WHILE-ENDWHILE)
{
    control_block_t control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = WHILE-ENDWHILE;

    rc = control_block_init(&control, next, control_type);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed");
    cr_assert_eq(control.next, next, "control_block_init() didn't set control.next");
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                 "didn't set control.control_type");
}

/* Checks that a new FOR-ENDFOR control block is initialized without interruption */
Test(control_block_t, init_FOR-ENDFOR)
{
    control_block_t control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);
    enum control_type control_type = FOR-ENDFOR;

    rc = control_block_init(&control, next, control_type);

    cr_assert_eq(rc, SUCCESS, "control_block_init() failed");
    cr_assert_eq(control.next, next, "control_block_init() didn't set control.next");
    cr_assert_eq(control.control_type, control_type, "control_block_init()"
                 "didn't set control.control_type");
}


/* Checks that a new IF-ELSE control block is freed without interruption */
Test(control_block_t, free_IF-ELSE)
{
    control_block_t *control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);

    control = control_block_new(next, IF-ELSE);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}

/* Checks that a new WHILE-ENDWHILE control block is freed without interruption */
Test(control_block_t, free_WHILE-ENDWHILE)
{
    control_block_t *control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);

    control = control_block_new(next, WHILE-ENDWHILE);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}

/* Checks that a new FOR-ENDFOR control block is freed without interruption */
Test(control_block_t, free_FOR-ENDFOR)
{
    control_block_t *control;
    int rc;
    AST_block_t *next = AST_block_new(control_block, CONTROL);

    control = control_block_new(next, FOR-ENDFOR);

    cr_assert_not_null(control, "control_block_new() failed");

    rc = control_block_free(control);

    cr_assert_eq(rc, SUCCESS, "control_block_free() failed");
}
