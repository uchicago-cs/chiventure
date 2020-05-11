#include <stdbool.h>
#include <string.h>
#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct stats_t
{       
        int speed;
        int strength;
        int dexterity;
        int hp;
        int xp;
} stats_t;

struct item_t
{
        char* description;
        bool battle;
        int attack;
        int defense;
} item_t;


typedef struct _ilist_t ilist_t;
struct _ilist_t
{
	struct item_t *item;
    	struct ilist_t *next;
};

enum class{bard, cleric, paladin, wizard};

typedef struct player_t
{
        enum class cl;
        ilist_t inventory;
        ilist_t armor;
        struct stats_t *stats;
} player_t;

typedef struct enemy_t
{ 
    char *name;
    struct stats_t *stats;
    ilist_t *inventory;
    ilist_t *armor;
} enemy_t;
	
#endif 
