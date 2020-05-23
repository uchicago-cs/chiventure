#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_structs.h"

/* Tests player_new() */
Test(battle_structs, player_new)
{
    player_t *ctx_player = player_new("player_new_Name", NULL, NULL, NULL);

    cr_assert_not_null(ctx_player, "player_new() failed");
    cr_assert_str_eq(ctx_player->player_id, "player_new_Name", "player_new() didn't set id");
}

/* Tests make_npc_enemy() with 1 enemy */
Test(battle_structs, make_one_npc_enemy)
{
    npc_enemy_t *npc_enemy = make_npc_enemy("make_one_npc_enemy_Name", NULL, NULL, NULL);

    cr_assert_not_null(npc_enemy, "make_npc_enemy() failed");
    cr_assert_str_eq(npc_enemy->npc_id, "make_one_npc_enemy_Name", "make_npc_enemy() didn't set name");
    cr_assert_eq(npc_enemy->next, NULL, "make_npc_enemy() didn't set next");
    cr_assert_eq(npc_enemy->prev, NULL, "make_npc_enemy() didn't set prev");
}


/* Tests make_npc_enemy() with 2 enemies */
Test(battle_structs, set_two_npc_enemies)
{
    npc_enemy_t *head = NULL;
    npc_enemy_t *npc_e1 = make_npc_enemy("set_two_enemies_Name2", NULL, NULL, NULL);
    npc_enemy_t *npc_e2 = make_npc_enemy("set_two_enemies_Name1", NULL, NULL, NULL);
    DL_APPEND(head, npc_e1);
    DL_APPEND(head, npc_e2);

    // Check first npc enemy
    cr_assert_not_null(npc_e1, "make_npc_enemy() failed");
    cr_assert_str_eq(npc_e1->name, "set_two_enemies_Name1", "make_npc_enemy() didn't set name");
    cr_assert_eq(npc_e1->is_friendly, false, "make_npc_enemy() didn't set type");
    cr_assert_eq(npc_e1->next, npc_e2, "make_npc_enemy() didn't set next");
    cr_assert_not_null(npc_e1->prev, "make_npc_enemy() didn't set prev");

    // Check second npc enemy
    cr_assert_not_null(npc_e2, "make_npc_enemy() failed");
    cr_assert_str_eq(npc_e2->name, "set_two_enemies_Name2", "make_npc_enemy() didn't set name");
    cr_assert_eq(npc_e2->is_friendly, false, "make_npc_enemy() didn't set type");
    cr_assert_eq(npc_e2->next, NULL, "make_npc_enemy() didn't set next");
    cr_assert_eq(npc_e2->prev, npc_e1, "make_npc_enemy() didn't set prev");
}

/* Tests game_new() */
Test(battle_structs, game_new)
{
    game_t *g = game_new();

    cr_assert_not_null(g, "game_new() failed");
    cr_assert_eq(g->curr_player, NULL, "game_new() failed");
}
