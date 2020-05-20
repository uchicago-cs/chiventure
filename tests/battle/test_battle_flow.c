#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_flow.h"


combatant_info_t *make_comb_info(stat_t *stats, move_t *moves, item_t* items)
{
    combatant_info_t *cinfo = calloc(1,sizeof(combatant_info_t));

    cinfo = {stats, moves, items};

    return cinfo;
}

npc_enemy_t *make_npc_enemy(char* npc_id, stats_t *stats, move_t *moves, item_t* items)
{
    npc_enemy_t *npc_e = calloc(1,sizeof(npc_enemy_t));

    npc_e = {npc_id, stats, moves, items};

    return cinfo;
}


Test(battle_flow, set_player)
{
    combatant_t *comb_player;

    player_t *ctx_player = player_new("set_player_Name",100);
    combatant_info_t *pinfo = make_comb_info(NULL,NULL,NULL,bard);

    comb_player = set_player(ctx_player,combatant_info_t);

    cr_assert_not_null(comb_player, "set_player() failed");
    cr_assert_str_eq(comb_player->name, "set_player_Name", "set_player() didn't set name");
    cr_assert_eq(comb_player->is_friendly, true, "set_player() didn't set type");
    cr_assert_eq(comb_player->next, NULL, "set_player() didn't set next");
    cr_assert_eq(comb_player->prev, NULL, "set_player() didn't set prev");

}

Test(battle_flow, set_enemies)
{

}

Test(battle_flow, set_battle)
{
    player_t *ctx_player = player_new("set_battle_Name",100);
    environment_t env = ENV_DESERT;

    battle_t *b = set_battle(ctx_player,npc_enemies,env);

    cr_assert_not_null(b, "set_player() failed");
    cr_assert_str_eq(b->name, "set_player_Name", "set_player() didn't set name");
    cr_assert_eq(b->enemy, true, "set_player() didn't set type");
    cr_assert_eq(b->env, ENV_DESERT, "set_player() didn't set next");
    cr_assert_eq(b->turn, PLAYER, "set_player() didn't set prev");
}

Test(battle_flow, start_battle)
{

}
