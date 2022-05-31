/*
 * Defines prefabricated classes for use by game devs and in testing.
 */

#ifndef CLASS_PREFABS_H
#define CLASS_PREFABS_H

#include "playerclass/class_structs.h"
#include "game-state/game.h"

/*
 * Allocates and initializes a prefab class, and the following fields:
 *  - Short description
 *  - Long description
 *  - Stats
 * To add skill-related fields, see class_prefab_add_skills().
 *
 * Parameters:
 *  - game: The current game struct (contains the global stat hashtable, which 
 *         can be NULL).
 *  - class_name: The name of the prefab class to be generated.  Must match one
 *                of our classes.
 * 
 * Note: class_name is case insensitive, but the name stored is always lowercase.
 * 
 * Returns:
 *  - A pointer to the new class on success, NULL on failure.
 */
class_t* class_prefab_new(game_t* game, char* class_name);

/*
 * Initializes a prefab class's skilltree and active combat and noncombat skill 
 * lists.
 *
 * Parameters:
 *  - class: the class the skilltree and lists should be placed in. The field
 *    initialized here are assumed to be empty.
 *
 * Returns:
 *  - status code (FAILURE if the given class or skill is NULL, SUCCESS otherwise.)
 *  - the structs in the class now contain skills.
 *
 * Notes:
 *  - This function is not fully implemented, as we are waiting for the skill
 *    effects to be more fully developed. However, the warrior class does work,
 *    as a proof of concept.
 */
int class_prefab_add_skills(class_t* class);

/*
 * Initializes default items for prefab classes.
 *
 * Parameters:
 *  - class: the class that the item is associated with.
 *
 * Returns:
 *  - an item struct, with an ID, short description, and long description,
 *    or NULL if the input class is not found
 * 
 * Notes:
 *  - Since items aren't an intrinsic part of classes, this function would
 *    likely be used in conjunction with creation of a player in game state.
 *  - The current version of the function doesn't have item effects. This could
 *    be added later.
 *  - The function currently only returns one item; this could be expanded later
 *    to return multiple. It's structured in a way that would likely accomodate
 *    such a change.
 */
item_t* class_prefab_add_items(class_t* class);

/*
 * The code in here is for integration purposes with multiclass_prefabs
 * and does not actually provide use outside of its own module, 
 * see class_prefabs.c for more information.
 */
int set_stats_hashtable(game_t* game, stats_hash_t** stats,
                        double max_health, 
                        double speed,
                        double physical_defense, 
                        double physical_attack,
                        double ranged_attack,
                        double magic_defense,
                        double magic_attack,
                        double max_mana);

int class_allocate_skills(class_t* class, int max_skills_in_tree, 
                          int max_active_skills, int max_passive_skills);

#endif /* CLASS_PREFABS_H */
