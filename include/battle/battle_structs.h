#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <string.h>

/* moves stub */
typedef struct
{
	item_t *item;
	bool attack;
	int damage;
	int defense;
    move_t *next;
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
} stats_t;

/* items stub */
typedef struct
{
	int id;
	int quantity;
	int durability;
    char* description;
    bool battle;
    int attack;
    int defense;
	int hp;
    item_t *next;
} item_t;

/* class stub */
enum class{bard, cleric, paladin, wizard};




#endif
