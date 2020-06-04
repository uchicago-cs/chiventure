/* 
 * A demo of playerclass functionality using x/battle-systems' battle_flow_example.c
 * This executable aims to demonstrate:
 * - Some information playerclass stores
 * - Proof-of-concept class-specific skills
 * - Class-specific item restrictions
 * - How playerclass plays a role in the battle flow
 */ 

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "playerclass/class.h"
#include "playerclass/class_item_restriction.h"
#include "playerclass/class_structs.h"
#include "demo-functions.h"
#include "class-list.h"
#include "../../battle/examples/battle_move_maker.h"

void main()
{
    move_list_t* classlist = move_list();

    fprintf(stdout, "Please choose a class from the the following list:\n");
    list_class_show(classlist);

    fprintf(stdout, "You have chosen: \n");
    class_show(classlist->c);

    fprintf(stdout, "Proceeding with battle.\n");
}