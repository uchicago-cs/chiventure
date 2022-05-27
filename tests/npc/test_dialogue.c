#include <string.h>
#include <criterion/criterion.h>
#include "npc/dialogue.h"
#include "game-state/item.h"
#include "game-state/player.h"
#include "game-state/mode.h"
#include "game-state/game.h"

/* This function is called by test functions to check if add_node works. */
void check_add_node(int num_nodes)
{
    convo_t *c = convo_new();
    char node_id[3];
    char npc_dialogue[3];
    node_list_t *cur;
    int rc;

    strcpy(node_id, "N_");
    strcpy(npc_dialogue, "D_");

    for (int i = 1; i <= num_nodes && i < 10; i++)
    {
        node_id[1] = '0' + i;
        npc_dialogue[1] = '0' + i;

        rc = add_node(c, node_id, npc_dialogue);

        cr_assert_eq(rc, SUCCESS, "add_node() failed for Node %d", i);

        if (i == 1) cur = c->all_nodes;
        else cur = cur->next;

        cr_assert_not_null(cur, "add_node() did not append Node %d to "
                           "all_nodes in the convo", i);

        cr_assert_eq(strcmp(cur->node->node_id, node_id), 0,
                     "Expected %s for the node_id of Node %d but add_node set "
                     "a different value", node_id, i);
        cr_assert_eq(strcmp(cur->node->npc_dialogue, npc_dialogue), 0,
                     "Expected %s for the npc_dialogue of Node %d but add_node "
                     "set a different value", npc_dialogue, i);
    }
}

/* This function is called by test functions to check if add_edge works. */
void check_add_edge(int num_edges)
{
    convo_t *c = convo_new();
    char quip[3];
    edge_list_t *convo_lst_ptr, *node_lst_ptr;
    int rc;

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");

    strcpy(quip, "Q_");

    for (int i = 1; i <= num_edges && i < 10; i++)
    {
        quip[1] = '0' + i;

        rc = add_edge(c, quip, "N1", "N2", NULL);

        cr_assert_eq(rc, SUCCESS, "add_edge() failed for Edge %d", i);

        if (i == 1)
        {
            convo_lst_ptr = c->all_edges;
            node_lst_ptr = c->all_nodes->node->edges;
        }
        else
        {
            convo_lst_ptr = convo_lst_ptr->next;
            node_lst_ptr = node_lst_ptr->next;
        }

        cr_assert_not_null(convo_lst_ptr, "add_edge() did not append Edge %d "
                           "to all_edges in the convo", i);
        cr_assert_not_null(node_lst_ptr, "add_edge() did not append Edge %d "
                           "to edges in Node 1", i);

        cr_assert_eq(strcmp(convo_lst_ptr->edge->quip, quip), 0,
                     "Expected %s for the quip of Edge %d but add_edge set "
                     "a different value", quip, i);
        cr_assert_eq(strcmp(convo_lst_ptr->edge->from->node_id, "N1"), 0,
                     "add_edge set the wrong from node for Edge %d", i);
        cr_assert_eq(strcmp(convo_lst_ptr->edge->to->node_id, "N2"), 0,
                     "add_edge set the wrong to node for Edge %d", i);
    }
}

/*** Node ***/

/* Checks that node_new creates a node with the given parameters */
Test(dialogue, node_new)
{
    node_t *n;

    n = node_new("ID", "Dialogue");

    cr_assert_not_null(n, "node_new() failed");

    cr_assert_eq(strcmp(n->node_id, "ID"), 0, "node_new() didn't set node_id");
    cr_assert_eq(strcmp(n->npc_dialogue, "Dialogue"), 0,
                 "node_new() didn't set dialogue");
    cr_assert_null(n->edges, "node_new() didn't set edges to NULL");
    cr_assert_null(n->actions, "node_new() didn't actions to NULL");
}

/* Checks that node_init initializes a node with the given parameters */
Test(dialogue, node_init)
{
    node_t n;
    int rc;

    rc = node_init(&n, "ID", "Dialogue");

    cr_assert_eq(rc, SUCCESS, "node_init() failed");

    cr_assert_eq(strcmp(n.node_id, "ID"), 0, "node_init() didn't set node_id");
    cr_assert_eq(strcmp(n.npc_dialogue, "Dialogue"), 0,
                 "node_init() didn't set dialogue");
    cr_assert_null(n.edges, "node_init() didn't set edges to NULL");
    cr_assert_null(n.actions, "node_init() didn't set action to NULL");
}

