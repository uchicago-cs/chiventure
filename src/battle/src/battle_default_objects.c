#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "battle/battle_default_objects.h"

/* resource: https://stackoverflow.com/questions/17846212/generate-a-random-number-between-1-and-10-in-c/49099642 */
/* and: https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand */

/* See battle_default_objects.h */
int randnum(int min, int max)
{
    // random seed
    srand((unsigned)time(NULL));

    int rv = rand() % (max + 1 - min) + min; 
    return rv; 
}

/* See battle_default_objects.h */
battle_item_t *get_random_default_battle_item()
{
    battle_item_t *rv_item = calloc(1, sizeof(battle_item_t));
    assert(rv_item != NULL);

    int rand = randnum(1,10); 
    char* name_array[]= {"STICK", "HAMMER", "SHIV", "CLUB",  "BOW & ARROW", 
                         "SPEAR", "AXE", "TRIDENT", "SWORD", "SHIELD"};

    rv_item->id = rand;
    rv_item->quantity = 1;
    rv_item->durability = rand * 10; 

    int name_len = strlen(name_array[rand - 1]);
    rv_item->name = (char*)calloc(name_len + 1, sizeof(char));
    strncpy(rv_item->name, name_array[rand - 1], name_len + 1);
    
    rv_item->description = NULL; 
    rv_item->battle = true;
    rv_item->attack = rand * 10;
    rv_item->defense = rand * 10 + 5;
    rv_item->hp = rand * 10 + 10;
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

    battle_item_t *item = get_random_default_battle_item();
    int id = rand;
    char *info = name_array[rand - 1];
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

    rv_stat->speed = randnum(20, 50);
    rv_stat->defense = randnum(20, 50);
    rv_stat->strength = randnum(20, 50);
    rv_stat->dexterity = randnum(20, 50);
    rv_stat->hp = randnum(50, 100);
    rv_stat->max_hp = 100;
    rv_stat->xp  = randnum(20, 100);
    rv_stat->level = randnum(1, 5);

    return rv_stat;
}
