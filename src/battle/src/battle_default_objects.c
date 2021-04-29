
#include <stdio.h>
#include <stdlib.h>
#include "battle/battle_structs.h"

/*resource:https://stackoverflow.com/questions/17846212/generate-a-random-number-between-1-and-10-in-c/49099642 */
/*and: https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand */


/*Helper function to generate random numbers from min to max*/
int randnum(int min, int max)
{
    //random seed
    srand((unsigned)time(NULL));

    int rv = rand() % (max + 1 - min) + min; 

    return rv; 

}

item_t *get_random_default_item()
{
    //is there a function to initialize/allocate memory for item_t struct? if not..
    item_t *rv_item = (item_t)malloc(sizeof(item_t));
    
    char name_array[]= {"SWORD", "SHIELD", "SPEAR", "HAMMER", "STICK", "CLUB", "TRIDENT", "BOW & ARROW", "SHIV", "AXE"};

    rv_item->id = randnum(1,10);
    rv_item->quantity = randnum(1,10);
    rv_item->durability = randnum(20,70);   
    rv_item->name = name_array[randnum(0,9)];
    //not sure what to do for the description
    rv_item->description = NULL;
    //also unsure about the "battle" field in item_t struct
    rv_item->battle = randnum(0,1);
    rv_item->attack = randnum(20,70);
    rv_item->defense = randnum(20,70);
    rv_item->hp = randnum(50,100);
    rv_item->next = NULL;
    rv_item->prev = NULL;

    return rv_item;

}