#include <stdlib.h>
#include <stdio.h>
#include "actionmanagement.h"



int act_give_to(game_t *g, item_t *i, npc_t *n)
{
  while (g->all_players_t->inventory)
  {
    if (i == g->all_players_t->inventory->tagged_objs->object_type_t[i])
    {
      //use add_object_to_hash function
      //need a remove from hash function
      return 0;
    }
  }
  fprintf(stderr, "%s\n", "unable to give item");
  return 1;
}