/* Checks that node_free frees memory allocated to a node */
Test(dialogue, node_free)
{
    node_t *n;
    int rc;

    n = node_new("ID", "Dialogue");

    cr_assert_not_null(n, "node_new() failed");

    rc = node_free(n);

    cr_assert_eq(rc, SUCCESS, "node_free() failed");
}


/*** Edge ***/

/* Checks that edge_new creates an edge with the given parameters */
Test(dialogue, edge_new)
{
    edge_t *e;
    condition_t *cond = malloc(sizeof(condition_t));

    e = edge_new("Quip", node_new("N1", "Dia_1"), node_new("N2", "Dia_2"),
                 cond);

    cr_assert_not_null(e, "edge_new() failed");

    cr_assert_eq(strcmp(e->quip, "Quip"), 0, "edge_new() didn't set quip");
    cr_assert_eq(strcmp(e->from->node_id, "N1"), 0,
                 "edge_new() didn't set from");
    cr_assert_eq(strcmp(e->to->node_id, "N2"), 0,
                 "edge_new() didn't set to");
    cr_assert_eq(e->conditions, cond, "edge_new() didn't set conditions");
}

/* Checks that edge_init initializes an edge with the given parameters */
Test(dialogue, edge_init)
{
    edge_t e;
    int rc;
    condition_t *cond = malloc(sizeof(condition_t));

    rc = edge_init(&e, "Quip", node_new("N1", "Dia_1"),
                   node_new("N2", "Dia_2"), cond);

    cr_assert_eq(rc, SUCCESS, "edge_init() failed");

    cr_assert_eq(strcmp(e.quip, "Quip"), 0, "edge_init() didn't set quip");
    cr_assert_eq(strcmp(e.from->node_id, "N1"), 0,
                 "edge_init() didn't set from");
    cr_assert_eq(strcmp(e.to->node_id, "N2"), 0,
                 "edge_init() didn't set to");
    cr_assert_eq(e.conditions, cond, "edge_init() didn't set conditions");
}

/* Checks that edge_free frees memory allocated to an edge */
Test(dialogue, edge_free)
{
    edge_t *e;
    int rc;

    e = edge_new("Quip", node_new("N1", "Dia_1"), node_new("N2", "Dia_2"),
                 NULL);

    cr_assert_not_null(e, "edge_new() failed");

    rc = edge_free(e);

    cr_assert_eq(rc, SUCCESS, "edge_free() failed");
}


/*** Convo ***/

/* Checks that convo_new creates an empty convo */
Test(dialogue, convo_new)
{
    convo_t *c;

    c = convo_new();

    cr_assert_not_null(c, "convo_new() failed");

    cr_assert_eq(c->num_nodes, 0,
                 "convo_new() didn't set num_nodes to 0");
    cr_assert_null(c->all_nodes,
                   "convo_new() didn't set all_nodes to NULL");
    cr_assert_null(c->all_edges,
                   "convo_new() didn't set all_edges to NULL");
    cr_assert_null(c->cur_node,
                   "convo_new() didn't set cur_node to NULL");
}

/* Checks that convo_init initializes a convo */
Test(dialogue, convo_init)
{
    convo_t c;
    int rc;

    rc = convo_init(&c);

    cr_assert_eq(rc, SUCCESS, "convo_init() failed");

    cr_assert_eq(c.num_nodes, 0,
                 "convo_init() didn't set num_nodes to 0");
    cr_assert_null(c.all_nodes,
                   "convo_init() didn't set all_nodes to NULL");
    cr_assert_null(c.all_edges,
                   "convo_init() didn't set all_edges to NULL");
    cr_assert_null(c.cur_node,
                   "convo_init() didn't set cur_node to NULL");
}

/* Checks that convo_free frees memory allocated to a convo */
Test(dialogue, convo_free)
{
    convo_t *c;
    int rc;

    c = convo_new();

    cr_assert_not_null(c, "convo_new() failed");

    rc = convo_free(c);

    cr_assert_eq(rc, SUCCESS, "convo_free() failed");
}

/* Checks that add_node works for 1 node */
Test(dialogue, add_one_node)
{
    check_add_node(1);
}

/* Checks that add_node works for 5 nodes */
Test(dialogue, add_five_nodes)
{
    check_add_node(5);
}

/* Checks that add_edge works for 1 edge */
Test(dialogue, add_one_edge)
{
    check_add_edge(1);
}

