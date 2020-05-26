#ifndef _DIALOGUE_H
#define _DIALOGUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/utlist.h"


// BASIC PRINTING FUNCTIONS ---------------------------------------------------

/*
 * Three functions to print given string in gold, yellow, or red respectively
 */
void print_gold(char *str);

void print_yellow(char *str);

void print_red(char *str);

/*
 * Prints a string in NPC dialog format: gold by default and yellow for
 * text surrounded by #hashes# to denote dialog choices.
 * Parameters:
 *  - dialogue: the string to be printed in NPC format
 * Returns: nothing
 */
void npc_print(char *dialogue);


// DIALOGUE STRUCTURE DEFINITION ----------------------------------------------

/*
 * A struct to represent a conversation.
 * Includes:
 *  - node_count: the number of nodes the convo currently has
 *  - nodes: a linked list of node pointers (list of included nodes)
 *
 */
typedef struct convo {
    int node_count;
    node_list_t *nodes;
} convo_t;

/*
 * A struct to represent one scene in a conversation.
 * Includes:
 *  - node_id: a marker of which node this is
 *  - dialogue: a string of what the NPC says on arriving at the node
 *  - connection_count: the number of connections the node currently has
 *  - edges: a linked list of edge pointers (list of attached edges)
 *
 */
typedef struct node {
    int node_id;
    char *dialogue;
    int connection_count;
    edge_list_t *edges;
} node_t;

/*
 * A struct to represent an edge to a node (Note: does not include source node)
 * Includes:
 *  - toward: points toward which node traversing this edge leads to
 *  - keyword: a string that the user's input must match to enter the edge
 *  - quip: a string of what the player's character says if they enter the edge
 *
 */
typedef struct edge {
    node_t *toward;
    char *keyword;
    char *quip;
} edge_t;

/*
 * A doubly-linked list of nodes for containing all involved nodes in a convo
 * Includes:
 *  - cur_node: Points to the location of the node currently focused on
 *  - prev: A pointer to the previous entry in the list, NULL if none left
 *  - next: A pointer to the next entry in the list, NULL if none left
 */
typedef struct node_list {
    node_t *cur_node;
    struct node_list *prev;
    struct node_list *next;
} node_list_t;

/*
 * A doubly-linked list of edges for containing all potential paths for a node
 * Includes:
 *  - cur_edge: Points to the location of the edge currently focused on
 *  - prev: A pointer to the previous entry in the list, NULL if none left
 *  - next: A pointer to the next entry in the list, NULL if none left
 */
typedef struct edge_list {
    edge_t *cur_edge;
    struct edge_list *prev;
    struct edge_list *next;
} edge_list_t;


// DIALOGUE BASIC FUNCTIONS ---------------------------------------------------

/*
 * A function to allocate a new convo struct
 * Returns:
 *  - A pointer to the new convo
 *
 */
convo_t *new_convo();

/*
 * A function to allocate and initialize a new node struct
 * Parameters:
 *  - tag: a marker for the node's identity
 *  - dialog: a string of what the NPC says when the player reaches this node
 *  - max_edges: the maximum number of edges that can be added
 * Returns:
 *  - A pointer to the new node
 *
 */
node_t *make_node(int node_id, char *dialog, int max_edges);

/*
 * Attaches a given node to the head list of a given convo.
 * Parameters:
 *  - c: the convo that the node is to be attached to
 *  - n: the node to be attached
 * Returns: Nothing
 */
void add_node(convo_t *c, node_t *n);

/*
 * Allocates and initializes an edge struct
 * Parameters:
 *  - toward: the node that traversing this edge will bring you to
 *  - keyword: a string that the user's input must match to enter the edge
 *  - quip: a string of what the player character should say
 *    when this edge is traversed
 * Returns:
 *  - A pointer to the new edge struct
 *
 */
edge_t *make_edge(node_t *toward, char *keyword, char *quip);

/*
 * Attaches a given edge to the connections list of a given node.
 * Parameters:
 *  - n: the node that the edge is to be attached to
 *  - edge: the (previously-made) edge to be attached
 * Returns: Nothing
 *
 */
void add_edge(node_t *n, edge_t *edge);

/*
 * Compares the input to the keyword and returns index of matching edge
 * Parameters:
 *  - n: the node that player is currently on
 *  - input: the player-inputted command
 * Returns:
 *  - Index of the matching edge, -1 if it doesn't match any of the keywords
 *
 */
int read_input(node_t *n, char *input);

/*
 * Asks for input and traverses to the edge specified by the input's index
 * Prints player quip, moves to new node, and prints npc's dialog at that node
 * Parameters:
 *  - n: the node that the player is currently on
 * Returns:
 *  - index of new current node on success, -1 otherwise
 *
 */
int traverse_edge(node_t *n);

/*
 * Ends the conversation
 * Parameters:
 *  - None
 * Returns:
 *  - Nothing
 *
 */
void end_convo();

/*
 * Runs the entire conversation until it reaches an end
 * Parameters:
 *  - c: A conversation
 * Returns:
 *  - Nothing, just runs through each node and asks for input
 *
 */
void run_convo(convo_t *c);

#endif