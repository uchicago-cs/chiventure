#include <stdbool.h>
#include <string.h>
#ifndef STRUCTS_H
#define STRUCTS_H


struct stats_t
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
    	struct ilist_t * next;
};

enum class{bard, cleric, paladin, wizard};

struct player_t
{
        enum class cl;
        ilist_t inventory;
        ilist_t armor;
} player_t;

struct enemy_t
{ 
    char *name;
    stats_t *stats;
}
	
#endif 
