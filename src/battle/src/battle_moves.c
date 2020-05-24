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
<<<<<<< HEAD
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(SIZE, sizeof(char));
    strncpy(move->info, "Diss track", SIZE);

=======
    move_t* move = (move_t*) malloc(sizeof(move_t));
    
    move->info = (char*) malloc(sizeof(char) * 100);
    strcpy(move->info, "Diss track");
    
>>>>>>> 5413e47396586b8381f9c7306edf668ed22b4af3
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
<<<<<<< HEAD
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(SIZE,sizeof(char));
    strncpy(move->info, "Divine smite", SIZE);

=======
    move_t* move = (move_t*) malloc(sizeof(move_t));
    
    move->info = (char*) malloc(sizeof(char) * 100);
    strcpy(move->info, "Divine smite");
    
>>>>>>> 5413e47396586b8381f9c7306edf668ed22b4af3
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
<<<<<<< HEAD
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(SIZE, sizeof(char));
    strncpy(move->info, "360 no scope", SIZE);

=======
    move_t* move = (move_t*) malloc(sizeof(move_t));
    
    move->info = (char*) malloc(sizeof(char) * 100);
    strcpy(move->info, "360 no scope");
    
>>>>>>> 5413e47396586b8381f9c7306edf668ed22b4af3
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
<<<<<<< HEAD
    move_t* move = (move_t*) calloc(1, sizeof(move_t));

    move->info = (char*) calloc(SIZE, sizeof(char));
    strncpy(move->info, "Magic, betches", SIZE);

=======
    move_t* move = (move_t*) malloc(sizeof(move_t));
    
    move->info = (char*) malloc(sizeof(char) * 100);
    strcpy(move->info, "Magic, betches");
    
>>>>>>> 5413e47396586b8381f9c7306edf668ed22b4af3
    move->id = 130;

    move->item = NULL;

    move->attack = true;
    move->damage = 10;
    move->defense = 0;

    return move;
}
