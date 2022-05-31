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
*/
/* Defines an CLI operation for starting a fight */
/*
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

class_t *make_minion()
{
    return class_new("Minion", "Stupid", "Unintelligent, but very strong", NULL, NULL, NULL);
}

battle_player_t * create_player_one() 
{
    // create player one (sorcerer)
    stat_t *p_stats = (stat_t*) calloc(1, sizeof(stat_t));
    p_stats->hp = 100;
    p_stats->max_hp = 100;
    p_stats->xp = 10;
    p_stats->speed = 10;
    p_stats->level = 3;
    p_stats->phys_def = 50;
    p_stats->mag_def = 50;
    p_stats->phys_atk = 80;
    p_stats->mag_atk = 80;
    p_stats->sp = 100;
    p_stats->max_sp = 100;
    p_stats->crit = 25;
    p_stats->accuracy = 100;
    battle_item_t *p1_item = make_items();
    move_t *p1_move = generate_moves_user_one();
    move_t *second_batch = generate_moves_user_two();
    p1_move->next->next = second_batch;
    second_batch->prev = p1_move->next->next;
    class_t *p1_class = make_sorcerer();
    battle_player_t *p1 = new_ctx_player("Nicholas the Wise", p1_class, 
                                         p_stats, p1_move, p1_item, 
                                         NULL, NULL, NULL);
}

npc_t *create_minion_one() 
{
  // create enemy one (minion)
    stat_t *e_stats = (stat_t*) calloc(1, sizeof(stat_t));
    e_stats->hp = 80;
    e_stats->max_hp = 80;
    e_stats->xp = 10;
    e_stats->speed = 8;
    e_stats->level = 3;
    e_stats->phys_def = 40;
    e_stats->mag_def = 20;
    e_stats->phys_atk = 60;
    e_stats->mag_atk = 60;
    e_stats->sp = 100;
    e_stats->max_sp = 100;
    e_stats->crit = 25;
    e_stats->accuracy = 100;
    move_t *e_move = generate_moves_enemy_one();
    class_t *e_class = make_minion();
    battle_item_t *p_item = make_items();
    npc_t *e = npc_new("Minion", "Enemy Minion!", "Enemy Minion!", e_class, NULL, HOSTILE);
    npc_battle_t *npc_b = npc_battle_new(e_stats, e_move, BATTLE_AI_GREEDY, 
                                          HOSTILE, e_class, p_item, NULL, NULL, NULL);
    e->npc_battle = npc_b;
    return e;
}
npc_t *create_ninja()
{
  // create enemy one (minion)
    stat_t *e_stats = (stat_t*) calloc(1, sizeof(stat_t));
    e_stats->hp = 80;
    e_stats->max_hp = 80;
    e_stats->xp = 10;
    e_stats->speed = 8;
    e_stats->level = 3;
    e_stats->phys_def = 40;
    e_stats->mag_def = 20;
    e_stats->phys_atk = 60;
    e_stats->mag_atk = 60;
    e_stats->sp = 100;
    e_stats->max_sp = 100;
    e_stats->crit = 25;
    e_stats->accuracy = 100;
    move_t *e_move = generate_moves_enemy_one();
    class_t *e_class = make_minion();
    battle_item_t *p_item = make_items();
    npc_t *e = npc_new("ninja", "Enemy Minion!", "Enemy Minion!", e_class, NULL, HOSTILE);
    npc_battle_t *npc_b = npc_battle_new(e_stats, e_move, BATTLE_AI_GREEDY, 
                                          HOSTILE, e_class, p_item, make_zenith(), make_razor_claw(), make_ninja_armor());
    e->npc_battle = npc_b;
    return e;
}

/* sets up the context for the first demo battle */
room_t *setup_battle_one(chiventure_ctx_t *ctx)
{
    srand(time(0)); // sets seed

    // creates a battle_ctx for the battle
    battle_ctx_t *battle_ctx = (battle_ctx_t *)calloc(1, sizeof(battle_ctx_t));

    // sets up the turn component list
    turn_component_t *tc1 = new_turn_component(1, 1, 0);
    turn_component_t *tc2 = new_turn_component(0, 1, 1);

    turn_component_list_t *turn_cl_rest = new_turn_component_list(tc2, NULL);
    turn_component_list_t *turn_cl = new_turn_component_list(tc1, turn_cl_rest);
    battle_ctx->tcl = turn_cl;
    battle_ctx->current_turn_tcl = battle_ctx->tcl;

    // creates a game and attaches it to the battle_ctx
    battle_game_t *g = new_battle_game();
    battle_ctx->game = g;

    // creates player 1 (sorcerer), and minion 1 (no armor)
    battle_player_t *p1 = create_player_one();
    npc_t *e1 = create_minion_one();
    npc_t *e2 = create_ninja();
    
    // create a room and add the npc to it
    room_t *room = room_new("room1", 
                            "This is The Room", 
                            "You are in a torchlit hallway. a minion blocks your path and a ninja crouches in the shadows beyond");
    add_npc_to_room(room->npcs, e1);
    add_npc_to_room(room->npcs, e2);

    //adds battle_player to battle_ctx
    battle_ctx->game->player = p1;
    
    // add battle context to the game
    int add_battle_ctx = add_battle_ctx_to_game(ctx->game, battle_ctx);
*/
/* start_battle begins the battle by finalizing
   all finishing touches for a battle to begin */
/*
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
*/
/*
 * Creates a chiventure context with a sample game.
 *
 * Returns: a chiventure context with
 */
/*
chiventure_ctx_t *create_sample_ctx()
{
   game_t *game = game_new("Welcome to the Battle CLI Integration Demo for Chiventure!");
   room_t *room1 = room_new("room1", "This is The Room", "You are in The Room. You'll will fight a Goblin in The Room.");
   add_room_to_game(game, room1);
   game->curr_room = room1;
*/
/* Create context */
/*
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return room;
}

int main(int argc, char **argv)
{
    /*
    chiventure_ctx_t *ctx = create_sample_ctx();
    */
    /* Monkeypatching in a fight action to support dialogue */

    // add the room to the game in the chiventure_ctx
    add_room_to_game(game, room);
    game->curr_room = room;

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}