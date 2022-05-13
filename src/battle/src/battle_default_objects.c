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
battle_item_t *get_random_default_weapon()
{
    battle_item_t *rv_weapon = calloc(1, sizeof(battle_item_t));
    assert(rv_weapon != NULL);

    int rand = randnum(1, 6); 
    char* name_array[]= {"Sword", "Hammer", "Slime", "Sleeping gas", "Squid ink", "Laughing gas"};
    char* description_array[] = {"Reduces enemy's HP by 20", "Reduces enemy's HP by 10", 
                                 "Reduces enemy's ATTACK by 5", "Reduces enemy's ATTACK by 10",
                                 "Reduces enemy's DEFENSE by 10", "Reduces enemy's DEFENSE by 15"};
    int hp_array[] = {-20, -10, 0, 0, 0, 0};
    int attack_array[] = {0, 0, -5, -10, 0, 0};
    int defense_array[] = {0, 0, 0, 0, -10, -15};
    int durability_array[] = {100, 80, 60, 40, 30, 20};

    rv_weapon->id = rand;
    rv_weapon->is_weapon = true;
    rv_weapon->effectiveness_decrement = 10;
    rv_weapon->quantity = randnum(1, 3);
    rv_weapon->durability = durability_array[rand - 1]; 

    /* sets name */
    int name_len = strlen(name_array[rand - 1]);
    rv_weapon->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_weapon->name, name_array[rand - 1], name_len + 1);
    /* sets description */
    int description_len = strlen(description_array[rand - 1]);
    rv_weapon->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_weapon->description, description_array[rand - 1], description_len + 1);
                                     
    rv_weapon->battle = true;
    rv_weapon->attack = attack_array[rand - 1];
    rv_weapon->defense = defense_array[rand - 1];
    rv_weapon->hp = hp_array[rand - 1];
    rv_weapon->next = NULL;
    rv_weapon->prev = NULL;
    return rv_weapon;

/*  --BATTLE ITEM TEST CHANGES TO BE IMPLEMENTED WITH BATTLE ITEM CHANGES
    battle_item_t *rv_weapon = calloc(1, sizeof(battle_item_t));
    assert(rv_weapon != NULL);

    int rand = (randnum(1, 4)) - 1; 
    char* name_array[]= {"Sword of the Leviathan", "Hammer of Thor", 
                         "Slime Ball", "Wand of the Restless"};
    char* description_array[] = {"Adds 25 to HP", "Adds 15 to Physical Attack",
                                 "Adds 15 to Speed", "Adds 15 to Magical Attack"};
    int mod_array[] = {25, 15, 15, 15};

    rv_weapon->id = rand;
    rv_weapon->is_weapon = true;
    rv_weapon->effectiveness_decrement = 10;
    rv_weapon->quantity = 1;
    rv_weapon->durability = 1; 

    // sets name
    int name_len = strlen(name_array[rand]);
    rv_weapon->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_weapon->name, name_array[rand], name_len + 1);
    // sets description
    int description_len = strlen(description_array[rand]);
    rv_weapon->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_weapon->description, description_array[rand], description_len + 1);
    
    rv_weapon->battle = true;
//
    if (rand == 0) {
        rv_item->hp = mod_array[rand];
    } else if (rand == 1) {
        rv_item->phys_atk = mod_array[rand];
    } else if (rand == 2) {
        rv_item->speed = mod_array[rand];
    } else if (rand == 3) {
        rv_item->mag_atk = mod_array[rand];
    }
//

    rv_weapon->next = NULL;
    rv_weapon->prev = NULL;

    return rv_weapon;
*/
}

