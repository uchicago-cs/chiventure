/*
 * Skill tree implementation for chiventure
 */

#ifndef INCLUDE_SKILLTREE_H_
#define INCLUDE_SKILLTREE_H_

#include "skilltrees/stdst.h"
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"

/*
 * Allocates a new skill node in the heap.
 *
 * Parameters:
 *  - skill: The skill represented by the skill node
 *  - nprepreqs: The number of prerequisite skills to acquire the skill
 *  - size: The size of the skill node, for the graphics team
 *
 * Returns:
 *  - A pointer to the skill node, or NULL if a skill node cannot be
 *    allocated
 */
 skill_node_t* skill_node_new(skill_t* skill, unsigned int nprereqs,
                              unsigned int size);

/*
 * Frees the resources associated with a skill node.
 *
 * Parameters:
 *  - node: A skill node. Must point to node allocated with skill_node_new
 *
 * Returns:
 *  - Always returns 0
 */
int skill_node_free(skill_node_t* node);

/*
 * Adds a prerequisite to a skill node.
 *
 * Parameters:
 *  - node: A skill node
 *  - prereq: A prerequisite skill node
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int node_prereq_add(skill_node_t* node, skill_node_t* prereq);

/*
 * Removes a prerequisite from a skill node.
 *
 * Parameters:
 *  - node: A skill node
 *  - prereq: A prerequisite skill node
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int node_prereq_remove(skill_node_t* node, skill_node_t* prereq);

/*
 * Allocates a new (empty) skill tree in the heap.
 *
 * Parameters:
 *  - tid: The tree ID that uniquely identifies the skill tree
 *  - name: The name of the skill tree
 *  - nnodes: The number of tree nodes in the skill tree
 *
 * Returns:
 *  - A pointer to the skill tree, or NULL if the skill tree cannot be allocated
 */
skill_tree_t* skill_tree_new(tid_t tid, char* name, unsigned int nnodes);

/*
 * Frees the resources associated with a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree. Must point to skill tree allocated with skill_tree_new
 *
 * Returns:
 *  - Always returns 0
 */
int skill_tree_free(skill_tree_t* tree);

/*
 * Adds a skill node to a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - node: A skill node
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_tree_node_add(skill_tree_t* tree, skill_node_t* node);

/*
 * Searches for a skill node in a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - sid: A skill ID that uniquely identifies the skill (node)
 *
 * Returns:
 *  - The position of the node in the skill tree, -1 if the tree does not have
 *    a node that corresponds to skill ID `sid`
 */
int skill_tree_has_node(skill_tree_t* tree, sid_t sid);

/*
 * Removes a skill node from a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - node: A skill node
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_tree_node_remove(skill_tree_t* tree, skill_node_t* node);

/*
 * Returns all prerequisite skills for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - sid: A skill ID
 *  - nprereqs: An out-parameter. The number of prerequisite skills in the list
 *
 * Returns:
 *  - A pointer to the list of all prerequisite skills, NULL if there are none
 *    or an error occurs.
 *  - To distinguish between no prerequisites and errors, the out-parameter
 *    `nprereqs` is updated to 0 when there are no prerequisites, and is
 *    updated to -1 if an error has occurred
 */
skill_t** skill_prereqs_all(skill_tree_t* tree, sid_t sid, int* nprereqs);

/*
 * Returns prerequisite skills already acquired by a player for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: A skill ID
 *  - nacquired: An out-parameter. The number of acquired prerequisite skills in
 *              the list
 *
 * Returns:
 *  - A pointer to the list of missing prerequisite skills, NULL if there are
 *    none or an error occurs.
 *  - To distinguish between no missing prerequisites and errors, the out-
 *    parameter `nmissing` is updated to 0 when there are no missing
 *    prerequisites, is updated to -1 if the node is not in the tree,
 *    -2 if a malloc error occured, and -3 if a skill is found to be something
 *    other than a passive or active skill.
 */
skill_t** skill_prereqs_acquired(skill_tree_t* tree,
                                 skill_inventory_t* inventory, sid_t sid,
                                 int* nacquired);

/*
 * Returns prerequisite skills missing by a player for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: A skill ID
 *  - nacquired: An out-parameter. The number of missing prerequisite skills in
 *              the list
 *
 * Returns:
 *  - A pointer to the list of missing prerequisite skills, NULL if there are
 *    none or an error occurs.
 *  - To distinguish between no missing prerequisites and errors, the out-
 *    parameter `nmissing` is updated to 0 when there are no missing
 *    prerequisites, is updated to -1 if the node is not in the tree, and
 *    -2 if a malloc error occured.
 */
skill_t** skill_prereqs_missing(skill_tree_t* tree,
                                skill_inventory_t* inventory, sid_t sid,
                                int* nmissing);

/*
 * Adds a skill to an inventory, if the inventory contains all its prerequisite
 * skills
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: The skill ID of the desired skill
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int inventory_skill_acquire(skill_tree_t* tree, skill_inventory_t* inventory,
                            skill_t* skill);

#endif /* INCLUDE_SKILLTREE_H_ */
