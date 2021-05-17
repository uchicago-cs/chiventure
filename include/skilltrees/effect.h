/* Implementation for an effect caused by a skill.  
 * Skills can have multiple effects as defined by the linked list.
 * Effects are of various types depending on what they do.
 */

#ifndef INCLUDE_EFFECT_H_
#define INCLUDE_EFFECT_H_

#include "common/ctx.h"
#include "common/common.h"
#include "common/ctx.h"  
/* Removing the comment above causes the code to not compile correctly. 
 * This is because of duplicate naming of structs in battle_flow_structs and battle_structs.
 * RPG-battles is currently working on fixing this problem and have already submitted a pull request
 */
#include <stdbool.h>
#include "battle/battle_moves.h"

/* List of all the effect types that a skill can have.  We can add more in the future */
typedef enum effect_type {
    // Effect that modifies statistics of player
    STATISTIC_MOD,

    // Effect that unlocks a move
    MOVE_UNLOCK,

    // Effect that modifies attributes of the player
    ATTRIBUTE_MOD,

}effect_type_t;

// Defines an effect that modifies the statistics of a player
typedef struct stat_mod_effect {
    char* stat_name; // Takes the name of the statistic that must be modified
    int modification;         // Modifies the statistic by this number.  If effect decreases stats, specify negative number.
    int duration;    // The duration for how long the effect should be applied (O if permanent)
}stat_mod_effect_t;

//Defines an effect that unlocks a move
typedef struct move_effect {
    /* More fields will probably be added after speaking with 
     * the rpg-battles team */

    // TODO - Add more fields
    move_t move;      // Specifies the move that will be unlocked
}move_effect_t;

// A struct used to define a union data type that we use to change attributes
union data
{
    bool b;
    char c;
    int  i;
    char *s;
}; // The value to which we want to change the attribute (NOT THE VALUE BY WHICH WE WANT TO MODIFY THE ATTRIBUTE)

/* Defines an effect that changes the attribute of an item.  
 * We currently can change the attribute value if it is a bool, character, integer, or string. 
 * We may need to be able to change other stuff in the future but this remains to be seen.
 * Currently, creating a new attribute is not supported but this can be changed.
 */

typedef struct att_effect {
    char* item_id; // The ID of the parent object 
    char* att_id; // The ID that refers to the given attribute (see obj.h)
    union data mod; 
}att_effect_t;

/* Union of all the effect types given above.*/
typedef struct effect {
    effect_type_t effect_type; // Contains the value of the effect.  Check enum above
    union
    {
        stat_mod_effect_t* s;
        move_effect_t* m;
        att_effect_t* a;
    } data; // Contains a pointer to the effect itself so that we can make the necessary modifications to execute the skill
}effect_t;

/* Defines a statistic modifying effect and returns a pointer to it 
 * Parameters: char* statname: The stat name to be modified
 *             int mod: The value to modify the statistic by
 *             int duration: the duration for which the effect should be applied
 * Returns:  A pointer to the created statistic modifying effect
 */
stat_mod_effect_t* define_stat_mod_effect(char* stat_name, int modification, int duration);

/* Defines an move effect that unlcoks a and returns a pointer to it
 * Parameters: move_t move: The move that will be unlocked
 * Returns: A pointer to the created move efect
 */
move_effect_t* define_move_effect(move_t move);

/* Defines an attribute modifying effect and returns a pointer to it
 * Parameters: char* obj_id:  The unique ID of the parent object
 *            char* att_id:  The ID of the attribute
 *            data mod: Contains a value of the union data type to which the attribute value must be changed
 * Returns: A pointer to the created attribute modifying effect
 */
att_effect_t* define_att_effect(char* item_id, char* att_id, union data mod);

/* Takes the given stats modifying effect and converts it to an effect
 * Parameters: stat_mod_effect_t* stat_effect- Pointer to the stats modifying effect
 * Returns: A pointer to an effect with parameters based on what has been given
 */

effect_t* make_stat_mod_effect(stat_mod_effect_t* stat_effect);


/* Takes the given move effect and converts it to an effect
 * Parameters: move_effect_t* move_effect- Pointer to the move effect
 * Returns: A pointer to an effect with parameters based on what has been given
 */

effect_t* make_move_effect(move_effect_t* move_effect);


/* Takes the given attribute modifying effect and converts it to an effect
 * Parameters: att_effect_t* att_effect- Pointer to the attribute modifying effect
 * Returns: A pointer to an effect with parameters based on what has been given
 */

effect_t* make_att_effect(att_effect_t* att_effect);


/* Takes the given statistic modifying effect and executes it
 * Parameters: stat_mod_effect_t* stat_effect - Pointer to the statistic modifying effect
 * Returns: 0 is the execution was successful, 1 otherwise
 */
int execute_stat_mod_effect(stat_mod_effect_t* stat_effect);


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
int execute_att_effect(att_effect_t* att_effect);

#endif /*INCLUDE_EFFECT_H*/