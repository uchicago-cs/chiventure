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

/* This defines what type of damage if any the move would do. 
    We will do this to specify attack. */
/*
typedef enum damage_type {
    PHYS, //A move that would inflict physical damage on the opponent.
    MAG, //A move that would inflict magical damage on the opponent. 
    NO_DAMAGE //A move that does not inflict damage.
} damage_type_t;

typedef enum target_type {
    USER, //A move that targets the user.
    TARGET, //A move that would target the target.
    BOTH,  //A move that targets both the user and target. How it affects both can be different.
    NO_TARGET //A move that does not target the opponent nor the user that is not an attacking move.
} target_type_t;

typedef enum target_count {
    SINGLE, //A move that hits a single target
    MULTI //A move that hits multiple targets
} target_count_t;*/
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

/* moves stub */
typedef struct move_t {
    int id; 
    char* name; 
    char* info; 
    damage_type_t dmg_type; 
    target_type_t stat_mods; 
    target_type_t effects; 
    target_count_t count; 
    int sp_cost; 
    battle_item_t* req_item; 
    int damage; 
    int accuracy; 
    stat_changes_t* user_mods; 
    stat_changes_t* opponent_mods; 
    struct move_t* prev; 
    struct move_t* next;
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


#endif
