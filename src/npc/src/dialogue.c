#include "npc/dialogue.h"

// STRUCT FUNCTIONS -----------------------------------------------------------
/* See dialogue.h */
int convo_init(convo_t *c, char *farewell)
{
    assert(c != NULL);
    strncpy(c->farewell, farewell, strlen(farewell));
    c->node_count = 0;
    c->nodes = NULL;

    return SUCCESS;
}

/* See dialogue.h */
convo_t *convo_new(char *farewell)
{
    convo_t *c;
    c = calloc(1, sizeof(convo_t));
    c->farewell = (char*)malloc(MAX_FW_LEN);

    int check = convo_init(c, farewell);

    if (c == NULL || c->farewell == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return c;
}

/* See LINKED LIST FUNCTIONS section of dialogue.h */
int delete_all_nodes(node_list_t *nodes)
{
    node_list_t *elt, *tmp;
    DL_FOREACH_SAFE(nodes, elt, tmp)
    {
        DL_DELETE(nodes, elt);
        free(elt);
    }
    return SUCCESS;
}

/* See dialogue.h */
int convo_free(convo_t *c)
{
    free(c->farewell);
    delete_all_nodes(c->nodes);
    free(c);
    return SUCCESS;
}

/* See dialogue.h */
int node_init(node_t *n, char *node_id, char *dialogue)
{
    assert(n != NULL);
    strncpy(n->node_id, node_id, strlen(node_id));
    strncpy(n->dialogue, dialogue, strlen(dialogue));
    n->connection_count = 0;
    n->edges = NULL;

    return SUCCESS;
}

/* See dialogue.h */
node_t *node_new(char *node_id, char *dialogue)
{
    node_t *n;
    n = calloc(1, sizeof(node_t));
    n->node_id = calloc(1, MAX_ID_LEN);
    n->dialogue = calloc(1, MAX_DIA_LEN);

    int check = node_init(n, node_id, dialogue);
    
    if (n == NULL || n->node_id == NULL || 
        n->dialogue == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return n;
}

/* See LINKED LIST FUNCTIONS section of dialogue.h */
int delete_all_edges(edge_hash_t *edges)
{
    edge_t *cur_edge, *tmp;
    HASH_ITER(hh, edges, cur_edge, tmp)
    {
        HASH_DEL(edges, cur_edge);
        edge_free(cur_edge);
    }
    return SUCCESS;
}

/* See dialogue.h */
int node_free(node_t *n)
{
    assert(n != NULL);

    free(n->node_id);
    free(n->dialogue);
    delete_all_edges(n->edges);
    free(n);

    return SUCCESS;
}

/* See dialogue.h */
int edge_init(edge_t *e, node_t *toward, char *keyword, char *quip)
{
    assert(e != NULL);
    strncpy(e->keyword, keyword, strlen(keyword));
    strncpy(e->quip, quip, strlen(quip));
    e->toward = toward;

    return SUCCESS;
}

/* See dialogue.h */
edge_t *edge_new(node_t *toward, char *keyword, char *quip)
{
    edge_t *e;
    e = calloc(1, sizeof(edge_t));
    e->keyword = calloc(1, MAX_KEY_LEN);
    e->quip = calloc(1, MAX_QUIP_LEN);

    int check = edge_init(e, toward, keyword, quip);
    
    if (e == NULL || e->keyword == NULL || 
        e->quip == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return e;
}

/* See dialogue.h */
int edge_free(edge_t *e)
{
    assert(e != NULL);

    free(e->keyword);
    free(e->quip);
    node_free(e->toward);

    return SUCCESS;
}

// DIALOGUE BUILDING FUNCTIONS ------------------------------------------------
/* See LINKED LIST FUNCTIONS section of dialogue.h */
int node_cmp(node_list_t *n1, node_list_t *n2)
{
    return (strcmp(n1->cur_node->node_id, n2->cur_node->node_id));
}

/* See dialogue.h */
int prepend_node(convo_t *c, node_t *n)
{
    node_list_t *check, *list;

    check = malloc(sizeof(node_list_t));
    list = malloc(sizeof(node_list_t));

    list->cur_node = n;
    list->next = NULL;
    list->prev = NULL;

    DL_SEARCH(c->nodes, check, list, node_cmp);
    if (check != NULL)
    {
        return FAILURE; //this node id is already in use
    }

    DL_PREPEND(c->nodes, list);
    c->node_count++;

    return SUCCESS;
}

/* See dialogue.h */
int append_node(convo_t *c, node_t *n)
{
    node_list_t *check, *list;

    check = malloc(sizeof(node_list_t));
    list = malloc(sizeof(node_list_t));

    list->cur_node = n;
    list->next = NULL;
    list->prev = NULL;

    DL_SEARCH(c->nodes, check, list, node_cmp);
    if (check != NULL)
    {
        return FAILURE; //this node id is already in use
    }

    DL_APPEND(c->nodes, list);
    c->node_count++;

    return SUCCESS;
}

/* See dialogue.h */
int add_edge(node_t *n, edge_t *e)
{
    edge_t *check;
    HASH_FIND(hh, n->edges, e->keyword, strlen(e->keyword), check);
    
    if (check != NULL)
    {
        return FAILURE; //this keyword is already in use
    }
    HASH_ADD_KEYPTR(hh, n->edges, e->keyword, strlen(e->keyword), e);
    n->connection_count++;

    return SUCCESS;
}
