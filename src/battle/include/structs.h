#include <stdbool.h>
#include <string.h>
//#include
#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct
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

typedef struct
{
    int id;
    int quantity;
    double durability;
    char* description;
    bool battle;
    double attack;
    double defense;
    double hp;
} item_t;

typedef struct
{
    char* description;
    double defense;
    double weight;
} armor_t;


typedef struct _ilist_t ilist_t;
struct _ilist_t
{
    item_t *item;
    ilist_t *next;
};

typedef struct _alist_t alist_t;
struct _alist_t
{
    armor_t *armor;
    alist_t *next;
};


/** Players get stat bonuses based on their class.
This enum type is part of the class struct. Whichever stat
is stored in class_t.st is increased by class_t.bonus **/
enum stats{spd, str, dex, chrsma};

/** Players can be one of four classes as outlined by the
below enum type. **/
enum class{bard, cleric, paladin, wizard};

/** The player class struct, which includes the enum class, a short
description of the class, which stat the class gets a bonus for, and
how much that bonus is **/
typedef struct
{
    enum class cl;
    char *info;
    enum stats st;
    int bonus;
} class_t;


typedef struct
{
    class_t cl;
    ilist_t *inventory;
    alist_t *armor;
    stats_t *stats;
    mlist_t *moves;
} player_t;

typedef struct
{
    char *name;
    stats_t *stats;
    class_t cl;
    ilist_t *inv;
    alist_t *armor;
    mlist_t *moves;
} enemy_t;

typedef struct
{
    item_t *item;
    bool attack;
    int damage;
    int defense;
} move_t;

typedef struct _mlist_t mlist_t;
struct _mlist_t
{
    move_t *move;
    mlist_t *next;
};


#endif
