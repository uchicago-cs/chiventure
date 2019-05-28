#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"

bool execute_do_item_item_action(char *c_name, enum action_kind kind, char *expected_output)
{
    game_t *g = game_new;
    action_type_t *a = action_type_new(c_name, kind);
    item_t *direct = item_new("direct", "The direct item", "The directmost object of interest");
    item_t *indirect = item_new("indirect", "The indirect item", "The indirectmost object of interest");
    
    bool rc;
    if (strcmp(do_item_item_action(g, a, direct, indirect), expected_output) == 0) 
    {
        rc = true;
    }
    else 
    {
        rc = false;
    }

    item_free(direct);
    item_free(indirect);
    action_type_free(a);
    game_free(g);

    return rc;
}