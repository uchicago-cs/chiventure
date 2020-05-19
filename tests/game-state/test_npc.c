#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "npc.h"
#include "item.h"


Test (npc, new) {

	npc_t *npc; 
	npc = npc_new("npc_22", 20, NULL);

	cr_assert_not_null(npc, "npc_new() failed");
	
	cr_assert_eq(npc->npc_id, "npc_new didn't set npc_id"); 
	cr_assert_eq(npc->health, 20, "npc_new() didn't set health"); 
}

Test (npcs_in_room, new) {
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = npcs_in_room_new("test_room");

    cr_assert_not_null(npcs_in_room, "npcs_in_room_new() failed");

    cr_assert_eq(npcs_in_room->room_id, "test_room",
                "npcs_in_room_new() did not set room_id");
	cr_assert_eq(npcs_in_room->num_of_npcs, 0,
                "npcs_in_room_new() did not set num_of_npcs");		
}

Test (npc, init) {
 
	npc_t *npc; 
	int init = npc_init(&npc, "npc_22", 20); 
	
	cr_assert_eq(init, SUCCESS, "npc_init() failed"); 
	
	cr_assert_eq(npc.npc_id, "npc_22", "npc_init didn't set npc_id"); 
	cr_assert_eq(npc.health, 20, "npc_init didn't set health"); 
} 

Test (npcs_in_room, init) {
    npcs_in_room_t *npcs_in_room;
    int check = npcs_in_room_init(&npcs_in_room, "test_room");
     
    cr_assert_eq(check, SUCCESS, "npcs_in_room_init() failed"); 

    cr_assert_eq(npcs_in_room.room_id, "test_room",
                "npcs_in_room_init() did not set room_id");
	cr_assert_eq(npcs_in_room.num_of_npcs, 0,
                "npcs_in_room_init() did not set num_of_npcs");
}

Test (npc, free)
{ 
	npc_t *npc; 
	int v; 
	npc =  npc_new("npc_22", 20, NULL);
		
	cr_assert_not_null(npc, "npc_free() failed"); 
	
	v = npc_free(npc); 
	cr_assert_eq(v, SUCCESS, "npc_free() failed"); 
}

Test (npcs_in_room, free)
{ 
	npcs_in_room_t *npcs_in_room; 
	int check; 
	npcs_in_room =  npc_new("test_room");
		
	cr_assert_not_null(npcs_in_room, "npcs_in_room_free() failed"); 
	
	check = npcs_in_room_free(npcs_in_room); 
	cr_assert_eq(check, SUCCESS, "npcs_in_room_free() failed"); 
}

Test (npc, change_npc_health) { 
	npc_t *npc; 
	npc = npc_new("npc_22", 20, NULL); 
	
	int foo = change_npc_health(npc, 20, 50); 
	cr_assert_eq(foo, 40, "change_npc_health() did not change the value correctly"); 
	
	npc = npc_free(npc); 
	npc = npc_new("npc_32", 40, NULL); 

	int foo = change_npc_health(npc, 20, 50); 
	cr_assert_eq(foo, 50, "change_npc_health() did not change the value correctly");
}	 

/*
void insert(item_list_t** h, item_t* itm) { 
	item_list_t* node = (item_list_t*) malloc(sizeof(item_list_t)); 
	node->item = &itm;
	node->next = *h; 
	*h = node; 
}
*/

void insert(npc_t* npc, item_t* itm) {
	HASH_ADD_KEYPTR(hh, npc->inventory, item->item_id,
                    strlen(item->item_id), item);
}

	

	
Test (npc, add_item_to_npc) {
	//NULL case 
	item_t* itm = item_new("itm", "short desc", "longer description"); 
	npc_t* npc = npc_new("npc_22", 20, NULL); 
	int a = add_item_to_npc(npc, itm); 
	cr_assert_eq(a, SUCCES, "add_item_to_npc() failed"); 

	//non-NULL Success Case 
	npc_t* npc2 = npc_new("npc_32", 40, NULL);
        item_t* itm1 = item_new("itm1", "short desc 1", "longer description 1");
        item_t* itm2 = item_new("itm2", "short desc 2", "longer description 2");
        item_t* itm3 = item_new("itm3", "short desc 3", "longer description 3");
	insert(npc2, itm1);
        insert(npc2, itm3);
	int v = add_item_to_npc(npc, itm2);
	cr_assert_eq(v, SUCCESS, "add_item_to_npc() failed");

	// test failure case
	npc_t* npc3 = npc_new("npc_32", 40, NULL);
        item_t* itm4 = item_new("itm1", "short desc 1", "longer description 1");
        item_t* itm5 = item_new("itm2", "short desc 2", "longer description 2");
        item_t* itm6 = item_new("itm3", "short desc 3", "longer description 3");
        insert(npc, itm1);
        insert(npc, itm2);
        insert(npc, itm3);
        int f = add_item_to_npc(npc, itm1);
        cr_assert_eq(a, FAILURE, "add_item_to_npc() failed");

	// testing hash items 	
}	

Test (npc, get_all_items_inv_npc) {
        // equivalency test 
} 

Test (npcs_in_room, add_npc_to_room) {
    npc_t *npc = npc_new("npc_test", 20, NULL); 
    npcs_in_room_t *npcs_in_room = npcs_in_room_new("test_room");
	int num_of_npcs_initial = npcs_in_room->num_of_npcs;

    int check1 = add_npc_to_room(npcs_in_room, npc);
	int num_of_npcs_final = npcs_int_room->num_of_npcs;

    cr_assert_eq(check1, SUCCESS, "add_npc_to_room() failed");

    npc_t *check2;
    HASH_FIND(hh, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check2);

    cr_assert_not_null(check2, "add_npc_to_room() failed,"
								" could not find newly added npcs");

	cr_assert_eq(num_of_npcs_initial+1,num_of_npcs_final,
				 "add_npc_to_room() failed, incorrect number of npcs in room");
}