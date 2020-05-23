#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/battle/battle_moves.h"


 /* Creates test move for bard 
  *
  * Parameters:
  *  none, values are hard coded in
  *
  * Returns:
  *  - A pointer to the test move
  *
  */
move_t *test_move_bard()
{
    move_t* move = (move_t*) malloc(sizeof(move_t);
    
    move->info = (char*) malloc(sizeof(char) * 100));
    strcpy(move->info, "Diss track");
    
    move->id = 100;

    move->item = NULL;

    move->attack = true;
    move->damage = 15;
    move->defense = 0;

    return move;
}


/* Creates test move for cleric 
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to the test move
 *
 */
move_t *test_move_cleric()
{
    move_t* move = (move_t*) malloc(sizeof(move_t);
    
    move->info = (char*) malloc(sizeof(char) * 100));
    strcpy(move->info, "Divine smite");
    
    move->id = 110;

    move->item = NULL;

    move->attack = true;
    move->damage = 10;
    move->defense = 0;

    return move;
}


/* Creates test move for paladin 
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to the test move
 *
 */
move_t *test_move_paladin()
{
    move_t* move = (move_t*) malloc(sizeof(move_t));
    
    move->info = (char*) malloc(sizeof(char) * 100);
    strcpy(move->info, "360 no scope");
    
    move->id = 120;

    move->item = NULL;

    move->attack = true;
    move->damage = 20;
    move->defense = 0;

    return move;
}


/* Creates test move for wizard 
 *
 * Parameters:
 *  none, values are hard coded in
 *
 * Returns:
 *  - A pointer to the test move
 *
 */
move_t *test_move_wizard()
{
    move_t* move = (move_t*) malloc(sizeof(move_t));
    
    move->info = (char*) malloc(sizeof(char) * 100);
    strcpy(move->info, "Magic, betches");
    
    move->id = 130;

    move->item = NULL;

    move->attack = true;
    move->damage = 10;
    move->defense = 0;

    return move;
}
