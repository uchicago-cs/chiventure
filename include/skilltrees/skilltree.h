/*
 * Skill tree implementation for chiventure
 */

#ifndef INCLUDE_SKILLTREE_H_
#define INCLUDE_SKILLTREE_H_

#include "common/common.h"
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"

/* ======================= */
/* === DATA STRUCTURES === */
/* ======================= */
/* Unique tree IDs for each tree */
typedef enum tid {
    // Example 1
    HEALTH,

    // Example 2
    COMBAT,

    // Example 3
    CHARMS,

    // Example 4
    POTIONS,

} tid_t;

/* Skill branch, contains general information about an acquirable skill in a
 * game
 */
typedef struct branch {
    // The skill ID that uniquely identifies the skill
    sid_t sid;

    // The list of prerequisite skills to acquire skill `sid`
    skill_t** prereqs;

    // The number of prerequisite skills
    unsigned int nprereqs;

    // The maximum level to which the skill can be upgraded
    unsigned int max_level;

    // The number of experience points needed to level up
    unsigned int min_xp;

} branch_t;

/* Skill tree, contains all skill branches in a game */
typedef struct tree {
    // The tree ID that uniquely identifies the tree
    tid_t tid;

    // The list of tree branches
    branch_t** branches;

    // The number of tree branches
    unsigned int nbranches;

} tree_t;

/* ================= */
/* === FUNCTIONS === */
/* ================= */
/*
 * Allocates a new skill branch in the heap.
 *
 * Parameters:
 *  - sid: The skill ID that uniquely identifies the skill
 *  - nprepreqs: The number of prerequisite skills to acquire the skill
 *  - max_level: The maximum level to which the skill can be upgraded
 *  - min_xp: The number of experience points needed to level up
 *
 * Returns:
 *  - A pointer to the skill branch, or NULL if a skill branch cannot be
 *    allocated
 */
 branch_t* branch_new(sid_t sid, unsigned int nprereqs, unsigned int max_level,
                      unsigned int min_xp);

/*
 * Frees the resources associated with a skill tree branch.
 *
 * Parameters:
 *  - branch: A skill branch. Must point to branch allocated with branch_new
 *
 * Returns:
 *  - Always returns 0
 */
int branch_free(branch_t* branch);

/*
 * Adds a prerequisite skill to a skill branch.
 *
 * Parameters:
 *  - branch: A skill branch
 *  - skill: A skill
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int branch_prereq_add(branch_t* branch, skill_t* prereq);

/*
 * Removes a prerequisite skill from a skill branch.
 *
 * Parameters:
 *  - branch: A skill branch
 *  - skill: A skill
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int branch_prereq_remove(branch_t* branch, skill_t* prereq);

/*
 * Allocates a new (empty) skill tree in the heap.
 *
 * Parameters:
 *  - tid: The skill tree ID that uniquely identifies the skill tree
 *  - nbranches: The number of branches to allocate in the skill tree
 *
 * Returns:
 *  - A pointer to the skill tree, or NULL if the skill tree cannot be allocated
 */
tree_t* tree_new(tid_t tid, unsigned int nbranches);

/*
 * Frees the resources associated with a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree. Must point to skill tree allocated with tree_new
 *
 * Returns:
 *  - Always returns 0
 */
int tree_free(tree_t* tree);

/*
 * Adds a skill branch to a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - branch: A skill branch
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int tree_branch_add(tree_t* tree, branch_t* branch);

/*
 * Removes a skill branch from a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - branch: A skill branch
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int tree_branch_remove(tree_t* tree, branch_t* branch);

/*
 * Searches for a skill branch in a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - sid: A skill ID that uniquely identifies the skill branch
 *
 * Returns:
 *  - The position of the branch in the skill tree, -1 if the tree does not have
 *    a branch that corresponds to skill ID `sid`
 */
int tree_has_branch(tree_t* tree, sid_t sid);

/*
 * Returns all prerequisite skills for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - sid: A skill ID
 *  - nprereqs: An out parameter. The number of prerequisite skills in the list
 *
 * Returns:
 *  - A pointer to the list of all prerequisite skills, NULL if an error occurs
 */
skill_t** prereqs_all(tree_t* tree, sid_t sid, unsigned int* nprereqs);

/*
 * Returns prerequisite skills already acquired by a player for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: A skill ID
 *  - nprereqs: An out parameter. The number of acquired prerequisite skills in
 *              the list
 *
 * Returns:
 *  - A pointer to the list of acquired prerequisite skills, NULL if an error
 *    occurs
 */
skill_t** prereqs_acquired(tree_t* tree, inventory_t* inventory, sid_t sid,
                           unsigned int* nacquired);

/*
 * Returns prerequisite skills already missing by a player for a given skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: A skill ID
 *  - nprereqs: An out parameter. The number of missing prerequisite skills in
 *              the list
 *
 * Returns:
 *  - A pointer to the list of missing prerequisite skills, NULL if an error
 *    occurs
 */
skill_t** prereqs_missing(tree_t* tree, inventory_t* inventory, sid_t sid,
                          unsigned int* nmissing);

/*
 * Updates levels of all skills in an inventory.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *
 * Returns:
 *  - None
 */
void levels_update(tree_t* tree, inventory_t* inventory);

/*
 * Adds a skill to an inventory, if the inventory contains all its prerequisite
 * skills
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *  - sid: A skill ID
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int inventory_skill_acquire(tree_t* tree, inventory_t* inventory, sid_t sid);

#endif /* INCLUDE_SKILLTREE_H_ */
