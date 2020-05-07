#include <stdlib.h>
#include <stdio.h>
#include "structs.h"


void create_test_stats()
{
	struct stats_t *test_stats = malloc(sizeof(stats_t));
	test_stats->speed = 30;
	test_stats->strength = 80;
	test_stats->dexterity = 20;
	test_stats->hp = 100;
	test_stats->xp = 180;
}

void create_test_inventory()
{
	ilist_t *inv_list = malloc(sizeof(ilist_t));
	
}

void create_test_player()
{
	struct player_t *test_player = malloc(sizeof(player_t));
	test_player->cl = 3;
//	test_player->inventory = NULL;
//	test_player->armor = NULL;
}

int main()
{
	printf("Meow\n");
}
