#ifndef BATTLE_STRUCTS_H
#define BATTLE_STRUCTS_H

#include <stdbool.h>
#include <string.h>

/* max name length */
#define MAX_NAME_LEN (50)

typedef struct stats
{
    double speed;
    double strength;
    double dexterity;
    double charisma;
    double hp;
    double max_hp;
    double xp;
    unsigned int level;
} stats_t;

typedef struct item
{
    int id;
    int quantity;
    double durability;
    char* description;
    bool battle;
    double attack;
    double defense;
    double hp;
    struct item *next;
    struct item *prev;
} item_t;

typedef struct armor
{
    char* description;
    double defense;
    double weight;
    struct armor *next;
    struct armor *prev;
} armor_t;


typedef struct move
{
    item_t *item;
    bool attack;
    int damage;
    int defense;
    struct move *next;
    struct move *prev;
} move_t;

/** Players get stat bonuses based on their class.
This enum type is part of the class struct. Whichever stat
is stored in class_t.st is increased by class_t.bonus **/
typedef enum possible_stats
{
    spd,
    str,
    dex,
    chrsma
} possible_stats_t;

/* class stub */
typedef enum class_type
{
    bard,
    cleric,
    paladin,
    wizard
} class_type_t;

/** The player class struct, which includes the enum class, a short
description of the class, which stat the class gets a bonus for, and
how much that bonus is **/
typedef struct class
{
    class_type_t cl;
    char *info;
    possible_stats_t st;
    int bonus;
} class_t;


typedef struct player
{
    class_t cl;
    item_t *inventory;
    armor_t *armors;
    stats_t *stats;
    move_t *moves;
} player_t;

typedef struct enemy
{
    char *name;
    class_t cl;
    item_t *inventory;
    armor_t *armors;
    stats_t *stats;
    move_t *moves;
} enemy_t;


#endif
