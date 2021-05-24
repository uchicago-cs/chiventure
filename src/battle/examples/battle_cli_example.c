/*
 * This example program runs a full instance of chiventure with a
 * memory game. The CLI is monkey-patched to accept a FIGHT action
 * to initiate a battle by switching chiventure to BATTLE mode
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "common/ctx.h"
#include "cli/operations.h"
#include "ui/ui.h"
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle_move_maker.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"
#include "battle/battle_logic.h"
#include "battle/battle_default_objects.h"
#include <time.h>

const char *banner = "BATTLE MODE DEMO";

/* Defines an CLI operation for starting a fight */
char *fight_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    int rc;

    srand(time(0)); // sets seed
    // creates the stats of the player to begin the battle
    stat_t *p_stats = get_random_stat();
    
    // creates the stats of the enemy to begin the battle
    stat_t *e_stats = get_random_stat();

    // creates consumable for the player
    battle_item_t *p_item = get_random_default_consumable();

    // this creates the player and enemy so that they are inside of ctx
    npc_enemy_t *e = NULL;
    DL_APPEND(e, make_npc_enemy("Goblin", make_bard(), e_stats, NULL, NULL, BATTLE_AI_GREEDY));
    battle_player_t *p = new_ctx_player("John", make_wizard(), p_stats, NULL, p_item);

    chiventure_ctx_battle_t *battle_ctx =
        (chiventure_ctx_battle_t *)calloc(1, sizeof(chiventure_ctx_battle_t));

    // new_game creates a game that is then attached to ctx
    battle_game_t *g = new_battle_game();
    battle_ctx->game = g;

    battle_ctx->game->player = p;

    /* start_battle begins the battle by finalizing 
       all finishing touches for a battle to begin */
    start_battle(battle_ctx, e, ENV_GRASS);

    // prints the beginning of the battle 
    char *start = print_start_battle(battle_ctx->game->battle);

    if (!rc)
    {
        //This doesn't work yet, we need to figure lots of stuff out first
        game_mode_init(ctx->game->mode, BATTLE, 
                       run_battle_mode, "Goblin");
    }

    return start;
}



int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatching in a fight action to support dialogue */
    add_entry("FIGHT", fight_operation, NULL, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}