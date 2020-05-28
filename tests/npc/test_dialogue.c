#include <criterion/criterion.h>
#include "npc/dialogue.h"


/* Checks that convo_new() properly mallocs a new convo struct */
Test(dialogue, convo_new)
{
    convo_t *c;

    c = convo_new();

    cr_assert_not_null(c, "convo_new() failed");
}

/* Checks that convo_free() frees the given convo struct from memory */
Test(dialogue, convo_free)
{
    convo_t *c;
    int res;

    c = convo_new();
    
    cr_assert_not_null(c, "convo_new() failed");

    res = convo_free(c);

    cr_assert_eq(res, SUCCESS, "convo_free() failed");
}

Test(dialogue, node_new)
{
    node_t *n;

    n = node_new("Test node", "Well here I am saying some test dialogue!");

    cr_assert_not_null(n, "node_new() failed");

    cr_assert_eq(strncmp(n->node_id, "Test node", MAX_ID_LEN), 0,
                 "node_new didn't set node_id");
    cr_assert_eq(strncmp(n->dialogue, 
                 "Well here I am saying some test dialogue!", MAX_DIA_LEN), 0,
                 "node_new didn't set dialogue");
}

Test(dialogue, node_init)
{
    node_t *n;
    int res;

    n = node_new("test1", "dialogue version 1");
    res = node_init(n, "2test", "2 dialogue second version");

    cr_assert_eq(res, SUCCESS, "node_init() failed");

    cr_assert_eq(strncmp(n->node_id, "2test", MAX_ID_LEN), 0,
                 "node_init didn't set node_id");
    cr_assert_eq(strncmp(n->dialogue, "2 dialogue second version", 
                 MAX_DIA_LEN), 0, "node_init didn't set dialogue");
}

Test(dialogue, node_free)
{
    node_t *n;
    int res;

    n = node_new("Test node", "This is some test dialogue.");

    cr_assert_not_null(n, "node_new() failed");

    res = node_free(n);

    cr_assert_eq(res, SUCCESS, "node_free() failed");
}

Test(dialogue, prepend_node)
{
    convo_t *c;
    node_t *n1, *n2;
    int res1, res2;

    c = convo_new();
    n1 = node_new("1test node", "Here we have some test dialogue!");
    n2 = node_new("2test node", "This is the second testing dialogue.");

    cr_assert_not_null(c, "convo_new() failed");
    cr_assert_not_null(n1, "node_new() failed");
    cr_assert_not_null(n2, "node_new() failed");

    res1 = prepend_node(c, n1);
}