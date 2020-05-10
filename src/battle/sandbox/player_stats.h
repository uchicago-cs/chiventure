#include <stdbool.h>
#include <string.h>
#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

/* Creates a new item and initializes its parameters */
item_t* new_item(int ID, int quantity, int durability, 
				char* description, bool battle, int attack,
				int defense, int hp)

/* Adds an item to a player's inventory */
ilist_t *add_item_to_inventory(ilist_t *inv, item_t *item);

/* Adds an item to a player's armor list */
alist_t *add_armor_to_list(alist_t *alist, armor_t *armor)

/* Creates new armor and initializes its parameters */
armor_t* new_armor(char* description, int defense, int weight)

#endif