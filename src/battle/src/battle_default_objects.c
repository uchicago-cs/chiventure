#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_structs.h"

/* resource: https://stackoverflow.com/questions/17846212/generate-a-random-number-between-1-and-10-in-c/49099642 */
/* and: https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand */


/* Helper function to generate random integer in range min to max */
int randnum(int min, int max)
{
    // random seed
    srand((unsigned)time(NULL));

    int rv = rand() % (max + 1 - min) + min; 
    return rv; 
}

/* Returns random default item */
item_t *get_random_default_item()
{
    // is there a function to initialize/allocate memory for item_t struct? if not..
    item_t *rv_item = calloc(1, sizeof(item_t));
    assert(rv_item != NULL);
    
    char* name_array[]= {"SWORD", "SHIELD", "SPEAR", "HAMMER", "STICK", 
                         "CLUB", "TRIDENT", "BOW & ARROW", "SHIV", "AXE"};

    rv_item->id = randnum(1,10);
    rv_item->quantity = 1;
    rv_item->durability = randnum(20,70);   
    rv_item->name = name_array[randnum(0,9)];
    rv_item->description = strcat("It is a ", rv_item->name);
    rv_item->battle = true;
    rv_item->attack = randnum(20,70);
    rv_item->defense = randnum(20,70);
    rv_item->hp = randnum(50,100);
    rv_item->next = NULL;
    rv_item->prev = NULL;

    return rv_item;
}

/* Returns random default move*/
move_t *get_random_default_move()
{
    move_t *rv_move = calloc(1, sizeof(move_t));
    assert(rv_move != NULL);

    char *name_array[] = {"JAB", "KICK", "HEADBUTT", "GRAPPLE", "SLAP"
                          "UPPERCUT", "HAMMERFIST", "BITE", "THRASH", "THROW"}
    
    rv_move->item = get_random_default_item();
    rv_move->id = randnum(1,10);
    rv_move->name = name_array[randnum(0,9)];
    rv_move->info = strcat("Move is ", rv_move->name);
    rv_move->attack = true;
    rv_move->damage = randnum(20,70);
    rv_move->defense = randnum(20,70);
    rv_move->next = NULL;
    rv_move->prev = NULL;
}
