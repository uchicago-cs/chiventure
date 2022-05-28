/*
 * Enables players to have more than one class at the same time.
 *
 * For more information see multiclass_prefabs.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "playerclass/class_structs.h"
#include "playerclass/class.h"
#include "playerclass/class_prefabs.h"
#include "playerclass/multiclass_prefabs.h"
#include "skilltrees/skilltree.h"
#include "skilltrees/inventory.h"
#include "common/utlist.h"
#include "playerclass/multiclass.h"
#include "game-state/game.h"


/* Default Multiclasses in alphabetical order. */
const char* const DEFAULT_MULTICLASS_NAMES[] = {
    "hexblade",
    "infernal",
    "paladin",
    "enchanter",
    "assassin"
};

/* Number of predefined default multiclasses (see above). */
const int DEFAULT_MULTICLASS_COUNT = 5;
/* Number of predefined default classes. This is used to index the id for the skills */
const int DEFAULT_CLASS_INDEX = 17;

/*
 * Determines the index of name in the DEFAULT_MULTICLASS_NAMES array, 
 * for use as an internal id.
 * 
 * Parameters
 *  - name: The name of the class.  Case sensitive.
 * 
 * Returns:
 *  - The index of the name in the DEFAULT_MULTICLASS_NAMES array. Returns -1 if the 
 *    name does not appear or is NULL.
 */
int get_multiclass_name_index(char* name) {
    if (name == NULL)
        return -1;

    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, name, MAX_NAME_LEN + 1);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);

    for (int i = 0; i < DEFAULT_MULTICLASS_COUNT; i++) 
        if (strncmp(temp_name, DEFAULT_MULTICLASS_NAMES[i], MAX_NAME_LEN) == 0) 
            return i;

    return -1;
}

/* See multiclass_prefabs.h */
class_t* multiclass_prefab_new(game_t* game, char* multiclass_name)
{
    char temp_name[MAX_NAME_LEN + 1]; 
    strncpy(temp_name, multiclass_name, MAX_NAME_LEN);
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
    /* names of the two classes being combined */
    class_t* base_class;
    class_t* second_class;

    /* Hexblade stats:
     * Wizard + Warrior
     * 10 Max Health
     * 10 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 10 Ranged Attack
     * 20 Magic Defense
     * 25 Magic Attack
     * 25 Max Mana */ 
    if (!strncmp(temp_name, "hexblade", MAX_NAME_LEN)) {
        int succ1;
        int succ2;
        base_class = class_prefab_new(game, "wizard");
        second_class = class_prefab_new(game, "warrior");
        short_desc = multiclass_shortdesc(base_class, second_class, &succ1);
        long_desc = multiclass_longdesc(base_class, second_class, &succ2);
        set_stats_hashtable(game, &stats, 10, 10, 5, 5, 10, 20, 25, 25);
    }

    /* Infernal stats:
     * Elementalist + Sorceror
     * 20 Max Health
     * 5 Speed
     * 10 Physical Defense
     * 10 Physical Attack
     * 10 Ranged Attack
     * 20 Magic Defense
     * 20 Magic Attack
     * 20 Max Mana */
    else if (!strncmp(temp_name, "infernal", MAX_NAME_LEN)) {
        int succ1;
        int succ2;
        base_class = class_prefab_new(game, "elementalist");
        second_class = class_prefab_new(game, "sorceror");
        short_desc = multiclass_shortdesc(base_class, second_class, &succ1);
        long_desc = multiclass_longdesc(base_class, second_class, &succ2);
        set_stats_hashtable(game, &stats, 20, 5, 10, 10, 10, 20, 20, 20);
    }

    /* Paladin stats:
     * Knight + Monk
     * 40 Max Health
     * 30 Physical Defense
     * 30 Physical Attack
     * 10 Ranged Attack
     * 0 Magic Defense
     * 0 Magic Attack
     * 20 Max Mana */

    else if (!strncmp(temp_name, "paladin", MAX_NAME_LEN)) {
        int succ1;
        int succ2;
        base_class = class_prefab_new(game, "knight");
        second_class = class_prefab_new(game, "monk");
        short_desc = multiclass_shortdesc(base_class, second_class, &succ1);
        long_desc = multiclass_longdesc(base_class, second_class, &succ2);
        set_stats_hashtable(game, &stats, 40, 20, 30, 30, 10, 0, 0, 20);
    }

    /* Enchanter stats:
     * Bard + Healer
     * 15 Health
     * 15 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 5 Ranged Attack
     * 20 Magic Defense
     * 20 Magic Attack
     * 20 Max Mana */ 
    if (!strncmp(temp_name, "enchanter", MAX_NAME_LEN)) {
        int succ1;
        int succ2;
        base_class = class_prefab_new(game, "bard");
        second_class = class_prefab_new(game, "healer");
        short_desc = multiclass_shortdesc(base_class, second_class, &succ1);
        long_desc = multiclass_longdesc(base_class, second_class, &succ2);
        set_stats_hashtable(game, &stats, 15, 15, 5, 5, 5, 20, 20, 20);
    }

    /* Assassin stats:
     * Rogue + Ranger
     * 10 Max Health
     * 25 Speed
     * 15 Physical Defense
     * 15 Physical Attack
     * 15 Ranged Attack
     * 10 Magic Defense
     * 5 Magic Attack
     * 15 Max Mana */
    else if (!strncmp(temp_name, "assassin", MAX_NAME_LEN)) {
        int succ1;
        int succ2;
        base_class = class_prefab_new(game, "rogue");
        second_class = class_prefab_new(game, "ranger");
        short_desc = multiclass_shortdesc(base_class, second_class, &succ1);
        long_desc = multiclass_longdesc(base_class, second_class, &succ2);
        set_stats_hashtable(game, &stats, 10, 25, 15, 15, 15, 10, 5, 15);
    }

    else {
        fprintf(stderr, "Could not find class name: \"%s\" "
                        "in multiclass_prefab_new\n", temp_name);
        return NULL;
    }

<<<<<<< HEAD
=======

>>>>>>> 99494edaf37725ea9c3f498b12ba6158b3aa2bdd
    return multiclass(base_class, second_class, temp_name);
}