/* Checks that add_edge works for 5 edges */
Test(dialogue, add_five_edges)
{
    check_add_edge(5);
}

/* Checks that add_edge works for bidirectional edges */
Test(dialogue, add_edge_bidirectional)
{
    convo_t *c = convo_new();
    int rc;

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");

    rc = add_edge(c, "Q1", "N1", "N2", NULL);
    cr_assert_eq(rc, SUCCESS, "First add_edge() failed");

    rc = add_edge(c, "Q2", "N2", "N1", NULL);
    cr_assert_eq(rc, SUCCESS, "Second add_edge() failed");

    cr_assert_eq(strcmp(c->all_nodes->node->edges->edge->quip, "Q1"), 0,
                 "add_edge failed to add edge to Node 1");
    cr_assert_eq(strcmp(c->all_nodes->next->node->edges->edge->quip, "Q2"), 0,
                 "add_edge failed to add edge to Node 2");
}


/*** Dialogue Execution Functions ***/

/* Checks that start_conversation works for 1 node with 0 edges */
Test(dialogue, start_conversation_one_node_no_edges)
{
    convo_t *c = convo_new();
    int rc;
    char *ret_str;
    char *expected = "D1\n";

    add_node(c, "N1", "D1");

    ret_str = start_conversation(c, &rc, NULL);

    cr_assert_eq(rc, 1, "Return Code was set to %d when it should have been 1, "
                 "indicating that the conversation has ended", rc);
    cr_assert_eq(strcmp(ret_str, expected), 0,
                 "Expected:\n%s for the return string of start_conversation "
                 "but start_conversation returned:\n%s", expected, ret_str);
}

/* Checks that start_conversation works for 3 nodes with 3 edges */
Test(dialogue, start_conversation_three_nodes_three_edges)
{
    convo_t *c = convo_new();
    int rc;
    char *ret_str;
    char *expected = "D1\n1. Q1\n2. Q2\n3. Q3\nEnter your choice: ";

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");
    add_node(c, "N3", "D3");

    add_edge(c, "Q1", "N1", "N2", NULL);
    add_edge(c, "Q2", "N1", "N3", NULL);
    add_edge(c, "Q3", "N1", "N3", NULL);

    ret_str = start_conversation(c, &rc, NULL);

    cr_assert_eq(rc, 0, "Return Code was set to %d when it should have been 0, "
                 "indicating that the conversation has not ended", rc);
    cr_assert_eq(strcmp(ret_str, expected), 0,
                 "Expected:\n%s for the return string of start_conversation "
                 "but start_conversation returned:\n%s", expected, ret_str);
}

/* Checks that run_conversation_step works for a 2 node, 1 edge convo that
   ends */
Test(dialogue, run_conversation_step_two_nodes_end)
{
    convo_t *c = convo_new();
    int rc;
    char *ret_str;
    char *expected = "D2\n";

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");

    add_edge(c, "Q1", "N1", "N2", NULL);

    start_conversation(c, &rc, NULL);
    cr_assert_eq(rc, 0, "start_conversation() set the wrong Return Code");

    ret_str = run_conversation_step(c, 1, &rc, NULL);

    cr_assert_eq(rc, 1, "Return Code was set to %d when it should have been 1, "
                 "indicating that the conversation has ended", rc);
    cr_assert_eq(strcmp(ret_str, expected), 0,
                 "Expected:\n%s for the return string of start_conversation "
                 "but start_conversation returned:\n%s", expected, ret_str);
}

/* Checks that run_conversation_step works for a 3 node, 2 edge convo that
   ends */
Test(dialogue, run_conversation_step_three_nodes_end)
{
    convo_t *c = convo_new();
    int rc;
    char *ret_str;
    char *expected = "D3\n";

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");
    add_node(c, "N3", "D3");

    add_edge(c, "Q1", "N1", "N2", NULL);
    add_edge(c, "Q2", "N1", "N3", NULL);

    start_conversation(c, &rc, NULL);
    cr_assert_eq(rc, 0, "start_conversation() set the wrong Return Code");

    ret_str = run_conversation_step(c, 2, &rc, NULL);

    cr_assert_eq(rc, 1, "Return Code was set to %d when it should have been 1, "
                 "indicating that the conversation has ended", rc);
    cr_assert_eq(strcmp(ret_str, expected), 0,
                 "Expected:\n%s for the return string of start_conversation "
                 "but start_conversation returned:\n%s", expected, ret_str);
}

