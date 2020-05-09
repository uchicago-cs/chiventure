#include <stdlib.h>
#include <stdio.h>
#include "structs.h"


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

item_t *create_item(char* descrip, bool bat, int attack, int defense)
{
	item_t *new_item = (item_t*) malloc(sizeof(item_t));
	strcpy(new_item->description, descrip);
	new_item->battle = bat;
	new_item->attack = attack;
	new_item->defense = defense;
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
