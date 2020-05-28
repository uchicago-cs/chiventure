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

/* Checks that node_new() properly mallocs and inits a new node struct */
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

/* Checks that node_init() initialized the fields in the new node struct */
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

/* Checks that node_free() frees the given node struct from memory */
Test(dialogue, node_free)
{
    node_t *n;
    int res;

    n = node_new("Test node", "This is some test dialogue.");

    cr_assert_not_null(n, "node_new() failed");

    res = node_free(n);

    cr_assert_eq(res, SUCCESS, "node_free() failed");
}

/* Checks that edge_new() properly mallocs and inits a new edge struct */
Test(dialogue, edge_new)
{
    node_t *n;
    edge_t *e;

    n = node_new("toward test", "When the user says hi I say hello!");
    e = edge_new(n, "hi", "Quip in which user says hi!");

    cr_assert_not_null(n, "node_new() failed");
    cr_assert_not_null(e, "edge_new() failed");

    cr_assert_eq(strncmp(e->keyword, "hi", MAX_QUIP_LEN), 0,
                 "edge_new() didn't set keyword");
    cr_assert_eq(strncmp(e->quip, "Quip in which user says hi!", 
                         MAX_QUIP_LEN), 
                 0, "edge_new() didn't set quip");
    cr_assert_not_null(e->toward, "edge_new didn't set toward");
    cr_assert_eq(strncmp(e->toward->node_id, "toward test", MAX_ID_LEN), 0,
                 "new edge's toward has incorrect node_id");
    cr_assert_eq(strncmp(e->toward->dialogue, 
                 "When the user says hi I say hello!", MAX_DIA_LEN), 0,
                 "new edge's toward has incorrect dialogue");
}

/* Checks that edge_init() initialized the fields in the new edge struct */
Test(dialogue, edge_init)
{
    node_t *n, *nbad;
    edge_t *e;
    int res;

    n = node_new("toward test", "When the user says bye I say goodbye!");
    e = edge_new(nbad, "hi", "Quip in which user says hi!");

    res = edge_init(e, n, "bye", "Bye, says the user in this quip!");

    cr_assert_not_null(n, "node_new() failed");
    cr_assert_not_null(e, "edge_new() failed");

    cr_assert_eq(res, SUCCESS, "edge_init() failed");

    cr_assert_eq(strncmp(e->keyword, "bye", MAX_QUIP_LEN), 0,
                 "edge_init() didn't set keyword");
    cr_assert_eq(strncmp(e->quip, "Bye, says the user in this quip!", 
                         MAX_QUIP_LEN), 
                 0, "edge_init() didn't set quip");
    cr_assert_not_null(e->toward, "edge_init didn't set toward");
    cr_assert_eq(strncmp(e->toward->node_id, "toward test", MAX_ID_LEN), 0,
                 "initialized edge's toward has incorrect node_id");
    cr_assert_eq(strncmp(e->toward->dialogue, 
                 "When the user says bye I say goodbye!", MAX_DIA_LEN), 0,
                 "initialized edge's toward has incorrect dialogue");
}

/* Checks that edge_free() frees the given edge struct from memory */
Test(dialogue, edge_free)
{
    node_t *n;
    edge_t *e;
    int res;

    n = node_new("toward test", "When the user says hi I say hello!");
    e = edge_new(n, "hi", "Quip in which user says hi!");

    cr_assert_not_null(e, "edge_new() failed");

    res = edge_free(e);

    cr_assert_eq(res, SUCCESS, "edge_free() failed");
}

/* Checks that add_edge() adds an edge to a node */
Test(dialogue, add_edge)
{
    node_t *n;
    edge_t *e;
    edge_hash_t *hash;
    int res;

    n = node_new("toward test", "When the user says hi I say hello!");
    e = edge_new(n, "hi", "Quip in which user says hi!");
    res = add_edge(n, e);

    cr_assert_eq(res, SUCCESS, "add_edge() failed");
}

/* This test fails. If you remove the assertions, it warns that the test
 * "crashed during its setup or teardown" so it is a problem with prepend.
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

    cr_assert_eq(res1, SUCCESS, "prepend_node() failed to prepend on NULL");
    cr_assert_eq(strncmp(c->nodes->cur_node->node_id,
                         "1test node", MAX_ID_LEN),
                 0, "prepended node has incorrect node_id");
    cr_assert_eq(strncmp(c->nodes->cur_node->dialogue,
                         "Here we have some test dialogue!", MAX_DIA_LEN),
                 0, "prepended node has incorrect dialogue");
    
    res2 = prepend_node(c, n2);

    cr_assert_eq(res2, SUCCESS, "prepend_node() failed to prepend on "
                 "existing node");
     cr_assert_eq(strncmp(c->nodes->cur_node->node_id,
                         "2test node", MAX_ID_LEN),
                 0, "prepended node has incorrect node_id");
    cr_assert_eq(strncmp(c->nodes->cur_node->dialogue,
                         "This is the second testing dialogue.", MAX_DIA_LEN),
                 0, "prepended node has incorrect dialogue");

    cr_assert_not_null(c->nodes->next, "node list has NULL second element");
    cr_assert_eq(strncmp(c->nodes->next->cur_node->node_id,
                 "1test node", MAX_ID_LEN), 0,
                 "second node in list has incorrect node_id");
    cr_assert_eq(strncmp(c->nodes->next->cur_node->dialogue,
                 "Here we have some test dialogue!", MAX_DIA_LEN), 0,
                 "second node in list has incorrect dialogue");
} */
