/*
 * Skill tree implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/skilltree.h"

/* See skilltree.h */
skill_node_t* skill_node_new(skill_t* skill, unsigned int num_prereq_skills,
                            unsigned int prereq_level, char** player_classes, 
                            int num_classes, unsigned int size) {
    skill_node_t* node;
    node = (skill_node_t*)malloc(sizeof(skill_node_t));
    if (node == NULL) {
        fprintf(stderr, "skill_node_new: memory allocation failed\n");
        return NULL;
    }
    node->prereq_level = prereq_level;

    // Adjusting initial num_prereq_skills not yet implemented.
    node->num_prereq_skills = 0;

    node->player_classes = (char**) malloc(sizeof(char*)*(num_classes + 1));
    if (node->player_classes == NULL) {
        fprintf(stderr, "skill_node_new: memory allocation failed\n");
        return NULL;
    }

    for(int i = 0; i < num_classes; i++){
        node->player_classes[i] = (char*) malloc(sizeof(char)*(strlen(player_classes[i])+1));
        if (node->player_classes[i] == NULL) {
            fprintf(stderr, "skill_node_new: memory allocation failed\n");
            return NULL;
        }
        strcpy(node->player_classes[i], player_classes[i]);
    }

    node->num_classes = num_classes;
    node->skill = skill;
    node->prereqs = NULL;
    node->size = size;
 }

/* See skilltree.h */
int skill_node_free(skill_node_t* node) {
    assert(node != NULL);

    if (node->prereqs) {
        free(node->prereqs);
    }

    for(int i = 0; i < node->num_classes; i++){
        free(node->player_classes[i]);
    }
    free(node->player_classes);

    free(node);

    return SUCCESS;
}

/* See skilltree.h */
int node_prereq_add(skill_node_t* node, skill_node_t* prereq, 
                    unsigned int prereqlevel) {
    assert(node != NULL && prereq != NULL);

    skill_node_t** n = node->prereqs;
    if (node->num_prereq_skills == 0) {
        node->num_prereq_skills += 1;
        n = (skill_node_t**)malloc(sizeof(skill_node_t*));
        node->prereqs = n;
    } else {
        node->num_prereq_skills += 1;
        n = (skill_node_t**)realloc(n, sizeof(skill_node_t*)*node->num_prereq_skills);
    }

    node->prereq_level = prereqlevel;
    n[node->num_prereq_skills - 1] = prereq;
    return SUCCESS;
}

/* See skilltree.h */
int node_prereq_remove(skill_node_t* node, skill_node_t* prereq) {
    assert(node != NULL && prereq != NULL);
    if (node->num_prereq_skills <= 0) {
        fprintf(stderr, "node_prereq_remove: invalid number of prereqs");
        return FAILURE;
    }

    skill_node_t** n = node->prereqs;
    sid_t prereq_sid = prereq->skill->sid;
    // Iterating through prereqs to see where this node is.
    for (unsigned int i = 0; i < node->num_prereq_skills; i++) {
        sid_t node_sid = n[i]->skill->sid;
        if (node_sid == prereq_sid) {
            // Found the node, now to reorganize list.
            node->num_prereq_skills -= 1;
            if ( i < node->num_prereq_skills) {
                n[i] = n[node->num_prereq_skills];
            }
            skill_node_free(n[node->num_prereq_skills]);

            n = (skill_node_t**)realloc(
                    n, sizeof(skill_node_t*)*node->num_prereq_skills);
            return SUCCESS;
        }
    }
    fprintf(stderr, "node_prereq_remove: couldn't find node in prereqs");
    return FAILURE;
}

/* See skilltree.h */
skill_tree_t* skill_tree_new(tid_t tid, char* name, unsigned int num_nodes) {

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

    // Initializing num_nodes through parameters not yet designed.
    tree->num_nodes = 0;

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
    assert(tree != NULL && node != NULL);

    skill_node_t** n = tree->nodes;
    if (tree->num_nodes == 0) {
        // First time mallocing
        tree->num_nodes += 1;
        n = (skill_node_t**)malloc(sizeof(skill_node_t*));
        if (n == NULL) {
            fprintf(stderr, "skill_tree_node_add: malloc failed\n");
            return FAILURE;
        }
        tree->nodes = n;
    } else {
        tree->num_nodes += 1;
        n = (skill_node_t**)realloc(n, sizeof(skill_node_t*)*tree->num_nodes);
    }

    n[tree->num_nodes - 1] = node;
    return SUCCESS;
}

/* See skilltree.h */
int skill_tree_has_node(skill_tree_t* tree, sid_t sid) {
    assert(tree != NULL);

    for (unsigned int i = 0; i < tree->num_nodes; i++) {
        if (tree->nodes[i]) {
            if (tree->nodes[i]->skill->sid == sid) {
                return i;
            }
        }
    }
    // Failed to find node.
    return -1;
}

