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

    if (a == NULL)
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

/* A function that returns the canonical name of an action as a string */
char *get_action_cname(action_t *a)
{
    return a->c_name;
}

/* A function that returns the canonical name of an action as a string */
list_t *get_action_synonyms(action_t *a)
{
    return a->synonyms;
}

/* A function that returns the KIND of an action as an integer
 * Returns 1 for KIND 1, 2 for KIND 2, etc.
 */
int *get_action_kind(action_t *a)
{
    return a->kind;
}

/* A function that returns all supported actions
 * Parameters:
 * - kind: The enumerated value of KIND, specifying which action KIND necessary
 * Returns:
 * - a linked list of action_t structs
 */
list_t *get_supported_actions(enum action_kind *kind)
{
    int kind = get_action_kind(kind);
    switch(kind)
    {
        case ITEM:
            list_t *actions_kind1 = get_actions_kind1();
            return actions_kind1;
        case DIRECTION:
            list_t *actions_kind2 = get_actions_kind2();
            return actions_kind2;
        case NPC:
            list_t *actions_kind3 = get_actions_kind3();
            return actions_kind3;
        case ITEM_NPC:
            list_t *actions_kind4 = get_actions_kind4();
            return actions_kind4;
        case ITEM_ITEM:
            list_t *actions_kind5 = get_actions_kind5();
            return actions_kind5;
    }
}

// ===========================================================

//KIND 1
/* See actionmanagement.h */
int action_item(game_t *g, action_t *a, item_t *i)
{
	assert(g);
	assert(g->current_player); // assumes game_t has a field for current player
	assert(a);
	assert(i);
	if (a->kind != ITEM) {
		fprintf(stderr, "The action provided is not of the correct type.\n");
		return FAILURE;
	}
	/* function needs to be implemented by game state
	 * takes in a player, npc, and item
	 * removes object from inventory
	 * frees object if necessary
	 * returns 0 if success, 1 if failed
	 */
	int given = remove_inventory_object(g->current_player, i);
    // THIS IS A non-existent FUNCTION we depend on GAME STATE FOR
	//ex if "OPEN DOOR", game state needs to change the state of the door
	if (given != SUCCESS) {
		fprintf(stderr, "Object could not be moved from inventory.\n");
		return FAILURE;
	}
	return SUCCESS;

}

//KIND 2
/* See actionmanagement.h */
int action_direction(game_t *g, action_t *a, direction_t *d)
{
    assert(g);
    assert(a);
    assert(n);
    if (a->kind != DIRECTION) {
        fprintf(stderr, "The action provided is not of the correct type.\n");
        return FAILURE;
    }

    int moved = player_move(d); // THIS IS A non-existent FUNCTION we depend on GAME STATE FOR
    if (moved == SUCCESS) {
        return SUCCESS;
    } else {
        fprintf(stderr, "Player was unable to move.\n");
        return FAILURE;
    }
}

//KIND 3
/* See actionmanagement.h */
int action_npc(game_t *g, action_t *a, npc_t *n)
{
    assert(g);
  assert(a);
  assert(n);
  if (a->kind != NPC) {
    fprintf(stderr, "The action provided is not of the correct type.\n");
    return FAILURE;
  }

  int talked = player_talk(n); // THIS IS A non-existent FUNCTION we depend on GAME STATE FOR
  if (talked == SUCCESS) {
      return SUCCESS;
  } else {
      fprintf(stderr, "Player was unable to talk to NPC.\n");
      return FAILURE;
  }
}


//KIND 4
/* See actionmanagement.h */
int action_item_npc(game_t *g, action_t *a, item_t *i, npc_t *n)
{
  assert(g);
  assert(g->current_player); // assumes game_t has a field for current player
  assert(a);
  assert(i);
  assert(n);
  if (a->kind != ITEM_NPC) {
    fprintf(stderr, "The action provided is not of the correct type.\n");
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
    fprintf(stderr, "Object could not be moved from inventory.\n");
    return FAILURE;
  }
  fprintf(stderr, "%s", npc->dialogue);
  return SUCCESS;
}



//KIND 5
/* See actionmanagement.h */
int action_item_item(player_t *p, action_t *a,
		     item_t *direct, item_t *indirect)
{
  assert(p);
  assert(a);
  assert(direct);
  assert(indirect);
  if (a->kind != ITEM_ITEM) {
    fprintf(stderr, "The action provided is not of the correct type.\n");
    return FAILURE;
  }
  int moved = remove_inventory_object(g->current_player, i);
  if (moved != SUCCESS) {
    fprintf(stderr, "Object could not be moved from inventory.\n");
    return FAILURE;
  }
  fprintf(stderr, "%s", indirect->status_change); // notifies status change
  return SUCCESS;
}
