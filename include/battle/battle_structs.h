#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <string.h>

/* items stub */
typedef struct _item_t{
    int id;
    int quantity;
    int durability;
    char* description;
    bool battle;
    int attack;
    int defense;
    int hp;
    struct _item_t *next;
} item_t;

/* moves stub */
typedef struct _move_t{
    item_t *item;
    bool attack;
    int damage;
    int defense;
    struct _move_t *next;
} move_t;

/* stats stub */
typedef struct
{
    int speed;
    int strength;
    int dexterity;
    int hp;
    int max_hp;
    int xp;
} stat_t;

/* class stub */
typedef enum _class_t{bard, cleric, paladin, wizard} class_t;




#endif

