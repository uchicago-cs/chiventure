#include "npc/dialogue.h"


/**********************************************
 *        DIALOGUE BUILDING FUNCTIONS         *
 **********************************************/

/* Returns the node corresponding to a given ID.
 *
 * Parameters:
 *  - n_lst: node list
 *  - node_id: node ID
 *
 * Returns:
 *  - a pointer to the corresponding node, or NULL if it does not exist
 */
node_t *get_node(node_list_t *n_lst, char *node_id)
{
    while (n_lst != NULL) {
        if (strcmp(n_lst->node->node_id, node_id) == 0) return n_lst->node;
        n_lst = n_lst->next;
    }

    return NULL;
}

/* See dialogue.h */
int add_node(convo_t *c, char *node_id, char *npc_dialogue)
{   
    // Check if a node with the same ID already exists
    if (get_node(c->all_nodes, node_id) != NULL) return FAILURE;

    // Create node
    node_t *n;
    if ((n = node_new(node_id, npc_dialogue)) == NULL) return FAILURE;

    // Create node list element
    node_list_t *elt;
    if ((elt = (node_list_t *) malloc(sizeof(node_list_t))) == NULL) return
        FAILURE;

    elt->node = n;

    // Append element to convo's node list
    DL_APPEND(c->all_nodes, elt);

    c->num_nodes++;

    return SUCCESS;
}

/* Returns an edge list element.
 *
 * Parameters:
 *  - e: edge
 *
 * Returns:
 *  - a pointer to the new edge list element
 *  - NULL if memory allocation failed
 */
edge_list_t *create_edge_list_element(edge_t *e)
{
    edge_list_t *elt;

    if ((elt = (edge_list_t *) malloc(sizeof(edge_list_t))) == NULL) return
        NULL;

    elt->availability = EDGE_AVAILABLE;
    elt->edge = e;

    return elt;
}

/* See dialogue.h */
int add_edge(convo_t *c, char *quip, char *from_id, char *to_id,
             condition_t *conditions)
{
    assert(c->num_nodes >= 2);

    // Get source and destination nodes
    node_t *from_node, *to_node;
    if ((from_node = get_node(c->all_nodes, from_id)) == NULL) return FAILURE;
    if ((to_node = get_node(c->all_nodes, to_id)) == NULL) return FAILURE;

    // Create edge
    edge_t *e;
    if ((e = edge_new(quip, from_node, to_node, conditions)) == NULL)
        return FAILURE;

    edge_list_t *c_elt, *n_elt;

    // all_edges in convo
    if ((c_elt = create_edge_list_element(e)) == NULL) {
        edge_free(e);
        return FAILURE;
    }

    // edges in source node
    if ((n_elt = create_edge_list_element(e)) == NULL) {
        edge_free(e);
        free(c_elt);
        return FAILURE;
    }

    // Append edge to convo and the source node's edge lists
    DL_APPEND(c->all_edges, c_elt);
    DL_APPEND(from_node->edges, n_elt);

    from_node->num_edges++;

    return SUCCESS;
}


/**********************************************
 *       DIALOGUE EXECUTION FUNCTIONS         *
 **********************************************/

/* Executes all actions on a node.
 *
 * Parameters:
 *  - n: node
 *  - game: the Chiventure game being run
 *
 * Returns:
 *  - SUCCESS if the action executed successfully, FAILURE if an error occured
 */
int do_node_actions(node_t *n, game_t *game)
{
    node_action_t *cur_action = n->actions;

    while (cur_action != NULL) {

        switch(cur_action->action) {

            case GIVE_ITEM: ;
                npc_t *npc = get_npc_in_room(game->curr_room,
                                             game->mode->mode_ctx);
                item_t *item = get_item_in_hash(npc->inventory,
                                                cur_action->action_id);
                if (item == NULL) return FAILURE;
                if (remove_item_from_npc(npc, item) != SUCCESS) return FAILURE;
                if (add_item_to_player(game->curr_player, item) != SUCCESS)
                    return FAILURE;
                break;

            case TAKE_ITEM:
                npc = get_npc_in_room(game->curr_room, game->mode->mode_ctx);
                item = get_item_in_hash(game->curr_player->inventory,
                                                cur_action->action_id);
                if (item == NULL) return FAILURE;
                if (remove_item_from_player(game->curr_player, item) != SUCCESS)
                    return FAILURE;
                if (add_item_to_npc(npc, item) != SUCCESS) return FAILURE;
                break;

            case START_QUEST:
                // to do
                break;

            case START_BATTLE:
                // to do
                break;

            default:
                return FAILURE;
        }

        cur_action = cur_action->next;
    }

    return SUCCESS;
}