/* Checks that run_conversation_step works for a 4 node, 3 edge convo that
   does not end */
Test(dialogue, run_conversation_step_four_nodes_continue)
{
    convo_t *c = convo_new();
    int rc;
    char *ret_str;
    char *expected = "D2\n1. Q2\n2. Q3\nEnter your choice: ";

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");
    add_node(c, "N3", "D3");
    add_node(c, "N4", "D4");

    add_edge(c, "Q1", "N1", "N2", NULL);
    add_edge(c, "Q2", "N2", "N3", NULL);
    add_edge(c, "Q3", "N2", "N4", NULL);

    start_conversation(c, &rc, NULL);
    cr_assert_eq(rc, 0, "start_conversation() set the wrong Return Code");

    ret_str = run_conversation_step(c, 1, &rc, NULL);

    cr_assert_eq(rc, 0, "Return Code was set to %d when it should have been 0, "
                 "indicating that the conversation has not ended", rc);
    cr_assert_eq(strcmp(ret_str, expected), 0,
                 "Expected:\n%s for the return string of start_conversation "
                 "but start_conversation returned:\n%s", expected, ret_str);
}


/*** Conditional Dialogue ***/

/* 1 conditional edge, not satisfied, results in 0 available edges */
Test(dialogue, one_failing_conditional)
{
    convo_t *c = convo_new();
    int rc;
    char *ret_str;
    char *expected = "D1\n";

    player_t *p = player_new("player");
    item_t *i = item_new("item", "short_desc", "long_desc");
    condition_t *cond = inventory_condition_new(p, i);

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");
    add_edge(c, "Q1", "N1", "N2", cond);

    ret_str = start_conversation(c, &rc, NULL);

    cr_assert_eq(rc, 1, "Return Code was set to %d when it should have been 1, "
                 "indicating that the conversation has ended", rc);
    cr_assert_eq(strcmp(ret_str, expected), 0,
                 "Expected:\n%s for the return string of start_conversation "
                 "but start_conversation returned:\n%s", expected, ret_str);
}

/* 2 unconditional edges and 2 conditional edges, one satisfied and one
   unsatisfied, results in 3 available edges */
Test(dialogue, two_conditionals)
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);
    convo_t *c = convo_new();
    int rc;
    char *ret_str;
    char *expected = "D1\n1. Q1\n2. Q2\n3. Q4\nEnter your choice: ";

    player_t *p = player_new("player");
    item_t *i1 = item_new("item1", "short_desc", "long_desc");
    item_t *i2 = item_new("item2", "short_desc", "long_desc");
    add_item_to_player(p, i1, ctx->game);
    condition_t *cond1 = inventory_condition_new(p, i1);
    condition_t *cond2 = inventory_condition_new(p, i2);

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");
    add_node(c, "N3", "D3");
    add_node(c, "N4", "D4");
    add_node(c, "N5", "D5");
    add_edge(c, "Q1", "N1", "N2", NULL);
    add_edge(c, "Q2", "N1", "N3", cond1);
    add_edge(c, "Q3", "N1", "N3", cond2);
    add_edge(c, "Q4", "N1", "N4", NULL);

    ret_str = start_conversation(c, &rc, NULL);

    cr_assert_eq(rc, 0, "Return Code was set to %d when it should have been 0, "
                 "indicating that the conversation has not ended", rc);
    cr_assert_eq(strcmp(ret_str, expected), 0,
                 "Expected:\n%s for the return string of start_conversation "
                 "but start_conversation returned:\n%s", expected, ret_str);
}

/*** Actions ***/

/* Give the player one item */
Test(dialogue, give_one_item)
{
    convo_t *c = convo_new();
    int rc;

    game_t *g = game_new("game");
    player_t *p = player_new("player");
    npc_t *npc = npc_new("npc", "short", "long", NULL, NULL, 0);
    item_t *i = item_new("item", "short_desc", "long_desc");

    g->curr_player = p;
    g->mode = game_mode_new(NORMAL, NULL, "npc");
    add_item_to_npc(npc, i);

    room_t *r = room_new("room", "short", "long");
    g->curr_room = r;
    add_room_to_game(g, r);
    add_npc_to_room(r->npcs, npc);
    add_npc_to_game(g, npc);

    add_node(c, "N1", "D1");

    add_give_item(c, "N1", "item");

    start_conversation(c, &rc, g);

    cr_assert_eq(rc, 1, "After start_conversation, the Return Code was set to "
                 "%d when it should have been 1", rc);
    cr_assert_eq(item_in_inventory(p, i), true, "The item was not added to "
                 "the player's inventory");
}

