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

    cr_assert_null(ret_player->moves->item,
                   "add_class_move() didn't set battle_item to NULL");
   
    cr_assert_eq(ret_player->moves->id, 0, "add_class_move() didn't set id");

    cr_assert_str_eq(ret_player->moves->info, "Diss Track",
                    "add_class_move() didn't set move/spell info");

    cr_assert(ret_player->moves->attack,
             "add_class_move() didn't set attack to true");

    cr_assert_eq(ret_player->moves->damage, 80,
                 "add_class_move() didn't set damage");

    cr_assert_eq(ret_player->moves->defense, 0,
                 "add_class_move() didn't set defense");
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

    cr_assert_null(ret_player->moves->item,
                   "add_class_move() didn't set battle_item to NULL");

    cr_assert_eq(ret_player->moves->id, 1, "add_class_move() didn't set id");

    cr_assert_str_eq(ret_player->moves->info, "Fireball",
                    "add_class_move() didn't set move/spell info");

    cr_assert(ret_player->moves->attack,
             "add_class_move() didn't set attack to true");

    cr_assert_eq(ret_player->moves->damage, 100,
                 "add_class_move() didn't set damage");

    cr_assert_eq(ret_player->moves->defense, 0,
                 "add_class_move() didn't set defense");
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

    cr_assert_null(ret_player->moves->item,
                   "add_class_move() didn't set battle_item to NULL");

    cr_assert_eq(ret_player->moves->id, 2, "add_class_move() didn't set id");

    cr_assert_str_eq(ret_player->moves->info, "Sword Slash",
                    "add_class_move() didn't set move/spell info");

    cr_assert(ret_player->moves->attack,
             "add_class_move() didn't set attack to true");

    cr_assert_eq(ret_player->moves->damage, 90,
                 "add_class_move() didn't set damage");

    cr_assert_eq(ret_player->moves->defense, 0,
                 "add_class_move() didn't set defense");
}