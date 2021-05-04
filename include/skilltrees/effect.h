/* Implementation for an effect caused by a skill.  
 * Skills can have multiple effects as defined by the linked list.
 * Effects are of various types depending on what they do.
 */

#ifndef INCLUDE_EFFECT_H_
#define INCLUDE_EFFECT_H_

#include "common/common.h"
//#include "common/ctx.h"  (Removing the comment causes the code to not compile correctly.  Please advise)
#include <stdbool.h>

/*List of all the effect types that a skill can have.  We can add more in the future */
typedef enum effect_type {
    //Effect that modifies statistics of player
    STATISTIC_MOD,

    //Effect that deals damage
    DAMAGE,

    //Effect that modifies attributes of the player
    ATTRIBUTE_MOD,

}effect_type_t;

//Defines an effect that modifies the statistics of a player
typedef struct stat_effect{
    char* stat_name; //Takes the name of the statistic that must be modified
    int mod;         //Modifies the statistic by this number.  If effect decreases stats, specify negative number.
    int duration;    //The duration for how long the effect should be applied (O if permanent)
}stat_mod_effect_t;

//Defines an effect that deals damage
typedef struct damage_effect{
    int damage;      //Specifies the amount of damage that the skill does
}damage_effect_t;

//A struct used to define a union data type that we use to change attributes
union data
{
    bool b;
    char c;
    int  i;
    char *s;
}; //The value to which we want to change the attribute (NOT THE VALUE BY WHICH WE WANT TO MODIFY THE ATTRIBUTE)

/*Defines an effect that changes the attribute of an item.  
 *We currently can change the attribute value if it is a bool, character, integer, or string. 
 *We may need to be able to change other stuff in the future but this remains to be seen.
 *Currently, creating a new attribute is not supported but this can be changed.
 */

typedef struct att_effect{
    char* item_id; //The ID of the parent object 
    char* att_id; //The ID that refers to the given attribute (see obj.h)
    union data mod; 
}att_effect_t;

/*Union of all the effect types given above.*/
typedef struct effect{
    effect_type_t effect_type; //Contains the value of the effect.  Check enum above
    union
    {
        stat_mod_effect_t* s;
        damage_effect_t* d;
        att_effect_t* a;
    } data; //Contains a pointer to the effect itself so that we can make the necessary modifications to execute the skill
}effect_t;

//Node in the effects linked list
typedef struct effect_node{
    effect_t* data; //Pointer to the effect in this node
    struct effect_node* next; //Pointer to the next node
}effect_node_t;

//The linked list itself
typedef struct effects_linked_list{
    effect_node_t* head; //Pointer to the start of the linked list
    int num; //Number of effects
}effects_linked_list_t;

/* Defines a statistic modifying effect and returns a pointer to it 
 * Parameters: char* statname: The stat name to be modified
 *             int mod: The value to modify the statistic by
 *             int duration: the duration for which the effect should be applied
 * Returns:  A pointer to the created statistic modifying effect
 */
stat_mod_effect_t* define_stat_mod_effect(char* stat_name, int mod, int duration);

/* Defines an attack effect that damages a target by a given amount and returns a pointer to it
 * Parameters: int mod: The amount of damage to be dealt
 * Returns: A pointer to the created damage efect
 */
damage_effect_t* define_damage_effect(int mod);

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


/* Takes the given damage effect and converts it to an effect
 * Parameters: damage_effect_t* damage_effect- Pointer to the damage effect
 * Returns: A pointer to an effect with parameters based on what has been given
 */

effect_t* make_damage_effect(damage_effect_t* damage_effect);


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


/* Takes the given damage effect and executes it
 * Parameters: damage_effect_t* damage_effect - a pointer to the damage effect
 * Returns: 0 is the execution was successful, 1 otherwise
 */
int execute_damage_effect(damage_effect_t* damage_effect);

/* Takes the given attribute modifying effect and executes it
 * Parameters: att_effect_t* att_effect - a pointer to the attribute modifying effect
 * Returns: 0 is the execution was successful, 1 otherwise
 */
int execute_att_effect(att_effect_t* att_effect);


/* Initializes a linked list of effects
 * Returns: a pointer to the first element of the initialized linked list
 */
effects_linked_list_t* init_linked_list();

/* Adds an effect_t_node to the tail of a linked list of effects
 * Returns: 0 adding was successful, 1 otherwise
 */
int add_node (effects_linked_list_t* ll, effect_t* effect);


/* Removes an effect_t_node from the tail of a linked list of effects
 * Returns: 0 is removing was successful, 1 otherwise
 */
int remove_node (effects_linked_list_t* ll, effect_t* effect);

#endif /*INCLUDE_EFFECT_H*/