#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_default_objects.h"

/* resource: https://stackoverflow.com/questions/17846212/generate-a-random-number-between-1-and-10-in-c/49099642 */
/* and: https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand */

/* See battle_default_objects.h */
int randnum(int min, int max)
{
    /* must put "srand(time(0));" before using 
    these functions in a file to set the seed */

    int rv = rand() % (max + 1 - min) + min; 
    return rv; 
}

/* See battle_default_objects.h */
battle_item_t *get_random_offensive_item()
{
    battle_item_t *rv_offitem = calloc(1, sizeof(battle_item_t));
    assert(rv_offitem != NULL);

    int rand = randnum(1, 6) - 1; 
    char* name_array[]= {"Sword", "Hammer", "Slime", "Sleeping gas", 
                         "Squid ink", "Laughing gas"};
    char* description_array[] = {"Reduces enemy's HP by 20", 
                                 "Reduces enemy's HP by 10", 
                                 "Reduces enemy's ATTACK by 5", 
                                 "Reduces enemy's ATTACK by 10",
                                 "Reduces enemy's DEFENSE by 10", 
                                 "Reduces enemy's DEFENSE by 15"};

    int mod_array[] = {-20, -10, -5, -10, -10, -15};

    rv_offitem->id = rand + 1;
    
    /* sets name */
    int name_len = strlen(name_array[rand]);
    rv_offitem->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_offitem->name, name_array[rand], name_len + 1);

    /* sets description */
    int description_len = strlen(description_array[rand]);
    rv_offitem->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_offitem->description, description_array[rand], description_len + 1);

    rv_offitem->attributes = stat_changes_new();
    switch (rand) {
        case 0:
            rv_offitem->attributes->hp = mod_array[rand];
            break;
        case 1:
            rv_offitem->attributes->hp = mod_array[rand];
            break;
        case 2:
            rv_offitem->attributes->phys_atk = mod_array[rand];
            break;
        case 3:
            rv_offitem->attributes->phys_atk = mod_array[rand];
            break;
        case 4:
            rv_offitem->attributes->phys_def = mod_array[rand];
            break;
        default:
            rv_offitem->attributes->phys_def = mod_array[rand]; 
    }
    
    rv_offitem->quantity = randnum(1, 3);
    rv_offitem->attack = true;

    rv_offitem->next = NULL;
    rv_offitem->prev = NULL;
    return rv_offitem;
}

battle_equipment_t *get_random_equip_weapon()
{
    battle_equipment_t *rv_weapon = calloc(1, sizeof(battle_equipment_t));
    assert(rv_weapon != NULL);

    int rand = (randnum(1, 4)) - 1; 
    char* name_array[]= {"Sword of the Leviathan", "Hammer of Thor", 
                         "Slime Ball", "Wand of the Restless"};
    char* description_array[] = {"Adds 25 to HP", "Adds 15 to Physical Attack",
                                 "Adds 15 to Speed", "Adds 15 to Magical Attack"};
    int mod_array[] = {25, 15, 15, 15};

    rv_weapon->id = rand + 1; 

    // sets name
    int name_len = strlen(name_array[rand]);
    rv_weapon->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_weapon->name, name_array[rand], name_len + 1);

    // sets description
    int description_len = strlen(description_array[rand]);
    rv_weapon->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_weapon->description, description_array[rand], description_len + 1);
    
    rv_weapon->attributes = stat_changes_new();
    switch (rand) {
        case 0:
            rv_weapon->attributes->hp = mod_array[rand];
            break;
        case 1:
            rv_weapon->attributes->phys_atk = mod_array[rand];
            break;
        case 2:
            rv_weapon->attributes->speed = mod_array[rand];
            break;
        default:
            rv_weapon->attributes->mag_atk = mod_array[rand];
    }

    rv_weapon->type = WEAPON;

    return rv_weapon;
}

