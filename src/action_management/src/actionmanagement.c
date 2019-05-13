#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "actionmanagement.h"

/* See actionmanagement.h */
action_t *action_new(enum actions act, char *c_name,
		     list_t *synonyms, enum kind)
{
  action_t *a = malloc(sizeof(action_t));
  
  if(!a)
    {
      error("Could not allocate memory");
      return NULL;
    }
  
  int new_a = action_init(a, act, c_name, synonyms, parameters);
  if (new_a != SUCCESS)
    {
      error("Could not initialize this action");
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
    error("The action provided is not of the correct type");
    return 0;
  }
  fprintf(stderr, "%s", n->dialogue);
  return 1;
}


/* See actionmanagement.h */
int action_item_npc(player_t *p, action_t *a, item_t *i, npc_t *n)
{
  assert(p);
  assert(a);
  assert(i);
  assert(n);
  if (a->kind != ITEM_NPC) {
    error("The action provided is not of the correct type");
    return 0;
  }
  /* function needs to be implemented by game state 
   * takes in a player, npc, and item
   * removes object from inventory
   * frees object if necessary
   * returns 1 if success, 0 if failed
   */
  int given = remove_inventory_object(p, i);
  if (given) {
    printf(stderr, "%s", npc->dialogue);
    return 1;
  }
  else
    return 0;
}


/* See actionmanagement.h */
int action_item_item(player_t *p, action_t *a, item_t *direct, item_t *indirect)
{
  assert(p);
  assert(a);
  assert(direct);
  assert(indirect);
  if (a->kind != ITEM_ITEM) {
    error("The action provided is not of the correct type");
    return 0;
  }
  int moved = remove_inventory_object(p, i);
  if (moved) {
    printf(stderr, "%s", indirect->status_change);
    return 1;
  }
  else
    return 0;
  
}
