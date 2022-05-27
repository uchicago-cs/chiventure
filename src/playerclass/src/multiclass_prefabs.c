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


/* Default Multiclasses in alphabetical order. */
const char* const DEFAULT_MULTICLASS_NAMES[] = {
    "hexblade",
    "name1",
    "name2"
};

/* Number of predefined default multiclasses (see above). */
const int DEFAULT_MULTICLASS_COUNT = 3;

/*
 * Determines the index of name in the DEFAULT_MULTICLASS_NAMES array, 
 * for use as an internal id.
 * 
 * Parameters
 *  - name: The name of the class.  Case sensitive.
 * 
 * Returns:
 *  - The index of the name in the DEFAULT_CLASS_NAMES array. Returns -1 if the 
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
class_t* multiclass_prefab_new(game_t* game, class_t* base_class, 
                            class_t* second_class, char* multiclass_name)
{
    char temp_name[MAX_NAME_LEN + 1]; 
<<<<<<< HEAD
    strncpy(temp_name, class_name, MAX_NAME_LEN);
=======
    strncpy(temp_name, multiclass_name, MAX_NAME_LEN);
>>>>>>> 39df9cf0fd5df463695c52691cebd05afda49bd9
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

    /* Hexblade stats:
<<<<<<< HEAD
     * 10 Max Health
     * 10 Speed
     * 5 Physical Defense
     * 5 Physical Attack
     * 10 Ranged Attack
     * 20 Magic Defense
     * 25 Magic Attack
     * 25 Max Mana */ 
    if (!strncmp(temp_name, "hexblade", MAX_NAME_LEN)) {
        int succ;
        short_desc = multiclass_shortdesc(class_prefab_new(game, wizard), 
                                        class_prefab_new(game, warrior));
        long_desc = multiclass_longdesc(class_prefab_new(game, wizard), 
                                        class_prefab_new(game, warrior));
        set_stats_hashtable(game, &stats, 10, 10, 5, 5, 10, 20, 25, 25);
    }

=======
     * TODO
     */ 
    if (!strncmp(temp_name, "hexblade", MAX_NAME_LEN)) {
        short_desc = multiclass_shortdesc(base_class, second_class);
        long_desc = multiclass_longdesc(base_class, second_class);
        //smt w setting hash stats here? 
    } else {
        fprintf(stderr, "Could not find class name: \"%s\" "
                        "in multiclass_prefab_new\n", multiclass_name);
        return NULL;
    }
    return multiclass(base_class, second_class, multiclass_name);
>>>>>>> 39df9cf0fd5df463695c52691cebd05afda49bd9
}

/* some function about adding skills to multiclass trees? */

/* See multiclass_prefabs.h */
int multiclass_prefab_add_skills(class_t* multiclass)
{
    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, multiclass->name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);
    if (!strncmp(temp_name, "hexblade", MAX_NAME_LEN)) {
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
       // add_skill(class, skill_0, 0, 25, true, NULL, 0);
     //   add_skill(class, skill_1, 1, 50, false, NULL, 0, 0);
     //   add_skill(class, skill_2, 1, 34, false, NULL, 0, 1);
    } else {
        fprintf(stderr, "Could not find class for skill inventories "
                        "in multiclass_prefab_add_skills\n");
        return EXIT_FAILURE;
    }

    return SUCCESS;
}