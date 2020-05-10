#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "player_stats.h"


void create_test_stats()
{
	stats_t *test_stats = malloc(sizeof(stats_t));
	test_stats->speed = 30;
	test_stats->strength = 80;
	test_stats->dexterity = 20;
	test_stats->hp = 100;
	test_stats->xp = 180;
}

ilist_t *create_test_inventory()
{
	ilist_t *inv_list = malloc(sizeof(ilist_t));
	return inv_list;	
}

item_t* new_item(int ID, int quantity, int durability, 
				char* description, bool battle, int attack,
				int defense, int hp)
{
	item_t *new_item = (item_t*) malloc(sizeof(item_t));
	strcpy(new_item->description, descrip);
	new_item->id = ID;
	new_item->quantity = quantity;
	new_item->durability = durability;
	new_item->battle = battle;
	new_item->attack = attack;
	new_item->defense = defense;
	new_item->hp = hp;
	return new_item;
}

ilist_t *add_item_to_inventory(ilist_t *inv, item_t *item)
{
	ilist_t *new_item = (ilist_t*) malloc(sizeof(ilist_t));
	new_item->item = item;
	new_item->next = inv;
	inv = new_item;
	return inv;
}

alist_t *add_armor_to_list(alist_t *alist, armor_t *armor)
{
	alist_t *new_armor_list = (alist_t*) malloc(sizeof(alist_t));
	new_armor_list->armor = armor;
	new_armor_list->next = alist;
	alist = new_armor_list;
	return alist;
}

armor_t* new_armor(char* description, int defense, int weight)
{
	armor_t* new_armor = malloc(sizeof(armor_t));
	new_armor->description = description;
	new_armor->defense = defense;
	new_armor->weight = weight;
}

void create_test_player()
{
	player_t *test_player = malloc(sizeof(player_t));
	test_player->cl = 3;
//	test_player->inventory = NULL;
//	test_player->armor = NULL;
}

int main()
{
	printf("Meow\n");
}