/* some function about adding skills to multiclass trees? */
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



/* See multiclass_prefabs.h */
int multiclass_prefab_add_skills(game_t* game, class_t* multiclass)
{
    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, multiclass->name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);
    if (!strncmp(temp_name, "hexblade", MAX_NAME_LEN)) {
<<<<<<< HEAD
        class_t* c1 = class_prefab_new(game, "wizard");
        class_t* c2 = class_prefab_new(game, "warrior");
        class_prefab_add_skills(c1);
        class_prefab_add_skills(c2);

        multiclass_tree("Hexblade Tree", c1->skilltree, c2->skilltree);
=======
        /* class_allocate_skills(multiclass->base_class, 3, 3, 0);
        sid_t skill_id = class->skilltree->tid * 100; */

        /* Currently point to null effects */
        /* Skills */
       /* skill_t* skill_0 = skill_new(skill_id++, ACTIVE, "Magic Word", 
                                     "You deal damage to your opponent with " 
                                     "just a word.", 1, 75, NULL, NULL); */

        /* Add skills to tree */
       /* add_skill(multiclass->base_class, skill_0, 0, 25, true, NULL, 0);
        add_skill(multiclass->base_class, skill_1, 1, 50, false, NULL, 0, 0);
        add_skill(multiclass->base_class, skill_2, 1, 34, false, NULL, 0, 1); */
>>>>>>> 99494edaf37725ea9c3f498b12ba6158b3aa2bdd
    }  

    else if (!strncmp(temp_name, "infernal", MAX_NAME_LEN)){

    }

    else if (!strncmp(temp_name, "paladin", MAX_NAME_LEN)){

    }

    else if (!strncmp(temp_name, "enchanter", MAX_NAME_LEN)){

    }
    
    else {
        fprintf(stderr, "Could not find class for skill inventories "
                        "in multiclass_prefab_add_skills\n");
        return EXIT_FAILURE;
    }
    return SUCCESS;
}