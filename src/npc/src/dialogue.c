#include "npc/dialogue.h"


/**********************************************
 *        DIALOGUE BUILDING FUNCTIONS         *
 **********************************************/

/* See dialogue.h */
convo_t *create_new_convo()
{
    convo_t *c = convo_new();

    assert(c != NULL);

    return c;
}

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

/* Returns an edge list element containing an appropriate option number.
 *
 * Parameters:
 *  - e_lst: edge list
 *  - e: edge
 *
 * Returns:
 *  - a pointer to the new edge list element
 *  - NULL if memory allocation failed
 */
edge_list_t *create_edge_list_element(edge_list_t *e_lst, edge_t *e)
{
    edge_list_t *elt;

    if ((elt = (edge_list_t *) malloc(sizeof(edge_list_t))) == NULL) return
        NULL;

    elt->edge = e;
    if (e_lst == NULL) {
        elt->option_number = 1;
    } else {
        elt->option_number = e_lst->prev->option_number + 1;
    }

    return elt;
}

/* See dialogue.h */
int add_edge(convo_t *c, char *quip, char *from_id, char *to_id)
{
    assert(c->num_nodes >= 2);

    // Get source and destination nodes
    node_t *from_node, *to_node;
    if ((from_node = get_node(c->all_nodes, from_id)) == NULL) return FAILURE;
    if ((to_node = get_node(c->all_nodes, to_id)) == NULL) return FAILURE;

    // Create edge
    edge_t *e;
    if ((e = edge_new(quip, from_node, to_node)) == NULL) return FAILURE;

    // Create edge list elements (for convo and the source node)
    edge_list_t *c_elt, *n_elt;

    if ((c_elt = create_edge_list_element(c->all_edges, e)) == NULL) {
        edge_free(e);
        return FAILURE;
    }

    if ((n_elt = create_edge_list_element(from_node->edges, e)) == NULL) {
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

/* Given an edge list, print out the available options to the terminal.
 *
 * Parameters:
 *  - e_lst: edge list
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int print_options(edge_list_t *e_lst)
{
    while (e_lst != NULL) {
        printf("%d. %s\n", e_lst->option_number, e_lst->edge->quip);
        e_lst = e_lst->next;
    }

    return SUCCESS;
}

/* See dialogue.h */
int run_conversation(convo_t *c)
{
    node_t *cur_node = c->all_nodes->node;
    edge_list_t *chosen_option;
    int player_response;
    int i;

    while (cur_node->num_edges > 0) {

        // Print NPC dialogue
        printf("\n%s\n\n", cur_node->npc_dialogue);

        // Print available options
        print_options(cur_node->edges);

        // User input
        printf("Enter your choice: ");
        scanf("%d", &player_response);
        assert(player_response > 0 && player_response <= cur_node->num_edges);

        // Find edge corresponding to chosen option
        chosen_option = cur_node->edges;
        for (i = 1; i < player_response; i++) {
            chosen_option = chosen_option->next;
        }

        // Traverse to next node
        cur_node = chosen_option->edge->to;
    }

    // NPC closing statement
    printf("\n%s\n\n", cur_node->npc_dialogue);

    return SUCCESS;
}

/* FOR FUTURE USE */
int cat_options(char *buf, edge_list_t *e_lst, int *i)
{
    return SUCCESS;

    /*
    int j;
    char option_str[255];

    while (e_lst != NULL) {
        sprintf(option_str, "%d. %s\n", e_lst->option_number,
            e_lst->edge->quip);

        if (((*i) + strlen(option_str)) > 2499) return FAILURE;

        j = 0;
        while (option_str[j] != '\0') {
            buf[(*i)++] = c->cur_node->npc_dialogue[j++];
        }

        e_lst = e_lst->next;
    }

    return SUCCESS; */
}

/* FOR FUTURE USE -- Note: Assumes c contains a "node_t *cur_node" member */
int run_conversation_step(convo_t *c, int input, char *outstring)
{
    return 0;

    /*
    assert(input > 0 && input <= c->cur_node->num_edges);

    edge_list_t *chosen_option, *cur_edge;
    int i, j;
    char *buf = (char *) malloc(sizeof(char) * 2500);

    chosen_option = c->cur_node->edges;
    for (i = 1; i < player_response; i++) {
        chosen_option = chosen_option->next;
    }

    c->cur_node = cur_edge->edge->to;

    i = 0;
    j = 0;

    while (c->cur_node->npc_dialogue[j] != '\0') {
        buf[i++] = c->cur_node->npc_dialogue[j++];
    }
    buf[i++] = '\n';
    buf[i++] = '\n';

    if (c->cur_node->num_edges == 0) {
        buf[i] = '\0';
        outstring = buf;
        return 1;
    }

    if (cat_options(buf, c->cur_node->edges, &i) != SUCCESS) {
        free(buf);
        return -1;
    }

    buf[i] = '\0';
    outstring = buf;
    return 0;*/
}


/**********************************************
 *    STRUCT (INIT, NEW, FREE) FUNCTIONS      *
 **********************************************/

/* See dialogue.h */
int edge_init(edge_t *e, char *quip, node_t *from, node_t *to)
{
    assert(e != NULL);
    assert(strlen(quip) < MAX_QUIP_LEN);
    assert(from != NULL && to !=NULL);

    if (e->quip != NULL) free(e->quip);
    if ((e->quip = (char *) malloc(sizeof(char) * (strlen(quip) + 1))) == NULL)
        return FAILURE;
    strcpy(e->quip, quip);

    e->from = from;
    e->to = to;

    return SUCCESS;
}

/* See dialogue.h */
edge_t *edge_new(char *quip, node_t *from, node_t *to)
{
    assert(strlen(quip) < MAX_QUIP_LEN);
    assert(from != NULL && to !=NULL);

    edge_t *e;
    if ((e = (edge_t *) malloc(sizeof(edge_t))) == NULL) return NULL;

    e->quip = NULL;

    if (edge_init(e, quip, from, to) != SUCCESS) {
        edge_free(e);
        return NULL;
    }

    return e;
}

/* See dialogue.h */
int edge_free(edge_t *e)
{
    if (e != NULL) free(e);

    return SUCCESS;
}

/* See dialogue.h */
int node_init(node_t *n, char *node_id, char *npc_dialogue)
{
    assert(n != NULL);
    assert(strlen(node_id) < MAX_NODE_ID_LEN);
    assert(strlen(npc_dialogue) < MAX_DIA_LEN);

    // Node ID
    if (n->node_id != NULL) free(n->node_id);
    if ((n->node_id = (char *) malloc(sizeof(char) *
        (strlen(node_id) + 1))) == NULL) return FAILURE;
    strcpy(n->node_id, node_id);

    // NPC dialogue
    if (n->npc_dialogue != NULL) free(n->npc_dialogue);
    if ((n->npc_dialogue = (char *)malloc(sizeof(char) *
        (strlen(npc_dialogue)+ 1))) == NULL) return FAILURE;
    strcpy(n->npc_dialogue, npc_dialogue);

    n->num_edges = 0;
    n->edges = NULL;

    return SUCCESS;
}

/* See dialogue.h */
node_t *node_new(char *node_id, char *npc_dialogue)
{
    assert(strlen(node_id) < MAX_NODE_ID_LEN);
    assert(strlen(npc_dialogue) < MAX_DIA_LEN);

    node_t *n;
    if ((n = (node_t *) malloc(sizeof(node_t))) == NULL) return NULL;

    n->node_id = NULL;
    n->npc_dialogue = NULL;

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
