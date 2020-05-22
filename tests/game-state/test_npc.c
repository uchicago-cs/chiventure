#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "npc.h"
#include "item.h"


Test (npc, new) 
{
	npc_t *npc; 
	npc = npc_new("npc_22", 20, NULL, NULL);

	cr_assert_not_null(npc, "npc_new() failed");
	
	cr_assert_eq(npc->npc_id, "npc_new didn't set npc_id"); 
	cr_assert_eq(npc->health, 20, "npc_new() didn't set health"); 
}


Test (npc, init) 
{ 
	npc_t *npc; 
	int init = npc_init(&npc, "npc_22", 20, NULL, NULL); 
	
	cr_assert_eq(init, SUCCESS, "npc_init() failed"); 
	
	cr_assert_eq(npc.npc_id, "npc_22", "npc_init didn't set npc_id"); 
	cr_assert_eq(npc.health, 20, "npc_init didn't set health"); 
} 


Test (npc, free)
{ 
	npc_t *npc; 
	int ret; 
	npc =  npc_new("npc_22", 20, NULL, NULL);
		
	cr_assert_not_null(npc, "npc_free() failed"); 
	
	ret = npc_free(npc); 
	cr_assert_eq(ret, SUCCESS, "npc_free() failed"); 
}


Test (npc, change_npc_health) 
{ 
	npc_t *npc; 
	npc = npc_new("npc_22", 20, NULL, NULL); 
	
	int ret1 = change_npc_health(npc, 20, 50); 
	cr_assert_eq(ret1, 40, "change_npc_health() did not change the value correctly"); 
	
	npc = npc_free(npc); 
	npc = npc_new("npc_32", 40, NULL, NULL); 

	int ret2 = change_npc_health(npc, 20, 50); 
	cr_assert_eq(ret2, 50, "change_npc_health() did not change the value correctly");
}	 


void insert(npc_t* npc, item_t* itm) 
{
	HASH_ADD_KEYPTR(hh, npc->inventory, item->item_id,
                    strlen(item->item_id), item);
}

	
Test (npc, add_item_to_npc) {
	//NULL case 
	item_t* itm = item_new("itm", "short desc", "longer description"); 
	npc_t* npc = npc_new("npc_22", 20, NULL, NULL); 
	int ret1 = add_item_to_npc(npc, itm); 
	cr_assert_eq(ret1, SUCCESS, "add_item_to_npc() failed"); 

	//non-NULL Success Case 
	npc_t* npc2 = npc_new("npc_32", 40, NULL, NULL);
	item_t* itm1 = item_new("itm1", "short desc 1", "longer description 1");
    item_t* itm2 = item_new("itm2", "short desc 2", "longer description 2");
    item_t* itm3 = item_new("itm3", "short desc 3", "longer description 3");
	insert(npc2, itm1);
    insert(npc2, itm3);
	int ret2 = add_item_to_npc(npc, itm2);
	cr_assert_eq(ret2, SUCCESS, "add_item_to_npc() failed");

	// test failure case
	npc_t* npc3 = npc_new("npc_32", 40, NULL, NULL);
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

Test (npc, get_all_items_inv_npc) {
        // equivalency test 
} 