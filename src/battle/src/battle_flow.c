#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow.h"

/* see battle_flow.h */
int start_battle(chiventure_ctx_battle_t *ctx, npc_enemy_t *npc_enemies, environment_t env)
{
    game_t *g = ctx->game;
    player_t *player = g->curr_player;

    // Set player, enemies, and battle structs for a new battle
    battle_t *b = set_battle(player, npc_enemies, env);

    return SUCCESS;
}

/* see battle_flow.h */
combatant_t *set_player(player_t *ctx_player)
{
    // Setting up arguments for combatant_new
    char* name = ctx_player->player_id;
    bool is_friendly = true;
    class_t *class = ctx_player->class;
    stat_t *stats = ctx_player->stats;
    move_t *moves = ctx_player->moves;
    item_t *items = ctx_player->items;

    // Allocating new combatant_t for the player in memory
    combatant_t *comb_player = combatant_new(name, is_friendly, class, stats,
                                             moves, items);

    assert(comb_player != NULL);

    return comb_player;
}

/* see battle_flow.h */
combatant_t *set_enemies(npc_enemy_t *npc_enemies)
{
    combatant_t *head = NULL;
    combatant_t *comb_enemy;

    npc_enemy_t *enemy_elt;
    DL_FOREACH(npc_enemies, enemy_elt)
    {
        char* name = enemy_elt->npc_id;
        bool is_friendly = false;
        class_t *class = enemy_elt->class;
        stat_t *stats = enemy_elt->stats;
        move_t *moves = enemy_elt->moves;
        item_t *items = enemy_elt->items;

        comb_enemy = combatant_new(name, is_friendly, class, stats, moves, items);

        assert(comb_enemy != NULL);

        DL_APPEND(head, comb_enemy);
    }
    return head;
};

/* see battle_flow.h */
battle_t *set_battle(player_t *ctx_player, npc_enemy_t *npc_enemies, environment_t env)
{
    combatant_t *comb_player  = set_player(ctx_player);
    combatant_t *comb_enemies = set_enemies(npc_enemies);

    turn_t turn = PLAYER;

    battle_t *b = battle_new(comb_player, comb_enemies, env, turn);

    assert(b != NULL);

    return b;
};
