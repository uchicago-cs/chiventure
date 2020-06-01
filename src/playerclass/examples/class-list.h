/*
 * Class list to integrate with battle systems. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "common/utlist.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

typedef struct move_list {
    class_t* c;
    char* spell;
    int damage;
    int id;
    struct move_list *prev;
    struct move_list *next;
} move_list_t;

/* Returns a hard-coded linked list with the class, spell name, damage, 
 * and id number of the spell. 
 * 
 * Parameters:
 * - none
 * 
 * Returns:
 * - move_list_t* linked list with the class, spell, damage, and id number
 */ 