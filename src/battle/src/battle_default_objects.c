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
    char* name_array[]= {"SWORD", "HAMMER", "SLIME", "SLEEPING GAS", "SQUID INK", "LAUGHING GAS"};
    char* description_array[] = {"Reduces enemy's HP by 20", "Reduces enemy's HP by 10", 
                                 "Reduces enemy's ATTACK by 5 ", "Reduces enemy's ATTACK by 10",
                                 "Reduces enemy's DEFENSE by 10", "Reduces enemy's DEFENSE by 15"};
    int hp_array[] = {-20, -10, 0, 0, 0, 0};
    int attack_array[] = {0, 0, -5, -10, 0, 0};
    int defense_array[] = {0, 0, 0, 0, -10, -15};
    int durability_array[] = {100, 80, 60, 40, 30, 20};

    rv_weapon->id = rand;
    rv_weapon->is_weapon = true;
    //set effectiveness_decrement?
    rv_weapon->quantity = randnum(1, 3);
    rv_weapon->durability = durability_array[rand - 1]; 

    // sets name
    int name_len = strlen(name_array[rand - 1]);
    rv_weapon->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_weapon->name, name_array[rand - 1], name_len + 1);
    // sets description
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
}

/* See battle_default_objects.h */
battle_item_t *get_random_default_consumable()
{
    battle_item_t *rv_item = calloc(1, sizeof(battle_item_t));
    assert(rv_item != NULL);

    int rand = randnum(1, 4); 
    char* name_array[]= {"Elixir of Life", "Healing Potion", "Defense Up", "Strength Up"};
    char* description_array[] = {"Adds 50 to your HP!", "Adds 20 to your HP!", 
                                 "Adds 5 to your defense!", "Adds 5 to your strength!"};
    int hp_array[] = {50, 20, 0, 0};
    int attack_array[] = {0, 0, 0, 5};
    int defense_array[] = {0, 0, 5, 0};

    rv_item->id = rand;
    rv_item->is_weapon = false;
    rv_item->effectiveness_decrement = 0;
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
    bool attack = true;
    int damage = rand * 10;
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

    rv_stat->speed = randnum(5, 10);
    rv_stat->defense = randnum(5, 15);
    rv_stat->strength = randnum(10, 20);
    rv_stat->dexterity = randnum(10, 20);
    rv_stat->hp = randnum(30, 70);
    rv_stat->max_hp = 70;
    rv_stat->xp  = randnum(50, 100);
    rv_stat->level = randnum(1, 10);

    return rv_stat;
}
