
#include <ctype.h>

#include "playerclass/class_prefabs.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/*
 * this is a placeholder function for the skill struct to satisfy
 * the effect_t field, which wants a function of this form
 *
 * in the future, playerclass and skilltrees teams should coordinate
 * so that the effect_t field can be a function pointer to a function
 * that will actually execute the skill
 *
 * Paramters:
 *  - sk. a string representing the skill effects
 *
 * Returns:
 *  - the input parameter (placeholder)
 */
char* class_execute_skill(char* sk) {
    return sk;
}

/* Testing out how this might work */
class_t* class_prefab_warrior() {
    char *name = "Warrior"; 
    char *short_desc = "Guy with sword."; 
    char *long_desc = "Guy with sword. Guy hit thing in head with sword. Guy use " 
    "few words, sword is better than words.";
    
    obj_t *attr = NULL;
    stats_hash_t *stats = NULL;
    effects_hash_t *effects = NULL;
    return class_new(name, short_desc, long_desc, attr, stats, effects);
}

/* See class.h */
int class_allocate_skills(class_t* class, int max_skills_in_tree, 
                      int max_active_skills, int max_passive_skills) {
    class->combat = inventory_new(max_active_skills, max_passive_skills);
    class->noncombat = inventory_new(max_active_skills, max_passive_skills);
    
    /* tree ID needs to be unique across all chiventure code.  Our team has been
     * assigned the range 3000-3999.  Default classes start at 3000. There is
     * currently no support for non-prefab classes. */
    int class_id = get_class_name_index(class->name);
    if (class_id == -1) {
        fprintf(stderr, "Could not find class name: \"%s\" "
                        "in class_init_skills\n", class->name);
        return EXIT_FAILURE;
    }
    int tid = 3000 + class_id;
    class->skilltree = skill_tree_new(tid, class->name, max_skills_in_tree);

    if (class->skilltree == NULL) {
        fprintf(stderr, "Could not allocate memory for skill trees "
                        "in class_init_skills\n");
        return EXIT_FAILURE;
    }
    if (class->combat == NULL || class->noncombat == NULL) {
        fprintf(stderr, "Could not allocate memory for skill inventories"
                        "in class_init_skills\n");
        return EXIT_FAILURE;
    }
    if (class_prefab_add_skills(class) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* See class_prefabs.h */
int class_prefab_add_skills(class_t* class) {
    /* 
     * TODO: If we ever develop a "class prototype struct" with a pointer to an
     * init_skill() function, this if-else ladder should be replaced with a call
     * to that function.
     */
    int init_success = 0;

    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, class->name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);
    
    if (!strncmp(temp_name, "bard", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "druid", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "elementalist", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "knight", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "monk", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "ranger", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "rogue", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "sorcerer", MAX_NAME_LEN)) {
        /* TODO */
    }

    else if (!strncmp(temp_name, "warrior", MAX_NAME_LEN)) {
        /* TODO */ 
    }
        

    else if (!strncmp(temp_name, "wizard", MAX_NAME_LEN)) {
        /* TODO */
    }
    
    else {
        fprintf(stderr, "Could not find class for skill inventories "
                        "in class_skills_init\n");
        return EXIT_FAILURE;
    }

    return SUCCESS;
}
