#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "npc/npc.h"
#include "game-state/item.h"


/* Checks that npc_new() properly mallocs and inits a new npc struct */
Test (npc, new) 
{
	npc_t *npc; 

	npc = npc_new("npc_22", 20);

	cr_assert_not_null(npc, "npc_new() failed");
	
	cr_assert_eq(strncmp(npc->npc_id, "npc_22", MAX_ID_LEN), 0, 
				 "npc_new didn't set npc_id"); 
	cr_assert_eq(npc->health, 20, "npc_new() didn't set health"); 
}

/* Checks that npc_init() initialized the fields in the new npc struct */
Test (npc, init) 
{ 
	npc_t *npc; 
	int res;
	
	res = npc_init(npc, "npc_22", 20); 
	
	cr_assert_eq(res, SUCCESS, "npc_init() failed"); 
	
	cr_assert_eq(strncmp(npc->npc_id, "npc_22", MAX_ID_LEN), 0,
				 "npc_22", "npc_init didn't set npc_id"); 
	cr_assert_eq(npc->health, 20, "npc_init didn't set health"); 
} 

/* Checks that npc_free() frees the given npc struct from memory */
Test (npc, free)
{ 
	npc_t *npc;
	int res; 

	npc = npc_new("npc_22", 20);
		
	cr_assert_not_null(npc, "npc_new() failed"); 
	
	res = npc_free(npc); 

	cr_assert_eq(res, SUCCESS, "npc_free() failed"); 
}

/* Checks that get_health() returns the health of the npc */
Test(npc, get_npc_health)
{
	npc_t *npc;
	int health;

	npc = npc_new("npc_22", 20);

	health = get_npc_health(npc);

	cr_assert_not_null(npc, "npc_new() failed");

	cr_assert_eq(health, 20, "get_npc_health() returned incorrect health");
}

/* Checks that an npc's health is changed by change_npc_health()
both positively and negatively with a set maximum */
Test (npc, change_npc_health) 
{ 
	npc_t *npc; 
	int health1, health2, health3;

	npc = npc_new("npc_22", 99); 
	health1 = change_npc_health(npc, 2, 100); 
	health2 = change_npc_health(npc, -20, 100);
  	health3 = change_npc_health(npc, 3, 83);

  	cr_assert_not_null(npc, "npc_new() failed");

 	cr_assert_eq(health1, 100, 
	 			 "change_npc_health() increased health past max");
 	cr_assert_eq(health2, 80, 
	 			 "change_npc_health() did not properly reduce health");
  	cr_assert_eq(health3, 83, 
	  			 "change_npc_health() did not properly add health");
}

/* Checks that get_inventory() returns the npc's inventory */
Test(npc, get_npc_inventory)
{
  npc_t *npc1, *npc2;
  item_t *new_item;
  item_hash_t *inv1, inv2;

  npc1 = npc_new("npc_1",20);
  npc2 = npc_new("npc_2", 21);
  new_item = item_new("test_item", "item for npc testing",
  "item for testing get_npc_inventory()");
  add_item_to_npc(npc2, new_item);

  inv1 = get_npc_inventory(npc1);
  inv2 = get_npc_inventory(npc2);

  cr_assert_not_null(npc1, "npc_new() failed on npc1");
  cr_assert_not_null(npc2, "npc_new() failed on npc2");
  cr_assert_not_null(new_item, "item_new() failed");

  cr_assert_eq(inv1, npc1->inventory,
      "get_npc_inventory() failed to return NULL for empty inventory");
  cr_assert_eq(inv2, npc2->inventory,
      "get_npc_inventory() failed to return inventory");
}


void insert(npc_t* npc, item_t* itm) 
{
	HASH_ADD_KEYPTR(hh, npc->inventory, item->item_id,
                    strlen(item->item_id), item);
}

	
Test (npc, add_item_to_npc) {
	//NULL case 
	item_t* itm = item_new("itm", "short desc", "longer description"); 
	npc_t* npc = npc_new("npc_22", 20, NULL); 
	int ret1 = add_item_to_npc(npc, itm); 
	cr_assert_eq(ret1, SUCCESS, "add_item_to_npc() failed"); 

	//non-NULL Success Case 
	npc_t* npc2 = npc_new("npc_32", 40, NULL);
	item_t* itm1 = item_new("itm1", "short desc 1", "longer description 1");
    item_t* itm2 = item_new("itm2", "short desc 2", "longer description 2");
    item_t* itm3 = item_new("itm3", "short desc 3", "longer description 3");
	insert(npc2, itm1);
    insert(npc2, itm3);
	int ret2 = add_item_to_npc(npc, itm2);
	cr_assert_eq(ret2, SUCCESS, "add_item_to_npc() failed");

	// test failure case
	npc_t* npc3 = npc_new("npc_32", 40, NULL);
    item_t* itm4 = item_new("itm1", "short desc 1", "longer description 1");
    item_t* itm5 = item_new("itm2", "short desc 2", "longer description 2");
    item_t* itm6 = item_new("itm3", "short desc 3", "longer description 3");
    insert(npc, itm1);
    insert(npc, itm2);
    insert(npc, itm3);
    int ret3 = add_item_to_npc(npc, itm1);
    cr_assert_eq(ret3, FAILURE, "add_item_to_npc() failed");
	// testing hash items 	
}	
