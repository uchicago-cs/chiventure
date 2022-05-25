/*
 * Class list to integrate with battle systems. 
 * See class-list.h for more information.
 */
#include "class-list.h"

#define MAX_SPELL_DESC_LEN (50)

/* See class-list.h */
move_list_t* new_move_list(class_t* c, char* spell, int damage, int id) {
    
    move_list_t* list = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (list == NULL) {
        fprintf(stderr, "Could not allocate memory for new_move_list()");
        exit(1);
    }

    list->c = c;
    list->spell = strdup(spell);
    list->damage = damage;
    list->id = id;
    list->next = NULL;
    list->prev = NULL;
}


/* see class-list.h */
move_list_t* move_list() {

    move_list_t *head = NULL;

    // Bard

    class_t *bard = class_new("Bard", "Song-singer", "Song-singer and tale-teller", NULL, NULL, NULL);
    move_list_t* bardlist = new_move_list(bard, "Diss Track", 80, 0);

    // Wizard

    class_t *wizard = class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
    move_list_t* wizardlist = new_move_list(wizard, "Fireball", 100, 1);
    
    // Knight

    class_t *knight = class_new("Knight", "Brave", "Brave and shiny", NULL, NULL, NULL);
    move_list_t* knightlist = new_move_list(knight, "Sword Slash", 90, 2);

    DL_APPEND(head, bardlist);
    DL_APPEND(head, wizardlist);
    DL_APPEND(head, knightlist);

    return head;
}