battle_equipment_t *get_random_equip_armor()
{
    battle_equipment_t *rv_armor = calloc(1, sizeof(battle_equipment_t));
    assert(rv_armor != NULL);

    int rand = (randnum(1, 4)) - 1; 
    char* name_array[]= {"Simple Leather Armor", "Chainmail", 
                         "Heavy Armor", "Loincloth"};
    char* description_array[] = {"Adds 10 to Physical Defense.", 
                                 "Adds 15 to Physical Defense.",
                                 "Adds 25 to Physical Defense.", 
                                 "Adds 15 to Magical Defense."};
    int mod_array[] = {10, 15, 25, 15};

    rv_armor->id = rand + 1; 

    // sets name
    int name_len = strlen(name_array[rand]);
    rv_armor->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_armor->name, name_array[rand], name_len + 1);

    // sets description
    int description_len = strlen(description_array[rand]);
    rv_armor->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_armor->description, description_array[rand], description_len + 1);
    
    rv_armor->attributes = stat_changes_new();
    switch (rand) {
        case 0:
            rv_armor->attributes->phys_def = mod_array[rand];
            break;
        case 1:
            rv_armor->attributes->phys_def = mod_array[rand];
            break;
        case 2:
            rv_armor->attributes->phys_def = mod_array[rand];
            break;
        default:
            rv_armor->attributes->mag_def = mod_array[rand];
    }

    rv_armor->type = ARMOR;

    return rv_armor;
}

battle_equipment_t *get_random_equip_accessory()
{
    battle_equipment_t *rv_access = calloc(1, sizeof(battle_equipment_t));
    assert(rv_access != NULL);

    int rand = (randnum(1, 4)) - 1; 
    char* name_array[]= {"Heart-Shaped Pendant", "Faded Ribbon", 
                         "Winged Boots", "Sword Charm"};
    char* description_array[] = {"Adds 20 to HP.", 
                                 "Adds 10 to Physical Defense.",
                                 "Adds 15 to Speed.", 
                                 "Adds 10 to Magical Defense."};
    int mod_array[] = {20, 10, 15, 10};

    rv_access->id = rand + 1; 

    // sets name
    int name_len = strlen(name_array[rand]);
    rv_access->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_access->name, name_array[rand], name_len + 1);

    // sets description
    int description_len = strlen(description_array[rand]);
    rv_access->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_access->description, description_array[rand], description_len + 1);
    
    rv_access->attributes = stat_changes_new();
    switch (rand) {
        case 0:
            rv_access->attributes->hp = mod_array[rand];
            break;
        case 1:
            rv_access->attributes->phys_def = mod_array[rand];
            break;
        case 2:
            rv_access->attributes->speed = mod_array[rand];
            break;
        default:
            rv_access->attributes->mag_def = mod_array[rand];
    }

    rv_access->type = ACCESSORY;

    return rv_access;
}



/* See battle_default_objects.h */
battle_item_t *get_random_default_consumable()
{
    battle_item_t *rv_item = calloc(1, sizeof(battle_item_t));
    assert(rv_item != NULL);

    int rand = randnum(1, 4); 
    char* name_array[]= {"Elixir of Life", "Healing Potion", 
                         "Defense Up", "Strength Up"};
    char* description_array[] = {"Adds 50 to your HP!", "Adds 20 to your HP!", 
                                 "Adds 5 to your Physical Defense!", 
                                 "Adds 5 to your Physical Attack!"};
    int mod_array[] = {50, 20, 5, 5};

    rv_item->id = rand;

    // sets name
    int name_len = strlen(name_array[rand - 1]);
    rv_item->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_item->name, name_array[rand - 1], name_len + 1);

    // sets description
    int description_len = strlen(description_array[rand - 1]);
    rv_item->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_item->description, description_array[rand - 1], description_len + 1);

    rv_item->attributes = stat_changes_new();
    switch(rand){

        case 1:
            rv_item->attributes->hp = mod_array[rand-1];
            break;
        case 2:
            rv_item->attributes->hp = mod_array[rand-1];
            break;
        case 3:
            rv_item->attributes->phys_def = mod_array[rand-1];
            break;
        default:
            rv_item->attributes->phys_atk = mod_array[rand-1];
    }

    rv_item->quantity = randnum(1, 3);
    rv_item->attack = false;

    rv_item->next = NULL;
    rv_item->prev = NULL;

    return rv_item;
}