/* Checks each edge and updates their availability status, then counts the
 * total number of available edges.
 *
 * Parameters:
 *  - n: node
 *
 * Returns:
 *  - SUCCESS if the action executed successfully, FAILURE if an error occured
 */
int update_edge_availabilities(node_t *n)
{
    if (n == NULL) return FAILURE;

    int num_avail_edges = 0;
    edge_list_t *cur_edge = n->edges;

    while (cur_edge != NULL) {
        if (cur_edge->availability != EDGE_DISABLED) {
            if (cur_edge->edge->conditions != NULL) {
                // true = 1 = EDGE_AVAILABLE, false = 0 = EDGE_UNAVAILABLE
                cur_edge->availability =
                    all_conditions_met(cur_edge->edge->conditions);
            }
            if (cur_edge->availability) num_avail_edges++;
        }
        cur_edge = cur_edge->next;
    }

    n->num_available_edges = num_avail_edges;

    return SUCCESS;
}

/* Creates a return string containing NPC dialogue and dialogue options
 * (to be printed by the CLI).
 *
 * SAMPLE OUTPUT:
 * Pick an item: a sword or a shield?
 * 1. Sword
 * 2. Shield
 * Enter your choice: 
 *
 * Parameters:
 *  - n: pointer to a node
 *  - is_leaf: 1 or 0, indicating whether c->cur_node is a leaf
 *
 * Returns:
 *  - A string that can be directly printed by the CLI
 */
char *create_return_string(node_t *n, int is_leaf)
{
    char *input_prompt = "Enter your choice: ";
    int totlen = 0;
    int len_lst[n->num_available_edges + 2];
    edge_list_t *cur_edge = n->edges;
    int i = 0;
    int option_number = 1;

    // Compute buffer length
    totlen += (len_lst[i++] = strlen(n->npc_dialogue));
    totlen += 1;
    while (cur_edge != NULL) {
        if (cur_edge->availability == EDGE_AVAILABLE) {
            totlen += (int) log10(option_number++) + 1;
            totlen += (len_lst[i++] = strlen(cur_edge->edge->quip));
            totlen += 3;
        }
        cur_edge = cur_edge->next;
    }
    if (!is_leaf) totlen += (len_lst[i] = strlen(input_prompt));
    totlen += 1;

    // Create return string
    char *buf, *p;
    char temp[5]; 
    cur_edge = n->edges;
    i = 0;
    option_number = 1;

    if ((buf = malloc(sizeof(char) * totlen)) == NULL) return NULL;
    p = buf;

    memcpy(p, n->npc_dialogue, len_lst[i]);
    p += len_lst[i++];
    *p++ = '\n';
    while (cur_edge != NULL) {
        if (cur_edge->availability == EDGE_AVAILABLE) {
            sprintf(temp, "%d", option_number);
            memcpy(p, temp, (int) log10(option_number) + 1);
            p += (int) log10(option_number++) + 1;
            *p++ = '.';
            *p++ = ' ';
            memcpy(p, cur_edge->edge->quip, len_lst[i]);
            p += len_lst[i++];
            *p++ = '\n';
        }
        cur_edge = cur_edge->next;
    }
    if (!is_leaf) {
        memcpy(p, input_prompt, len_lst[i]);
        p += len_lst[i];
    }
    *p = '\0';

    return buf;
}

/* See dialogue.h */
char *start_conversation(convo_t *c, int *rc, game_t *game)
{   
    if (c == NULL) {
        *rc = -1;
        return NULL;
    }

    char *ret_str;

    // Step 1: Set current node to first node
    c->cur_node = c->all_nodes->node;

    // Step 2: Execute actions (item, quest, battle, etc.), if any
    if (do_node_actions(c->cur_node, game) != SUCCESS) {
        *rc = -1;
        return NULL;
    }

    // Step 3: Recheck the availability of each edge, count total avail. edges
    if (update_edge_availabilities(c->cur_node) != SUCCESS) {
        *rc = -1;
        return NULL;
    }

    // Step 4: Prepare return code and return string
    if (c->cur_node->num_available_edges == 0) *rc = 1;
    else *rc = 0;

    ret_str = create_return_string(c->cur_node, *rc);
    if (ret_str == NULL) *rc = -1;
    
    return ret_str;
}

