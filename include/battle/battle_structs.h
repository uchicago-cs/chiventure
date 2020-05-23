#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <string.h>

/* max name length */
#define MAX_NAME_LEN (50)

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
    item_t *item;
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

/* class stub */
typedef enum class {
    bard,
    cleric,
    paladin, 
    wizard
} class_t;




#endif

