#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/battle/battle_test_utility.h"

/* Tests new_ctx_player() */
Test(battle_flow_structs, new_ctx_player)
{
    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                    NULL, NULL, NULL);

    battle_player_t *ctx_player = new_ctx_player("new_ctx_player_Name", test_class,
                                          NULL, NULL, NULL, NULL, NULL, NULL);

    cr_assert_not_null(ctx_player, "new_ctx_player() failed");
    cr_assert_str_eq(ctx_player->player_id, "new_ctx_player_Name", "new_ctx_player() didn't set id");

    cr_assert_str_eq(ctx_player->class_type->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(ctx_player->class_type->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(ctx_player->class_type->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(ctx_player->class_type->attributes, "set_player() didn't set class attribute");
    cr_assert_null(ctx_player->class_type->base_stats, "set_player() didn't set class stats");
}

/* Tests new_battle_game() */
Test(battle_flow_structs, new_battle_game)
{
    battle_game_t *g = new_battle_game();

    cr_assert_not_null(g, "new_battle_game() failed");
    cr_assert_eq(g->player, NULL, "new_battle_game() failed");
}
