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
    target_type_t stat_mods; //whether a move changes a user's stats, the opponent's stats, both, or neither
    target_type_t effects; //whether a move has an effect that targets the user, opponent, both, or neither
    struct move *next;
    struct move *prev;

    //stub to be replaced when merging with other team
    target_count_t count; 
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

/* stat changes stub */
typedef struct stat_changes {
    int speed;
    int defense;
    int strength;
    int dexterity;
    int hp;
    int max_hp;
    int turns_left;
    struct stat_changes* next;
    struct stat_changes* prev;
} stat_changes_t;

#endif
