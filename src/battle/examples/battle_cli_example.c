/*
 * This example program runs a full instance of chiventure with a
 * memory game. The CLI is monkey-patched to accept a FIGHT action
 * to initiate a battle by switching chiventure to BATTLE mode
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "common/ctx.h"
#include "ui/print_functions.h"
#include "cli/operations.h"
#include "ui/ui.h"
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_move_maker.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"
#include "battle/battle_logic.h"
#include "battle/battle_default_objects.h"
#include "move_demo.c"
#include "demo_items_and_equipment.c"
#include <time.h>

const char *banner = "BATTLE MODE DEMO";

class_t *make_ninja()
{
    return class_new("Ninja", "Stealthy", "Super stealthy and a fully trained assasin", NULL, NULL, NULL);
}

/* initializes a dummy wizard class */

class_t *make_sorcerer()
{
    return class_new("Sorcerer", "Wise", "Old and wise with crazy magecraft ability", NULL, NULL, NULL);
}

class_t *make_minion()
{
    return class_new("Minion", "Stupid", "Unintelligent, but very strong", NULL, NULL, NULL);
}

/* Defines an CLI operation for starting a fight */
char *run_battle_one(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    //int rc;

    srand(time(0)); // sets seed

    // this creates the player and enemy so that they are inside of ctx
    
    // create player one (sorcerer)
    stat_t *p1_stats = get_random_stat();
    battle_item_t *p1_item = make_items();
    move_t *p1_move = generate_moves_user_one();
    class_t *p1_class = make_sorcerer();
    battle_player_t *p1 = new_ctx_player("Nicholas the Wise", p1_class, p1_stats, p1_move, p1_item, 
                                        NULL, NULL, NULL);

    // create enemy one (minion)
    stat_t *e1_stats = get_random_stat();
    move_t *e1_move = generate_moves_enemy_one();
    class_t *e1_class = make_minion();
    npc_t *e1 = npc_new("Minion", "Enemy Minion!", "Enemy Minion!", e1_class, NULL, true);
    npc_battle_t *npc1_b = npc_battle_new(e1_stats, e1_move, BATTLE_AI_GREEDY, 
                                          HOSTILE, e1_class, p1_item, NULL, NULL, NULL);
    e1->npc_battle = npc1_b;

    battle_ctx_t *battle_ctx = (battle_ctx_t *)calloc(1, sizeof(battle_ctx_t));

    // new_game creates a game that is then attached to ctx
    battle_game_t *g = new_battle_game();
    battle_ctx->game = g;

    battle_ctx->game->player = p1;

    int add_battle_ctx = add_battle_ctx_to_game(ctx->game, battle_ctx);

    /* start_battle begins the battle by finalizing 
       all finishing touches for a battle to begin */

    int rc = start_battle(battle_ctx, e1, ENV_GRASS);

    // prints the beginning of the battle 
    char *start = print_start_battle(battle_ctx->game->battle);
    int start_rc = print_to_cli(ctx, start);
    char *turn_start = print_start_turn(battle_ctx->game->battle);
    int turn_start_rc = print_to_cli(ctx, turn_start);

    if (!rc)
    {
        
        game_mode_init(ctx->game->mode, BATTLE, 
                       run_battle_mode, "Goblin");
    }

    return start;
}

/*
 * Creates a chiventure context with a sample game.
 *
 * Returns: a chiventure context with 
 */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to the Battle CLI Integration Demo for Chiventure!");
    room_t *room1 = room_new("room1", "This is The Room", "You are in The Room. You'll will fight a Minion in The Room.");
    add_room_to_game(game, room1);
    game->curr_room = room1;

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

int main(int argc, char **argv)
{
    
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatching in a fight action to support dialogue */
    add_entry("FIGHT", run_battle_one, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}