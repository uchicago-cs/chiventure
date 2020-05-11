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
	int max_hp;
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

typedef struct _alist_t alist_t;
struct _alist_t
{
	armor_t *armor;
	alist_t *next;
};

enum class{bard, cleric, paladin, wizard};

typedef struct
{
        enum class cl;
        ilist_t *inventory;
        alist_t *armor;
        stats_t *stats;
} player_t;

typedef struct
{ 
    char *name;
    stats_t *stats;
    enum class cl;
    ilist_t *inv;
    alist_t *armor;
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
