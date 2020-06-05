/*
 * Class and skill list to integrate with battle systems. 
 */
#ifndef SKILL_LIST_H
#define SKILL_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common/utlist.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"
#include "skilltrees/skill.h"
#include "skilltrees/skill-example.h"

typedef struct move_list {
    class_t* c;
    skill_t* spell;
    struct move_list *prev;
    struct move_list *next;
} move_list_t;

/* Returns a new move_list. Only creates a copy of the spell name.
 *
 * Parameters:
 * - c: the class
 * - spell: a pointer to a skill that holds name, damage, id
 * 
 * Returns:
 * - move_list_t* A new move_list_t not linked with anything
 * 
 */ 
move_list_t* new_move_list(class_t* c, skill_t* spell);

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

#endif /* SKILL_LIST_H */
