/*
 * Class list to integrate with battle systems. 
 */
#ifndef CLASS_LIST_H
#define CLASS_LIST_H

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

/* Returns a new move_list. Only creates a copy of the spell name.
 *
 * Parameters:
 * - c: the class
 * - spell: the name of the spell
 * - damage: the amount of damage the spell does
 * - id: the id of the spell
 * 
 * Returns:
 * - move_list_t* A new move_list_t not linked with anything
 * 
 */ 
move_list_t* new_move_list(class_t* c, char* spell, int damage, int id);

/* Returns a hard-coded doubly linked list with the class, spell name, damage, 
 * and id number of the spell. 
 * 
 * Parameters:
 * - none
 * 
 * Returns:
 * - move_list_t* doubly linked list with the class, spell, damage, and id 
 *   number
 */ 
move_list_t* move_list();

#endif /* CLASS_LIST_H */
