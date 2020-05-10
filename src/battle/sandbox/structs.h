#include <stdbool.h>
#include <string.h>
#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct
{       
        int speed;
        int strength;
        int dexterity;
        int hp;
        int xp;
} stats_t;

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
} item_t;

typedef struct
{
	char* description;
	int defense;
	int weight;
} armor_t;


typedef struct _ilist_t ilist_t;
struct _ilist_t
{
	item_t *item;
    	ilist_t *next;
};

typedef struct
{
	struct armor_t *armor;
	struct alist_t *next;
} alist_t;

enum class{bard, cleric, paladin, wizard};

typedef struct
{
        enum class cl;
        ilist_t inventory;
        alist_t armor;
        stats_t stats;
} player_t;

typedef struct
{ 
    char *name;
    stats_t *stats;
    enum class cl;
    ilist_t inventory;
    alist_t armor;
} enemy_t;
	
#endif 
