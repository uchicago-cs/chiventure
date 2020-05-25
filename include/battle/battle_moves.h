#ifndef BATTLE_MOVES_H
#define BATTLE_MOVES_H

#include <stdbool.h>
#include <string.h>
#include "battle_classes.h"

/* define max size of class info strings */
static const int SIZE2 = 100;


/* items stub */
typedef struct item {
    int id;
    int quantity;
    int durability;
    char* description;
    bool battle;
    int attack;
    int defense;
    int hp;
    struct item *next;
    struct item *prev;
} item_t;


/* moves stub */
typedef struct move {
    char *info;
    int id;
    item_t *item;
    bool attack;
    int damage;
    int defense;
    struct move *next;
    struct move *prev;
} move_t;


/* For use in testing battle code,
make a test move for each class */

move_t *test_move_bard();

move_t *test_move_cleric();

move_t *test_move_paladin();

move_t *test_move_wizard();


#endif

