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

/* This defines what type of damage if any the move would do. 
    We will do this to specify attack. */
typedef enum damage_type {
    PHYS, //A move that would inflict physical damage on the opponent.
    MAG, //A move that would inflict magical damage on the opponent. 
    NO_DAMAGE //A move that does not inflict damage.
} damage_type_t;

typedef enum target_type {
    USER, //A move that targets the user.
    TARGET, //A move that would target the target.
    BOTH,  //A move that targets both the user and target. How it affects both can be different.
    NO_TARGET //A move that does not target the opponent nor the user that is not an attacking move.
} target_type_t;

typedef enum target_count {
    SINGLE, //A move that hits a single target
    MULTI //A move that hits multiple targets
} target_count_t;

typedef struct move_list {
    class_t* c;
    char* spell;
    int damage;
    int id;
    struct move_list *prev;
    struct move_list *next;

    //The following code has been changed because of move_t
    char *name;
    char *info;
    damage_type_t dmg_type; 
    target_type_t stat_mods; 
    target_type_t effects; 
    target_count_t count; 
    int sp_cost; 
    battle_item_t* req_item; 
    int accuracy; 
    stat_changes_t* user_mods; 
    stat_changes_t* opponent_mods; 


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
