#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cmd.h"

/* Checks if the memory for a lookup table is successfully allocated */
Test(lookup, new)
{
    lookup_t **l;

    l = lookup_t_new();

    cr_assert_not_null(l, "lookup_t_new() failed");
}

/* Checks if a lookup table is be successfully initialized */
Test(lookup, init)
{
    lookup_t *l;
    int rc;

    rc = lookup_t_init(&l);

    cr_assert_eq(rc, SUCCESS, "lookup_t_init() failed");
}

/* Checks if a lookup table is successfully freed */
Test(lookup, free)
{
    lookup_t **l;
    int rc;

    l = lookup_t_new();

    cr_assert_not_null(l, "lookup_t_new() failed");

    rc = lookup_t_free(l);

    cr_assert_eq(rc, SUCCESS, "lookup_t_free() failed");
}

/* Checks if a new cmd struct is successfully created */
Test(cmd, new)
{
    char *token[1] = {"LOOK"}, *tokens[2] = {"Take", "orb"};
    cmd *c1, *c2;
    c1 = cmd_new(token);
    c2 = cmd_new(tokens);

    cr_assert_not_null(c1, "cmd_new() failed");
    cr_assert_not_null(c2, "cmd_new() failed");

    cr_assert_eq(c1->tokens, token, 
                 "cmd_new() didn't set the tokens field correctly");
    cr_assert_eq(c2->tokens, tokens, 
                 "cmd_new() didn't set the tokens field correctly");
}

/* */
Test(cmd, init)
{
}

/* */
Test(cmd, free)
{
}
