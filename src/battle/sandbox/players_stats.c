#include <stdlib.h>
#include <stdio.h>
#include "structs.h"


stats_t * create_test_stats()
{
	stats_t *test_stats = malloc(sizeof(stats_t));
	test_stats->speed = 30;
	test_stats->strength = 80;
	test_stats->dexterity = 20;
	test_stats->hp = 100;
	test_stats->xp = 180;
	return test_stats;
}

ilist_t *create_test_inventory()
{
	ilist_t *inv_list = malloc(sizeof(ilist_t));
	return inv_list;	
}

item_t *create_item(int id, int quan, int durab, char* descrip, bool bat, int attack, int defense, int hp)
{
	item_t *new_item = (item_t*) malloc(sizeof(item_t));
	new_item->id = id;
	new_item->quantity = quan;
	new_item->durability = durab;
	strcpy(new_item->description, descrip);
	new_item->battle = bat;
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

alist_t *create_test_armor()
{
        alist_t *arm_list = malloc(sizeof(alist_t));
        return arm_list;
}

armor_t *create_armor(char* descrip, int defense, int weight)
{
        armor_t *new_armor = (armor_t*) malloc(sizeof(armor_t));
        new_armor->defense = defense;
        new_armor->weight = weight;
        strcpy(new_armor->description, descrip);
        return new_armor;
}

alist_t *add_armor(alist_t *arm, armor_t *armor)
{
        alist_t *new_armor = (alist_t*) malloc(sizeof(alist_t));
        new_armor->armor = armor;
        new_armor->next = arm;
        arm = new_armor;
        return arm;
}

bool item_battle(item_t *item)
{
	return item->battle;
}



player_t *create_test_player(ilist_t *inv, alist_t *arm) 
{
        player_t *test_player = malloc(sizeof(player_t));
        test_player->cl = 3;
        test_player->inventory = inv;
        test_player->armor = arm;
	return test_player;
}

stats_t *award_xp(stats_t *stats, int xp)
{
	stats->xp += xp;
	return stats;
}

mlist_t *create_mlist()
{
	mlist_t *mov_list = malloc(sizeof(mlist_t));
        return mov_list;
}

move_t *create_move(item_t *item, bool atk, int dmg, int df)
{
	move_t *move = (move_t*) malloc(sizeof(move_t));
	move->item = item;
	move->attack = atk;
	move->damage = dmg;
	move->defense = df;
	return move;
}

bool attack_item(item_t *item)
{
	return (item->attack >= item->defense);
}

mlist_t *add_move(mlist_t *moves, move_t *move)
{
        mlist_t *new_move = (mlist_t*) malloc(sizeof(mlist_t));
        new_move->move = move;
        new_move->next = moves;
        moves= new_move;
        return moves;
}

mlist_t *enemy_moves(ilist_t *inv)
{
	mlist_t *moves = create_mlist();
	ilist_t *tmp;
	while(tmp)
	{
		if(tmp->item->battle)
		{
			move_t *move = create_move(tmp->item, attack_item(tmp->item), tmp->item->attack, tmp->item->defense);
			moves = add_move(moves, move);
		}
	tmp = tmp->next;
	}
	return moves;
}
		


int main()
{
	printf("Meow\n");
	item_t *item1 = create_item(1,1,60,"sword",true, 15, 5, 0);
 printf("pls\n");
	item_t *item2 = create_item(2,1,10,"cake", false, 0, 0, 5);
	item_t *item3 = create_item(3,2,100, "healing potion", true, 0, 0, 5);
	item_t *item4 = create_item(4,1,70, "shield", true, 5, 15, 0);
	ilist_t *inv = create_test_inventory();
	inv = add_item_to_inventory(inv,item1);
	inv = add_item_to_inventory(inv,item2);
	inv = add_item_to_inventory(inv,item3);
	inv = add_item_to_inventory(inv,item4);
	armor_t *arm1 = create_armor("helmet",1, 1);
	armor_t *arm2 = create_armor("chest plate", 5, 3);
	armor_t *arm3 = create_armor("boots",1,1);
	alist_t *arm = create_test_armor();
	arm = add_armor(arm,arm1);
	arm = add_armor(arm,arm2);
	arm = add_armor(arm,arm3);
	player_t *player = create_test_player(inv, arm);

}
