#ifndef _DIALOGUE_H
#define _DIALOGUE_H

#include "game-state/condition.h"
#include "cli/util.h"

#define MAX_DIA_LEN 500
#define MAX_QUIP_LEN 250
#define MAX_NODE_ID_LEN 50


/**********************************************
 *       DIALOGUE STRUCTURE DEFINITIONS       *
 **********************************************/

/* Actions */
typedef enum {
    GIVE_ITEM,
    TAKE_ITEM,
    START_QUEST,
    START_BATTLE
} node_action_type;

/* An action flag. This allows designers to integrate actions into their
 * dialogue. NOTE: This is a linked list, allowing for multiple actions.
 * 
 * Includes:
 *  - action: the type of action (see above)
 *  - action_id: ID associated with the action (e.g. quest ID)
 *  - next, prev: next and previous list elements
 */
typedef struct node_action {
    node_action_type action;
    char *action_id;
    struct node_action *next, *prev;
} node_action_t;

/* Edge availability status: for conditional dialogue options */
typedef enum {
    EDGE_DISABLED = -1,
    EDGE_UNAVAILABLE,
    EDGE_AVAILABLE
} edge_avail_status;

/* Forward Declaration */
typedef struct node node_t;

/* An edge between two nodes. Each edge represents a dialogue option available
 * to the player at that node.
 * 
 * Includes:
 *  - quip: dialogue option text
 *  - from: source node
 *  - to: destination node
 *  - conditions: conditions determining an edge's availability, NULL if none
 *    Note: conditions come from game-state/condition.h
 */
typedef struct edge {
    char *quip;
    node_t *from, *to;
    condition_t *conditions;
} edge_t;

/* A doubly-linked list containing edges and their "availabilities."
 *
 * Includes:
 *  - availablility: -1 = DISABLED, 0 = UNAVAILABLE, 1 = AVAILABLE (see above)
 *  - edge: the edge
 *  - next, prev: next and previous list elements
 */
typedef struct edge_list {
    edge_avail_status availability;
    edge_t *edge;
    struct edge_list *next, *prev;
} edge_list_t;

/* A stage in a conversation.
 *
 * Includes:
 *  - node_id: the node's "name"
 *  - npc_dialogue: what the NPC says on arriving at the node
 *  - num_edges: total number of edges
 *  - num_available_edges: number of accessible edges
 *  - edges: possible responses
 *  - actions: actions associated with the node (item, quest, battle, etc.)
 */
