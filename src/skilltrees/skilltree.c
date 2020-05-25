/*
 * Skill tree implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "skilltrees/skilltree.h"

/* See skilltree.h */
branch_t* branch_new(sid_t sid, unsigned int nprereqs, unsigned int max_level,
                     unsigned int min_xp) {
    branch_t* branch;
    skill_t** prereqs;
    unsigned int i;

    branch = (branch_t*)malloc(sizeof(branch_t));
    if (branch == NULL) {
        fprintf(stderr, "branch_new: could not allocate memory\n");
        return NULL;
    }
    prereqs = (skill_t**)malloc(sizeof(skill_t*) * nprereqs);
    if (prereqs == NULL) {
        fprintf(stderr, "branch_new: could not allocate memory\n");
        return NULL;
    }

    for (i = 0; i < nprereqs; i++) {
        prereqs[i] = NULL;
    }

    branch->sid = sid;
    branch->prereqs = prereqs;
    branch->nprereqs = nprereqs;
    branch->max_level = max_level;
    branch->min_xp = min_xp;

    return branch;
}

/* See skilltree.h */
int branch_free(branch_t* branch) {
    assert(branch != NULL);

    free(branch->prereqs);
    free(branch);

    return SUCCESS;
}

/* See skilltree.h */
int branch_prereq_add(branch_t* branch, skill_t* skill) {
    assert(branch != NULL && skill != NULL);

    unsigned int i;
    skill_t* prereq;

    for (i = 0; i < branch->nprereqs; i++) {
        if (prereq = branch->prereqs[i] == NULL) {
            prereq = skill;
            return SUCCESS;
        }
    }

    return FAILURE;
}

/* See skilltree.h */
int branch_prereq_remove(branch_t* branch, skill_t* skill) {
    assert(branch != NULL && skill != NULL);

    unsigned int i;

    for (i = 0; i < branch->nprereqs; i++) {
        if (branch->prereq[i]->sid == skill->sid) {
            branch->prereq[i] = NULL;
            return SUCCESS;
        }
    }

    return FAILURE;
}

/* See skilltree.h */
tree_t* tree_new(tid_t tid, unsigned int nbranches) {
    tree_t* tree;
    branch_t** branches;
    unsigned int i;

    tree = (tree_t*)malloc(sizeof(tree_t));
    if (tree == NULL) {
        fprintf(stderr, "tree_new: could not allocate memory\n");
        return NULL;
    }
    branches = (branch_t**)malloc(sizeof(branch_t*) * nbranches);
    if (branches == NULL) {
        fprintf(stderr, "tree_new: could not allocate memory\n");
        return NULL;
    }

    for (i = 0; i < nbranches; i++) {
        branches[i] = NULL;
    }

    tree->tid = tid;
    tree->branches = branches;
    tree->nbranches = nbranches;

    return tree;
}

/* See skilltree.h */
int tree_free(tree_t* tree) {
    assert(tree != NULL);

    free(tree->branches);
    free(tree);

    return SUCCESS;
}

/* See skilltree.h */
int tree_branch_add(tree_t* tree, branch_t* branch) {
    assert(tree != NULL && branch != NULL);

    unsigned int i;
    branch_t* b;

    for (i = 0; i < tree->nbranches; i++) {
        if (b = tree->branches[i] == NULL) {
            b = branch;
            return SUCCESS;
        }
    }

    return FAILURE;
}

/* See skilltree.h */
int tree_branch_remove(tree_t* tree, branch_t* branch) {
    assert(tree != NULL && branch != NULL);

    int pos = tree_has_branch(tree, branch->sid);
    if (pos == -1) {
        fprintf(stderr, "tree_branch_remove: branch is not in tree\n");
        return FAILURE;
    }

    tree->branches[pos] = NULL;
    return SUCCESS;
}

/* See skilltree.h */
int tree_has_branch(tree_t* tree, sid_t sid) {
    assert(tree != NULL);

    unsigned int i;

    for (i = 0; i < tree->nbranches; i++) {
        if (tree->branches[i]->sid == sid) {
            return i;
        }
    }

    return -1;
}

/* See skilltree.h */
skill_t** prereqs_all(tree_t* tree, sid_t sid, unsigned int* nprereqs) {
    return NULL;
}

/* See skilltree.h */
skill_t** prereqs_acquired(tree_t* tree, inventory_t* inventory, sid_t sid,
                           unsigned int* nacquired) {
    return NULL;
}

/* See skilltree.h */
skill_t** prereqs_missing(tree_t* tree, inventory_t* inventory, sid_t sid,
                          unsigned int* nmissing) {
    return NULL;
}

/* See skilltree.h */
int levels_update(tree_t* tree, inventory_t* inventory) {
    return 0;
}

/* See skilltree.h */
int inventory_skill_acquire(tree_t* tree, inventory_t* inventory, sid_t sid) {
    return 0;
}
