#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cmd.c"

/* Checks if the memory for a lookup table is successfully allocated */
Test(lookup, new)
{
    lookup_t *l;

    l = lookup_t_new();

    cr_assert_not_null(l, "lookup_t_new() failed");
}

/* Checks if a lookup table is be successfully initialized */
Test(lookup, init)
{
    lookup_t l;
    int rc;

    rc = lookup_t_init(&p, 42, 37);

    cr_assert_eq(rc, SUCCESS, "lookup_t_init() failed");
}

/* Checks if a lookup table is successfully freed */
Test(lookup, free)
{
    lookup_t *l;
    int rc;

    l = lookup_t_new();

    cr_assert_not_null(l, "lookup_t_new() failed");

    rc = lookup_t_free(l);

    cr_assert_eq(rc, SUCCESS, "lookup_t_free() failed");
}

/* */
Test(cmd, new)
{
}

/* */
Test(cmd, init)

/* */
Test(cmd, free)
{
}
