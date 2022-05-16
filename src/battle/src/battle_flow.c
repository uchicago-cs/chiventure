#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "battle/battle_print.h"


/* see battle_flow.h */
int start_battle(battle_ctx_t *ctx, npc_t *npc_enemy, environment_t env)
{
    battle_game_t *g = ctx->game;
    battle_player_t *player = g->player;
    // Set battle_player, enemies, and battle structs for a new battle
    battle_t *b = set_battle(player, npc_enemy, env);

    g->battle = b;
    ctx->status = BATTLE_IN_PROGRESS;
    return SUCCESS;
}

/* see battle_flow.h */
combatant_t *set_battle_player(battle_player_t *ctx_player)
{
    // Setting up arguments for combatant_new
    char* name = ctx_player->player_id;
    bool is_friendly = true;
    class_t *c_type = ctx_player->class_type;
    stat_t *stats = ctx_player->stats;
    move_t *moves = ctx_player->moves;
    battle_item_t *items = ctx_player->items;

    // Allocating new combatant_t for the player in memory
    combatant_t *comb_player = combatant_new(name, is_friendly, c_type, stats,
                                             moves, items, BATTLE_AI_NONE);

    assert(comb_player != NULL);

    return comb_player;
}

/* see battle_flow.h */
combatant_t *set_enemy(npc_t *npc_enemy)
{
    if (npc_enemy->npc_battle == NULL)
    {
        return NULL;
    }

    combatant_t *comb_enemy;

    char* name = npc_enemy->npc_id;
    bool is_friendly = false;
    class_t *c_type = npc_enemy->class;
    stat_t *stats = npc_enemy->npc_battle->stats;
    move_t *moves = npc_enemy->npc_battle->moves;
    battle_item_t *items = NULL; // TODO: extract battle_item_t from npc's inventory
    difficulty_t ai = npc_enemy->npc_battle->ai;
    
    comb_enemy = combatant_new(name, is_friendly, c_type, stats, moves, items, ai);
    assert(comb_enemy != NULL);

    return comb_enemy;
}

/* see battle_flow.h */
battle_t *set_battle(battle_player_t *ctx_player, npc_t *npc_enemy, environment_t env)
{
    combatant_t *comb_player  = set_battle_player(ctx_player);
    combatant_t *comb_enemies = set_enemy(npc_enemy);

    /* Builds a move list using player class module */
    if (comb_player->moves == NULL)
    {
        build_moves(comb_player);
    }
    if (comb_enemies->moves == NULL)
    {
        build_moves(comb_enemies); // This will have to be updated if multiple enemies are added
    }
    
    turn_t turn = PLAYER;

    battle_t *b = battle_new(comb_player, comb_enemies, env, turn);

    assert(b != NULL);

    return b;
}

/* see battle_flow.h */
char *battle_flow_move(battle_ctx_t *ctx, move_t *move, char* target)
{
    battle_t *b = ctx->game->battle;

    /* the following 3 if statements are stubs, error handling must be clarified
       with custom actions at a later date */
    if (ctx == NULL || move == NULL || target == NULL)
    {
        return "FAILURE";
    }
    combatant_t *enemy = check_target(b, target);
    
    if(enemy == NULL)
    {
        /* print stub: should tell player that their target was invalid
           battle_flow then returns the original, unmodified ctx and waits
           for the next move */
        return "Non-valid enemy chosen";
    }
    
    /* move stub, battle_flow should call either a custom action block or a
       function that works with a move_t struct */
    /* additionally, a check must be performed here to see if player has
       this move, currently not implemented, waiting for player class
       to resolve move_lists() */
    int dmg = damage(b->enemy, move, b->player);
    enemy->stats->hp -= dmg;
    char *string = print_battle_move(b, b->turn, move);

    if(battle_over(b) == BATTLE_VICTOR_PLAYER)
    {
        /* print stub: should tel player they won */
        award_xp(b->player->stats, 2.0);
        ctx->status = BATTLE_VICTOR_PLAYER;
    }
    
    if(battle_over(b) == BATTLE_IN_PROGRESS)
    {
        char *res = enemy_make_move(ctx);
        strncat(string, res, 150);
        free(res);
    }

    return string;
}

char *battle_flow_item(battle_ctx_t *ctx, battle_item_t *item)
{
    battle_t *b = ctx->game->battle;
    char *string = calloc(150, sizeof(char));

    if (ctx == NULL)
    {
        snprintf(string, 150, "FAILURE\n");
        return string;
    }
    if (item == NULL)
    {
        snprintf(string, 150, "FAILURE\n");
        return string;
    }
    if (item->quantity <= 0){
       snprintf(string, 150, "FAILURE\n");
        return string;
    }

    char *item_name;
    strcpy(item_name, item->name);

    int usage = use_battle_item(ctx->game->battle->player, ctx->game->battle, item->name);
    snprintf(string, 150, "You used the %s\n", item_name);

    if (usage == FAILURE) 
    {
        snprintf(string, 150, "That item is Unavailable.\n");
        return string;
    } 

    if(battle_over(b) == BATTLE_IN_PROGRESS)
    {
        char *res = enemy_make_move(ctx);
        strncat(string, res, 150);
        free(res);
    }

    return string;
}

