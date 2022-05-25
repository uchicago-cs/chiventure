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
#include <time.h>

const char *banner = "BATTLE MODE DEMO";

class_t *make_bard2()
{
    return class_new("Bard", "Cool", "Super Duper and Awesome", NULL, NULL, NULL);
}

/* initializes a dummy wizard class */
class_t *make_wizard2()
{
    return class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
}

/* Defines an CLI operation for starting a fight */
char *fight_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    //int rc;

    srand(time(0)); // sets seed
    // creates the stats of the player to begin the battle
    stat_t *p_stats = get_random_stat();
    
    // creates the stats of the enemy to begin the battle
    stat_t *e_stats = get_random_stat();

    // creates consumable for the player
    battle_item_t *p_item = get_random_default_consumable();
    battle_item_t *p_item2 = get_random_default_consumable();

    while (p_item2->id == p_item->id) {
        p_item2 = get_random_default_consumable();
    }

    p_item->next = p_item2;
    p_item2->prev = p_item;

    move_t *p_move = get_random_default_move();
    move_t *p_move2 = get_random_default_move();

    while (p_move2->id == p_move->id) {
        p_move2 = get_random_default_move();
    }

    p_move->next = p_move2;
    p_move2->prev = p_move;
    

    // this creates the player and enemy so that they are inside of ctx
    move_t *e_move = get_random_default_move();
    npc_t *e = npc_new("Goblin", "Enemy goblin!", "Enemy goblin!", make_bard2(), NULL, HOSTILE);
    npc_battle_t *npc_b = npc_battle_new(e_stats, e_move, BATTLE_AI_GREEDY, HOSTILE, NULL, NULL,
                                         NULL, NULL, NULL);
    e->npc_battle = npc_b;
    battle_player_t *p = new_ctx_player("John", make_wizard2(), p_stats, p_move, p_item,
                                        NULL, NULL, NULL);

    battle_ctx_t *battle_ctx =
        (battle_ctx_t *)calloc(1, sizeof(battle_ctx_t));

    // new_game creates a game that is then attached to ctx
    battle_game_t *g = new_battle_game();
    battle_ctx->game = g;

    battle_ctx->game->player = p;

    int add_battle_ctx = add_battle_ctx_to_game(ctx->game, battle_ctx);

    /* start_battle begins the battle by finalizing 
       all finishing touches for a battle to begin */

    int rc = start_battle(battle_ctx, e, ENV_GRASS);

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
    room_t *room1 = room_new("room1", "This is The Room", "You are in The Room. You'll will fight a Goblin in The Room.");
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
    add_entry("FIGHT", fight_operation, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}