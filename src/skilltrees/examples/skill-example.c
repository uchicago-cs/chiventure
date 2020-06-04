/*
 * Skill examples for battle demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/skill-example.h"


/* See skill-example.h */
char* effect_diss_track(char* args){
    return "8";
}


/* See skill-example.h */
char* effect_fireball(char* args){
    return "10";
}


/* See skill-example.h */
char* effect_sword_slash(char* args){
    return "9";
}


/* See skill-example.h */
skill_inventory_t* bard_inventory() {
    skill_inventory_t* bard_inventory = inventory_new(1, 0);

    skill_t* diss_track = skill_new(0, ACTIVE, "Diss Track", "A Bard attack spell that deals 8 damage.", 2, 5, effect_diss_track);

    inventory_skill_add(bard_inventory, diss_track);

    return bard_inventory;
}


/* See skill-example.h */
skill_inventory_t* wizard_inventory() {
    skill_inventory_t* wizard_inventory = inventory_new(1, 0);

    skill_t* fireball = skill_new(1, ACTIVE, "Fireball", "A Wizard attack spell that deals 10 damage.", 2, 5, effect_fireball);

    inventory_skill_add(wizard_inventory, fireball);

    return wizard_inventory;
}


/* See skill-example.h */
skill_inventory_t* knight_inventory() {
    skill_inventory_t* knight_inventory = inventory_new(1, 0);

    skill_t* sword_slash = skill_new(2, ACTIVE, "Sword Slash", "A Knight attack that deals 9 damage.", 2, 5, effect_sword_slash);

    inventory_skill_add(knight_inventory, sword_slash);

    return knight_inventory;
}