/*
 * Alternate class list to integrate with battle systems. 
 * This class list does not use skill_inventory.
 * See class-list.h for more information.
 */
#include "skilltrees/skill-list.h"

#define MAX_SPELL_DESC_LEN (50)

/* See class-list.h */
move_list_t* new_move_list(class_t* c, skill_t* spell) {
    
    move_list_t* list = (move_list_t*) calloc(1, sizeof(move_list_t));

    if (list == NULL) {
        fprintf(stderr, "Could not allocate memory for new_move_list()");
        exit(1);
    }

    list->c = c;
    list->spell = strdup(spell->name);
    list->damage = spell->effect("") - '0';
    list->id = spell->sid;
    list->next = NULL;
    list->prev = NULL;
}


/* see class-list.h */
move_list_t* move_list() {

    move_list_t *head = NULL;

    // Bard

    class_t *bard = class_new("Bard", "Song-singer", "Song-singer and tale-teller", NULL, NULL, NULL, NULL, NULL, NULL);
    skill_t *diss_track = skill_new(0, ACTIVE, "Diss Track", "A Bard attack spell that deals 8 damage.", 2, 5, effect_diss_track);
    move_list_t* bardlist = new_move_list(bard, diss_track);

    // Wizard

    class_t *wizard = class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL, NULL, NULL, NULL);
    skill_t *fireball = skill_new(1, ACTIVE, "Fireball", "A Wizard attack spell that deals 10 damage.", 2, 5, effect_fireball);
    move_list_t* wizardlist = new_move_list(wizard, fireball);
    
    // Knight

    class_t *knight = class_new("Knight", "Brave", "Brave and shiny", NULL, NULL, NULL, NULL, NULL, NULL);
    skill_t *sword_slash = skill_new(2, ACTIVE, "Sword Slash", "A Knight attack that deals 9 damage.", 2, 5, effect_sword_slash);
    move_list_t* knightlist = new_move_list(knight, sword_slash);

    DL_APPEND(head, bardlist);
    DL_APPEND(head, wizardlist);
    DL_APPEND(head, knightlist);

    return head;
}
