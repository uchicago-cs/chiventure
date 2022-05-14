#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "../include/battle/battle_move_maker.h"
#include "playerclass/class.h"
#include "battle/battle_default_objects.h"


Test(class_moves, bard)
{
    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                    NULL, NULL, NULL);
    
    battle_player_t *player = new_ctx_player("name", test_class,
                                          NULL, NULL, NULL);
    combatant_t *ret_player = set_battle_player(player);

    int rc = build_moves(ret_player);

    cr_assert_eq(rc, SUCCESS, "build_moves() failed");

    cr_assert_eq(ret_player->moves->id, 100, "move_new() didn't set move id");

    cr_assert_str_eq(ret_player->moves->name, "",
                     "move_new() didn't set move info");

    cr_assert_str_eq(ret_player->moves->info, "Diss track",
                     "move_new() didn't set move info");

    cr_assert_eq(ret_player->moves->dmg_type, MAG, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->count, 0, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->sp_cost, 10, "move_new() didn't set move id");

    cr_assert_null(ret_player->moves->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(ret_player->moves->damage, 15, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(ret_player->moves->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->next, "move_new() didn't set battle_item to NULL");
}


Test(class_moves, wizard)
{
    class_t* test_class = class_new("Wizard", "Wise",
                                    "Old and wise",
                                    NULL, NULL, NULL);

    battle_player_t *player = new_ctx_player("new_ctx_player_Name", test_class,
                                          NULL, NULL, NULL);

    combatant_t *ret_player = set_battle_player(player);

    int rc = build_moves(ret_player);

    cr_assert_eq(rc, SUCCESS, "build_moves() failed");

    cr_assert_eq(ret_player->moves->id, 130, "move_new() didn't set move id");

    cr_assert_str_eq(ret_player->moves->name, "",
                     "move_new() didn't set move info");

    cr_assert_str_eq(ret_player->moves->info, "Fireball",
                     "move_new() didn't set move info");

    cr_assert_eq(ret_player->moves->dmg_type, MAG, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->count, 0, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->sp_cost, 10, "move_new() didn't set move id");

    cr_assert_null(ret_player->moves->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(ret_player->moves->damage, 10, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(ret_player->moves->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->next, "move_new() didn't set battle_item to NULL");

}


Test(class_moves, knight)
{
    class_t* test_class = class_new("Knight", "Brave",
                                    "Brave and shiny",
                                    NULL, NULL, NULL);

    battle_player_t *player = new_ctx_player("new_ctx_player_Name", test_class,
                                          NULL, NULL, NULL);

    combatant_t *ret_player = set_battle_player(player);
    
    int rc = build_moves(ret_player);

    cr_assert_eq(rc, SUCCESS, "build_moves() failed");

    cr_assert_eq(ret_player->moves->id, 130, "move_new() didn't set move id");

    cr_assert_str_eq(ret_player->moves->name, "",
                     "move_new() didn't set move info");

    cr_assert_str_eq(ret_player->moves->info, "Fireball",
                     "move_new() didn't set move info");

    cr_assert_eq(ret_player->moves->dmg_type, MAG, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->count, 0, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->sp_cost, 10, "move_new() didn't set move id");

    cr_assert_null(ret_player->moves->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(ret_player->moves->damage, 10, "move_new() didn't set move id");

    cr_assert_eq(ret_player->moves->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(ret_player->moves->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(ret_player->moves->next, "move_new() didn't set battle_item to NULL");
}
