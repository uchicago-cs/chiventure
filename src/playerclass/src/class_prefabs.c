
#include <ctype.h>
#include <stdio.h> 
#include <stdarg.h>

#include "playerclass/class_prefabs.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"
#include "common/ctx.h"
#include "libobj/obj.h"
#include "game-state/stats.h"
#include "common/uthash.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltree.h" 
#include "skilltrees/inventory.h"

/* Rudimentary id system for prefab classes (internal) */

/* Default Classes in alphabetical order. 
 * Currently, we have NPC classes and Playerclasses all integrated inside of playerclass.
 * For the future, we may want to consider refactoring these out to seperate modules. This 
 * is because reasonably, we might expect NPC stats to differ sparsly with player stats, with
 * room for different actionable characteristics. One additional solution to this may also 
 * be to just add additional stats that are more tailored to NPC/friendly classes.
 */
const char* const DEFAULT_CLASS_NAMES[] = {
    // Here are Player-specific playerclasses
    "bard",
    "monk",
    "ranger",
    "rogue",
    "warrior",
    "wizard",
    "druid",
    "elementalist",
    "knight",
    "sorceror",
    
    // Here are NPC-specifc playerclasses
    "alchemist",
    "basic",
    "chef",
    "fisherman",
    "healer",
    "lord",
    "shopkeeper"
};

