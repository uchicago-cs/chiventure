#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"
#include "player.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (1)

int execute_do_path_action(char *c_name, enum action_kind kind)
{
    room_t *dest = room_new("dummyroom", "a dummy room", "a placeholder room");
    char *direction = "south";
    player_t *player = player_new("player", 1);
    game_t *g = game_new("this is a dummy game");
    add_player_to_game(g, player);
    set_curr_player(g, player);
    action_type_t *a = action_type_new(c_name, kind);
    path_t *p = path_new(dest, direction);
    char *string = malloc(BUFFER_SIZE);

    int rc = do_path_action(g, a, p, &string);

    path_free(p);
    action_type_free(a);
    game_free(g);

    return rc;
}


Test(path_actions, kind_ITEM)
{
    int rc = execute_do_path_action("dummy", ITEM);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_path_action returned %d for wrong kind ITEM, expected WRONG_KIND (1)", rc);
}


Test(path_actions, kind_PATH)
{

    int rc = execute_do_path_action("dummy", PATH);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_path_action returned %d for correct kind PATH expected SUCCESS (0)", rc);
}


Test(path_actions, kind_ITEM_ITEM)
{
    int rc = execute_do_path_action("dummy", ITEM_ITEM);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_path_action returned %d for wrong kind ITEM_ITEM expected WRONG_KIND (1)");
}
