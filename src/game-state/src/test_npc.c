#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "npc.h"






Test (npc, new) {

	npc_t *npc; 
	npc = npc_new("npc_22", 20, NULL);

	cr_assert_not_null(npc, "npc_new() failed");
	
	cr_assert_eq(npc->npc_id, "npc_new didn't set npc_id"); 
	cr_assert_eq(npc->health, 20, "npc_new() didn't set health"); 
}

Test (npc, init) {
 
	npc_t *npc; 
	int init = npc_init(&npc, "npc_22", 20); 
	
	cr_assert_eq(init, SUCCESS, "npc_init() failed"); 
	
	cr_assert_eq(npc.npc_id, "npc_22", "npc_init didn't set npc_id"); 
	cr_assert_eq(npc.health, 20, "npc_init didn't set health"); 
} 

Test (npc, free)
{ 
	npc_t *npc; 
	int i = npc_new("npc_22", 20, NULL);
		
	cr_assert_not_null(p, "npc_free() failed"); 
	
	i = npc_free(npc); 
	cr_assert_eq(i, SUCCESS, "npc_free() failed"); 
}

 