/* Number of predefined default classes (see above). */
const int DEFAULT_CLASS_COUNT = 17;

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
    strncpy(temp_name, name, MAX_NAME_LEN + 1);
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
    obj_t* attributes = obj_new("attributes");
    stats_hash_t* stats = NULL;
    /* effects for each class not yet provided, so this will remain NULL */
    effects_hash_t* effects = NULL;


    /*-----------------------------------------------------------------
     *-------------------Player-specific prefabs-----------------------
     *-----------------------------------------------------------------
     */

    /* Bard stats:
     * 15 Health
     * 15 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 20 Magic Defense
     * 20 Magic Attack
     * 20 Max Mana */ 
    if (!strncmp(temp_name, "bard", MAX_NAME_LEN)) {
        short_desc = "A skilled musician and magician.";
        long_desc = "The Bard combines their skill as a magician and musician "
                    "to support their allies or vanquish their foes.";
        set_stats_hashtable(game, &stats, 15, 15, 5, 5, 5, 20, 20, 20);
    }

    /* Basic class stats:
     * 25 Max Health
     * 5 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 5 Magic Defense
     * 5 Magic Attack
     * 5 Max Mana 
     * These stats can be off the scale stupid because why not? This is a placeholder class */ 
    else if (!strncmp(temp_name, "basic", MAX_NAME_LEN)) {
        short_desc = "An ordinary person.";
        long_desc = "This is just an ordinary human being. There's nothing special about this guy.";
        set_stats_hashtable(game, &stats, 25, 5, 5, 5, 5, 5, 5, 5);
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
        long_desc = "The Monk is an expert of unarmed combat, and, through their "
                    "training--in accordance with their strict spirituality--have "
                    "learned how to defend themselves from attackers.";
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
        long_desc = "The ranger is the embodiment of an apex predator: while they may "
                    " tend to lurk away from civilisation in the wild, they are a "
                    "skilled killer and have no qualms about doing so.";
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
        long_desc = "The Rogue embodies stealth. They are feared by many, and "
                    "for good reason. They use their exceptional speed and "
                    "agility to surprise their enemies and attack when least expected.";
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
        long_desc = "The Warrior is an elite, battle-hardened fighter who excels in physical combat.";
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
        long_desc = "The Wizard is a master of the arcane; a formidable wielder" 
                    "of magic, and an academic whose studies delve into its "
                    "secrets.";
        set_stats_hashtable(game, &stats, 10, 10, 5, 5, 10, 20, 25, 25);
    }

    /*-----------------------------------------------------------------
     *-------------------Player-specific prefabs-----------------------
     *-----------------------------------------------------------------
     */

    /* Alchemist stats:
     * 10 Max Health
     * 20 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 10 Ranged Attack
     * 20 Magic Defense
     * 25 Magic Attack
     * 35 Max Mana */ 
    else if (!strncmp(temp_name, "alchemist", MAX_NAME_LEN)) {
        short_desc = "A skillfull alchemist.";
        long_desc = "The Alchemist is a connoisseur of all things potions, a wise "
                    "and academic who devotes his life to the craft of alchemy. Creator "
                    "of arcanic liquids, usable for devious and healing aspects alike, the "
                    "Alchemist is a precise magician with magical utilities.";
        set_stats_hashtable(game, &stats, 10, 20, 5, 5, 10, 20, 25, 35);
    }

    /* Chef stats:
     * 10 Max Health
     * 20 Speed
     * 5 Physical Defense
     * 25 Physical Attack
     * 5 Ranged Attack
     * 5 Magic Defense
     * 5 Magic Attack
     * 5 Max Mana */ 
    else if (!strncmp(temp_name, "chef", MAX_NAME_LEN)) {
        short_desc = "A swift chef.";
        long_desc = "The Chef is a master of the knife, artist of the kitchen. Speedy, aggressive, "
                    "and efficient, the chef prepares the most exquisite foods from across the globe, "
                    "ranging from salads to proteins to desserts. These nutritional meals offer bonuses "
                    "to your current stats, making you beefier, more magical, or faster.";
        set_stats_hashtable(game, &stats, 10, 20, 5, 25, 5, 5, 5, 5);
    }

    /* Fisherman stats:
     * 10 Max Health
     * 15 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 5 Magic Defense
     * 5 Magic Attack
     * 5 Max Mana */ 
    else if (!strncmp(temp_name, "fisherman", MAX_NAME_LEN)) {
        short_desc = "A patient fisherman.";
        long_desc = "The Fisherman is a resourceful provider who plays an important role in providing "
                    "sustenance for their village.";
        set_stats_hashtable(game, &stats, 10, 15, 5, 5, 5, 5, 5, 5);
    }

    /* Shopkeeper stats:
     * 10 Max Health
     * 10 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 5 Magic Defense
     * 5 Magic Attack
     * 5 Max Mana */ 
    else if (!strncmp(temp_name, "shopkeeper", MAX_NAME_LEN)) {
        short_desc = "A dedicated store manager.";
        long_desc = "The Shopkeeper is a resourceful merchant who provides many eclectic items "
                    "available for trade.";
        set_stats_hashtable(game, &stats, 10, 10, 5, 5, 5, 5, 5, 5);
    }
    /* Lord stats:
     * 10 Max Health
     * 10 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 10 Magic Defense
     * 10 Magic Attack
     * 5 Max Mana */ 
    else if (!strncmp(temp_name, "lord", MAX_NAME_LEN)) {
        short_desc = "An all powerful master.";
        long_desc = "The Lord is a powerful master that has magical abilities to "
                    "save those in the village who deserve it, or damage those who "
                    "do harm" ;
        set_stats_hashtable(game, &stats, 10, 10, 5, 5, 5, 10, 10, 5);
    }
    /* Healer stats:
     * 10 Max Health
     * 5 Speed
     * 10 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 10 Magic Defense
     * 5 Magic Attack
     * 10 Max Mana */ 
    else if (!strncmp(temp_name, "healer", MAX_NAME_LEN)) {
        short_desc = "A patient healer.";
        long_desc = "The healer is a powerful and magical witch that has magical abilities to "
                    "save anyone in the village that has been injured.";
        set_stats_hashtable(game, &stats, 10, 5, 10, 5, 5, 10, 5, 10);
    }
    /* Druid stats:
     * 15 Max Health
     * 5 Speed
     * 10 Physical Defense
     * 10 Physical Attack
     * 10 Ranged Attack
     * 30 Magic Defense
     * 30 Magic Attack
     * 25 Max Mana */

    else if (!strncmp(temp_name, "druid", MAX_NAME_LEN)) {
        short_desc = "A Druid.";
        long_desc = "Members of the high-ranking class in ancient Celtic "
                    "cultures, Druids were religious leaders as well as "
                    "adjudicators, and medical professionals.";
        set_stats_hashtable(game, &stats, 15, 5, 10, 10, 10, 30, 30, 25);
    }
    /* Elementalist stats:
     * 20 Max Health
     * 5 Speed
     * 10 Physical Defense
     * 10 Physical Attack
     * 10 Ranged Attack
     * 20 Magic Defense
     * 20 Magic Attack
     * 20 Max Mana */
    else if (!strncmp(temp_name, "elementalist", MAX_NAME_LEN)) {
        short_desc = "An Elementalist.";
        long_desc = "Multi faceted spellcasters who channel elemental forces, "
                    "making fire, air, earth, and water do their bidding.";
        set_stats_hashtable(game, &stats, 20, 5, 10, 10, 10, 20, 20, 20);
    }
    /* Knight stats:
     * 40 Max Health
     * 30 Physical Defense
     * 30 Physical Attack
     * 10 Ranged Attack
     * 0 Magic Defense
     * 0 Magic Attack
     * 20 Max Mana */
    else if (!strncmp(temp_name, "knight", MAX_NAME_LEN)) {
        short_desc = "A brave Knight.";
        long_desc = "Professional cavalry warriors, some of whom were vassals " 
                    "holding lands as fiefs from the lords in whose armies they" 
                    " served";
        set_stats_hashtable(game, &stats, 40, 20, 30, 30, 10, 0, 0, 20);
    }
    /* Sorceror stats:
     * 15 Max Health
     * 10 Speed
     * 5 Physical Defense
     * 10 Physical Attack
     * 5 Ranged Attack
     * 25 Magic Defense
     * 20 Magic Attack
     * 25 Max Mana */
    else if (!strncmp(temp_name, "sorceror", MAX_NAME_LEN)) {
        short_desc = "A slick Sorceror.";
        long_desc = "Young master of the mystic arts; inherits talent and"
                    " battle prowess from their family";
        set_stats_hashtable(game, &stats, 15, 10, 5, 10, 5, 25, 20, 25);
    }
    else {
        fprintf(stderr, "Could not find class name: \"%s\" "
                        "in class_prefab_new\n", class_name);
    }

    return class_new(class_name, short_desc, long_desc, attributes, stats, 
                    effects);
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
    class->starting_skills = inventory_new(max_active_skills, 
                                           max_passive_skills);
    
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
 *  - player_classes: a list of player classes that the skill node belongs to
 *  - num_classes: number of classes in the player_classes list
 *  - (...): Indices of the skills that are prereqs to this skill (note that 
 *           skills are added in order, starting at index 0).
 *         
 * Returns:
 *  - SUCCESS on success.
 *  - FAILURE on failure.
 */
