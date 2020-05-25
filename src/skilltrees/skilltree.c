/*
 * Skill tree implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

    int rc;

    rc = array_element_add(branch->prereqs, branch->nprereqs, skill);
    if (rc) {
        fprintf(stderr, "branch_prereq_add: failed to add prerequisite\n");
        return FAILURE;
    }

    return SUCCESS;
}

/* See skilltree.h */
int branch_prereq_remove(branch_t* branch, skill_t* skill) {
    assert(branch != NULL && skill != NULL);

    int pos = list_has_skill(branch->prereqs, branch->nprereqs, skill->sid);
    if (pos == -1) {
        fprintf(stderr, "branch_prereq_remove: prequisite is not in branch\n");
        return FAILURE;
    }

    branch->prereqs[pos] = NULL;

    return SUCCESS;
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

    int rc;

    rc = array_element_add(tree->branches, tree->nbranches, branch);
    if (rc) {
        fprintf(stderr, "tree_branch_add: failed to add tree branch\n");
        return FAILURE;
    }

    return SUCCESS;
}

/* See skilltree.h */
int tree_has_branch(tree_t* tree, sid_t sid) {
    assert(tree != NULL);

    unsigned int i;

    for (i = 0; i < tree->nbranches; i++) {
        if (tree->branches[i]) {
            if (tree->branches[i]->sid == sid) {
                return i;
            }
        }
    }

    return -1;
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
skill_t** prereqs_all(tree_t* tree, sid_t sid, unsigned int* nprereqs) {
    assert(tree != NULL);

    int pos = tree_has_branch(tree, sid);
    if (pos == -1) {
        fprintf(stderr, "prereqs_all: branch is not in tree\n");
        return NULL;
    }

    *nprereqs = tree->branches[pos]->nprereqs;
    return tree->branches[pos]->prereqs;
}

/* See skilltree.h */
skill_t** prereqs_acquired(tree_t* tree, inventory_t* inventory, sid_t sid,
                           unsigned int* nacquired) {
    assert(tree != NULL && inventory != NULL);

    unsigned int nprereqs;
    skill_t** prereqs = prereqs_all(tree, sid, &nprereqs);

    unsigned int i;
    sid_t prereq;
    skill_type_t type;
    int pos;

    skill_t** acquired;
    *nacquired = 0;

    for (i = 0; i < nprereqs; i++) {
        prereq = prereqs[i]->sid;
        type = prereqs[i]->type;
        if (pos = inventory_has_skill(inventory, prereq, type)) {
            (*nacquired)++;
            acquired = (skill_t**)realloc(acquired, sizeof(skill_t*) * (*nacquired));
            if (acquired == NULL) {
                fprintf(stderr, "prereqs_acquired: failed to reallocate acquired\n");
                return NULL;
            }
            switch (type) {
                case ACTIVE:
                    array_element_add(acquired, (*nacquired), inventory->active[pos]);
                    break;
                case PASSIVE:
                    array_element_add(acquired, (*nacquired), inventory->passive[pos]);
                    break;
                default:
                    fprintf(stderr, "prereqs_acquired: not a valid skill type\n");
                    return NULL;
            }
        }
    }

    return acquired;
}

/* See skilltree.h */
skill_t** prereqs_missing(tree_t* tree, inventory_t* inventory, sid_t sid,
                          unsigned int* nmissing) {
    assert(tree != NULL && inventory != NULL);

    unsigned int nprereqs;
    skill_t** prereqs = prereqs_all(tree, sid, &nprereqs);

    unsigned int nacquired;
    skill_t** acquired = prereqs_acquired(tree, inventory, sid, &nacquired);

    unsigned int i;
    sid_t prereq;
    int pos;

    skill_t** missing;
    *nmissing = 0;

    for (i = 0; i < nprereqs; i++) {
        prereq = prereqs[i]->sid;
        pos = list_has_skill(acquired, nacquired, prereq);
        if (pos == -1) {
            (*nmissing)++;
            missing = (skill_t**)realloc(missing, sizeof(skill_t*) * (*nmissing));
            if (missing == NULL) {
                fprintf(stderr, "prereqs_missing: failed to reallocate missing\n");
                return NULL;
            }
            array_element_add(missing, (*nmissing), prereqs[i]);
        }
    }

    return missing;
}

/* HELPER FUNCTION */
int level_update(tree_t* tree, skill_t* skill) {
    assert(tree != NULL && skill != NULL);

    int pos = tree_has_branch(tree, skill->sid);
    if (pos == -1) {
        fprintf(stderr, "level_update: branch is not in tree\n");
        return FAILURE;
    }

    if (skill->xp >= tree->branches[pos]->min_xp) {
        skill->xp -= tree->branches[pos]->min_xp;
        skill->level += 1;
        return SUCCESS;
    }

    return FAILURE;
}

/* See skilltree.h */
void levels_update(tree_t* tree, inventory_t* inventory) {
    assert(tree != NULL && inventory != NULL);

    unsigned int i;

    for (i = 0; i < inventory->nactive; i++) {
        level_update(tree, inventory->active[i]);
    }

    for (i = 0; i < inventory->npassive; i++) {
        level_update(tree, inventory->passive[i]);
    }
}

/* See skilltree.h */
int inventory_skill_acquire(tree_t* tree, inventory_t* inventory, sid_t sid) {
    return 0;
}
