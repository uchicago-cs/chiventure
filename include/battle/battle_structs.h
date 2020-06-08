#ifndef BATTLE_STRUCTS_H
#define BATTLE_STRUCTS_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "playerclass/class.h"


/* items stub */
typedef struct item {
    int id;
    int quantity;
    int durability;
    char* name;
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
    item_t *item;
    int id;
    // NOTE: functions to create move_new do not take into account a name
    char* name;
    char* info;
    bool attack;
    int damage;
    int defense;
    struct move *next;
    struct move *prev;
} move_t;

/* stats stub */
typedef struct stat {
    int speed;
    int defense;
    int strength;
    int dexterity;
    int hp;
    int max_hp;
    int xp;
    int level;
} stat_t;

#endif
