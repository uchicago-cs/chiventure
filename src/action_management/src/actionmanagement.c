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

/* See actionmanagement.h */
char *get_action_cname(action_t *a)
{
    return a->c_name;
}

/* See actionmanagement.h */
list_t *get_action_synonyms(action_t *a)
{
    return a->synonyms;
}

/* See actionmanagement.h */
int *get_action_kind(action_t *a)
{
    return a->kind;
}

/* See actionmanagement.h */
list_t *get_supported_actions(enum action_kind *kind)
{
    switch (kind)
    {
        case ITEM:
            list_t *actions_kind1 = get_actions_kind1();
            return actions_kind1;
	    break;
        case DIRECTION:
            list_t *actions_kind2 = get_actions_kind2();
            return actions_kind2;
	    break;
        case NPC:
            list_t *actions_kind3 = get_actions_kind3();
            return actions_kind3;
	    break;
        case ITEM_NPC:
            list_t *actions_kind4 = get_actions_kind4();
            return actions_kind4;
	    break;
        case ITEM_ITEM:
            list_t *actions_kind5 = get_actions_kind5();
            return actions_kind5;
	    break;
    }
}

// ===========================================================

// KIND 1
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
    switch (a->act) {
    case PUSH:
    case PULL:
    case OPEN:
    case CLOSE:
    case TURN_ON:
    case TURN_OFF:
      // non-existent function implemented by game state
      // turns things from on to off, open to closed, pushed to pulled vice versa
      int toggle = toggle_condition(g, a, i);
      if (toggle != SUCCESS) {
	fprintf(stderr, "%s failed", a->c_name);
	return FAILURE;
      }
      break;
    case EXAMINE:
      // function implemented by game state
      int describe = get_long_desc(i);
      if (describe != SUCCESS) {
	fprintf(stderr, "%s failed", a->c_name);
	return FAILURE;
      }
      break;
    case DROP:
      // non-existent function to be implemented by game state
      int drop = remove_inventory_object(g->current_player, i);
      if (drop != SUCCESS) {
        fprintf(stderr, "Object could not be removed from inventory.\n");
        return FAILURE;
      }
    case TAKE:
      // function implemented by game state
      int take = take_object(i);
      if (take != SUCCESS) {
	fprintf(stderr, "item can't be taken");
	return FAILURE;
      }
      // function implemented by game state
      int add = add_inventory_item(i, g->current_player);
      if (add != SUCCESS) {
	fprintf(stderr, "item was not taken");
	return FAILURE;
      }
      break;
    case CONSUME:
      // non-existent function to be implemented by game state
      int consumed = remove_inventory_object(g->current_player, i);
      if (consumed != SUCCESS) {
        fprintf(stderr, "Object could not be removed from inventory.\n");
        return FAILURE;
      }
      // function implemented by game state
      int boosted = change_health(g->current_player, i->change, 
				g->current_player->max_health);
      if (boosted) {
	fprintf(stderr, "Player's health is %d", boosted);
      }
      break;
    }
    return SUCCESS;
}

// KIND 2
/* See actionmanagement.h */
int action_direction(game_t *g, action_t *a, direction_t *d)
{
    assert(g);
    assert(a);
    if (a->kind != DIRECTION) {
        fprintf(stderr, "The action provided is not of the correct type.\n");
        return FAILURE;
    }
    // THIS IS A non-existent FUNCTION we depend on GAME STATE FOR
    int moved = player_move(d);
    if (moved == SUCCESS) {
        return SUCCESS;
    } else {
        fprintf(stderr, "Player was unable to move.\n");
        return FAILURE;
    }
}

// KIND 3
/* See actionmanagement.h */
int action_npc(game_t *g, action_t *a, npc_t *n)
{
  assert(g);
  assert(g->current_player);
  assert(a);
  assert(n);
  if (a->kind != NPC) {
    fprintf(stderr, "The action provided is not of the correct type.\n");
    return FAILURE;
  }
  // THIS IS A non-existent FUNCTION we depend on GAME STATE FOR
  int available = in_room(g, n);
  if (available == FAILURE) {
    fprintf(stderr, "NPC is not in room.\n");
    return FAILURE;
  }
  // THIS IS A non-existent FUNCTION we depend on GAME STATE FOR
  int talked = player_talk(g->current_player, n); 
  if (talked == SUCCESS) {
    return SUCCESS;
  } else {
    fprintf(stderr, "Player was unable to talk to NPC.\n");
    return FAILURE;
  }
}



// KIND 4
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
  // non-existent function to be implemented by game state
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
  // non-existent function to be implemented by game state
  int moved = remove_inventory_object(g->current_player, i);
  if (moved != SUCCESS) {
    fprintf(stderr, "Object could not be moved from inventory.\n");
    return FAILURE;
  }
  fprintf(stderr, "%s", indirect->status_change); // notifies status change
  return SUCCESS;
}
