/* Implementation for an effect caused by a skill.  
 * Skills can have multiple effects as defined by the linked list.
 * Effects are of various types depending on what they do.
 */

#ifndef INCLUDE_EFFECT_H_
#define INCLUDE_EFFECT_H_

#include <stdbool.h>
#include "common/ctx.h"
#include "common/common.h"
#include "common/uthash.h"
#include "common/utlist.h"
#include "battle/battle_moves.h"
#include "game-state/stats.h"
#include "game-state/item.h"

/* List of all the effect types that a skill can have.  We can add more in the future */
typedef enum effect_type {
    /* Effect that modifies statistics of player */
    PLAYER_STATISTIC_MOD,

    /* Effect that unlocks a move */
    MOVE_UNLOCK,

    /* Effect that modifies attributes of an item */
    ITEM_ATTRIBUTE_MOD,

    /* Effect that modifies statistics of an item */
    ITEM_STATISTIC_MOD
} effect_type_t;

/* Defines an effect that modifies the statistics of a player */
typedef struct player_stat_effect {
    /* The name assigned to the effect */
    char* player_stat_effect_name; 

    /* Takes the array of statistics that must be  */
    stats_t** stats; 

    /* Modifies the statistic by this number */
    double* modifications;         

    /* The array of durations for how long the effect should be applied */
    int* durations;    

    /* Number of statistic that will be modified */
    int num_stats; 
} player_stat_effect_t;

/* Defines an effect that unlocks a move */
typedef struct move_effect {
    /* More fields will probably be added after speaking with 
     * the rpg-battles team 
     */

    /* TODO - Add more fields */
    
    /* Specifies the move that will be unlocked */
    move_t* move;      
} move_effect_t;

/* Defines an effect that changes the attribute of an item.  
 * We currently can change the attribute value if it is a bool, character, integer, or string. 
 * We may need to be able to change other stuff in the future but this remains to be seen.
 * Currently, creating a new attribute is not supported but this can be changed.
 */
typedef struct item_attr_effect {
    /* The ID of the parent object */
    item_t* item; 
    
    /* The ID that refers to the given attribute (see obj.h) */
    char* att_id; 

    /* Enum that holds possible types of attribute value */
    enum attribute_tag att_tag; 

    /* The value to which we want to change the attribute */
    attribute_value_t attribute_mod; 
} item_attr_effect_t;

/* Defines an effect that changes the statistic of an item.
 * An item stat effect should take an item and a list of statistics and mods
 * and apply the mods to the statistics in the item's statistic hash table.
 * We expect that the implementation is going to be quite similar to player_stat_effect.
 * For more info, check the skilltrees wiki.  An issue will also be created so that future
 * developers know that they have to do this.
 */
typedef struct item_stat_effect {
    //TODO (2022)
} item_stat_effect_t;

/* Union of all the effect types given above.*/
typedef struct effect {
    /* Contains the value of the effect.  Check enum effect_type_t above */
    effect_type_t effect_type; 
    
    /* Contains a pointer to the effect itself so that we can make the necessary modifications to execute the skill */
    union
    {
        player_stat_effect_t* s;
        move_effect_t* m;
        item_attr_effect_t* i_a;
        item_stat_effect_t* i_s;
    } data; 
} effect_t;

/* Defines a statistic modifying effect and returns a pointer to it 
 * Parameters: char* stat_mod_effect_name: A string that has the name of the effect
 *             char** stat_names: A pointer to an array of stats that will be modified
 *             double modifications: A pointer to an array to modify each statistic by (multiplier)
 *             int durations: the duration for which each modification should be applied
 *             chiventure_ctx_t* ctx: Context object for chiventure that stores te game and all other data
 * Returns:  A pointer to the created statistic modifying effect
 */
player_stat_effect_t* define_player_stat_effect(char* player_stat_effect_name, char** stat_names, double* modifications, int* durations, int num_stats, chiventure_ctx_t* ctx);

/* Defines an move effect that unlcoks a and returns a pointer to it
 * Parameters: move_t move: The move that will be unlocked
 * Returns: A pointer to the created move efect
 */
move_effect_t* define_move_effect(move_t* move);

/* Defines an attribute modifying effect and returns a pointer to it
 * Parameters: item_t* item:  A pointer to an item 
 *             char* att_id:  The ID of the attribute
 *             data mod: Contains a value of the union data type to which the attribute value must be changed
 * Returns: A pointer to the created attribute modifying effect
 */
item_attr_effect_t* define_item_attr_effect(item_t* item, char* att_id, enum attribute_tag att_tag, attribute_value_t attribute_mod);

/* Defines an item stat effect and returns a pointer to it
 * Parameters: TO BE IMPLEMENTED
 * Returns: A pointer to the created item stat modifying effect
 */
item_stat_effect_t* define_item_stat_effect();

/* Takes the given stats modifying effect and converts it to an effect
 * Parameters: stat_mod_effect_t* stat_effect- Pointer to the stats modifying effect
 * Returns: A pointer to an effect with parameters based on what has been given
 */

effect_t* make_player_stat_effect(player_stat_effect_t* stat_effect);


/* Takes the given move effect and converts it to an effect
 * Parameters: move_effect_t* move_effect- Pointer to the move effect
 * Returns: A pointer to an effect with parameters based on what has been given
 */

effect_t* make_move_effect(move_effect_t* move_effect);


/* Takes the given attribute modifying effect and converts it to an effect
 * Parameters: item_attr_effect_t* item_attr_effect- Pointer to the attribute modifying effect
 * Returns: A pointer to an effect with parameters based on what has been given
 */

effect_t* make_item_attr_effect(item_attr_effect_t* item_attr_effect);

/* Takes the given item statistic modifying effecr and converts it into an effect
 * Parameters: item_stat_effect_t* item_stat_effect - Pointer to the item statistic modifying effect
 * Returns: A pointer to an effect
 */

effect_t* make_item_stat_effect(item_stat_effect_t* item_stat_effect);

/* Takes the given statistic modifying effect and executes it
 * Parameters: stat_mod_effect_t* stat_effect - Pointer to the statistic modifying effect
 * Returns: 0 is the execution was successful, 1 otherwise
 */
int execute_player_stat_effect(player_stat_effect_t* stat_effect, chiventure_ctx_t* ctx);


/* Takes the given move effect and adds the move to the player
 * Parameters: chiventure_ctx_t* ctx - Pointer to the ctx for the current gamestate
 *             move_effect_t* effect - Pointer to the move skill to be added
 * Returns: 0 is the execution was successful, 1 otherwise
 */
int execute_move_effect(chiventure_ctx_t* ctx, move_effect_t* effect);

/* Takes the given attribute modifying effect and executes it
 * Parameters: att_effect_t* att_effect - a pointer to the attribute modifying effect
 * Returns: 0 is the execution was successful, 1 otherwise
 */
int execute_item_attr_effect(item_attr_effect_t* item_attr_effect);

/* Takes the given attribute modifying effect and executes it
 * Parameters: item_stat_effect_t* item_stat_effect - a pointer to the item stat modifying effect
 * Returns: 0 is the execution was successful, 1 otherwise
 */
int execute_item_stat_effect(item_stat_effect_t* item_stat_effect);

#endif /*INCLUDE_EFFECT_H*/