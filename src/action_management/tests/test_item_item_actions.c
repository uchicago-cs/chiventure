#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"

char *execute_do_item_item_action(char *c_name, enum action_kind kind)
{
    game_t *g = game_new;
    item_t *direct = item_new("direct", "The direct item", "The directmost object of interest");
    item_t *indirect = item_new("indirect", "The indirect item", "The indirectmost object of interest");
    action_type_t *action = action_type_new(c_name, kind);

    item_free(direct);
    item_free(indirect);
    game_free(g);
}