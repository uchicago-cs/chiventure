#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "flow.h"
#include "player_stats.h"

//move to flow.c file??
/* see enemy.h */
int goes_first(int difficulty)
{
    switch(difficulty) 
    {
      case 1:
         return 0;
         break;
      case 2:
          int r = rand() % 2;   //random number generator
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

//for use in the future when the list is implemented
item_t* find_item(ilist_t *inventory, int ID)
{
	ilist_t *temp;
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

//place in battle flow?
int enemy_use_item(enemy_t* e, player_t* p, int ID)
{
	if (e->inventory == NULL)
	{
		fprintf(stderr, "Noooo! Your inventory is empty!");
	}
	item_t *desired_item = find_item(e->inventory, ID);
	if (desired_item->quantity == 0)
	{
		fprintf(stderr, "ARGH!! You don't have any!");
	}
	else
	{
		desired_item->quantity -= 1;
		desired_item->durability -= 1;
		hurt_player(desired_item->attack, player);
		heal_enemy(desired_item->hp, enemy);			//heal enemy function for readability?
        return desired_item;
	}
}

ilist_t* example_inventory()
{
	ilist_t* inventory = create_new_inventory();
	item_t* dagger = new_item(1, 1, 20, "A hearty dagger sure to take your breath away... for good",
	true, 20, 5, 0);
	item_t* tea_leaves = new_item(2, 1, 1, "Make yourself a warm cup of tea to heal your wounds!", 
	0, 0, 10);
	item_t* medicine = new_item(3, 1, 1, "A first aid kit, straight from your doctor!", 0, 0, 30);
	item_t* mace = new_item(4, 1, 20, "Temporary blindness leaves you quite vulnerable...", 0, -30, 0);
	item_t* diamond_sword = new_item(5, 1, 50, "Brings quick death to those who dare battle you...", 20, 0, 0);
	item_t* force_shield = new_item(6, 1, 30, "Rest comfortably as this shield protects you for 1 move", 0, 30, 5);
	add_item_to_inventory(inventory, dagger);
	add_item_to_inventory(inventory, tea_leaves);
	add_item_to_inventory(inventory, medicine);
	add_item_to_inventory(inventory, mace);
	add_item_to_inventory(inventory, diamond_sword);
	add_item_to_inventory(inventory, force_shield);
}

alist_t* example_armor_list {
	alist_t* armor_list = create_new_armor_list();
	armor_t* iron_chestplate = new_armor("This heavy duty iron armor can protect you... but emphasis on the heavy...", 50, 30);
	armor_t* leather_chestplate = new_armor("Readily available, readily pierceable...", 10, 5);
	armor_t* chain_chestplate = new_armor("Good for protection, good for making noise", 30, 15);
	add_armor_to_list(armor_list, iron_chestplate);
	add_armor_to_list(armor_list, leather_chestplate);
	add_armor_to_list(armor_list, chain_chestplate);

}