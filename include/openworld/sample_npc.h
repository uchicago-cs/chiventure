
#ifndef INCLUDE_SAMPLENPC_H_
#define INCLUDE_SAMPLENPC_H_
#include "sample_rooms.h"
#include "sample_items.h"

/* struct for npc
 * consists of a player id, level status, health status
 long description, short description, and question description.
 Aditionally, it include the item_hash_t inventory. 
 */
 
typedef struct npc{
	UT_hash_handle hh;
	char *npc_id;
	int level;
	int health;
	char *npc_ldesc;
	char *npc_sdesc;
	char *npc_qdesc;
	item_hash_t *inventory;
} npc_t;

/* Struct for the prices of special items, which 
  consists of potions and weapons. 
 */ 
typedef struct item_prices
{ 
	int *redPotion;  // strength potion
	int *greenPotion; // healing potion
} prices;

/*
 *  new_npc() allocates a space for a npc struct in memory
 *  Parameters: 
 * a unique npc_id, sdesc, ldesc

*/ 
npc_t* new_npc(char *npc_id, char *npc_ldesc, char *npc_sdesc, char *npc_qdesc);



/* npc_init() initializes an npc struct with given values
 Parameters:
    a memory allocated new item pointer
    a unique item id
    a short description of the item
    a long description of the item
    a question with action description of the item
 Returns:
    FAILURE for failure, SUCCESS for success
*/

int npc_init(npc_t* new_npc, char *npc_id, char *npc_ldesc, char *npc_sdesc, char *npc_qdesc);


/* 
   Function provides a description to the player
   of the room and then the NPC 
*/

npc_t* introduce_npc();


/* 
   After being introduced with a room or NPC description,
   the user is asked if they want to engage with the NPC
*/
npc_t* ask_And_action();

#endif
