#ifndef INCLUDE_EFFECT_H_
#define INCLUDE_EFFECT_H_

#include "common/common.h"
#include <stdbool.h>

/*List of all the effect types that a skill can have.  We can add more in the future */
typedef enum effect_type {
    //Effect that modifies statistics of player
    STATISTIC,

    //Effect that deals damage
    DAMAGE,

    //Effect that modifies attributes of the player
    ATTRIBUTE,

}effect_type_t;

//Defines an effect that modifies the statistics of a player
typedef struct stat_effect{
    char* stat_name; //Takes the name of the statistic that must be modified
    int mod;         //Modifies the statistic by this number.  If effect decreases stats, specify negative number.
}stat_effect_t;

//Defines an effect that deals damage
typedef struct damage_effect{
    int damage;      //Specifies the amount of damage that the skill does
}damage_effect_t;

/*Defines an effect that changes the attribute of a player.  
 *We currently can change the attribute value if it is a bool, character, integer, or string. 
 *We may need to be able to change other stuff in the future but this remains to be seen.
 *Currently, creating a new attribute is not supported but this can be changed.
 */

typedef struct att_effect{
    char* obj_id; //The ID of the parent object 
    char* att_id; //The ID that refers to the given attribute (see obj.h)
    union 
    {
        bool b;
        char c;
        int  i;
        char *s;
    } mod; //The value to which we want to change the attribute
}att_effect_t;

/*Union of all the effect types given above.*/
typedef struct effect{
    effect_type_t effect_type; //Contains the value of the effect.  Check enum above
    union
    {
        stat_effect_t s;
        damage_effect_t d;
        att_effect_t a;
    } data; //Contains the effect itself so that we can make the necessary modifications to execute the skill
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

#endif /*INCLUDE_EFFECT_H*/