/* See battle_default_objects.h */
move_t *get_random_default_move()
{
    int rand = randnum(1,10);
    char *name_array[] = {"SLAP", "JAB", "KICK", "HEADBUTT", "GRAPPLE", 
                          "UPPERCUT", "HAMMERFIST", "BITE", "THRASH", "THROW"};

    battle_item_t *item = get_random_default_consumable();
    int id = rand;
    int info_len = strlen(name_array[rand - 1]);
    char* info = (char*)calloc(info_len + 1, sizeof(char));
    strncpy(info, name_array[rand - 1], info_len + 1);
    int damage = rand * 5 + 40;

    move_t *rv_move = move_new(id, "", info, PHYS, NO_TARGET, NO_TARGET, SINGLE,
                               0, NULL, damage, 100, NULL, NULL, NULL, NULL);
    
    assert(rv_move != NULL);
    return rv_move;
/* PROSPECTIVE CHANGES
    //Array of possible moves and descriptions.
    int rand = randnum(1,10) - 1;
    char *name_array[] = {"punch", "kick", "jab", "headbutt", "grapple", 
                          "fireball", "water gun", "shocking grasp", "freeze", "drain"};
    char *desc_array[] = {"A standard punch. Kapow!", "A standard kick.", 
                          "A jab aimed at a vital area.", "A standard headbutt.", 
                          "The opponent is temporarily grappled, reducing their speed.",
                          "A fireball hot enough to cook a steak. And the opponent, too.",
                          "The opponent is hit by a blast of water.", 
                          "The opponent is grabbed and shocked with electricity.",
                          "The opponent is frozen, reducing their speed.",
                          "The opponent's HP is drained and added to the user's."};
    
    // Sets the id, name, and description.
    int id = rand;
    char name[20], desc[75];
    strcpy(name, name_array[rand]);
    strcpy(desc, desc_array[rand]);

    //Sets the damage type.
    damage_type_t dmg_type;
    if (rand < 5)
    {
        dmg_type = PHYS; 
    } 
    else 
    {
        dmg_type = MAG;
    }

    //Sets the appropriate targets for stat mods and effects.
    target_type_t stat_mods, effects;
    if (rand == 4 || rand == 8)
    {
        stat_mods = TARGET;
    } 
    else if (rand == 9)
    {
        stat_mods == BOTH;
    }
    else
    {
        stat_mods = NO_TARGET;
    }
    effects == NO_TARGET;
    
    //Sets the amount of targets.
    target_count_t count = SINGLE;

    //Sets the sp cost.
    int sp_cost;
    if (rand < 5)
    {
        sp_cost = 0;
    }
    else
    {
        sp_cost = 10;
    }

    //Sets the required item.
    battle_item_t* req_item = NULL;

    //Sets the damage and accuracy.
    int damage = randnum(50, 100), accuracy = randnum(85, 100);

    //Sets the stat changes.
    stat_changes_t *user_mod, *opp_mod;
    if (!(rand == 4) && rand < 8)
    {
        user_mod == NULL;
        opp_mod == NULL;
    }
    else if (rand == 4 || rand == 8)
    {
        user_mod == NULL;
        opp_mod = stat_changes_new();
        stat_changes_init(opp_mod);
        opp_mod->speed = -10;
    }
    else if (rand == 9)
    {
        user_mod = stat_changes_new();
        stat_changes_init(user_mod);
        user_mod->hp = 15;
        opp_mod = stat_changes_new();
        stat_changes_init(opp_mod);
        opp_mod->hp = -15;
    }

    move_t *rv_move = move_new(id, name, desc, dmg_type, stat_mods, effects, 
                               count, sp_cost, req_item, damage, accuracy, 
                               user_mod, opp_mod, NULL, NULL);
    
    assert(rv_move != NULL);
    return rv_move; */
}

/* See battle_default_objects.h */
stat_t* get_random_stat()
{
    stat_t *rv_stat = calloc(1, sizeof(stat_t));
    assert(rv_stat != NULL);

    rv_stat->max_hp = randnum(50, 150);
    rv_stat->hp = rv_stat->max_hp;
    rv_stat->surrender_level = 0;
    rv_stat->max_sp = randnum(50, 80);
    rv_stat->sp = rv_stat->max_sp;
    rv_stat->phys_atk = randnum(20, 100);
    rv_stat->mag_atk = 110 - rv_stat->phys_atk;
    rv_stat->phys_def = randnum(20, 100);
    rv_stat->mag_def = 110 - rv_stat->phys_def;
    rv_stat->speed = randnum(40, 90);
    rv_stat->crit = randnum(5, 15);
    rv_stat->accuracy = randnum(80, 100);
    rv_stat->xp = randnum(100, 500);
    rv_stat->level = randnum(1, 10);

    return rv_stat;
}
