
#include <ctype.h>
#include <stdio.h> 

#include "playerclass/class_prefabs.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"
#include "common/ctx.h"
#include "libobj/obj.h"
#include "game-state/stats.h"
#include "common/uthash.h"

/* Rudimentary id system for prefab classes (internal) */

/* Default Classes in alphabetical order. */
const char* const DEFAULT_CLASS_NAMES[] = {
    "bard",
    "druid",
    "elementalist",
    "knight",
    "monk",
    "ranger",
    "rogue",
    "sorcerer",
    "warrior",
    "wizard",
};

/* Number of predefined default classes (see above). */
const int DEFAULT_CLASS_COUNT = 10;

/*
 * Determines the index of name in the DEFAULT_CLASS_NAMES array, for use as an
 * internal id.
 * 
 * Parameters
 *  - name: The name of the class.  Case sensitive.
 * 
 * Returns:
 *  - The index of the name in the DEFAULT_CLASS_NAMES array. Returns -1 if the 
 *    name does not appear or is NULL.
 */
int get_class_name_index(char* name) {
    if (name == NULL)
        return -1;

    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);

    for (int i = 0; i < DEFAULT_CLASS_COUNT; i++) 
        if (strncmp(temp_name, DEFAULT_CLASS_NAMES[i], MAX_NAME_LEN) == 0) 
            return i;

    return -1;
}

/*
 * Safely adds a stat to a stat hashtable, checking and updating the global stat
 * hashtable if necessary.
 *
 * Parameters: 
 *  - ctx: The chiventure context object (it contains the global stat hashtable, 
 *         but that can be NULL).
 *  - stats: A pointer to a possibly NULL stats_hash_t pointer. The new stat is
 *           added, and the intermediate pointer updated if necessary.
 *  - stat_name: A pointer to the name of the stat, case sensitive.
 *  - stat_val: The base value of the stat.
 *  - stat_max: The maximum value of the stat, only applies if the stat is not 
 *              yet on the global hash table.
 * 
 * Returns:
 *  - SUCCESS on success. stats and the global hashtable now contain the stat.
 *  - FAILURE on failure.
 */
int check_and_add_stat(chiventure_ctx_t* ctx, stats_hash_t** stats, 
                       char *stat_name, double stat_val, double stat_max) {
    if (ctx == NULL || stats == NULL || stat_name == NULL)
        return FAILURE;

    stats_global_t *global_stat;
    HASH_FIND_STR(ctx->game->curr_stats, stat_name, global_stat);
    if (global_stat == NULL) {
        global_stat = stats_global_new(stat_name, stat_max);
        HASH_ADD_KEYPTR(hh, ctx->game->curr_stats, stat_name, strlen(stat_name), global_stat);
    }

    add_stat(stats, stats_new(global_stat, stat_val));
    return SUCCESS;
}

/*
 * Safely adds a stat to a stat hashtable, checking and updating the global stat
 * hashtable if necessary.
 *
 * Parameters: 
 *  - ctx: The chiventure context object (it contains the global stat hashtable, 
 *         but that can be NULL).
 *  - stats: A pointer to a possibly NULL stats_hash_t pointer. The new stats
 *           are added, and the intermediate pointer updated if necessary.
 *  - max_health, speed, physical_defense, physical_attack, ranged_attack,
 *    magic_defense, magic_attack, max_magic_energy: The base stat values.
 * 
 * Returns:
 *  - SUCCESS on success. stats and the global hashtable now contain the stats.
 *  - FAILURE on failure.
 */
int set_stats_hashtable(chiventure_ctx_t* ctx, stats_hash_t** stats,
                         double max_health, 
                         double speed,
                         double physical_defense, 
                         double physical_attack,
                         double ranged_attack,
                         double magic_defense,
                         double magic_attack,
                         double max_magic_energy) {
    if (ctx == NULL || stats == NULL)
        return FAILURE;

    check_and_add_stat(ctx, stats, "max_health",       max_health,       100);
    check_and_add_stat(ctx, stats, "speed",            speed,            100);
    check_and_add_stat(ctx, stats, "physical_defense", physical_defense, 100);
    check_and_add_stat(ctx, stats, "physical_attack",  physical_attack,  100);
    check_and_add_stat(ctx, stats, "ranged_attack",    ranged_attack,    100);
    check_and_add_stat(ctx, stats, "magic_defense",    magic_defense,    100);
    check_and_add_stat(ctx, stats, "magic_attack",     magic_attack,     100);
    check_and_add_stat(ctx, stats, "max_magic_energy", max_magic_energy, 100);
    
    return SUCCESS;
}

