#include <criterion/criterion.h>
#include "npc/dialogue.h"


/* Checks that convo_new() properly mallocs a new convo struct */
Test(dialogue, convo_new)
{
    convo_t *c;

    c = convo_new();

    cr_assert_eq(c->num_nodes, 0,
                 "create_new_convo() didn't initialize num_nodes");
    cr_assert_null(c->all_nodes,
                   "create_new_convo() didn't set all_nodes to NULL");
    cr_assert_null(c->all_nodes,
                   "create_new_convo() didn't set all_nodes to NULL");
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

    cr_assert_eq(strcmp(n->node_id, "Test node"), 0,
                 "node_new didn't set node_id");
    cr_assert_eq(strcmp(n->npc_dialogue, 
                 "Well here I am saying some test dialogue!"), 0,
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

    cr_assert_eq(strcmp(n->node_id, "2test"), 0,
                 "node_init didn't set node_id");
    cr_assert_eq(strcmp(n->npc_dialogue, "2 dialogue second version"), 0,
                 "node_init didn't set dialogue");
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
    node_t *n1, *n2;
    edge_t *e;

    n1 = node_new("from test", "When the user says hi I say hello!");
    n2 = node_new("to test", "Hello!");
    e = edge_new("Hi", n1, n2);

    cr_assert_not_null(n1, "node_new() failed");
    cr_assert_not_null(n2, "node_new() failed");
    cr_assert_not_null(e, "edge_new() failed");

    cr_assert_eq(strcmp(e->quip, "Hi"), 0, "edge_new() didn't set quip");
    
    cr_assert_not_null(e->from, "edge_new didn't set from");
    cr_assert_not_null(e->to, "edge_new didn't set to");
    cr_assert_eq(strcmp(e->from->node_id, "from test"), 0,
                 "new edge's from has incorrect node_id");
    cr_assert_eq(strcmp(e->from->npc_dialogue, 
                 "When the user says hi I say hello!"), 0,
                 "new edge's from has incorrect dialogue");
    cr_assert_eq(strcmp(e->to->node_id, "to test"), 0,
                 "new edge's to has incorrect node_id");
    cr_assert_eq(strcmp(e->to->npc_dialogue, "Hello!"), 0,
                 "new edge's to has incorrect dialogue");
}

/* Checks that edge_init() initialized the fields in the new edge struct */
Test(dialogue, edge_init)
{
    node_t *n1, *n2, *nbad;
    edge_t *e;
    int res;

    n1 = node_new("from test", "When the user says hi I say hello!");
    n2 = node_new("to test", "Hello!");
    nbad = n1 - 1;
    e = edge_new("Bye", n1, nbad);

    res = edge_init(e, "Hi", n1, n2);

    cr_assert_not_null(n1, "node_new() failed");
    cr_assert_not_null(n2, "node_new() failed");
    cr_assert_not_null(e, "edge_new() failed");

    cr_assert_eq(res, SUCCESS, "edge_init() failed");

    cr_assert_eq(strcmp(e->quip, "Hi"), 0,
                 "new edge's from has incorrect dialogue");
    cr_assert_not_null(e->from, "edge_init didn't set from");
    cr_assert_not_null(e->to, "edge_init didn't set to");
    cr_assert_eq(strcmp(e->from->node_id, "from test"), 0,
                 "new edge's from has incorrect node_id");
    cr_assert_eq(strcmp(e->from->npc_dialogue, 
                 "When the user says hi I say hello!"), 0,
                 "new edge's from has incorrect dialogue");
    cr_assert_eq(strcmp(e->to->node_id, "to test"), 0,
                 "new edge's to has incorrect node_id");
    cr_assert_eq(strcmp(e->to->npc_dialogue, "Hello!"), 0,
                 "new edge's to has incorrect dialogue");
}

/* Checks that create_new_convo() creates a convo properly */
Test(dialogue, create_new_convo)
{
    convo_t *c;

    c = create_new_convo();

    cr_assert_not_null(c, "create_new_convo() failed");
    cr_assert_eq(c->num_nodes, 0,
                 "create_new_convo() didn't initialize num_nodes");
    cr_assert_null(c->all_nodes,
                   "create_new_convo() didn't set all_nodes to NULL");
    cr_assert_null(c->all_nodes,
                   "create_new_convo() didn't set all_nodes to NULL");
}

/* Checks that add_node() adds nodes to a convo */
Test(dialogue, add_node)
{
    convo_t *c;
    int res1, res2;

    c = create_new_convo();

    res1 = add_node(c, "1", "First test");
    res2 = add_node(c, "2", "Second test");

    cr_assert_not_null(c, "create_new_convo() failed");

    cr_assert_eq(res1, SUCCESS, "First add_node() failed");  
    cr_assert_eq(res2, SUCCESS, "Second add_node() failed");    

    cr_assert_not_null(c->all_nodes, "add_edge() did not append nodes to convo");
    cr_assert_eq(strcmp(c->all_nodes->node->node_id, "1"), 0,
                 "add_edge() did not append node #1 correctly");
    cr_assert_eq(strcmp(c->all_nodes->next->node->node_id, "2"), 0,
                 "add_edge() did not append node #1 correctly");
    cr_assert_eq(c->num_nodes, 2,
                 "add_nodes() did not increment num_nodes on convo");
}

/* Checks that add_edge() adds edges to a convo */
Test(dialogue, add_edge)
{
    convo_t *c;
    int res1, res2;

    c = create_new_convo();

    add_node(c, "1", "First test");
    add_node(c, "2", "Second test");

    res1 = add_edge(c, "edge 1", "1", "2");
    res2 = add_edge(c, "edge 2", "2", "1");

    cr_assert_eq(res1, SUCCESS, "First add_edge() failed");  
    cr_assert_eq(res2, SUCCESS, "Second add_edge() failed");    

    cr_assert_not_null(c->all_edges, "add_edge() did not append edges to convo");
    cr_assert_not_null(c->all_nodes->node->edges,
                       "add_edge() did not append edge to node #1");
    cr_assert_not_null(c->all_nodes->next->node->edges,
                       "add_edge() did not append edges to node #2");
    cr_assert_eq(strcmp(c->all_nodes->node->edges->edge->quip, "edge 1"), 0,
                 "add_edge() did not append edge #1 to node #1 correctly");
    cr_assert_eq(strcmp(c->all_nodes->next->node->edges->edge->quip, "edge 2"),
                 0, "add_edge() did not append edge #1 to node #1 correctly");
    cr_assert_eq(strcmp(c->all_edges->edge->quip, "edge 1"), 0,
                 "add_edge() did not append edge #1 to convo->all_edges correctly");
    cr_assert_eq(strcmp(c->all_edges->next->edge->quip, "edge 2"), 0,
                 "add_edge() did not append edge #2 to convo->all_edges correctly");

    cr_assert_eq(c->all_nodes->node->num_edges, 1,
                 "add_edge() did not increment num_edges on node #1");
    cr_assert_eq(c->all_nodes->next->node->num_edges, 1,
                 "add_edge() did not increment num_edges on node #2");
    
    cr_assert_eq(c->all_edges->edge->from, c->all_nodes->node,
                 "edge #1's from is incorrect");
    cr_assert_eq(c->all_edges->edge->to, c->all_nodes->next->node,
                 "edge #1's to is incorrect");
    cr_assert_eq(c->all_edges->next->edge->from, c->all_nodes->next->node,
                 "edge #2's from is incorrect");
    cr_assert_eq(c->all_edges->next->edge->to, c->all_nodes->node,
                 "edge #2's to is incorrect");
}
