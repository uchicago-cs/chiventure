/*
 * Skill tree implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/skilltree.h"

/* See skilltree.h */
skill_node_t* skill_node_new(skill_t* skill, unsigned int nprereqs,
                             unsigned int size) {
     skill_node_t* node;
     node = (skill_node_t*)malloc(sizeof(skill_node_t));
     if (node == NULL) {
         fprintf(stderr, "skill_node_new: memory allocation failed\n");
         return NULL;
     }

     node->skill = skill;
     node->prereqs = NULL;
     node->nprereqs = nprereqs;
     node->size = size;
 }

/* See skilltree.h */
int skill_node_free(skill_node_t* node) {
    assert(node != NULL);

    if (node->prereqs) {
        free(node->prereqs);
    }

    free(node);

    return SUCCESS;
}

/* See skilltree.h */
int node_prereq_add(skill_node_t* node, skill_node_t* prereq) {
    assert(node != NULL && prereq != NULL);

    void** res;

    res = array_element_add((void**)node->prereqs, node->nprereqs, (void*)prereq);
    if (res == NULL) {
        fprintf(stderr, "node_prereq_add: addition failed\n");
        return FAILURE;
    }

    node->prereqs = (skill_node_t**)res;
    return SUCCESS;
}

/* See skilltree.h */
int node_prereq_remove(skill_node_t* node, skill_node_t* prereq) {
    assert(node != NULL && prereq != NULL);

    /* TO DO */
    return 0;
}

/* See skilltree.h */
skill_tree_t* skill_tree_new(tid_t tid, char* name, unsigned int nnodes) {
    assert(nnodes > 0);

    skill_tree_t* tree;
    tree = (skill_tree_t*)malloc(sizeof(skill_tree_t));
    if (tree == NULL) {
        fprintf(stderr, "skill_tree_new: memory allocation failed\n");
        return NULL;
    }

    tree->tid = tid;
    tree->name = strdup(name);
    if (tree->name == NULL) {
        fprintf(stderr, "skill_tree_new: name copy failed\n");
        return NULL;
    }
    tree->nodes = NULL;
    tree->nnodes = nnodes;

    return tree;
}

/* See skilltree.h */
int skill_tree_free(skill_tree_t* tree) {
    assert(tree != NULL);

    free(tree->name);

    if (tree->nodes) {
        free(tree->nodes);
    }

    free(tree);

    return SUCCESS;
}

/* See skilltree.h */
int skill_tree_node_add(skill_tree_t* tree, skill_node_t* node) {
    /* TO DO */
    return 0;
}

/* See skilltree.h */
int skill_tree_has_node(skill_tree_t* tree, sid_t sid) {
    /* TO DO */
    return 0;
}

/* See skilltree.h */
int skill_tree_node_remove(skill_tree_t* tree, skill_node_t* node) {
    /* TO DO */
    return 0;
}

/* See skilltree.h */
skill_t** skill_prereqs_all(skill_tree_t* tree, sid_t sid, int* nprereqs) {
    /* TO DO */
    return NULL;
}

/* See skilltree.h */
skill_t** skill_prereqs_acquired(skill_tree_t* tree,
                                skill_inventory_t* inventory, sid_t sid,
                                int* nacquired) {
    /* TO DO */
    return NULL;
}

/* See skilltree.h */
skill_t** skill_prereqs_missing(skill_tree_t* tree,
                               skill_inventory_t* inventory, sid_t sid,
                               int* nmissing) {
    /* TO DO */
    return NULL;
}

/* See skilltree.h */
int inventory_skill_acquire(skill_tree_t* tree, skill_inventory_t* inventory,
                           skill_t* skill) {
    return 0;
}
