#include <criterion/criterion.h>
#include "npc/dialogue.h"


/* Checks that convo_new() properly mallocs and inits a new convo struct */
Test (dialogue, convo_new)
{
    convo_t *c;

    c = convo_new();

    cr_assert_not_null(c, "convo_new() failed");
}

/* Checks that convo_free() frees the given convo struct from memory */
Test (dialogue, convo_free)
{
    convo_t *c;
    int res;

    c = convo_new();
    res = convo_init(c);

    cr_assert_not_null(c, "convo_new() failed");
}

