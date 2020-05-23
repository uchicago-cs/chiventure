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
    skill_t** prerequisites;

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
 * Allocates a new (empty) skill prerequisites list in the heap.
 *
 * Parameters:
 *  - nprepreqs: The number of prerequisite skills
 *
 * Returns:
 *  - A pointer to the list, or NULL if the list cannot be allocated
 */
skill_t** prereqs_new(unsigned int nprereqs);

/*
 * Frees the resources associated with a skill prerequisites list.
 *
 * Parameters:
 *  - prereqs: The list of prerequisite skills
 *  - nprepreqs: The number of prerequisite skills
 *
 * Returns:
 *  - Always returns 0
 */
int prereqs_free(skill_t** prereqs, unsigned int nprereqs);

/*
 * Adds a skill to a prerequisite skills list.
 *
 * Parameters:
 *  - prereqs: A skill prerequisite skills list
 *  - skill: A skill
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int prereq_skill_add(skill_t** prereqs, skill_t* skill);

/*
 * Removes a skill from a prerequisite skills list.
 *
 * Parameters:
 *  - prereqs: A skill prerequisite skills list
 *  - skill: A skill
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int prereq_skill_remove(skill_t** prereqs, skill_t* skill);

/*
 * Returns all prerequisites for a skill.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - skill: A skill
 *  - nprepreqs: A pointer to the number of prerequisites
 *
 * Returns:
 *  - A pointer to the list, or NULL if an error occurs
 */
skill_t** prereqs_all(tree_t* tree, skill_t* skill, unsigned int* nprereqs);

/*
 * Returns all prerequisites for a skill acquired by a player.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - skill: A skill
 *  - nprepreqs: A pointer to the number of prerequisites acquired
 *
 * Returns:
 *  - A pointer to the list, or NULL if an error occurs
 */
skill_t** prereqs_acquired(tree_t* tree, skill_t* skill, unsigned int* nprereqs);

/*
 * Returns all prerequisites for a skill missing by a player.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - skill: A skill
 *  - nprepreqs: A pointer to the number of prerequisites missing
 *
 * Returns:
 *  - A pointer to the list, or NULL if an error occurs
 */
skill_t** prereqs_missing(tree_t* tree, skill_t* skill, unsigned int* nprereqs);

/*
 * Allocates a new skill branch in the heap.
 *
 * Parameters:
 *  - sid: The skill ID that uniquely identifies the skill
 *  - prereqs: The prerequisite skills to acquire the skill
 *  - nprepreqs: A pointer to the number of prerequisites
 *  - max_level: The maximum level to which the skill can be upgraded
 *  - min_xp: The number of experience points needed to level up
 *
 * Returns:
 *  - A pointer to the skill branch, or NULL if a skill branch cannot be
 *    allocated
 */
branch_t* branch_new(sid_t sid, skill_t** prereqs, unsigned int nprereqs,
                     unsigned int max_level, unsigned int min_xp);

/*
 * Initializes a skill tree branch.
 *
 * Parameters:
 *  - sid: The skill ID that uniquely identifies the skill
 *  - prereqs: The prerequisite skills to acquire the skill
 *  - nprepreqs: A pointer to the number of prerequisites
 *  - max_level: The maximum level to which the skill can be upgraded
 *  - min_xp: The number of experience points needed to level up
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int branch_init(branch_t* branch, sid_t sid, skill_t** prereqs,
                unsigned int nprereqs, unsigned int max_level,
                unsigned int min_xp);

/*
 * Frees the resources associated with a skill tree branch.
 *
 * Parameters:
 *  - branch: A branch. Must point to skill allocated with branch_new
 *
 * Returns:
 *  - Always returns 0
 */
int branch_free(branch_t* branch);

/*
 * Allocates a new (empty) skill tree in the heap.
 *
 * Parameters:
 *  - nbranches: The number of branches to allocate in the skill tree
 *
 * Returns:
 *  - A pointer to the skill tree, or NULL if the skill tree cannot be allocated
 */
tree_t* tree_new(unsigned int nbranches);

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
 * Adds a branch to a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - branch: A branch
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int tree_branch_add(tree_t* tree, branch_t* branch);

/*
 * Removes a branch from a skill tree.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - branch: A branch
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int tree_branch_remove(tree_t* tree, branch_t* branch);

/*
 * Updates a skill level, if ready to be leveled-up.
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_level_update(tree_t* tree, inventory_t* inventory);

/*
 * Adds a skill to a player's inventory, if the player has all the prerequisites
 *
 * Parameters:
 *  - tree: A skill tree
 *  - inventory: A player's skill inventory
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_acquire(tree_t* tree, inventory_t* inventory);

#endif /* INCLUDE_SKILLTREE_H_ */
