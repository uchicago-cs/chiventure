/*
 * functions that set up the basic skills for the classes
 *
 * for more information see class_skills.h
 */
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

/* see class_skills.h */
int get_default_ranger(class_t* class) {

}

/* see class_skills.h */
int get_default_rogue(class_t* class) {

}

/* see class_skills.h */
int get_default_monk(class_t* class) {

}

/* see class_skills.h */
int get_default_sorcerer(class_t* class) {

}

/* see class_skills.h */
int get_default_druid(class_t* class) {

}

/* see class_skills.h */
int get_default_elementalist(class_t* class) {

}

/* see class_skills.h */
int get_default_bard(class_t* class) {

    return 0;
}

/* see class_skills.h */
int get_default_wizard(class_t* class) {

}

/* see class_skills.h */
int get_default_knight(class_t* class) {

}