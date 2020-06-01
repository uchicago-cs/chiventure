#ifndef BATTLE_MOVES_H
#define BATTLE_MOVES_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "battle_structs.h"

/* defines max length of class info */
#define MAX_MOVE_INFO_LEN (100)

move_t *move_new(char* info, int id, item_t *items, bool attack,
                 int damage, int defense);

int move_init(move_t *move, char* info, int id, item_t *items, bool attack,
                 int damage, int defense);

int move_free(move_t *move);

/* For use in testing battle code,
make a test move for each class */

move_t *test_move_bard();

move_t *test_move_cleric();

move_t *test_move_paladin();

move_t *test_move_wizard();


#endif
