/*
 * Skill tree implementation for chiventure
 */

#ifndef INCLUDE_SKILLTREE_H_
#define INCLUDE_SKILLTREE_H_

#include "skilltrees/skilltrees_common.h"
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"

/* ================================== */
/* === SKILL TREE DATA STRUCTURES === */
/* ================================== */
/* Unique tree IDs for each tree
 *
 * Note: This enum does not limit the number of tree IDs possible (at least,
 * within the range of the data type int...). The tid_t type is meant to be akin
 * to the C library size_t data type that is returned when calling functions
 * like sizeof(); it is merely an integer type, but we distinguish it from an
 * integer for clarity.
 *
 * Moreover, we do not expect individual enums to be defined for each tree as
 * written below (e.g. HEALTH, COMBAT, etc.), as updating the enums as such
 * would require frequently changing the code written here. The enums that are
 * explicitly defined within tid_t below are for testing purposes.
 *
 * In order to prevent tree enumeration overlap, we envision assigning each
 * chiventure team a range of 1000 IDs (e.g. rpg-battle is entitled to tid_t
 * 2000-2999).
 */
typedef enum tid {
    // Example 1
    HEALTH = 1000,

    // Example 2
    COMBAT = 1001,

    // Example 3
    CHARMS = 1002,

    // Example 4
    POTIONS = 1003,

} tid_t;

/* Skill node forward declaration, contains general information about an acquirable skill in a game
 */
typedef struct skill_node skill_node_t;

struct skill_node {
    // The skill represented by the skill node
    skill_t* skill;

    // Points to a list of prerequisites immediately preceeding the level in the
    // tree, in which the skill node presides
    skill_node_t** prereqs;

    // The number of prerequisite skill nodes
    unsigned int num_prereq_skills;

    // The level that of the character that a player must be to achieve the skill_node
    // This is an ADDITIONAL pre_req to the lists of skill_nodes preceding the tree
    unsigned int prereq_level;

    //List of player classes node belongs to.
    char** player_classes;

    //Num of classes in player_classes.
    int num_classes;

    // The size of the skill node, for the graphics team
    unsigned int size;

};

/* Skill tree, contains all skill nodes in a game */
typedef struct skill_tree {
    // The tree ID that uniquely identifies the skill tree
    tid_t tid;

    // The name of the skill tree
    char* name;

    // The list of tree nodes
    skill_node_t** nodes;

    // The number of tree nodes
    unsigned int num_nodes;

} skill_tree_t;

