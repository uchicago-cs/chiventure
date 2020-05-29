#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow_structs.h"

/* Tests new_ctx_player() */
Test(battle_flow_structs, new_ctx_player)
{
    class_t* test_class = class_new("Bard", "Music boi", "Charismatic, always
                                    has a joke or song ready", NULL, NULL, NULL,
                                    NULL, NULL);

    player_t *ctx_player = new_ctx_player("new_ctx_player_Name", test_class,
                                          NULL, NULL, NULL);

    cr_assert_not_null(ctx_player, "new_ctx_player() failed");
    cr_assert_str_eq(ctx_player->player_id, "new_ctx_player_Name", "new_ctx_player() didn't set id");

    cr_assert_str_eq(ctx_player->class->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(ctx_player->class->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(ctx_player->class->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(ctx_player->attr, "set_player() didn't set class attribute");
    cr_assert_null(ctx_player->stat, "set_player() didn't set class stats");
    cr_assert_null(ctx_player->skilltree,
                   "set_player() didn't set class skilltree");
    cr_assert_null(ctx_player->combat,
                   "set_player() didn't set class skills for combat");
    cr_assert_null(ctx_player->noncombat,
                   "set_player() didn't set class skills for noncombat");
}

/* Tests make_npc_enemy() with 1 enemy */
Test(battle_flow_structs, make_one_npc_enemy)
{
    npc_enemy_t *npc_enemy = make_npc_enemy("make_one_npc_enemy_Name", NULL, NULL, NULL, NULL);

    cr_assert_not_null(npc_enemy, "make_npc_enemy() failed");
    cr_assert_str_eq(npc_enemy->npc_id, "make_one_npc_enemy_Name", "make_npc_enemy() didn't set name");
    cr_assert_eq(npc_enemy->next, NULL, "make_npc_enemy() didn't set next");
    cr_assert_eq(npc_enemy->prev, NULL, "make_npc_enemy() didn't set prev");
}


/* Tests make_npc_enemy() with 2 enemies */
Test(battle_flow_structs, set_two_npc_enemies)
{
    npc_enemy_t *head = NULL;
    npc_enemy_t *npc_e1 = make_npc_enemy("set_two_enemies_Name1", NULL, NULL, NULL, NULL);
    npc_enemy_t *npc_e2 = make_npc_enemy("set_two_enemies_Name2", NULL, NULL, NULL, NULL);
    DL_APPEND(head, npc_e1);
    DL_APPEND(head, npc_e2);

    // Check first npc enemy
    cr_assert_not_null(npc_e1, "make_npc_enemy() failed");
    cr_assert_str_eq(npc_e1->npc_id, "set_two_enemies_Name1", "make_npc_enemy() didn't set name");
    cr_assert_eq(npc_e1->next, npc_e2, "make_npc_enemy() didn't set next");
    cr_assert_not_null(npc_e1->prev, "make_npc_enemy() didn't set prev");

    // Check second npc enemy
    cr_assert_not_null(npc_e2, "make_npc_enemy() failed");
    cr_assert_str_eq(npc_e2->npc_id, "set_two_enemies_Name2", "make_npc_enemy() didn't set name");
    cr_assert_eq(npc_e2->next, NULL, "make_npc_enemy() didn't set next");
    cr_assert_eq(npc_e2->prev, npc_e1, "make_npc_enemy() didn't set prev");
}

/* Tests new_game() */
Test(battle_flow_structs, new_game)
{
    game_t *g = new_game();

    cr_assert_not_null(g, "game_new() failed");
    cr_assert_eq(g->curr_player, NULL, "game_new() failed");
}
