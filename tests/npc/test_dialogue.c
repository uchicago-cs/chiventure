#include <criterion/criterion.h>
#include "npc/dialogue.h"


/* Checks that convo_new() properly mallocs a new convo struct */
Test(dialogue, convo_new)
{
    convo_t *c;

    c = convo_new("Talk to you later.");

    cr_assert_not_null(c, "convo_new() failed");
    cr_assert_eq(strncmp(c->farewell, "Talk to you later.", MAX_FW_LEN), 
                 0, "convo_new didn't set farewell");
}
