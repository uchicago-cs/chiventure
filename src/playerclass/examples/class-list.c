/*
 * Class list to integrate with battle systems. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "common/utlist.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

typedef struct move_list {
    class_t* class;
    char* spell;
    int damage;
    int id;
    struct class_list *next;
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
move_list_t* move_list() {

    // Bard

    class_t *bard = class_new("Bard", "Song-singer", "Song-singer and tale-teller", NULL, NULL, NULL, NULL, NULL);
    move_list_t* bardlist;

    bardlist = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (bardlist == NULL){
        fprintf(stderr, "Could not allocate memory for move_list()");
        exit(1);
    }
    
    bardlist->class = bard;
    bardlist->spell = "Diss Track";
    bardlist->damage = 8;
    bardlist->id = 0;
    
    // Wizard

    class_t *wizard = class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL, NULL, NULL);
    move_list_t* wizardlist;

    wizardlist = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (wizardlist == NULL){
        fprintf(stderr, "Could not allocate memory for move_list()");
        exit(1);
    }
    
    wizardlist->class = wizard;
    wizardlist->spell = "Fireball";
    wizardlist->damage = 10;
    wizardlist->id = 1;
    
    LL_PREPEND(wizardlist, bardlist);
    
    // Knight

    class_t *knight = class_new("Knight", "Brave", "Brave and shiny", NULL, NULL, NULL, NULL, NULL);
    move_list_t* knightlist;

    knightlist = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (knightlist == NULL){
        fprintf(stderr, "Could not allocate memory for move_list()");
        exit(1);
    }
    
    knightlist->class = knight;
    knightlist->spell = "Sword Slash";
    knightlist->damage = 9;
    knightlist->id = 2;

    LL_PREPEND(bardlist, knightlist);

    return knightlist;
}