/* See class_prefabs.h */
class_t* class_prefab_new(chiventure_ctx_t* ctx, char *class_name) {
    char temp_name[MAX_NAME_LEN + 1]; 
    strncpy(temp_name, class_name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);
    
    char* short_desc;
    char* long_desc;
    /* attributes are not yet customized at by each class */
    obj_t* attributes = obj_new("class_attributes");
    stats_hash_t* stats = NULL;
    /* effects for each class not yet provided, so this will remain NULL */
    effects_hash_t* effects = NULL;

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

    /* A hard hitting and beefy physical attacker:
     * 25 Max Health
     * 10 Speed
     * 15 Physical Defense
     * 25 Physical Attack
     *  5 Ranged Attack
     *  5 Magic Defense
     *  5 Magic Attack
     * 15 Max Magic Energy */
    else if (!strncmp(temp_name, "warrior", MAX_NAME_LEN)) {
        short_desc = "A mighty warrior.";
        long_desc = "A mighty yet noble warrior, skilled with the blade.";
        set_stats_hashtable(ctx, &stats, 25, 10, 15, 25, 5, 5, 5, 15);
    }
        
    else if (!strncmp(temp_name, "wizard", MAX_NAME_LEN)) {
        /* TODO */
    }

    else {
        fprintf(stderr, "Could not find class name: \"%s\" "
                        "in class_prefab_new\n", class_name);
        return NULL;
    }

    return class_new(temp_name, short_desc, long_desc, attributes, stats, effects);
}

/* Skill related functions */

/*
 * Initializes skill and skilltree related values for a player class.  Currently
 * only works for classes that match the name of one of our prefab classes.
 * 
 * Parameters:
 *  - class: a pointer to the class to be initialized.
 *  - max_skills_in_tree: the maximum number of skills in the class skilltree.
 *  - max_combat_skills: the maximum number of combat skills the class may have.
 *  - max_noncombat_skills: the maximum number of noncombat skills the class may
 *    have.
 * 
 * Returns:
 *  - EXIT_SUCCESS on successful initializtion.
 *  - EXIT_FAILURE otherwise.
 */
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
                        "in class_allocate_skills\n", class->name);
        return EXIT_FAILURE;
    }
    int tid = 3000 + class_id;
    class->skilltree = skill_tree_new(tid, class->name, max_skills_in_tree);

    if (class->skilltree == NULL) {
        fprintf(stderr, "Could not allocate memory for skill trees "
                        "in class_allocate_skills\n");
        return EXIT_FAILURE;
    }
    if (class->combat == NULL || class->noncombat == NULL) {
        fprintf(stderr, "Could not allocate memory for skill inventories"
                        "in class_allocate_skills\n");
        return EXIT_FAILURE;
    }
    if (class_prefab_add_skills(class) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

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
                        "in class_prefab_add_skills\n");
        return EXIT_FAILURE;
    }

    return SUCCESS;
}

/* Testing out how this might work
 * SAMPLE (we are probably not going to write a function per class) */
class_t* class_prefab_warrior(chiventure_ctx_t* ctx) {
    char* name = "Warrior"; 
    char* short_desc = "Guy with sword."; 
    char* long_desc = "Guy with sword. Guy hit thing in head with sword. Guy use " 
    "few words, sword is better than words.";
    
    obj_t* attributes = obj_new("class_attributes"); // Empty Attributes object (name could change)

    /* Stats */
    stats_hash_t *stats = NULL;
    check_and_add_stat(ctx, &stats, "moxie", 10, 100);
    check_and_add_stat(ctx, &stats, "blood-thirst", 97, 100);
    
    /* Effects: I don't know if we should put anything here yet. */
    effects_hash_t* effects = NULL; // This can actually stay NULL forever. The empty hashtable is represented by NULL in uthash.
    return class_new(name, short_desc, long_desc, attributes, stats, effects);
}