int add_skill(class_t* class, skill_t* skill, int prereq_count, 
                unsigned int prereq_level, bool is_starting, 
                char** player_classes, int num_classes, ...) {
    if (class == NULL || skill == NULL)
        return FAILURE;

    skill_node_t* node = skill_node_new(skill, prereq_count, prereq_level, 
                                        player_classes, num_classes, 
                                        (int) UI_NODE_SIZE);

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

    /* 
     * A simple linear tree for the bard class.
     *
     * starting skill: bard_magic_word 
     *  - active: deals 6 damage.
     * bard_magic_word -> bard_poetic_line
     *  - active: deals 12 damage.
     * bard_poetic_line -> bard_enchanted_stanza
     *  - active: deals 18 damage.
     */
    if (!strncmp(temp_name, "bard", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;
        
        /* Currently point to null effects */
        /* Skills */
        skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Magic Word", 
                                     "You deal damage to your opponent with " 
                                     "just a word.", 1, 75, NULL, NULL);
        skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Poetic Line", 
                                     "A full line of poetry hits your " 
                                     "opponent!", 1, 200, NULL, NULL);
        skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Enchanted Stanza", 
                                     "The full weight of your stanza strikes "
                                     "your opponent!", 1, 325, NULL, NULL);

        /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }


    else if (!strncmp(temp_name, "basic", MAX_NAME_LEN)){
        /* these guys potentially could have a prefabricated, basic skill to match the class
         * for now we will just have no skills */
        return SUCCESS;
    }

    /* 
     * A simple linear tree for a monk class
     *
     * starting skill: acrobatic_powers
     *  - active: deals 7 damage.
     * acrobatic_powers -> spirit_of_strength
     *  - active: deals 14 damage.
     * spirit_of_strength-> supernova_circle
     *  - active: deals 21 damage.
     */
    else if (!strncmp(temp_name, "monk", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;
        
        /* Currently point to null effects */
        /* Skills */
        skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Acrobatic Powers", 
                                    "enhanced dexterity to surprise your opponent"
                                    " with unique kicks and movements.", 1, 120, 
                                     NULL, NULL);                          
        skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Spirit of Strength", 
                                    "Uses inner spirit and peace to unleash "
                                     "powerful hits and kicks!", 1, 220, 
                                     NULL, NULL);
        skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Supernova Circle", 
                                    "Powerful circular motions that allows for " 
                                    "the most powerful jumps, kicks, and "
                                    "punchess!",
                                     1, 420, NULL, NULL);

        /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }
    
    /* 
     * A simple linear tree for the rogue class.
     *
     * starting skill: rogue_quick_hit 
     *  - active: deals 5 damage.
     * rogue_quick_hit -> rogue_backstab
     *  - active: deals 12 damage.
     * rogue_backstab -> rogue_leg_swipe
     *  - active: deals 21 damage.
     */
    else if (!strncmp(temp_name, "rogue", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;
        
        /* Currently point to null effects */
        /* Skills */
        skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Quick Hit", 
                                     "You hit your opponent with a quick jab.",
                                      1, 125, NULL, NULL);
        skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Backstab", 
                                     "You attack your opponent from behind, "
                                     "catching them by surprise!", 1, 250, 
                                     NULL, NULL);
        skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Leg Swipe", 
                                     "You knock your opponent’s legs out from "
                                     "under them, bringing them to the"
                                     "ground!", 1, 375, NULL, NULL);

        /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }

    /* 
     * A simple linear tree for the warrior class.
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
                                     "You slash your sword.", 1, 69, 
                                     NULL, NULL);
        skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Double Slash", 
                                     "You slash your sword, twice!", 1, 269, 
                                     NULL, NULL);
        skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Triple Slash", 
                                     "You slash your sword, thrice!", 1, 369, 
                                     NULL, NULL);

        /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }
    /* 
     * A simple linear tree for the wizard class
     *
     * starting skill: blinding_charm
     *  - active: deals 4 damage.
     * blinding_charm -> paralyze_spell
     *  - active: deals 9 damage.
     * paralyze_spell -> arcane_explosion
     *  - active: deals 24 damage.
     */
    else if (!strncmp(temp_name, "wizard", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;
        
        /* Currently point to null effects */
        /* Skills */
        skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Blinding Charm", 
                                     "You blinded your opponent.", 1, 100, 
                                     NULL, NULL);
        skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Paralyze Spell", 
                                     "Your opponent is paralyzed!", 1, 150, 
                                     NULL, NULL);
        skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Arcane Explosion", 
                                     "A powerful spell that causes a massive" 
                                     "explosion with high area damage!", 1, 
                                     200, NULL, NULL);

        /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    } /*
    * A simple linear tree for a ranger class
    *
    * starting skill: close_shot
    *  - active: deals 3 damage.
    * close_shot -> midrange_shot
    *  - active: deals 12 damage.
    * midrange_shot -> long_shot
    *  - active: deals 25 damage.
    */
    else if (!strncmp(temp_name, "ranger", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;
      
       /* Currently point to null effects */
       /* Skills */
       skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Close Shot",
                                    "You hit a weak, but close shot.", 1, 130,
                                    NULL, NULL);                         
       skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "Mid-range Shot",
                                    "You hit a further, and stronger, shot!", 
                                    1, 220, NULL, NULL);
       skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "Long Shot",
                                    "You hit a long, damaging shot!", 1, 400,      
                                    NULL, NULL);
 
       /* Add skills to tree */
       add_skill(class, skill_0, 0, 25, true, NULL, 0);
       add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
       add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
   }

    /*
    * A simple linear tree for a druid class
    *
    * starting skill: frostbite
    *  - active: deals 3 damage.
    * frostbite -> control_flames
    *  - active: deals 12 damage.
    * control_flames -> flame_blade
    *  - active: deals 25 damage.
    */
    else if (!strncmp(temp_name, "druid", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;

       /* Currently point to null effects */
       /* Skills */
       skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "frostbite",
                                    "weak but cold frostbite", 1, 100,
                                    NULL, NULL);                         
       skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "control flames",
                                    "you burned your opponent, stronger effect",
                                     1, 200,
                                    NULL, NULL);
       skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "flame blade",
                                    "you sliced your opponent with fire!", 1, 400,      
                                    NULL, NULL);

       /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }

    /*
    * A simple linear tree for a elementalist class
    *
    * starting skill: stone shards
    *  - active: deals 5 damage.
    * stone shards -> Lightning arc
    *  - active: deals 17 damage.
    * lightning arc -> dragon's tooth
    *  - active: deals 20 damage.
    */
    else if (!strncmp(temp_name, "elementalist", MAX_NAME_LEN)) {
       class_allocate_skills(class, 3, 3, 0);
       sid_t skill_id = class->skilltree->tid * 100;

       /* Currently point to null effects */
       /* Skills */
       skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "stone shards",
                                    "A hail of stone shards!", 1, 120,
                                    NULL, NULL);                         
       skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "arc lightning",
                                    "A lightning arc is casted at your enemy!", 
                                    1, 220,
                                    NULL, NULL);
       skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "dragon's tooth",
                                    "An explosive tooth of a Dragon is used on" 
                                    " your enemy.", 1, 320,      
                                    NULL, NULL);

       /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }

   /*
    * A simple linear tree for a Knight class
    *
    * starting skill: holy strike
    *  - active: deals 5 damage.
    * holy strike -> shield strike
    *  - active: deals 10 damage.
    * shield strike -> shackle strike
    *  - active: deals 25 damage.
    */
    else if (!strncmp(temp_name, "knight", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
       sid_t skill_id = class->skilltree->tid * 100;

       /* Currently point to null effects */
       /* Skills */
       skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "holy strike",
                                    "The knight delivers a holy strike!", 1, 100,
                                    NULL, NULL);                         
       skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "shield strike",
                                    "Strikes enemy with shield!", 1, 250,
                                    NULL, NULL);
       skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "shackle strike",
                                    "Strikes enemy with his shackle", 1, 350,      
                                    NULL, NULL);

        /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }

    /*
    * A simple linear tree for a Sorceror class
    *
    * starting skill: dark magic
    *  - active: deals 5 damage.
    * dark magic -> moon storm
    *  - active: deals 12 damage.
    * moon storm -> gates of rashonmon
    *  - active: deals 23 damage.
    */
    else if (!strncmp(temp_name, "sorceror", MAX_NAME_LEN)) {
        class_allocate_skills(class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100;

       /* Currently point to null effects */
       /* Skills */
       skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "dark magic",
                                    "The sorceror activates dark magic!", 1, 100,
                                    NULL, NULL);                         
       skill_t* skill_1 = skill_new(skill_id++, ACTIVE, "moon storm",
                                    "Strikes enemy with moon storm!", 1, 200,
                                    NULL, NULL);
       skill_t* skill_2 = skill_new(skill_id++, ACTIVE, "gates of rashonmon",
                                    "Strikes enemy with the gates of rashonmon", 
                                    1, 300,      
                                    NULL, NULL);

       /* Add skills to tree */
        add_skill(class, skill_0, 0, 25, true, NULL, 0);
        add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    }

    else {
        fprintf(stderr, "Could not find class for skill inventories "
                        "in class_prefab_add_skills\n");
        return EXIT_FAILURE;
    }

    return SUCCESS;
}
