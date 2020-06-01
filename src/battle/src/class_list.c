/*
 * Class list to integrate with battle systems. 
 * See class-list.h for more information.
 */
#include "class-list.h"

/* see class-list.h */
move_list_t* move_list() {

    // Bard

    class_t *bard = class_new("Bard", "Song-singer", "Song-singer and tale-teller", NULL, NULL, NULL, NULL, NULL, NULL);
    move_list_t* bardlist;

    bardlist = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (bardlist == NULL){
        fprintf(stderr, "Could not allocate memory for move_list()");
        exit(1);
    }
    
    bardlist->c = bard;
    bardlist->spell = "Diss Track";
    bardlist->damage = 8;
    bardlist->id = 0;
    bardlist->next = NULL;
    bardlist->prev = NULL;
    
    // Wizard

    class_t *wizard = class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL, NULL, NULL, NULL);
    move_list_t* wizardlist;

    wizardlist = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (wizardlist == NULL){
        fprintf(stderr, "Could not allocate memory for move_list()");
        exit(1);
    }
    
    wizardlist->c = wizard;
    wizardlist->spell = "Fireball";
    wizardlist->damage = 10;
    wizardlist->id = 1;
    
    DL_PREPEND(bardlist, wizardlist);
    
    // Knight

    class_t *knight = class_new("Knight", "Brave", "Brave and shiny", NULL, NULL, NULL, NULL, NULL, NULL);
    move_list_t* knightlist;

    knightlist = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (knightlist == NULL){
        fprintf(stderr, "Could not allocate memory for move_list()");
        exit(1);
    }
    
    knightlist->c = knight;
    knightlist->spell = "Sword Slash";
    knightlist->damage = 9;
    knightlist->id = 2;

    DL_PREPEND(wizardlist, knightlist);

    return knightlist;
}
