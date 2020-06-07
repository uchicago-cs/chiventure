#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow.h"

/* see battle_flow.h */
int start_battle(chiventure_ctx_battle_t *ctx, npc_enemy_t *npc_enemies, environment_t env)
{
    game_t *g = ctx->game;
    player_t *player = g->player;

    // Set player, enemies, and battle structs for a new battle
    battle_t *b = set_battle(player, npc_enemies, env);

    g->battle = b;
    ctx->status = BATTLE_IN_PROGRESS;
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
                                             moves, items, BATTLE_AI_NONE);

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
        difficulty_t ai = enemy_elt->ai;

        comb_enemy = combatant_new(name, is_friendly, class, stats, moves, items, ai);

        assert(comb_enemy != NULL);

        DL_APPEND(head, comb_enemy);
    }
    return head;
}

/* see battle_flow.h */
battle_t *set_battle(player_t *ctx_player, npc_enemy_t *npc_enemies, environment_t env)
{
    combatant_t *comb_player  = set_player(ctx_player);
    combatant_t *comb_enemies = set_enemies(npc_enemies);

    /* Builds a move list using player class module */
    build_moves(comb_player);
    build_moves(comb_enemies); // This will have to be updated if multiple enemies are added
    
    turn_t turn = PLAYER;

    battle_t *b = battle_new(comb_player, comb_enemies, env, turn);

    assert(b != NULL);

    return b;
}

/* see battle_flow.h */
int battle_flow(chiventure_ctx_battle_t *ctx, move_t *move, char* target)
{
    battle_t *b = ctx->game->battle;

    /* the following 3 if statements are stubs, error handling must be clarified
       with custom actions at a later date */
    if (ctx == NULL || move == NULL || target == NULL)
    {
        return FAILURE;
    }
    combatant_t *enemy = check_target(b, target);
    
    if(enemy == NULL)
    {
        /* print stub: should tell player that their target was invalid
           battle_flow then returns the original, unmodified ctx and waits
           for the next move */
        return FAILURE;
    }
    
    /* move stub, battle_flow should call either a custom action block or a
       function that works with a move_t struct */
    /* additionally, a check must be performed here to see if player has
       this move, currently not implemented, waiting for player class
       to resolve move_lists() */
    int dmg = damage(b->enemy, move, b->player);
    printf("e:%d - %d = %d\n",enemy->stats->hp,dmg,enemy->stats->hp - dmg);
    enemy->stats->hp -= dmg;

    if(battle_over(b) == BATTLE_VICTOR_PLAYER)
    {
        /* print stub: should tel player they won */
        award_xp(b->player->stats, 2.0);
        ctx->status = BATTLE_VICTOR_PLAYER;

        return SUCCESS;
    }

    /* move stub, battle_flow should call either a custom action block or a
       function that works with a move_t struct */
    move_t *enemy_move = give_move(b->player, b->enemy, b->enemy->ai);

    if(enemy_move != NULL)
    {
        int dmg = damage(b->player, enemy_move, b->enemy);
        printf("p:%d - %d = %d\n",b->player->stats->hp, dmg,
        b->player->stats->hp - dmg);
        b->player->stats->hp -= dmg;
    }
    else
    {
        return FAILURE;
    }
    
    if(battle_over(b) == BATTLE_VICTOR_ENEMY)
    {
        /* print stub: should tell player they lost */
        ctx->status = BATTLE_VICTOR_ENEMY;
        return SUCCESS;
    }

    return SUCCESS;
}
