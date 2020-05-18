#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skilltrees.h"

// Creates an empty list of passive and active skills to use in the game.
allskills_t* create_skill_list() {
    allskills_t* res = (allskills_t*)malloc(sizeof(allskills_t));
    if (res == NULL) {
        fprintf(stderr, "Invalid memory allocation in create_skill_list #1");
        exit(1);
    }

    res->cur_num_active = 0;
    res->cur_num_passive = 0;
    res->max_num_active = 5;
    res->max_num_passive = 5;
    skill_t** active_skills = (skill_t**)malloc(5 * sizeof(skill_t*));
    if (active_skills == NULL) {
        fprintf(stderr, "Invalid memory allocation in create_skill_list #2");
        exit(1);
    }
    skill_t** passive_skills = (skill_t**)malloc(5 * sizeof(skill_t*));
    if (passive_skills == NULL) {
        fprintf(stderr, "Invalid memory allocation in create_skill_list #3");
        exit(1);
    }
    res->active_skills = active_skills;
    res->passive_skills = passive_skills;

    // Make sure skills are initialized as null.
    for (int i = 0; i < 5; i++) {
        res->active_skills[i] = NULL;
        res->passive_skills[i] = NULL;
    }
    return res;
}

// Creates a new skill structure.
skill_t* new_skill(char* name, unsigned int cur_level, unsigned int experience,
                   char* description, int (*given_skill)(int, int)) {

    skill_t* res = (skill_t*)malloc(sizeof(skill_t));
    if (res == NULL) {
        fprintf(stderr, "Invalid memory allocation in new_skill");
        exit(1);
    }

    res->name = name;
    res->description = description;
    res->cur_level = cur_level;
    res->experience = experience;
    res->execute_skill = given_skill;
    return res;
}

// Frees a new skill
int free_skill(skill_t* skill) {
    free(skill);
    return 0;
}

// Frees all active skills in the skill list.
// Returns an error code.
int free_active_skills(allskills_t* list) {
    for (unsigned int i = 0; i < list->cur_num_active; i++) {
        int status = free_skill(list->active_skills[i]);
        if (status != 0) {
            return status;
        }
    }
    free(list->active_skills);
    return 0;
}

// Frees all passive skills in the skill list.
// Returns an error code.
int free_passive_skills(allskills_t* list) {
    for (unsigned int i = 0; i < list->cur_num_passive; i++) {
        int status = free_skill(list->passive_skills[i]);
        if (status != 0) {
            return status;
        }
    }
    free(list->passive_skills);
    return 0;
}

int free_all_skills(allskills_t* list) {
    int passive_status = free_passive_skills(list);
    if (passive_status != 0) {
        return passive_status;
    }
    int active_status = free_active_skills(list);
    if (active_status != 0) {
        return active_status;
    }
    free(list);
    return 0;
}

int push_active_skill(allskills_t* list, skill_t* skill) {
    if (list->cur_num_active < list->max_num_active) {
        list->active_skills[list->cur_num_active] = skill;
        list->cur_num_active += 1;
        return 0;
    } else if (list->cur_num_active == list->max_num_active) {
        list->active_skills = (skill_t**)realloc(
            list->active_skills, (list->max_num_active + 5) * sizeof(skill_t*));
        list->active_skills[list->cur_num_active] = skill;
        list->cur_num_active += 1;
        // Initialize all empty spaces in new list as null.
        for (unsigned int i = list->cur_num_active; i < list->max_num_active;
             i++) {
            list->active_skills[i] = NULL;
        }
        return 0;
    } else {
        // cur_num_active is somehow > max_num_active, which is a bug.
        return 1;
    }
}

int push_passive_skill(allskills_t* list, skill_t* skill) {
    if (list->cur_num_passive < list->max_num_passive) {
        list->passive_skills[list->cur_num_passive] = skill;
        list->cur_num_passive += 1;
        return 0;
    } else if (list->cur_num_passive == list->max_num_passive) {
        list->passive_skills = (skill_t**)realloc(
            list->passive_skills, (list->max_num_passive + 5)*sizeof(skill_t*));
        list->passive_skills[list->cur_num_passive] = skill;
        list->cur_num_passive += 1;
        for (unsigned int i = list->cur_num_passive; i < list->max_num_passive;
             i++) {
            list->passive_skills[i] = NULL;
        }
        return 0;
    } else {
        // cur_num_passive is somehow > max_num_passive, which is a bug.
        return 1;
    }
}

int has_active_skill(allskills_t* list, skill_t* skill) {
    for (unsigned int i = 0; i < list->cur_num_active; i++) {
        if (strcmp(list->active_skills[i]->name, skill->name) == 0) {
            return i;
        }
    }
    return -1;
}

int has_passive_skill(allskills_t* list, skill_t* skill) {
    for (unsigned int i = 0; i < list->cur_num_passive; i++) {
        if (strcmp(list->passive_skills[i]->name, skill->name) == 0) {
            return i;
        }
    }
    return -1;
}

int pop_active_skill(allskills_t* list, skill_t* skill) {
    int loc = has_active_skill(list, skill);
    if (loc == -1) {
        // Skill to be popped isn't in the active_skill list.
        return -1;
    } else {
        int status = free_skill(list->active_skills[loc]);
        if (status != 0) {
            return status;
        }
        list->active_skills[loc] = NULL; // Make sure nothing's left there.
        // To make sure we don't have empty pockets in our skill list, we
        // have to move the last skill in the full list to where we just
        // removed a skill.
        list->cur_num_active -= 1;
        list->active_skills[loc] = list->active_skills[list->cur_num_active];
        list->active_skills[list->cur_num_active] = NULL;
        return 0;
    }
}

int pop_passive_skill(allskills_t* list, skill_t* skill) {
    int loc = has_passive_skill(list, skill);
    if (loc == -1) {
        // Skill to be popped isn't in the passive_skill list.
        return -1;
    } else {
        int status = free_skill(list->passive_skills[loc]);
        if (status != 0) {
            return status;
        }
        list->passive_skills[loc] = NULL; // Make sure nothing's left there.
        // To make sure we don't have empty pockets in our skill list, we
        // have to move the last skill in the full list to where we just
        // removed a skill.
        list->cur_num_passive -= 1;
        list->passive_skills[loc] = list->passive_skills[list->cur_num_passive];
        list->passive_skills[list->cur_num_passive] = NULL;
        return 0;
    }
}



int test_skill(int param1, int param2) {
    printf("Testing test_skill: %i, %i\n", param1, param2);
    return 0;
}

int main() {
    char name[30] = "Hello";
    char description[50] = "Skill description"
    skill_t* our_struct = new_skill(name, 1, 0, description, &test_skill);
    int res = our_struct->execute_skill(1, 2);
    printf("Result: %i\n", res);
}
