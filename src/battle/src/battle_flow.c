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
int start_battle(chiventure_ctx_t *ctx, elist_t *enemynpcs, combatant_info_t *pinfo, environment_t env)
{
    game_t *g = ctx->game;
    player_t *player = g->curr_player;

    // Set player, enemies, and battle structs for a new battle
    battle_t *b = set_battle(player,pinfo,enemynpcs,env);

    return SUCCESS;
}

/* see battle_flow.h */
combatant_t *set_player(player_t *player, combatant_info_t *pinfo)
{
    // Setting up arguments for combatant_new
    char* name = player->player_id;
    bool is_friendly = true;
    class_t class = pinfo->class;
    stat_t *stats = pinfo->stats;
    move_t *moves = pinfo->moves;
    item_t *items = pinfo->items;
    combatant *prev = NULL; // Single player
    combatant *next = NULL;

    // Allocating new combatant_t for the player in memory
    combatant_t *comb_player = combatant_new(name,is_friendly,class,stats,
                                             moves,items,prev,next);

    assert(comb_player != NULL);

    return comb_player;
}

/* see battle_flow.h */
combatant_t *set_enemies(elist_t *enemynpcs)
{
    combatant_t *comb_enemy = NULL;
    combatant_t *next_enemy = NULL;

    while (enemynpcs) {

        enemynpc_t *e = enemynpcs->enemynpc;
        char* name = e->npc_id;
        bool is_friendly = false;
        class_t class = e->class;
        stat_t *stats = e->stats;
        move_t *moves = e->moves;
        item_t *items = e->items;
        combatant *next = NULL;

        next_enemy = combatant_new(name,is_friendly,class,stats,moves,items
                                    comb_enemy,next);
        assert(next_enemy != NULL);

        comb_enemy->next = next_enemy;

        comb_enemy = next_enemy;
        enemynpcs = enemynpcs->next;
    }

    return comb_enemy;
};

/* see battle_flow.h */
battle_t *set_battle(player_t *player, combatant_info_t *pinfo, elist_t *enemynpcs, environment_t env)
{
    combatant_t *comb_player  = set_player(player,pinfo);
    combatant_t *comb_enemies = set_enemies(enemynpcs);

    turn_t turn = PLAYER;

    battle_t *b = battle_new(comb_player,comb_enemies,env,turn);

    assert(b != NULL);

    return b;
};