/* See battle_default_objects.h */
battle_item_t *get_random_default_consumable()
{
    battle_item_t *rv_item = calloc(1, sizeof(battle_item_t));
    assert(rv_item != NULL);

    int rand = randnum(1, 4); 
    char* name_array[]= {"elixir of life ", "healing potion ", "defense up ", "strength up "};
    char* description_array[] = {"Adds 50 to your HP!", "Adds 20 to your HP!", 
                                 "Adds 5 to your defense!", "Adds 5 to your strength!"};
    int hp_array[] = {50, 20, 0, 0};
    int attack_array[] = {0, 0, 0, 5};
    int defense_array[] = {0, 0, 5, 0};

    rv_item->id = rand;
    rv_item->is_weapon = false;
    rv_item->quantity = randnum(1, 3);
    rv_item->durability = 0; 

    // sets name
    int name_len = strlen(name_array[rand - 1]);
    rv_item->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_item->name, name_array[rand - 1], name_len + 1);
    // sets description
    int description_len = strlen(description_array[rand - 1]);
    rv_item->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_item->description, description_array[rand - 1], description_len + 1);
                                     
    rv_item->battle = true;
    rv_item->attack = attack_array[rand - 1];
    rv_item->defense = defense_array[rand - 1];
    rv_item->hp = hp_array[rand - 1];
    rv_item->next = NULL;
    rv_item->prev = NULL;
    return rv_item;
/*  --BATTLE ITEM TEST CHANGES TO BE IMPLEMENTED WITH BATTLE ITEM CHANGES
    battle_item_t *rv_item = calloc(1, sizeof(battle_item_t));
    assert(rv_item != NULL);

    int rand = (randnum(1, 5)) - 1; 
    char* name_array[]= {"Elixir of Life", "Healing Potion", 
                         "Physical Attack-Up", " Physical Defense-Up", 
                         "Speed-Up"};
    char* description_array[] = {"Adds 50 to your HP!", "Adds 20 to your HP!", 
                                 "Adds 10 to your physical defense!", 
                                 "Adds 10 to your physical attack!", 
                                 "Adds 10 to your speed!"};
    int mod_array[] = {50, 20, 10, 10, 10}; 

    rv_item->id = rand;
    rv_item->is_weapon = false;
    rv_item->quantity = randnum(1, 3);
    rv_item->durability = 0; 

    // sets name
    int name_len = strlen(name_array[rand]);
    rv_item->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_item->name, name_array[rand], name_len + 1);
    // sets description
    int description_len = strlen(description_array[rand]);
    rv_item->description = (char*)calloc(description_len + 1, sizeof(char));
    strncpy(rv_item->description, description_array[rand], description_len + 1);
    
    rv_item->battle = true;

//
    if (rand < 2) {
        rv_item->hp = mod_array[rand];
    } else if (rand == 2) {
        rv_item->phys_atk = mod_array[rand];
    } else if (rand == 3) {
        rv_item->phys_def = mod_array[rand];
    } else if (rand == 4) {
        rv_item->speed = mod_array[rand];
    }
//

    rv_item->next = NULL;
    rv_item->prev = NULL;

    return rv_item;
*/
}

/* See battle_default_objects.h */
/* !!We will update this when we made move implementation changes */
move_t *get_random_default_move()
{
    int rand = randnum(1,10);
    char *name_array[] = {"slap", "jab", "kick", "headbutt", "grapple", 
                          "upperrcut", "hammerfist", "bite", "thrash", "throw"};

    battle_item_t *item = get_random_default_consumable();
    int id = rand;
    int info_len = strlen(name_array[rand - 1]);
    char* info = (char*)calloc(info_len + 1, sizeof(char));
    strncpy(info, name_array[rand - 1], info_len + 1);
    bool attack = true;
    int damage = rand * 5 + 40;
    int defense = rand * 10 + 5;

    move_t *rv_move = move_new(info, id, item, attack, damage, defense);
    
    assert(rv_move != NULL);
    return rv_move;
}

/* See battle_default_objects.h */
stat_t* get_random_stat()
{
    stat_t *rv_stat = calloc(1, sizeof(stat_t));
    assert(rv_stat != NULL);

    rv_stat->max_hp = randnum(50, 150);
    rv_stat->hp = rv_stat->max_hp;
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
