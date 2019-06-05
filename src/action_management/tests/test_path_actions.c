#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "game.h"
#include "room.h"

#define BUFFER_SIZE (100)

bool execute_do_path_action(char *c_name, enum action_kind kind)
{
    room_t *dest = room_new("dummyroom", "a dummy room", "a placeholder room");
    char *direction = "south";
    player_t *player = player_new("player", 1);
    game_t *g = game_new("this is a dummy game");
    add_player_to_game(g, player);
    set_curr_player(g, player);
    action_type_t *a = action_type_new(c_name, kind);
    path_t *p = path_new(dest, direction);

    char *expected_output = malloc(BUFFER_SIZE);
    sprintf(expected_output, "Requested action %s in direction %s into room %s",
            a->c_name, p->direction, p->dest->room_id);

    bool rc;
    if (strcmp(do_path_action(g, a, p), expected_output) == 0)
    {
        rc = true;
    }
    else
    {
        rc = false;
    }

    free(expected_output);
    path_free(p);
    action_type_free(a);
    game_free(g);

    return rc;
}

Test(path_actions, kind_ITEM)
{
    bool rc = execute_do_path_action("dummy", ITEM);

    cr_assert_eq(rc, false,
                  "execute_do_item_item_action returned true for wrong kind ITEM");
}

Test(path_actions, kind_PATH)
{

    bool rc = execute_do_path_action("dummy", PATH);

    cr_assert_eq(rc, true,
                 "execute_do_item_item_action returned false for correct kind PATH");
}

Test(path_actions, kind_ITEM_ITEM)
{
    bool rc = execute_do_path_action("dummy", ITEM_ITEM);

    cr_assert_eq(rc, false,
                 "execute_do_item_item_action returned true for wrong kind ITEM_ITEM");
}
