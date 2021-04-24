/*
 * functions that set up the basic skills for the classes
 *
 * for more information see class_skills.h
 */
#include <ctype.h>
#include <stdlib.h>

#include "class_skills.h"


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


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 bard
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_bard(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 druid
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_druid(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 elementalist
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_elementalist(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 knight
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_knight(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 monk
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_monk(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 ranger
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_ranger(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 rogue
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_rogue(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 sorcerer
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_sorcerer(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 warrior
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_warrior(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 wizard
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_wizard(class_t* class) {
    /* TODO */
    return SUCCESS;
}


/* See class_skills.h */
int class_skills_init(class_t* class) {
    /* 
     * TODO: If we ever develop a "class prototype struct" with a pointer to an
     * init_skill() function, this if-else ladder should be replaced with a call
     * to that function.
     */
    int init_success = 0;

    char* temp_name = (char *) calloc(MAX_NAME_LEN + 1, sizeof(char));
    strncpy(temp_name, class->name, MAX_NAME_LEN);
    // make temp_name lowercase
    for (char* ch_p = temp_name; *ch_p != '\0'; ch_p += sizeof(char)) 
        *ch_p = tolower(*ch_p);
    
    if (!strcmp(temp_name, "bard")) 
        init_success = get_default_bard(class);

    else if (!strcmp(temp_name, "druid")) 
        init_success = get_default_druid(class);

    else if (!strcmp(temp_name, "elementalist")) 
        init_success = get_default_elementalist(class);

    else if (!strcmp(temp_name, "knight")) 
        init_success = get_default_knight(class);

    else if (!strcmp(temp_name, "monk")) 
        init_success = get_default_monk(class);

    else if (!strcmp(temp_name, "ranger")) 
        init_success = get_default_ranger(class);

    else if (!strcmp(temp_name, "rogue")) 
        init_success = get_default_rogue(class);

    else if (!strcmp(temp_name, "sorcerer")) 
        init_success = get_default_sorcerer(class);

    else if (!strcmp(temp_name, "warrior")) 
        init_success = get_default_warrior(class);  

    else if (!strcmp(temp_name, "wizard")) 
        init_success = get_default_wizard(class);
    
    else 
        fprintf(stderr, "Could not find class for skill inventories "
                        "in class_skills_init\n");

    free(temp_name);
    return init_success;
}
