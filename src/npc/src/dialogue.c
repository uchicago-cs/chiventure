#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/utlist.h"
#include "../../../include/npc/dialogue.h"

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
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

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
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

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
convo_t *new_convo()
{
    convo_t *c = (convo_t*)malloc(sizeof(convo_t));
    c->node_count = 0;
    c->nodes = NULL;
    return c;
}

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
node_t *make_node(int node_id, char *dialogue, int max_edges)
{
    node_t *newnode = (node_t*)malloc(sizeof(node_t));
    newnode->node_id = node_id;
    newnode->dialogue = dialogue;
    newnode->connection_count = 0;
    newnode->edges = NULL;
    return newnode;
}

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
void add_node(convo_t *c, node_t *n)
{
    DL_APPEND(c->nodes, n);
    c->node_count++;
}

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
edge_t *make_edge(node_t *toward, char *keyword, char *quip)
{
    edge_t *new_edge = (edge_t*)malloc(sizeof(edge_t));
    new_edge->toward = toward;
    new_edge->keyword = keyword;
    new_edge->quip = quip;
    return new_edge;
}

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
void add_edge(node_t *n, edge_t *edge)
{
    DL_APPEND(n->edges, edge);
    n->connection_count++;
}

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
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

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
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

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
void end_convo()
{
    print_red("\n\nCongrats on finishing the chiventure dialogue showcase!\n");
    print_gold("Press ENTER to exit");
    getchar();
    exit(0);
}

/*
 * See chiventure/include/npc/dialogue.h for full function explanations
 */
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