/* See skilltree.h */
int skill_tree_node_remove(skill_tree_t* tree, skill_node_t* node) {
    assert(tree != NULL && node != NULL);

    int pos = skill_tree_has_node(tree, node->skill->sid);

    if (pos == -1) {
        fprintf(stderr, "skill_tree_node_remove: node is not in tree\n");
        return FAILURE;
    }

    int rc = skill_node_free(tree->nodes[pos]);
    if (rc == FAILURE) {
        fprintf(stderr, "skill_tree_node_remove: freeing failed\n");
        return FAILURE;
    }

    return SUCCESS;
}

/* See skilltree.h */
skill_node_t** get_all_skill_prereqs(skill_tree_t* tree, sid_t sid) {
    assert(tree != NULL);

    int pos = skill_tree_has_node(tree, sid);
    if (pos == -1) {
        fprintf(stderr, "get_all_skill_prereqs: node is not in tree\n");
        return NULL;
    }

    return tree->nodes[pos]->prereqs;
}

/* See skliltree.h */
unsigned int get_number_skill_prereqs(skill_tree_t* tree, sid_t sid) {
    assert(tree != NULL);

    int pos = skill_tree_has_node(tree, sid);
    if (pos == -1) {
        fprintf(stderr, "get_number_skill_prereqs: node is not in tree\n");
        return 0;
    }

    return tree->nodes[pos]->num_prereq_skills;
}


/* See skilltree.h */
unsigned int get_prereq_level(skill_tree_t* tree, sid_t sid) {
    assert(tree != NULL);

    int pos = skill_tree_has_node(tree, sid);
    if (pos == -1) {
        fprintf(stderr, "get_number_skill_prereqs: node is not in tree\n");
        return 0;
    }

    return tree->nodes[pos]->prereq_level;
}



/* See skilltree.h */
skill_t** get_acquired_skill_prereqs(skill_tree_t* tree,
                                     skill_inventory_t* inventory, sid_t sid,
                                     unsigned int* prereq_level,
                                     int* num_acquired_prereqs) {
    assert(tree != NULL && inventory != NULL);

    skill_node_t** prereqs = get_all_skill_prereqs(tree, sid);
    // this changes the out-parameters for the sid skill
    if (*num_acquired_prereqs == -1) {
        fprintf(stderr, "get_acquired_skill_prereqs: node is not in tree\n");
        *num_acquired_prereqs = -1;
        return NULL;
    }

    skill_t** acquired = (skill_t**)malloc(*num_acquired_prereqs * sizeof(skill_t*));
    if (acquired == NULL) {
        fprintf(stderr, "get_acquired_skill_prereqs: malloc acquired failed\n");
        *num_acquired_prereqs = -2;
        return NULL;
    }

    *num_acquired_prereqs = 0;

    unsigned int num_prereqs = get_number_skill_prereqs(tree, sid);

    for (unsigned int i = 0; i < num_prereqs; i++) {
        sid_t prereq = prereqs[i]->skill->sid;
        skill_type_t type = prereqs[i]->skill->type;
        int pos = inventory_has_skill(inventory, prereq, type);
        if (pos >= 0) {
            // Inventory has this skill, so we have to add it to the list of
            // acquired skills.
            void** res;
            switch (type) {
                case ACTIVE:
                    acquired[(*num_acquired_prereqs)] = inventory->active[pos];
                    break;
                case PASSIVE:
                    acquired[(*num_acquired_prereqs)] = inventory->passive[pos];
                    break;
                default:
                    fprintf(stderr,
                            "get_acquired_skill_prereqs: not valid skill type\n");
                    *num_acquired_prereqs = -3;
                    return NULL;
            }
            if (res == NULL) {
                fprintf(stderr,"get_acquired_skill_prereqs: adding skill failed\n");
                *num_acquired_prereqs = -4;
                return NULL;
            }
            (*num_acquired_prereqs)++;
        }
    }

    // Make sure we return null if there were no skills already acquired.
    if ((*num_acquired_prereqs) == 0) {
        return NULL;
    } else {
        return acquired;
    }
}

/* See skilltree.h */
skill_t** skill_prereqs_missing(skill_tree_t* tree,
                                skill_inventory_t* inventory, sid_t sid,
                                unsigned int* prereqlevel,
                                int* num_missing) {
    assert(tree != NULL && inventory != NULL);

    unsigned int num_prereqs;
    skill_node_t** prereqs = get_all_skill_prereqs(tree, sid);

    if (num_prereqs == -1) {
        fprintf(stderr, "skill_prereqs_missing: node is not in tree\n");
        *num_missing = -1;
        return NULL;
    }

    skill_t** missing = (skill_t**)malloc(num_prereqs * sizeof(skill_t*));
    if (missing == NULL) {
        fprintf(stderr,"skill_prereqs_missing: malloc missing skills failed\n");
        *num_missing = -2;
        return NULL;
    }

    *num_missing = 0;

    for (unsigned int i = 0; i < num_prereqs; i++) {
        skill_t* prereq = prereqs[i]->skill;
        skill_type_t type = prereqs[i]->skill->type;
        int pos = inventory_has_skill(inventory, prereq->sid, type);
        if (pos == -1) {
            // Inventory doesn't have this skill, so we have to add it to the
            // list of non-acquired skills.
            missing[*num_missing] = prereq;
            (*num_missing)++;
        }
    }

    // Make sure we return null if there were no skills already acquired.
    if ((*num_missing) == 0) {
        return NULL;
    } else {
        return missing;
    }
}

