#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cli/cmd.h"

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
    lookup_t *l = NULL;
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

/* Checks if a new cmd struct is successfully created with the
 * the correct tokens field
 */
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

/* Checks if a cmd is successfully initialized */
Test(cmd, init)
{
    int rc;
    cmd c;

    char *tokens[4] = {"Put", "orb", "on", "table"};
    rc = cmd_init(&c, tokens);

    cr_assert_eq(c.tokens, tokens,
                 "cmd_init() didn't set the tokens field correctly");
    cr_assert_eq(rc, SUCCESS, "cmd_init() failed");
}

/* Checks if a cmd is successfully freed */
Test(cmd, free)
{
    cmd *c;
    int rc;

    char *tokens[4] = {"Put", "orb", "on", "table"};
    c = cmd_new(tokens);

    cr_assert_not_null(c, "cmd_new() failed");

    rc = cmd_free(c);

    cr_assert_eq(rc, SUCCESS, "cmd_free() failed");
}
