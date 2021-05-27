
#include <ctype.h>
#include <stdio.h> 
#include <stdarg.h>

#include "playerclass/class_prefabs.h"
<<<<<<< HEAD
#include "playerclass/class.h"
#include "playerclass/class_structs.h"
#include "common/ctx.h"
#include "libobj/obj.h"
#include "game-state/stats.h"
#include "common/uthash.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltree.h" 
#include "skilltrees/inventory.h"
=======
>>>>>>> 01b82415209275f45e4bbbb14192f8a25b985e8a

/* Rudimentary id system for prefab classes (internal) */

/* Default Classes in alphabetical order. */
const char* const DEFAULT_CLASS_NAMES[] = {
    "bard",
    "monk",
    "ranger",
    "rogue",
    "warrior",
    "wizard"
};

/* Number of predefined default classes (see above). */
const int DEFAULT_CLASS_COUNT = 6;

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
 *  - game: The chiventure game struct (it contains the global stat hashtable, 
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
int check_and_add_stat(game_t* game, stats_hash_t** stats, char *stat_name, 
                       double stat_val, double stat_max) {
                    
    if (game == NULL) {
        fprintf(stderr, "game (game_t*) is NULL \n");
        return FAILURE;

    } else if (stats == NULL) {
        fprintf(stderr, "Stats (stats_hash_t**) is NULL \n");
        return FAILURE;

    } else if (stat_name == NULL) {
        fprintf(stderr, "Stat_name (char* ) is NULL \n");
        return FAILURE;
    }

    stats_global_t *global_stat;
    HASH_FIND_STR(game->curr_stats, stat_name, global_stat);
    if (global_stat == NULL) {
        global_stat = stats_global_new(stat_name, stat_max);
        HASH_ADD_STR(game->curr_stats, name, global_stat);
    }

    add_stat(stats, stats_new(global_stat, stat_val));
    return SUCCESS;
}

/*
 * Safely adds a stat to a stat hashtable, checking and updating the global stat
 * hashtable if necessary.
 *
 * Parameters: 
 *  - ctx: The chiventure game struct (it contains the global stat hashtable, 
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
int set_stats_hashtable(game_t* game, stats_hash_t** stats,
                        double max_health, 
                        double speed,
                        double physical_defense, 
                        double physical_attack,
                        double ranged_attack,
                        double magic_defense,
                        double magic_attack,
                        double max_mana) {
    if (game == NULL || stats == NULL)
        return FAILURE;

    check_and_add_stat(game, stats, "max_health", max_health, 100);
    check_and_add_stat(game, stats, "speed", speed, 100);
    check_and_add_stat(game, stats, "physical_defense", physical_defense, 100);
    check_and_add_stat(game, stats, "physical_attack", physical_attack, 100);
    check_and_add_stat(game, stats, "ranged_attack", ranged_attack, 100);
    check_and_add_stat(game, stats, "magic_defense", magic_defense, 100);
    check_and_add_stat(game, stats, "magic_attack", magic_attack, 100);
    check_and_add_stat(game, stats, "max_mana", max_mana, 100);
    
    return SUCCESS;
}

/* See class_prefabs.h */
class_t* class_prefab_new(game_t* game, char* class_name) {
    char temp_name[MAX_NAME_LEN + 1]; 
    strncpy(temp_name, class_name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);
    
    char* short_desc;
    char* long_desc;
    /* attributes are not yet customized by each class */
    obj_t* attributes = obj_new("class_attributes");
    stats_hash_t* stats = NULL;
    /* effects for each class not yet provided, so this will remain NULL */
    effects_hash_t* effects = NULL;

    /* Bard stats:
     * 15 Max Health
     * 15 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 20 Magic Defense
     * 20 Magic Attack
     * 20 Max Mana */ 
    if (!strncmp(temp_name, "bard", MAX_NAME_LEN)) {
        short_desc = "A skilled musician and magician.";
        long_desc = "The Bard combines their skill as a magician and musician to support their allies or vanquish their foes.";
        set_stats_hashtable(game, &stats, 15, 15, 5, 5, 5, 20, 20, 20);
    }

    /* Monk stats:
     * 25 Max Health
     * 20 Speed
     * 15 Physical Defense
     * 15 Physical Attack
     * 5 Ranged Attack
     * 20 Magic Defense
     * 5 Magic Attack
     * 5 Max Mana */ 
    else if (!strncmp(temp_name, "monk", MAX_NAME_LEN)) {
        short_desc = "An elite martial artist.";
        long_desc = "The Monk is an expert of unarmed combat, and, through their training-- "
                    "in accordance with their strict spirituality--have learned how to defend themselves from attackers.";
        set_stats_hashtable(game, &stats, 25, 20, 15, 15, 5, 20, 5, 5);
    }

    /* Ranger stats:
     * 10 Max Health
     * 20 Speed
     * 10 Physical Defense
     * 15 Physical Attack
     * 25 Ranged Attack
     * 10 Magic Defense
     * 10 Magic Attack
     * 10 Max Mana */
    else if (!strncmp(temp_name, "ranger", MAX_NAME_LEN)) {
        short_desc = "A master hunter.";
        long_desc = "The ranger is the embodiment of an apex predator: while they may tend to lurk away "
                    "from civilisation in the wild, they are a skilled killer and have no qualms about doing so.";
        set_stats_hashtable(game, &stats, 10, 20, 10, 15, 25, 10, 10, 10);
    }

    /* Rogue stats:
     * 10 Max Health
     * 25 Speed
     * 15 Physical Defense
     * 15 Physical Attack
     * 15 Ranged Attack
     * 10 Magic Defense
     * 5 Magic Attack
     * 15 Max Mana */
    else if (!strncmp(temp_name, "rogue", MAX_NAME_LEN)) {
        short_desc = "A sibling of the shadows.";
        long_desc = "The Rogue embodies stealth. They are feared by many, and for good reason. "
                    "They use their exceptional speed and agility to surprise their enemies and attack when least expected.";
        set_stats_hashtable(game, &stats, 10, 25, 15, 15, 15, 10, 5, 15);
    }

    /* Warrior stats:
     * 20 Max Health
     * 15 Speed
     * 20 Physical Defense
     * 25 Physical Attack
     * 10 Ranged Attack
     * 10 Magic Defense
     * 5 Magic Attack
     * 5 Max Mana */
    else if (!strncmp(temp_name, "warrior", MAX_NAME_LEN)) {
        short_desc = "A mighty warrior.";
        long_desc = "An elite, battle-hardened fighter who excels in physical combat.";
        set_stats_hashtable(game, &stats, 20, 15, 20, 25, 10, 10, 5, 5);
    }

    /* Wizard stats:
     * 10 Max Health
     * 10 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 10 Ranged Attack
     * 20 Magic Defense
     * 25 Magic Attack
     * 25 Max Mana */ 
    else if (!strncmp(temp_name, "wizard", MAX_NAME_LEN)) {
        short_desc = "A learned wizard.";
        long_desc = "The Wizard is a master of the arcane; a formidable wielder of magic, "
                    "and an academic whose studies delve into its secrets.";
        set_stats_hashtable(game, &stats, 10, 10, 5, 5, 10, 20, 25, 25);
    }

    else {
        fprintf(stderr, "Could not find class name: \"%s\" "
                        "in class_prefab_new\n", class_name);
        return NULL;
    }

    return class_new(class_name, short_desc, long_desc, attributes, stats, effects);
}

/* Skill related functions */

/* 
 * Skills are in a weird place right now: The skill trees team is interested in
 * changing the way skill effects are implemented, so everything in here is
 * subject to change.  
 * 
 * Right now, skill effects take in some theoretical number of string arguments,
 * and return some output to be parsed by the CLI.  However, the CLI doesn't 
 * actually have the ability to parse this stuff yet.
 * 
 * In the future, we would like skill effect functions to do more than simply
 * return a message describing what to do.  Perhaps they could receive pointers
 * to chiventure_ctx, or to the player or targets etc.  That way, they could
 * modify those structs.
 */

const unsigned int UI_NODE_SIZE = 75;

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
    class->starting_skills = inventory_new(max_active_skills, max_passive_skills);
    
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
    if (class->starting_skills == NULL) {
        fprintf(stderr, "Could not allocate memory for skill inventory"
                        "in class_allocate_skills\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Safely adds a skill to the class's skilltree, and skill inventory if needed.
 *
 * Parameters: 
 *  - class: A pointer to the class. Must not be NULL.
 *  - skill: A pointer to the skill being added. Must not be NULL.
 *  - prereq_count: The number of prereqs the skill has.
 *  - prereq_level: The pre_req level required to level the skill.
 *  - is_starting: true if the skill is a starting skill for the class.
 *  - (...): Indices of the skills that are prereqs to this skill (note that 
 *           skills are added in order, starting at index 0).
 *         
 * Returns:
 *  - SUCCESS on success.
 *  - FAILURE on failure.
 */
int add_skill(class_t* class, skill_t* skill, int prereq_count, 
                unsigned int prereq_level, bool is_starting, ...) {
    if (class == NULL || skill == NULL)
        return FAILURE;

    skill_node_t* node = skill_node_new(skill, prereq_count, prereq_level, UI_NODE_SIZE);

    /* Citation: (https://jameshfisher.com/2016/11/23/c-varargs/) */
    va_list prereq_p;
    va_start(prereq_p, is_starting);
    for (int i = 0; i < prereq_count; i++) {
        int index = va_arg(prereq_p, int);
        node_prereq_add(node, class->skilltree->nodes[index], prereq_level);
    }
    va_end(prereq_p);

    skill_tree_node_add(class->skilltree, node);

    if (is_starting)
        inventory_skill_acquire(class->skilltree, class->starting_skills, skill);
    return SUCCESS;
} 

/* See class_prefabs.h */
int class_prefab_add_skills(class_t* class) {
    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, class->name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);

    /* Note: All skills are combat skills for now */
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

    /* 
     * A simple linear tree for a simple class.
     *
     * starting skill: warrior_sword_slash 
     *  - active: deals 8 damage.
     * warrior_sword_slash -> warrior_double_slash
     *  - active: deals 16 damage.
     * warrior_double_slash -> warrior_triple_slash
     *  - active: deals 24 damage.
     */
    else if (!strncmp(temp_name, "warrior", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;
        
        /* Currently point to null effects */
        /* Skills */
        skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Sword Slash", 
                                     "You slash your sword.", 1, 100, 
                                     NULL);
        skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Double Slash", 
                                     "You slash your sword, twice!", 1, 200, 
                                     NULL);
        skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Triple Slash", 
                                     "You slash your sword, thrice!", 1, 400, 
                                     NULL);

        /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true);
        add_skill(class, skill_1, 1, 50, false, 0);
        add_skill(class, skill_2, 1, 34, false, 1);
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
