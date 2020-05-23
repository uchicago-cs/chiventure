/*
 * Skill tree implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/skilltree.h"

/* See skilltree.h */
skill_t** prereqs_new(unsigned int nprereqs) {
    return NULL;
}

/* See skilltree.h */
int prereqs_free(skill_t** prereqs, unsigned int nprereqs) {
    return 0;
}

/* See skilltree.h */
int prereq_skill_add(skill_t** prereqs, skill_t* skill) {
    return 0;
}

/* See skilltree.h */
int prereq_skill_remove(skill_t** prereqs, skill_t* skill) {
    return 0;
}

/* See skilltree.h */
skill_t** prereqs_all(tree_t* tree, skill_t* skill, unsigned int* nprereqs) {
    return NULL;
}

/* See skilltree.h */
skill_t** prereqs_acquired(tree_t* tree, skill_t* skill, unsigned int* nprereqs) {
    return NULL;
}

/* See skilltree.h */
skill_t** prereqs_missing(tree_t* tree, skill_t* skill, unsigned int* nprereqs) {
    return NULL;
}

/* See skilltree.h */
branch_t* branch_new(sid_t sid, skill_t** prereqs, unsigned int nprereqs,
                     unsigned int max_level, unsigned int min_xp) {
    return NULL;
}

/* See skilltree.h */
int branch_init(branch_t* branch, sid_t sid, skill_t** prereqs,
                unsigned int nprereqs, unsigned int max_level,
                unsigned int min_xp) {
    return 0;
}

/* See skilltree.h */
int branch_free(branch_t* branch) {
    return 0;
}

/* See skilltree.h */
tree_t* tree_new(unsigned int nbranches) {
    return NULL;
}

/* See skilltree.h */
int tree_free(tree_t* tree) {
    return 0;
}

/* See skilltree.h */
int tree_branch_add(tree_t* tree, branch_t* branch) {
    return 0;
}

/* See skilltree.h */
int tree_branch_remove(tree_t* tree, branch_t* branch) {
    return 0;
}

/* See skilltree.h */
int skill_level_update(tree_t* tree, inventory_t* inventory) {
    return 0;
}

/* See skilltree.h */
int skill_acquire(tree_t* tree, inventory_t* inventory) {
    return 0;
}