/* See dialogue.h */
char *run_conversation_step(convo_t *c, int input, int *rc, game_t *game)
{   
    if (input > c->cur_node->num_available_edges)
        input = c->cur_node->num_available_edges;

    char *ret_str;
    edge_list_t *cur_edge;

    // Step 1: Traverse to the player's selected node
    cur_edge = c->cur_node->edges;
    // The logic here works as follows:
    // (1) We only decrement input when we encounter an available edge, until
    //     input become 1
    // (2) However, we could end up on an unavailable edge, which is where
    //     "|| cur_edge->availability != EDGE_AVAILABLE" comes in
    // (3) Overall, this code ensures that we arrive at the player's selected
    //     edge
    while (input > 1 || cur_edge->availability != EDGE_AVAILABLE) {
        if (cur_edge->availability == EDGE_AVAILABLE) input--;
        cur_edge = cur_edge->next;
    }

    c->cur_node = cur_edge->edge->to;

    // Step 2: Disable edge if the node it leads to has an action
    // NOTE: This is a temporary solution that prevents issues like being able
    //       to receive multiple copies of items, starting the same quest twice.
    //       This SHOULD be changed / made more complex in the future.
    if (c->cur_node->actions != NULL) {
        cur_edge->availability = EDGE_DISABLED;
    }

    // Step 3: Execute actions (item, quest, battle, etc.), if any
    if (do_node_actions(c->cur_node, game) != SUCCESS) {
        *rc = -1;
        return NULL;
    }

    // Step 4: Recheck the availability of each edge, count total avail. edges
    if (update_edge_availabilities(c->cur_node) != SUCCESS) {
        *rc = -1;
        return NULL;
    }

    // Step 5: Prepare return code and return string
    if (c->cur_node->num_available_edges == 0) *rc = 1;
    else *rc = 0;

    ret_str = create_return_string(c->cur_node, *rc);
    if (ret_str == NULL) *rc = -1;

    return ret_str;
}


/**********************************************
 *             ACTION FUNCTIONS               *
 **********************************************/

/* Create a new action, and append it to the node's action list.
 *
 * Parameters:
 *  - n: node
 *  - action: type of action
 *  - action_id: ID associated with that action, if any
 *
 * Returns:
 *  - SUCCESS if the operation suceeded, FAILURE otherwise
 */
int add_action_to_node(node_t *n, node_action_type action, char *action_id)
{
    node_action_t *n_a;
    if ((n_a = node_action_new(action, action_id)) == NULL) return FAILURE;

    DL_APPEND(n->actions, n_a);

    return SUCCESS;
}

/* See dialogue.h */
int add_give_item(convo_t *c, char *node_id, char *item_id)
{
    assert(item_id != NULL);
    
    node_t *n;
    if ((n = get_node(c->all_nodes, node_id)) == NULL) return FAILURE;

    return add_action_to_node(n, GIVE_ITEM, item_id);
}

/* See dialogue.h */
int add_take_item(convo_t *c, char *node_id, char *item_id)
{
    assert(item_id != NULL);
    
    node_t *n;
    if ((n = get_node(c->all_nodes, node_id)) == NULL) return FAILURE;

    return add_action_to_node(n, TAKE_ITEM, item_id);
}

/* See dialogue.h */
int add_start_quest(convo_t *c, char *node_id, long quest_id)
{
    // to do
    return 0;
}

/* See dialogue.h */
int add_start_battle(convo_t *c, char *node_id, char *battle_id)
{
    // to do
    return 0;
}


/**********************************************
 *    STRUCT (INIT, NEW, FREE) FUNCTIONS      *
 **********************************************/

/* See dialogue.h */
int edge_init(edge_t *e, char *quip, node_t *from, node_t *to,
              condition_t *conditions)
{
    assert(e != NULL);
    assert(quip != NULL);
    assert(strlen(quip) < MAX_QUIP_LEN);
    assert(from != NULL && to != NULL);

    if ((e->quip = strdup(quip)) == NULL) return FAILURE;
    e->from = from;
    e->to = to;
    e->conditions = conditions;

    return SUCCESS;
}

/* See dialogue.h */
edge_t *edge_new(char *quip, node_t *from, node_t *to, condition_t *conditions)
{
    edge_t *e;
    if ((e = (edge_t *) malloc(sizeof(edge_t))) == NULL) return NULL;

    if (edge_init(e, quip, from, to, conditions) != SUCCESS) {
        edge_free(e);
        return NULL;
    }

    return e;
}

