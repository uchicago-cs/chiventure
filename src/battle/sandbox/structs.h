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
        char* description;
        bool battle;
        int attack;
        int defense;
} item_t;

typedef struct
{
	char* description;
	int defense;
	int weight;
} armor_t;


typedef struct
{
	item_t *item;
    	struct ilist_t * next;
} ilist_t;

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
        ilist_t armor;
} player_t;

typedef struct
{ 
    char *name;
    stats_t *stats;
    enum class cl;
    ilist_t inventory;
    ilist_t armor;
} enemy_t;
	
#endif 
