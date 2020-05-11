#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "flow.h"
#include "players_stats.h"


/* see enemy.h */
int goes_first(int difficulty)
{
	int r = rand() % 2;   //random number generator
    switch(difficulty) 
    {
      case 1:
         return 0;
         break;
      case 2:
          if (r == 0)
            return 0;
          else
            return 1;
          break;
      case 3:
         return 1;
         break;
      default:
         printf("Invalid difficulty!" );
         return -1;
    }
}

/* Creates a dumy armor list with hardcoded values
 * 	Inputs:
 * 		inventory - an player or enemy's inventory
 * 		ID - the ID number of the desired item
 * 	Outputs:
 * 		temp->item - pointer to the desired item */
item_t* find_item(ilist_t *inventory, int ID)
{
	ilist_t *temp = inventory;
	for (temp = inventory; temp != NULL; temp = temp->next)
	{
		if (temp->item->id == ID)
		{
			return temp->item;
		}
		else if ((temp->next == NULL) && 
				(temp->item->id != ID))
		{
			printf("\nError! You don't have any in inventory!");
			return NULL;
		}
	}
	return NULL;
}

/* see enemy.h */
item_t* enemy_use_item(enemy_t* e, int ID)
{
	if (e->inv == NULL)
	{
		fprintf(stderr, "Noooo! Your inventory is empty!");
		return NULL;
	}
	item_t *desired_item = malloc(sizeof(item_t));
	desired_item = find_item(e->inv, ID);
	if (desired_item->quantity == 0)
	{
		fprintf(stderr, "ARGH!! You don't have any!");
		return desired_item;
	}
	else
	{
		desired_item->quantity -= 1;
		desired_item->durability -= 1;
        return desired_item;
	}
}

/* Creates a dummy stats struct with hardcoded values
 * 	Inputs:
 * 		None
 * 	Outputs:
 * 		test_stats - an initialized stats struct */
stats_t* create_enemy_stats()
{
    stats_t* test_stats = malloc(sizeof(stats_t));

    test_stats->speed = 50;
    test_stats->strength = 150;
    test_stats->dexterity = 10;
    test_stats->hp = 200;
    test_stats->xp = 0;

    return test_stats;
}

/* Creates a dummy inventory with hardcoded values
 * 	Inputs:
 * 		None
 * 	Outputs:
 * 		inventory - an initialized inventory */
ilist_t* example_inventory()
{
	ilist_t* inventory = create_test_inventory();
	item_t* dagger = create_item(1, 1, 20, "A hearty dagger sure to take your breath away... for good",
	true, 20, 5, 0);
	item_t* tea_leaves = create_item(2, 1, 1, "Make yourself a warm cup of tea to heal your wounds!", true,
	0, 0, 10);
	item_t* medicine = create_item(3, 1, 1, "A first aid kit, straight from your doctor!", true, 0, 0, 30);
	item_t* mace = create_item(4, 1, 20, "Temporary blindness leaves you quite vulnerable...", true, 0, -30, 0);
	item_t* diamond_sword = create_item(5, 1, 50, "Brings quick death to those who dare battle you...", true, 20, 0, 0);
	item_t* force_shield = create_item(6, 1, 30, "Rest comfortably as this shield protects you for 1 move", true, 0, 30, 5);
	add_item_to_inventory(inventory, dagger);
	add_item_to_inventory(inventory, tea_leaves);
	add_item_to_inventory(inventory, medicine);
	add_item_to_inventory(inventory, mace);
	add_item_to_inventory(inventory, diamond_sword);
	add_item_to_inventory(inventory, force_shield);
	return inventory;
}

/* Creates a dummy armor list with hardcoded values
 * 	Inputs:
 * 		None
 * 	Outputs:
 * 		armor_list - an initialized armor_list */
alist_t* example_armor_list() {
	alist_t* armor_list = create_test_armor();
	armor_t* iron_chestplate = create_armor("This heavy duty iron armor can protect you... but emphasis on the heavy...", 50, 30);
	armor_t* leather_chestplate = create_armor("Readily available, readily pierceable...", 10, 5);
	armor_t* chain_chestplate = create_armor("Good for protection, good for making noise", 30, 15);
	add_armor(armor_list, iron_chestplate);
	add_armor(armor_list, leather_chestplate);
	add_armor(armor_list, chain_chestplate);
	return armor_list;
}

/* see enemy.h */
enemy_t* create_enemy_player()
{
	enemy_t* enemy = malloc(sizeof(enemy_t));
	enemy->name = "Hydra";
	enemy->stats = create_enemy_stats();
	enemy->inv = example_inventory();
	enemy->armor = example_armor_list();
	return enemy;
}



