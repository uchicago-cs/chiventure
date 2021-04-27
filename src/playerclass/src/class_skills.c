/*
 * functions that set up the basic skills for the classes
 *
 * for more information see class_skills.h
 */
#include <ctype.h>

#include "class_skills.h"
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

/* See class_skills.h */
int class_add_skills(class_t* class) {
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
