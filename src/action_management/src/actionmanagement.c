#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "actionmanagement.h"
#include "common.h"

/* See actionmanagement.h */
action_t *action_new(enum actions act, char *c_name,
		     list_t *synonyms, enum kind)
{
  action_t *a = malloc(sizeof(action_t));
  
  if(a == NULL)
    {
      error("Could not allocate memory");
      return NULL;
    }
  
  int new_a = action_init(a, act, c_name, synonyms, parameters);
  if (new_a != SUCCESS)
    {
      fprintf(stderr, "Could not initialize this action");
      return NULL;
    }
  
  return a;
}


/* See actionmanagement.h */
int action_init(action_t *a, enum actions act, char *c_name,
		list_t *synonyms, enum kind)
{
  assert(a);
  
  a->actions = act;
  a->c_name = cname;
  a->synonyms = synonyms;
  a->kind = kind;
  
  return SUCCESS;
}


/* See actionmanagement.h */
int action_free(action_t *a)
{
  assert(a);
  assert(a->c_name);
  assert(a->synonyms);
  free(a->c_name);
  free(a->synonyms);
  free(a);
  return SUCCESS;
}


// ===========================================================


/* See actionmanagement.h */
int action_npc(action_t *a, npc_t *n)
{
  assert(a);
  assert(n);
  if (a->kind != NPC) {
    fprintf(stderr, "The action provided is not of the correct type");
    return FAILURE;
  }
  fprintf(stderr, "%s", n->dialogue);
  return SUCCESS;
}


/* See actionmanagement.h */
int action_item_npc(game_t *g, action_t *a, item_t *i, npc_t *n)
{
  assert(g);
  assert(g->current_player); // assumes game_t has a field for current player
  assert(a);
  assert(i);
  assert(n);
  if (a->kind != ITEM_NPC) {
    fprintf(stderr, "The action provided is not of the correct type");
    return FAILURE;
  }
  /* function needs to be implemented by game state 
   * takes in a player, npc, and item
   * removes object from inventory
   * frees object if necessary
   * returns 1 if success, 0 if failed
   */
  int given = remove_inventory_object(g->current_player, i);
  if (given != SUCCESS) {
    fprintf(stderr, "Object could not be moved from inventory");
    return FAILURE;
  }
  fprintf(stderr, "%s", npc->dialogue);
  return SUCCESS;
}


/* See actionmanagement.h */
int action_item_item(player_t *p, action_t *a, 
		     item_t *direct, item_t *indirect)
{
  assert(p);
  assert(a);
  assert(direct);
  assert(indirect);
  if (a->kind != ITEM_ITEM) {
    fprintf(stderr, "The action provided is not of the correct type");
    return FAILURE;
  }
  int moved = remove_inventory_object(g->current_player, i);
  if (moved != SUCCESS) {
    fprintf(stderr, "Object could not be moved from inventory");
    return FAILURE;
  }
  fprintf(stderr, "%s", indirect->status_change); // notifies status change
  return SUCCESS;
}

//KIND 1
int action_item(game_t *g, action_t *a, item_t *i)
{
	//actions involving inventory
	while (g->all_players_t->inventory)
	{
		//if i is in inventory of the player
		if (i == g->all_players_t->inventory->tagged_objs->object_type_t[i])
		{
		 	//is it able to be consumed	;
			//remove from player inventory
			return 0;
		}
		else
		{
			return 1;
		}
	}
  //actions involving only items

  //this still needs work

}
