#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "battle/battle_flow.h"

#ifndef BATTLE_FLOW_H
#define BATTLE_FLOW_H

#include "battle_structs.h"
#include "battle_state.h"
#include "common/utlist.h"
#include "common/common.h"
#include <stdbool.h>
#include <string.h>

/* see battle_flow.h */
int start_battle(chiventure_ctx_battle_t *ctx, npc_enemy_t *npc_enemies, combatant_info_t *pinfo, environment_t env)
{
    game_t *g = ctx->game;
    player_t *player = g->curr_player;

    // Set player, enemies, and battle structs for a new battle
    battle_t *b = set_battle(player,pinfo,npc_enemies,env);

    return SUCCESS;
}

/* see battle_flow.h */
combatant_t *set_player(player_t *ctx_player, combatant_info_t *pinfo)
{
    // Setting up arguments for combatant_new
    char* name = ctx_player->player_id;
    bool is_friendly = true;
    stat_t *stats = pinfo->stats;
    move_t *moves = pinfo->moves;
    item_t *items = pinfo->items;
    combatant *prev = NULL; // Single player
    combatant *next = NULL;

    // Allocating new combatant_t for the player in memory
    combatant_t *comb_player = combatant_new(name,is_friendly,stats,
                                             moves,items,prev,next);

    assert(comb_player != NULL);

    return comb_player;
}

/* see battle_flow.h */
combatant_t *set_enemies(npc_enemy_t *npc_enemies)
{
    combatant_t *head = NULL;
    combatant_t *comb_enemy = NULL;

    npc_enemy_t *enemy_elt, *enemy_tmp;
    DL_FOREACH_SAFE(npc_enemies, enemy_elt, enemy_tmp)
    {
        DL_DELETE(npc_enemies, enemy_elt);

        char* name = enemy_elt->npc_id;
        bool is_friendly = false;
        stat_t *stats = enemy_elt->stats;
        move_t *moves = enemy_elt->moves;
        item_t *items = enemy_elt->items;
        combatant *next = NULL;

        comb_enemy = combatant_new(name,is_friendly,stats,moves,items
                                    comb_enemy,next);

        assert(next_enemy != NULL);

        DL_APPEND(head,comb_enemy);
    }

    return head;
};

/* see battle_flow.h */
battle_t *set_battle(player_t *ctx_player, combatant_info_t *pinfo, npc_enemy_t *npc_enemies, environment_t env)
{
    combatant_t *comb_player  = set_player(ctx_player,pinfo);
    combatant_t *comb_enemies = set_enemies(npc_enemies);

    turn_t turn = PLAYER;

    battle_t *b = battle_new(comb_player,comb_enemies,env,turn);

    assert(b != NULL);

    return b;
};
