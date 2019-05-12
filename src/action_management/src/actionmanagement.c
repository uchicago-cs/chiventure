#include <stdlib.h>
#include <stdio.h>
#include "actionmanagement.h"


action_t *action_new(enum actions act, char *c_name,
  list_t *synonyms, enum kind)
  {
    action_t *a = malloc(sizeof(action_t));

    if(a == NULL)
    {
      error("Could not allocate memory");
      return NULL;
    }

    new_a = action_init(a, act, c_name, synonyms, parameters);
    if (new_a != SUCCESS)
    {
      error("Could not initialize this action");
      return NULL;
    }

    return a;
  }



// int act_give_to(game_t *g, item_t *i, npc_t *n)
// {
//   while (g->all_players_t->inventory)
//   {
//     if (i == g->all_players_t->inventory->tagged_objs->object_type_t[i])
//     {
//       //use add_object_to_hash function
//       //need a remove from hash function
//       return 0;
//     }
//   }
//   fprintf(stderr, "%s\n", "unable to give item");
//   return 1;
// }