typedef struct node {
    char *node_id;
    char *npc_dialogue;
    int num_edges;
    int num_available_edges;
    edge_list_t *edges;
    node_action_t *actions;
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

/* A struct representing a conversation.
 *
 * Includes:
 *  - num_nodes: the total number of nodes
 *  - all_nodes: list of all nodes
 *  - all_edges: list of all edges
 *  - cur_node: current node (to run the conversation)
 */
typedef struct convo {
    int num_nodes;
    node_list_t *all_nodes;
    edge_list_t *all_edges;
    node_t *cur_node;
} convo_t;


/**********************************************
 *        DIALOGUE BUILDING FUNCTIONS         *
 **********************************************/

/* To create a new convo, use: convo_new()
 */

/* Adds a new node to a conversation.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - node_id: a string (max. 50 chars) representing the node's "name"
 *  - dialogue: a string (max. 500 chars) representing the NPC's speech at the
 *    node
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) input strings are too long (assertion error);
 *    (2) a node with the same ID already exists; (3) memory allocation errors;
 */
int add_node(convo_t *c, char *node_id, char *npc_dialogue);

/* Adds a new edge to a conversation.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - quip: a string (max. 250 chars) representing the dialogue option text
 *  - from_id: source node's ID
 *  - to_id: destination node's ID
 *  - conditions: conditions determining the edge's availability, NULL if none
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) quip is too long; (2) nodes matching from_id and
 *    to_id could not be found; (3) memory allocation errors;
 */
int add_edge(convo_t *c, char *quip, char *from_id, char *to_id,
             condition_t *conditions);


/**********************************************
 *             ACTION FUNCTIONS               *
 **********************************************/

/* Adds a give item flag to a node.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - node_id: ID of the target node
 *  - item_id: ID of the item
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) node matching node_id could not be found;
 */
int add_give_item(convo_t *c, char *node_id, char *item_id);

/* Adds a take item flag to a node.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - node_id: ID of the target node
 *  - item_id: ID of the item
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) node matching node_id could not be found;
 */
int add_take_item(convo_t *c, char *node_id, char *item_id);

/* Adds a start quest flag to a node.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - node_id: ID of the target node
 *  - quest_id: ID of the quest
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) node matching node_id could not be found;
 */
int add_start_quest(convo_t *c, char *node_id, long quest_id);

/* Adds a start battle flag to a node.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - node_id: ID of the target node
 *  - battle_id: ID of the battle
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 *  - Possible errors: (1) node matching node_id could not be found;
 */
int add_start_battle(convo_t *c, char *node_id, char *battle_id);


/**********************************************
 *    STRUCT (INIT, NEW, FREE) FUNCTIONS      *
 **********************************************/

/* Initializes an edge.
 *
 * Parameters:
 *  - e: an edge; must point to already allocated memory
 *  - quip: the dialogue option associated with the edge
 *  - from: source node
 *  - to: destination node
 *  - conditions: conditions determining the edge's availability, NULL if none
 *    Note: There can be multiple conditions (see condition.h)
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int edge_init(edge_t *e, char *quip, node_t *from, node_t *to,
              condition_t *conditions);

/* Allocates a new edge on the heap.
 * 
 * Parameters:
 *  - quip: the dialogue option associated with the edge
 *  - from: source node
 *  - to: destination node
 *  - conditions: conditions determining the edge's availability, NULL if none
 *    Note: There can be multiple conditions (see condition.h)
 *
 * Returns:
 *  - pointer to the new edge
 */
edge_t *edge_new(char *quip, node_t *from, node_t *to, condition_t *conditions);

/* Frees resources associated with an edge.
 *
 * Parameters:
 *  - e: the edge to be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int edge_free(edge_t *e);

/* Initializes a node.
 *
 * Parameters:
 *  - n: a node; must point to already allocated memory
 *  - node_id: the node's "name"
 *  - npc_dialogue: a string representing the NPC's speech at the node
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int node_init(node_t *n, char *node_id, char *npc_dialogue);

/* Allocates a new node on the heap.
 * 
 * Parameters:
 *  - node_id: the node's "name"
 *  - npc_dialogue: a string representing the NPC's speech at the node
 * 
 * Returns:
 *  - pointer to the new node
 */
node_t *node_new(char *node_id, char *npc_dialogue);

/* Frees resources associated with a node.
 *
 * Parameters:
 *  - n: the node to be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int node_free(node_t *n);

/* Initializes a convo.
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
 *  - pointer to the new convo
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

/* Frees an edge list (using macros from common/utlist.h). 
 *
 * Note: free_edges allows you to specify if you want to free the edges along
 *       with each edge list element. This prevents double freeing in certain
 *       cases.
 *
 * Parameters:
 *  - e_lst: the edge list to be freed
 *  - free_edge: true if edges should also be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int free_edge_list(edge_list_t *e_lst, bool free_edges);

/* Frees an node list (using macros from common/utlist.h).
 *
 * Note: free_nodes allows you to specify if you want to free the nodes along
 *       with each node list element. This prevents double freeing in certain
 *       cases.
 *
 * Parameters:
 *  - n_lst: the node list to be freed
 *  - free_nodes: true if nodes should also be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int free_node_list(node_list_t *n_lst, bool free_nodes);

/* Initializes a node action.
 *
 * Parameters:
 *  - n_a: a node action; must point to already allocated memory
 *  - action: type of action
 *  - action_id: ID associated with that action, if any
 *
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int node_action_init(node_action_t *n_a, node_action_type action,
                     char *action_id);

/* Allocates a new node action on the heap.
 *
 * Parameters:
 *  - action: type of action
 *  - action_id: ID associated with that action, if any
 *
 * Returns:
 *  - pointer to the new node action
 */
node_action_t *node_action_new(node_action_type action, char *action_id);

/* Frees an action list (using macros from common/utlist.h).
 *
 * Parameters:
 *  - action_lst: the action list to be freed
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE if an error occurs
 */
int free_node_actions(node_action_t *action_lst);



#endif /* DIALOGUE_H */