/* see battle_flow.h */
char *battle_flow_list(battle_ctx_t *ctx, char* label)
{
    if (strcmp(label, "items") == 0) 
    {
        battle_t *b = ctx->game->battle;

        char *string = calloc(500, sizeof(char));
        print_battle_items(b, string);

        return string;
    } if (strcmp(label, "moves") == 0) 
    {
        battle_t *b = ctx->game->battle;

        char *string = calloc(500, sizeof(char));
        print_moves(b, string);

        return string;
    } else 
    {
             
        char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
        snprintf(string, BATTLE_BUFFER_SIZE, "Please enter a valid battle command!");
        
        return string;
    }
}

/* see battle_flow.h */
char *enemy_make_move(battle_ctx_t *ctx) 
{
    battle_t *b = ctx->game->battle;
    b->turn = ENEMY;

    /* move stub, battle_flow should call either a custom action block or a
       function that works with a move_t struct */
    move_t *enemy_move = give_move(b->player, b->enemy, b->enemy->ai);
    int dmg;
    char *string = calloc(100, sizeof(char));

    if(enemy_move != NULL)
    {
        dmg = damage(b->player, enemy_move, b->enemy);
        b->player->stats->hp -= dmg;
        string = print_battle_move(b, b->turn, enemy_move);
    }
    
    if(battle_over(b) == BATTLE_VICTOR_ENEMY)
    {
        /* print stub: should tell player they lost */
        ctx->status = BATTLE_VICTOR_ENEMY;
    }

    b->turn = PLAYER;

    return string;
}


/* see battle_flow.h */
int run_turn_component(chiventure_ctx_t *ctx, turn_component_t component,
                        void *callback_args, cli_callback callback_func){
    move_t *legal_moves = NULL;
    battle_item_t *legal_items = NULL;
    get_legal_actions(legal_items, legal_moves, component, ctx->game->battle_ctx->game->battle);
    if (ctx->game->battle_ctx->game->battle->turn == ENEMY){
        battle_flow_move(ctx->game->battle_ctx, 
                                ctx->game->battle_ctx->game->player->moves, 
                                ctx->game->battle_ctx->game->battle->player->name);
        char *movestr = print_battle_move(ctx->game->battle_ctx->game->battle,
                                ctx->game->battle_ctx->game->battle->turn,
                                ctx->game->battle_ctx->game->battle->enemy->moves);
        //print_to_cli(ctx, movestr);
        //printf("%s",movestr);
        callback_func(ctx, movestr, callback_args);
    }
    char *strg = print_battle_action_menu(legal_items, legal_moves);
    // print to cli
      //_cli(ctx, strg);
    //printf("%s", strg);
    callback_func(ctx, strg, callback_args);
    // take in user input
    char *input;
    scanf("%s", input);
    if (input[0] == 'M' || input[0] == 'm'){
        // take the index of the move, under the assumption that the list is less than 10 moves long
        
        int index = (int) input[1];
        for (int k = 0; k < index; k++){
            if (ctx->game->battle_ctx->game->player->moves == NULL){
                return callback_func(ctx, "That move does not exist.", callback_args);
            }
            if (k == index-1){
                    battle_flow_move(ctx->game->battle_ctx, 
                                ctx->game->battle_ctx->game->player->moves, 
                                ctx->game->battle_ctx->game->battle->enemy->name);
                    char *movestr = print_battle_move(ctx->game->battle_ctx->game->battle,
                                ctx->game->battle_ctx->game->battle->turn,
                                ctx->game->battle_ctx->game->player->moves);
                    //print_to_cli(ctx, movestr);
                    //printf("%s",movestr);
                    callback_func(ctx, movestr, callback_args);
            }
            else {
                ctx->game->battle_ctx->game->player->moves = 
                ctx->game->battle_ctx->game->player->moves->next;
            }
        }
    } else if (input[0] == 'I' || input[0] == 'i'){
        int index = (int) input[1];
        for (int k = 0; k < index; k++){
            if (ctx->game->battle_ctx->game->player->items == NULL){
                return callback_func(ctx, "That item does not exist.", callback_args);
            }
            if (k == index-1){
                battle_flow_item(ctx->game->battle_ctx, 
                                ctx->game->battle_ctx->game->player->items);
                char *itemstr = print_battle_move(ctx->game->battle_ctx->game->battle,
                                ctx->game->battle_ctx->game->battle->turn,
                                ctx->game->battle_ctx->game->player->moves);
                //print_to_cli(ctx, itemstr);
                //printf("%s",itemstr);
                callback_func(ctx, itemstr, callback_args);
            }
            else {
                ctx->game->battle_ctx->game->player->items = 
                ctx->game->battle_ctx->game->player->items->next;
            }
        }
    } else if (input[0] == 'D' || input[0] == 'd') {
        char *str = (char *) malloc (sizeof(char) * 17);
        str = "You did nothing.";
        //print_to_cli(ctx, str);
        //printf("%s",str);
        callback_func(ctx, "You did nothing.", callback_args);
        return 1;
    } else {
        return callback_func(ctx, "That action does not exist.", callback_args);
    }

    return 1;
}