/* See dialogue.h */
int edge_free(edge_t *e)
{
    if (e != NULL) {
        free(e->quip);
        delete_condition_llist(e->conditions);
        free(e);
    }

    return SUCCESS;
}

/* See dialogue.h */
int node_init(node_t *n, char *node_id, char *npc_dialogue)
{
    assert(n != NULL);
    assert(node_id != NULL);
    assert(npc_dialogue != NULL);
    assert(strlen(node_id) < MAX_NODE_ID_LEN);
    assert(strlen(npc_dialogue) < MAX_DIA_LEN);

    if ((n->node_id = strdup(node_id)) == NULL) return FAILURE;
    if ((n->npc_dialogue = strdup(npc_dialogue)) == NULL) return FAILURE;
    n->num_edges = 0;
    n->num_available_edges = 0;
    n->edges = NULL;
    n->actions = NULL;

    return SUCCESS;
}

/* See dialogue.h */
node_t *node_new(char *node_id, char *npc_dialogue)
{
    node_t *n;
    if ((n = (node_t *) malloc(sizeof(node_t))) == NULL) return NULL;

    if (node_init(n, node_id, npc_dialogue) != SUCCESS) {
        node_free(n);
        return NULL;
    }

    return n;
}

/* See dialogue.h */
int node_free(node_t *n)
{
    if (n != NULL) {
        if (free_edge_list(n->edges, true) != SUCCESS) return FAILURE;
        free(n->node_id);
        free(n->npc_dialogue);
        free_node_actions(n->actions);
        free(n);
    }

    return SUCCESS;
}

/* See dialogue.h */
int convo_init(convo_t *c)
{
    assert(c != NULL);

    c->num_nodes = 0;
    c->all_nodes = NULL;
    c->all_edges = NULL;
    c->cur_node = NULL;

    return SUCCESS;
}

/* See dialogue.h */
convo_t *convo_new()
{
    convo_t *c;

    if ((c = (convo_t *) malloc(sizeof(convo_t))) == NULL) return NULL;

    if (convo_init(c) != SUCCESS) {
        convo_free(c);
        return NULL;
    }

    return c;
}

/* See dialogue.h */
int convo_free(convo_t *c)
{
    if (c != NULL) {
        if (free_node_list(c->all_nodes, true) != SUCCESS) return FAILURE;
        if (free_edge_list(c->all_edges, false) != SUCCESS) return FAILURE;
        free(c);
    }

    return SUCCESS;
}

/* See dialogue.h */
int free_edge_list(edge_list_t *e_lst, bool free_edges)
{
    edge_list_t *elt, *tmp;

    DL_FOREACH_SAFE(e_lst, elt, tmp) {
        DL_DELETE(e_lst, elt);
        if (free_edges) edge_free(elt->edge);
        free(elt);
    }

    return SUCCESS;
}

/* See dialogue.h */
int free_node_list(node_list_t *n_lst, bool free_nodes)
{
    node_list_t *elt, *tmp;

    DL_FOREACH_SAFE(n_lst, elt, tmp) {
        DL_DELETE(n_lst, elt);
        if (free_nodes) node_free(elt->node);
        free(elt);
    }

    return SUCCESS;
}

/* See dialogue.h */
int node_action_init(node_action_t *n_a, node_action_type action,
                     char *action_id)
{
    assert(n_a != NULL);

    n_a->action = action;

    if (action_id != NULL) {
        if ((n_a->action_id = strdup(action_id)) == NULL) return FAILURE;
    }
    else n_a->action_id = NULL;

    return SUCCESS;
}

/* See dialogue.h */
node_action_t *node_action_new(node_action_type action, char *action_id)
{
    node_action_t *n_a;
    if ((n_a = malloc(sizeof(node_action_t))) == NULL) return NULL;

    if (node_action_init(n_a, action, action_id) != SUCCESS) {
        free_node_actions(n_a);
        return NULL;
    }

    return n_a;
}

/* See dialogue.h */
int free_node_actions(node_action_t *actions_lst)
{
    node_action_t *elt, *tmp;

    DL_FOREACH_SAFE(actions_lst, elt, tmp) {
        DL_DELETE(actions_lst, elt);
        free(elt->action_id);
        free(elt);
    }

    return SUCCESS;
}
