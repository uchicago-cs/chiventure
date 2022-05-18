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
} target_count_t;

/* stat changes stub */
typedef struct stat_changes {
    int speed; //the amount speed changes from a stat change
    int max_sp; //the amount max_sp changes from a stat change
    int sp; //the amount sp changes from a stat change
    int phys_atk; //the amount phys_atk changes from a stat change
    int mag_atk; //the amount mag_atk changes from a stat change
    int phys_def; //the amount phys_def changes from a stat change
    int mag_def; //the amount mag_def changes from a stat change
    int crit; //the amount crit changes from a stat change
    int accuracy; //the amount accuracy changes from a stat change
    int hp; //the amount hp changes from a stat change
    int max_hp; //the amount max_hp changes from a stat change
    int turns_left; //specifies the turns left of the stat changes
    struct stat_changes* next; //the next stat_changes in the list, or NULL for no stat_change
    struct stat_changes* prev; //the previous stat_changes in the list, or NULL for no stat_change
} stat_changes_t;

/* moves stub */
typedef struct move_t {
    int id; //the unique identifier of the move
    char* name; //the name of the move
    char* info; //a description of what the move does
    damage_type_t dmg_type; //whether a move does physical damage, magical damage, or no damage
    target_type_t stat_mods; //whether a move changes a user's stats, the opponent's stats, both, or neither
    target_type_t effects; //whether a move has an effect that targets the user, opponent, both, or neither
    target_count_t count; //whether a move hits a single target or multiple targets
    int sp_cost; //the amount of sp required to use a mov
    battle_item_t* req_item; //an item required to use the move or NULL for none
    int damage; //the damage the move will do
    int accuracy; //the accuracy of the move
    stat_changes_t* user_mods; //stat changes for the user
    stat_changes_t* opponent_mods; //stat changes for the opponent
    struct move_t* prev; //the previous move in the list, or NULL for no move
    struct move_t* next; //the next move in the list, or NULL for no move
} move_t;

/* stats stub */
typedef struct stat {
    int max_sp; //The maximum amount of skill/special points this unit can currently have.
    int sp; //The current amount of skill/special points of the player; magic and skills deplete this resource.
    int speed;
    int phys_atk; //The physical damage capacity of the unit; used in damage calculation against phys_def.
    int mag_atk; //The magical damage capacity of the unit; used in damage calculation against mag_def.
    int phys_def; //The physical damage resistance of the unit; calculated against phys_atk.
    int mag_def; //The magical damage resistance of the unit; calculated against mag_atk;
    int crit; //The default odds of this unit getting bonus damage; the value is out of 100.
    int accuracy; //The default odds of any move used by this unit hitting the target; the value is out of 100.
    int hp; //The current health of the unit; the battle ends when this hits 0.
    int max_hp; //The maximum amount of health this unit can currently have.
    int xp; //The current amount of experience points gained by this unit.
    int level; //The current level of the unit.
} stat_t;


#endif