/*
 * Allocates a new skill node in the heap.
 *
 * Parameters:
 *  - skill: The skill represented by the skill node
 *  - nprepreqs: The number of prerequisite skills to acquire the skill
 *  - size: The size of the skill node, for the graphics team
 *  - prereq_level: The minimum level of the player required to acquire skill
 *  - player_classes: List of classes node belongs to
 *  - num_classes: Number of classes node belongs to
 *
 * Returns:
 *  - A pointer to the skill node, or NULL if a skill node cannot be
 *    allocated
 */
 skill_node_t* skill_node_new(skill_t* skill, unsigned int num_prereq_skills,
                            unsigned int prereq_level, char** player_classes, int num_classes,
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
 *  - preq_level: Prerequisite level
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int node_prereq_add(skill_node_t* node, skill_node_t* prereq,
                    unsigned int prereqlevel);

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
 *  - num_nodes: The number of tree nodes in the skill tree
 *
 * Returns:
 *  - A pointer to the skill tree, or NULL if the skill tree cannot be allocated
 */
skill_tree_t* skill_tree_new(tid_t tid, char* name, unsigned int num_nodes);

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

 * Returns:
 *  - A pointer to the list of all prerequisite skills, NULL if there are none
 *    or an error occurs.
*/
skill_node_t** get_all_skill_prereqs(skill_tree_t* tree, sid_t sid);



/*
 *  Returns number of prerequisite skill for a given skill
 *
 *  Parameters:
 *  - tree: a skill tree
 *  - sid: a skill ID
 *
 *  Returns:   
 * - Integer of the number of prerequisite skills
 *
 *
 */

unsigned int get_number_skill_prereqs(skill_tree_t* tree, sid_t sid);


/*
 *  Returns number of prerequisite skill for a given skill
 *
 *  Parameters:
 *  - tree: a skill tree
 *  - sid: a skill ID
 *
 *  Returns:   
 * - Integer of the prereq level
 *
 */

unsigned int get_prereq_level(skill_tree_t* tree, sid_t sid);

/*
 * Returns prerequisite skills already acquired by a player for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: A skill ID
 *  - num_acquired_prereqs: An out-parameter. The number of acquired prerequisite skills in
 *              the list
 *  - prereq_level: An out-paramter. The level that is a prerequisite to earn a skill
 *
 * Returns:
 *  - A pointer to the list of acquired prerequisite skills, NULL if there are
 *    none or an error occurs.
 *  - To distinguish between no acquired prerequisites and errors, the out-
 *    parameter `num_acquired_prereqs` is updated to 0 when there are no acquired
 *    prerequisites, and is updated to -1 if an error has occurred
 */
skill_t** get_acquired_skill_prereqs(skill_tree_t* tree,
                                     skill_inventory_t* inventory, sid_t sid,
                                     unsigned int* prereq_level,
                                     int* num_acquired_prereqs);

/*
 * Returns prerequisite skills missing by a player for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: The ID of the skill we want to check for prerequisites.
 *  - num_acquired_prereqs: An out-parameter. The number of missing prerequisite skills in
 *              the list
 *  - prereqlevel: an out-parameter, the prerequisite level to level the skill
 *
 * Returns:
 *  - A pointer to the list of missing prerequisite skills, NULL if there are
 *    none or an error occurs.
 *  - To distinguish between no missing prerequisites and errors, the out-
 *    parameter `nmissing` is updated to 0 when there are no missing
 *    prerequisites, and is updated to -1 if an error has occurred
 */
skill_t** skill_prereqs_missing(skill_tree_t* tree,
                                skill_inventory_t* inventory, sid_t sid,
                                unsigned int* prereqlevel,
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

/*
 * Prints useful, high-level information about a skilltree
 * Support for integration with action management for view action
 *
 * Parameters: 
 *  - tree: pointer to a skilltree whose info will be printed
 *  - buffer: an integer which is the maximum size of the resulting string. This 
 *            ensures that we won't hit the case of an incredibly large tree and 
 *            have a resultingly too large string.
 * 
 * Returns:
 *  - string to be printed, a high-level overview of each skill, prereq level,
 *    and current level
 * 
 *    For example, for a skilltree with one node containing the skill "Throw 
 *    Fireball", a current level of 75, and a prereq level of 34, this would 
 *    return the char *:
 *      - "Skill Name: Throw Fireball, Prereq Level: 34, Current Level: 75\n"
 */
char *display_tree(skill_tree_t* tree, int buffer);

/*
 * Given a skilltree that the name of a skill in that tree, prints its 
 * description
 * Support for integration with action management for view action
 *
 * Parameters: 
 *  - tree: pointer to the tree which contains the skill with the given name
 *  - skill_name: the name of the skill whose description is desired
 * 
 * Returns:
  *  - string to be printed, the description of the skill with the given name
 * 
 *    For example, given a skilltree with one node containing the skill "Throw 
 *    Fireball" with the associated description "A Powerful Projectile to SCORCH 
 *    your Enemies", and given the char *name "Throw Fireball", this would
 *    return the char *:
 *      - "Skill Description: A Powerful Projectile to SCORCH your Enemies\n"
 */
char *display_skill_description(skill_tree_t* tree, char *skill_name);

#endif /* INCLUDE_SKILLTREE_H_ */