/* See skilltree.h */
int inventory_skill_acquire(skill_tree_t* tree, skill_inventory_t* inventory,
                           skill_t* skill) {
    assert(tree != NULL);
    assert(inventory != NULL);
    assert(skill != NULL);
    
    unsigned int level_pointer;

    unsigned int num_missing;
    skill_t** missing = skill_prereqs_missing(tree, inventory, skill->sid, &level_pointer,
                                              &num_missing);

    if (num_missing == 0) {
        int rc = inventory_skill_add(inventory, skill);
        if (rc) {
            fprintf(stderr, "inventory_skill_acquire: did not acquire skill\n");
            return FAILURE;
        }
        return SUCCESS;
    }

    fprintf(stderr, "inventory_skill_acquire: missing prerequisites\n");
    return FAILURE;
}

/*
 * Given a number, counts its digits
 * Helper function for display_tree
 *
 * Parameters: 
 *  - num: the number whose number of digits is being calculated
 * 
 * Returns:
 *  - number of digits of the given num
 */
int count_digits(int num){
    if (num == 0)
        return 1;
    int count = 0;
    while (num != 0){
        num = (num/10);
        count += 1;
    }
    return count;
}

/* See skilltree.h */
char *display_tree(skill_tree_t* tree, int max_buf_len){
    int size = 0;
    char *skill_desc_template = "Skill Name: , Prereq Level: , Current Level: \n";
    int template_len = strlen(skill_desc_template);

    // Calculating size of string we need to store all necessary info
    for (int j = 0; j < tree->num_nodes; j++){
        // count size of skill name
        size += strlen(tree->nodes[j]->skill->name);

        // add size of prereq_level and current level
        // uses helper function to calculate their lengths
        size += count_digits(tree->nodes[j]->prereq_level);
        size += count_digits(tree->nodes[j]->skill->level);

        // add size of formatting text used around each info piece
        // meaning the size of the formatting string "Skill Name: , Prereq 
        // Level: , Current Level: \n", which is used to make the given
        // high-level information easier for the average user to understand 
        size += template_len;
    }

    // Finally, add the size of the null terminator of the string
    size += 2;

    if (size <= max_buf_len){
        char buffer[size];
        char* temp = buffer;

        for (int i = 0; i < tree->num_nodes; i++){
            sprintf(temp, "Skill Name: %s, Prereq Level: %d, Current Level: %d\n", tree->nodes[i]->skill->name, tree->nodes[i]->prereq_level, tree->nodes[i]->skill->level);
            temp += strlen(temp);
        }

        char *display = strdup(buffer);
        return display;
    } else {
        char buffer[max_buf_len];
        char* temp = buffer;

        int count = 0;
        int curr = 0;
        
        for (int i = 0; i < tree->num_nodes; i++){
            // count of current node size
            curr = template_len + strlen(tree->nodes[i]->skill->name) + 
                   count_digits(tree->nodes[i]->prereq_level) +
                   count_digits(tree->nodes[i]->skill->level);

            if (curr + count <= max_buf_len){
                sprintf(temp, "Skill Name: %s, Prereq Level: %d, Current Level: %d\n", tree->nodes[i]->skill->name, tree->nodes[i]->prereq_level, tree->nodes[i]->skill->level);
                temp += strlen(temp);
            }

            if (curr + count > max_buf_len){
                char *display = strdup(buffer);
                return display;  
            }

            count += curr;
        }

        char *display = strdup(buffer);
        return display;   
    }
}

/* See skilltree.h */
char *display_skill_description(skill_tree_t* tree, char *skill_name){
    assert(tree != NULL);

    for (int i = 0; i < tree->num_nodes; i++){
        if (!strcmp(tree->nodes[i]->skill->name,skill_name)){
            // size of the buf is calculated, using the strlen of the 
            // description plus the size of the surrounding "Skill Description:\n"
            // and null terminator
            int size = strlen(tree->nodes[i]->skill->desc) + 22;
            char buffer[size];

            sprintf(buffer, "Skill Description: %s\n", tree->nodes[i]->skill->desc);

            char *display = strdup(buffer);
            return display;
        }
    }
    
    char buffer[] = "No skill matches the given name";

    char *display = strdup(buffer);
    return display;
}