#ifndef BATTLE_STRUCTS_H
#define BATTLE_STRUCTS_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "playerclass/class.h"


/* battle_items stub */
typedef struct battle_item {
    int id;
    bool is_weapon;
    int effectiveness_decrement;
    int quantity;
    int durability;
    char* name;
    char* description;
    bool battle;
    int attack;
    int defense;
    int hp;
    struct battle_item *next;
    struct battle_item *prev;
} battle_item_t;

/* moves stub */
typedef struct move {
    battle_item_t *item;
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
    int max_sp;
    int sp;
    int speed;
    int phys_atk;
    int mag_atk;
    int phys_def;
    int mag_def;
    int crit;
    int accuracy;
    int hp;
    int max_hp;
    int xp;
    int level;
} stat_t;

/* stat changes stub */
typedef struct stat_changes {
    int speed;
    int max_sp;
    int sp;
    int phys_atk;
    int mag_atk;
    int phys_def;
    int mag_def;
    int crit;
    int accuracy;
    int hp;
    int max_hp;
    int turns_left;
    struct stat_changes* next;
    struct stat_changes* prev;
} stat_changes_t;

#endif
