/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/utlist.h"
#include "../../../include/npc/dialogue.h"*/
#include "npc/dialogue.h"

// BASIC PRINTING FUNCTIONS ---------------------------------------------------
/* See dialogue.h */
void print_gold(char *str)
{
    printf("\033[0;33m");
    printf("%s", str);
    printf("\033[0m");
    return;
}

void print_yellow(char *str)
{
    printf("\033[1;33m");
    printf("%s", str);
    printf("\033[0m");
    return;
}

void print_red(char *str)
{
    printf("\033[0;31m");
    printf("%s", str);
    printf("\033[0m");
    return;
}

/* See dialogue.h */
void npc_print(char *dialogue)
{
    char *divider = "#";
    char *to_print;
    char *remaining = strdup(dialogue);
    int color = 1; /* Increments with each print; odd = gold, even = yel */
    while ((to_print = strtok_r(remaining, divider, &remaining)) != NULL) {
        if (color % 2 == 1)
            print_gold(to_print);
        else
            print_yellow(to_print);
        color++;
    }
}

// STRUCT FUNCTIONS -----------------------------------------------------------
/* See dialogue.h */
convo_t *convo_new()
{
    convo_t *c = (convo_t*)malloc(sizeof(convo_t));
    c->node_count = 0;
    c->nodes = NULL;
    return c;
}

/* See dialogue.h */
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
    node_t *n = (node_t*)malloc(sizeof(node_t));
    memset(n, 0, sizeof(node_t));
    n->node_id = (char*)malloc(MAX_ID_LEN);
    n->dialogue = (char*)malloc(MAX_DIA_LEN);

    int check = node_init(n, node_id, dialogue);
    
    if (n == NULL || n->node_id == NULL || 
        n->dialogue == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return n;
}

/* See dialogue.h */
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
    edge_t *e = (edge_t*)malloc(sizeof(edge_t));
    memset(e, 0, sizeof(edge_t));
    e->keyword = (char*)malloc(MAX_KEY_LEN);
    e->quip = (char*)malloc(MAX_QUIP_LEN);

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

/* See dialogue.h */
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

/* See dialogue.h */
edge_t *read_input(node_t *n, char *input)
{
    char *adj_input = strtok(input, "\n");
    edge_t *res;

    HASH_FIND(hh, n->edges, adj_input, strlen(adj_input), res);

    return res;
}

/* See dialogue.h */
node_t *traverse_edge(node_t *n)
{
    char *input = malloc(MAX_KEY_LEN);
    fgets(input, MAX_KEY_LEN, stdin);

    edge_t *e;
    e = read_input(n, input);

    if (e != NULL) {
        printf("\n%s\n\n", e->quip);
        n = e->toward;
        npc_print(n->dialogue);
        return n;
    } else {
        print_gold("What?\n");
        return NULL;
    }
}

/* See dialogue.h */
void end_convo()
{
    print_red("\n\nCongrats on finishing the chiventure dialogue showcase!\n");
    print_gold("Press ENTER to exit");
    getchar();
    exit(0);
}

/* See dialogue.h */
void run_convo(convo_t *c)
{
    npc_print(c->nodes->cur_node->dialogue);
    node_t *cur;
    while (c->nodes->cur_node->connection_count != 0) {
        printf("\n\n> Talk about: ");
        cur = traverse_edge(c->nodes->cur_node);
        if (cur != NULL) {
            c->nodes->cur_node =
                c->nodes->cur_node->edges->toward;
        }
    }
    end_convo();
}

/* Pre-DL-lists artifact code
//See dialogue.h
void add_node(convo_t *c, node_t *n)
{
    DL_APPEND(c->nodes, n);
    c->node_count++;
}

//See dialogue.h
void add_edge(node_t *n, edge_t *edge)
{
    DL_APPEND(n->edges, edge);
    n->connection_count++;
}

//See dialogue.h
int read_input(node_t *n, char *input)
{
    char *adj_input = strtok(input, "\n");
    if (adj_input == NULL) {
        return -1;
    }
    for (int i = 0; i < n->connection_count; i++) {
        if (!strcmp(adj_input, n->connections[i]->keyword)) {
            return i;
        }
    }
    return -1;
}

//See dialogue.h
int traverse_edge(node_t *n)
{
    int buffer_size = 30;
    char *input = malloc(buffer_size * sizeof(char));
    fgets(input, buffer_size, stdin);
    int index;
    index = read_input(n, input);
    if (index >= 0) {
        printf("\n%s\n\n", n->connections[index]->quip);
        n = n->connections[index]->toward;
        npc_print(n->dialogue);
        return index;
    } else {
        print_gold("What?\n");
        return -1;
    }
}

//See dialogue.h
void end_convo()
{
    print_red("\n\nCongrats on finishing the chiventure dialogue showcase!\n");
    print_gold("Press ENTER to exit");
    getchar();
    exit(0);
}

//See dialogue.h
void run_convo(convo_t *c)
{
    int start_node = 1;
    npc_print(c->head[start_node]->dialogue);
    int index;
    while (c->head[start_node]->connection_count != 0) {
        printf("\n\n> Talk about: ");
        index = traverse_edge(c->head[start_node]);
        if (index != -1) {
            c->head[start_node] =
                c->head[start_node]->connections[index]->toward;
        }
    }
    end_convo();
}
*/