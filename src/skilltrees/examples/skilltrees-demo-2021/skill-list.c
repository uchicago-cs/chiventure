/*
 * Class list to integrate with battle systems. 
 * See skill-list.h for more information.
 */
#include "skilltrees/skill-list.h"

#define MAX_SPELL_DESC_LEN (50)

/* See -list.h */
skill_list_t* new_skill_list(class_t* c, skill_t* spell) {
    
    skill_list_t* list = (skill_list_t*) calloc(1, sizeof(skill_list_t));

    if (list == NULL) {
        fprintf(stderr, "Could not allocate memory for new_skill_list()");
        exit(1);
    }

    list->c = c;
    list->spell = strdup(spell->name);
    list->damage = spell->effect("") - '0';
    list->id = spell->sid;
    list->next = NULL;
    list->prev = NULL;
}


/* see skill-list.h */
skill_list_t* skill_list() {

    skill_list_t *head = NULL;

    // Bard

    class_t *bard = class_new("Bard", "Song-singer", "Song-singer and tale-teller", NULL, NULL, NULL);
    skill_inventory_t *bard_inv = bard_inventory();
    skill_list_t *bardlist = new_skill_list(bard, bard_inv->active[0]);

    // Wizard

    class_t *wizard = class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
    skill_inventory_t *wizard_inv = wizard_inventory();
    skill_list_t *wizardlist = new_skill_list(wizard, wizard_inv->active[0]);
    
    // Knight

    class_t *knight = class_new("Knight", "Brave", "Brave and shiny", NULL, NULL, NULL);
    skill_inventory_t *knight_inv = knight_inventory();
    skill_list_t *knightlist = new_skill_list(knight, knight_inv->active[0]);

    DL_APPEND(head, bardlist);
    DL_APPEND(head, wizardlist);
    DL_APPEND(head, knightlist);

    return head;
}