/* Give the player two items */
Test(dialogue, give_two_items)
{
    convo_t *c = convo_new();
    int rc;

    game_t *g = game_new("game");
    player_t *p = player_new("player");
    npc_t *npc = npc_new("npc", "short", "long", NULL, NULL, 0);
    item_t *i1 = item_new("item1", "short_desc", "long_desc");
    item_t *i2 = item_new("item2", "short_desc", "long_desc");

    g->curr_player = p;
    g->mode = game_mode_new(NORMAL, NULL, "npc");
    add_item_to_npc(npc, i1);
    add_item_to_npc(npc, i2);

    room_t *r = room_new("room", "short", "long");
    g->curr_room = r;
    add_room_to_game(g, r);
    add_npc_to_room(r->npcs, npc);
    add_npc_to_game(g, npc);

    add_node(c, "N1", "D1");

    add_give_item(c, "N1", "item1");
    add_give_item(c, "N1", "item2");

    start_conversation(c, &rc, g);

    cr_assert_eq(rc, 1, "After start_conversation, the Return Code was set to "
                 "%d when it should have been 1", rc);
    cr_assert_eq(item_in_inventory(p, i1), true, "Item 1 was not added to "
                 "the player's inventory");
    cr_assert_eq(item_in_inventory(p, i2), true, "Item 2 was not added to "
                 "the player's inventory");
}

/* Give the player one item, followed by another */
Test(dialogue, give_one_then_one_item)
{
    convo_t *c = convo_new();
    int rc;

    game_t *g = game_new("game");
    player_t *p = player_new("player");
    npc_t *npc = npc_new("npc", "short", "long", NULL, NULL, 0);
    item_t *i1 = item_new("item1", "short_desc", "long_desc");
    item_t *i2 = item_new("item2", "short_desc", "long_desc");

    g->curr_player = p;
    g->mode = game_mode_new(NORMAL, NULL, "npc");
    add_item_to_npc(npc, i1);
    add_item_to_npc(npc, i2);

    room_t *r = room_new("room", "short", "long");
    g->curr_room = r;
    add_room_to_game(g, r);
    add_npc_to_room(r->npcs, npc);
    add_npc_to_game(g, npc);

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");
    add_edge(c, "Q1", "N1", "N2", NULL);

    add_give_item(c, "N1", "item1");
    add_give_item(c, "N2", "item2");

    start_conversation(c, &rc, g);
    cr_assert_eq(rc, 0, "After start_conversation, the Return Code was set to "
                 "%d when it should have been 0", rc);

    run_conversation_step(c, 1, &rc, g);
    cr_assert_eq(rc, 1, "After run_conversation_step, the Return Code was set "
                 "to %d when it should have been 1", rc);

    cr_assert_eq(item_in_inventory(p, i1), true, "Item 1 was not added to "
                 "the player's inventory");
    cr_assert_eq(item_in_inventory(p, i2), true, "Item 2 was not added to "
                 "the player's inventory");
}

/* Take one item from the player */
Test(dialogue, take_one_item)
{
    convo_t *c = convo_new();
    int rc;

    game_t *g = game_new("game");
    player_t *p = player_new("player");
    npc_t *npc = npc_new("npc", "short", "long", NULL, NULL, 0);
    item_t *i = item_new("item", "short_desc", "long_desc");

    g->curr_player = p;
    g->mode = game_mode_new(NORMAL, NULL, "npc");
    add_item_to_player(p, i, g);

    room_t *r = room_new("room", "short", "long");
    g->curr_room = r;
    add_room_to_game(g, r);
    add_npc_to_room(r->npcs, npc);
    add_npc_to_game(g, npc);

    add_node(c, "N1", "D1");

    add_take_item(c, "N1", "item");

    start_conversation(c, &rc, g);

    cr_assert_eq(rc, 1, "After start_conversation, the Return Code was set to "
                 "%d when it should have been 1", rc);
    cr_assert_eq(item_in_inventory(p, i), false, "The item was not taken from "
                 "the player's inventory");
    cr_assert_not_null(get_item_in_hash(npc->inventory, "item"), "The item "
                       "was not given to the NPC");
}
