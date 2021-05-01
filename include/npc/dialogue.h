#ifndef _DIALOGUE_H
#define _DIALOGUE_H

#include "game-state/game_state_common.h"

#define MAX_DIA_LEN 500
#define MAX_QUIP_LEN 250
#define MAX_NODE_ID_LEN 50


/**********************************************
 *       DIALOGUE STRUCTURE DEFINITIONS       *
 **********************************************/

/* Forward Declaration */
typedef struct node node_t;

/* A directional edge between two nodes. An edge represents an "option" that
 * the player can choose to advance the conversation from their current node.
 * 
 * Includes:
 *  - quip: player's text
 *  - from: source node
 *  - to: destination node
 */
typedef struct edge {
    char quip[MAX_QUIP_LEN];
    node_t *from, *to;
} edge_t;

/* A doubly-linked list containing edges and associated "option numbers." The
 * "option number" (1,2,3,...) is used to label the edges numerically, which
 * is used to print out the conversation options.
 *
 * Includes:
 *  - option_number: an edge's number label
 *  - edge: the edge
 *  - next, prev: next and previous list elements
 */
typedef struct edge_list {
    int option_number;
    edge_t *edge;
    struct edge_list *next, *prev;
} edge_list_t;

/* A scene in a conversation. Contains an NPC's speech, and the player's
 * possible responses to it.
 *
 * Includes:
 *  - node_id: a "name" for the node
 *  - npc_dialogue: what the NPC says on arriving at the node
 *  - num_edges: number of possible responses
 *  - edges: possible responses
 */
typedef struct node {
    char node_id[MAX_NODE_ID_LEN];
    char npc_dialogue[MAX_DIA_LEN];
    int num_edges;
    edge_list_t *edges;
} node_t;

/* A doubly-linked list containing nodes.
 *
 * Includes:
 *  - node: a node
 *  - next, prev: next and previous list elements
 */
typedef struct node_list {
    node_t *node;
    struct node_list *next, *prev;
} node_list_t;

/* A struct to represent a conversation.
 * 
 * Includes:
 *  - num_nodes: the total number of nodes
 *  - all_nodes: list of all nodes
 *  - all_edges: list of all edges
 */
typedef struct convo {
    int num_nodes;
    node_list_t *all_nodes;
    edge_list_t *all_edges;
} convo_t;


/**********************************************
 *        DIALOGUE BUILDING FUNCTIONS         *
 **********************************************/

/* Creates a new, empty conversation.
 *
 * Returns:
 *  - pointer to a convo
 */
convo_t *create_new_convo();

/* Given a node ID and an NPC text, adds a new node to the conversation.
 *
 * Parameters:
 *  - c: pointer to a convo struct
 *  - node_id: a string (max. 50 chars) referencing the node's identity
 *  - dialogue: a string (max. 500 chars) of what the NPC says when the player
 *     reaches this node
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) input strings are too long (assertion error);
 *     (2) a node with the same ID already exists; (3) memory allocation error;
 */
int add_node(convo_t *c, char node_id[], char npc_dialogue[]);

/* Given a player option text (quip), a from node ID and a to node ID, adds
 * a new edge to the conversation.
 *
 * Parameters:
 *  - c: pointer to a convo struct
 *  - quip: a string (max. 250 chars) referencing the text associated with
 *     the edge
 *  - from_id: the source node's ID
 *  - to_id: the destination node's ID
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) quip is too long; (2) nodes matching from_id and
 *     to_id could not be found; (3) memory allocation error;
 */
int add_edge(convo_t *c, char quip[], char from_id[], char to_id[]);


/**********************************************
 *       DIALOGUE EXECUTION FUNCTIONS         *
 **********************************************/

/* Given a convo struct, runs the conversation.
 *
 * Parameters:
 *  - c: pointer to a convo struct
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int run_conversation(convo_t *c);


/**********************************************
 *    STRUCT (INIT, NEW, FREE) FUNCTIONS      *
 **********************************************/

/* Initializes the given edge with given parameters.
 *
 * Parameters:
 *  - e: an edge; must point to already allocated memory
 *  - quip: the player's text associated with the edge
 *  - from: the node this edge originated from
 *  - to: the node this edge will bring you to
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int edge_init(edge_t *e, char quip[], node_t *from, node_t *to);

/* Allocates a new edge struct on the heap.
 * 
 * Parameters:
 *  - quip: the player's text associated with the edge
 *  - from: the node this edge originated from
 *  - to: the node this edge will bring you to
 * 
 * Returns:
 *  - pointer to the new edge struct
 */
edge_t *edge_new(char quip[], node_t *from, node_t *to);

/* Frees resources associated with an edge.
 *
 * Parameters:
 *  - e: the edge to be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int edge_free(edge_t *e);

/* Initializes the given node with given parameters.
 *
 * Parameters:
 *  - n: a node; must point to already allocated memory
 *  - node_id: a string referencing the node's identity
 *  - dialogue: a string of what the NPC says when the player reaches this node
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int node_init(node_t *n, char node_id[], char dialogue[]);

/* Allocates a new node on the heap.
 * 
 * Parameters:
 *  - node_id: a string referencing the node's identity
 *  - dialogue: a string of what the NPC says when the player reaches this node
 * 
 * Returns:
 *  - pointer to the new node
 */
node_t *node_new(char node_id[], char npc_dialogue[]);

/* Frees resources associated with a node.
 *
 * Parameters:
 *  - n: the node to be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int node_free(node_t *n);

/* Initializes the given node with given parameters.
 *
 * Parameters:
 *  - c: a convo; must point to already allocated memory
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int convo_init(convo_t *c);

/* Allocates a new convo in the heap.
 * 
 * Returns:
 *  - pointer to the new, empty convo
 */
convo_t *convo_new();

/* Frees resources associated with a convo.
 *
 * Parameters:
 *  - c: the convo to be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int convo_free(convo_t *c);

/* Frees an edge list (using macros from common/utlist.h). You have the option
 * to specify if you want to free the edges (edges and edge_lists are different
 * things) in that edge list. This prevents double freeing in certain cases.
 *
 * Parameters:
 *  - e_lst: the edge list to be freed
 *  - free_edge: true if you want edges to also be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int free_edge_list(edge_list_t *e_lst, bool free_edges);

/* Frees an node list (using macros from common/utlist.h). You have the option
 * to specify if you want to free the nodes in that node list. This prevents
 * double freeing in certain cases.
 *
 * Parameters:
 *  - n_lst: the node list to be freed
 *  - free_edge: true if you want nodes to also be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int free_node_list(node_list_t *n_lst, bool free_nodes);



#endif /* DIALOGUE_H */
