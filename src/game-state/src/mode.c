/* Implementations of the mode struct */
#include <string.h>
#include <stdlib.h>

#include "game-state/mode.h"
#include "cli/parser.h"
#include "game-state/game.h"
#include "battle/battle_flow.h"
#include "battle/battle_logic.h"
#include "battle/battle_print.h"


/* see mode.h */
int game_mode_init(game_mode_t *mode, mode_type_t curr_mode, 
                   mode_operation run_mode, char *mode_ctx)
{
    assert(mode != NULL);
    strncpy(mode->mode_ctx, mode_ctx, MAX_ID_LEN);
    mode->curr_mode = curr_mode;
    mode->run_mode = run_mode;

    return SUCCESS;
}

/* see mode.h */
game_mode_t *game_mode_new(mode_type_t curr_mode, mode_operation run_mode, 
                           char *mode_ctx)
{
    game_mode_t *mode;
    mode = malloc(sizeof(mode_t));
    memset(mode, 0, sizeof(mode_t));
    mode->mode_ctx = malloc(MAX_ID_LEN * sizeof(char));

    int check = game_mode_init(mode, curr_mode, run_mode, mode_ctx);

    if (mode == NULL || mode->mode_ctx == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return mode;
}

/* see mode.h */
int game_mode_free(game_mode_t *mode)
{
    if (mode != NULL)
    {
        free(mode->mode_ctx);
        free(mode);
    }

    return SUCCESS;
}

/* see mode.h */
int load_normal_mode(game_t *g)
{
    char normal_ctx[20] = "normal";
    game_mode_t *mode = game_mode_new(NORMAL, NULL, normal_ctx);

    if (mode == NULL)
    {
        return FAILURE;
    }

    g->mode = mode;

    return SUCCESS;
}

/* see mode.h */
int set_game_mode(game_t *g, mode_type_t curr_mode, char *mode_ctx)
{
    int rc;
    switch (curr_mode) 
    {
        case NORMAL:
            rc = game_mode_init(g->mode, NORMAL, NULL, "normal");
            break;

        case CONVERSATION:
            if (mode_ctx == NULL)
            {
                return FAILURE;
            }

            rc = game_mode_init(g->mode, CONVERSATION,
                                run_conversation_mode, mode_ctx);
            break;

        default:
            return FAILURE;
    }
    
    return rc;
}

/* see mode.h */
int run_conversation_mode(char *input, cli_callback callback_func, 
                          void *callback_args, chiventure_ctx_t *ctx)
{
    char **parsed_input = parse(input);
    if (parsed_input == NULL)
    {
        return FAILURE;
    }
    
    int option, num_options, rc;
    option = atoi(parsed_input[0]);

    npc_t *npc = get_npc(ctx->game, ctx->game->mode->mode_ctx);
    num_options = npc->dialogue->cur_node->num_edges;

    if ((option <= 0) || (option > num_options) || 
        parsed_input[1] != NULL) 
    {
        return callback_func(ctx, "Enter a valid dialogue option.", callback_args);
    }

    int end_convo;
    char *outstring = run_conversation_step(npc->dialogue, option, &end_convo, ctx->game);

    assert(end_convo != -1); //checking for conversation error

    /* Print npc dialogue and dialogue options */
    rc = callback_func(ctx, outstring, callback_args);

    free(outstring);

    /* If conversation over, switches back to normal mode */
    if (end_convo)
    {
        rc = set_game_mode(ctx->game, NORMAL, NULL);
    }

    return SUCCESS;
}

/* see mode.h */
int run_battle_mode (char *input, cli_callback callback_func, 
                          void *callback_args, chiventure_ctx_t *ctx)
{
    char **parsed_input = parse(input);
    if (parsed_input == NULL) 
    {
        return FAILURE;
    }
    int rc;
    turn_component_list_t *buffer;
    turn_component_list_t *tcl_buffer = ctx->game->battle_ctx->tcl;
    DL_FOREACH(tcl_buffer, buffer)
    {
        char *output = run_action(input, ctx);
        buffer = buffer->next;
        if (buffer != NULL)
        {
            if (ctx->game->battle_ctx->status == BATTLE_IN_PROGRESS)
            {
                move_t *legal_moves = NULL;
                battle_item_t *legal_items = NULL;
                get_legal_actions(legal_items, legal_moves, buffer->current, 
                            ctx->game->battle_ctx->game->battle);
                char *menu = print_battle_action_menu(legal_items, legal_moves);
                char *output_and_menu = strcat(output, menu);
                ctx->game->battle_ctx->game->battle->current_tc = buffer->current;
                return callback_func(ctx, output_and_menu, callback_args);
            }
            else
            {
                char *battle_over = print_battle_winner (ctx->game->battle_ctx->status, 42);
                char *output_and_battle_over = strcat(output, battle_over);
                callback_func(ctx, battle_over, callback_args);
                free(battle_over);
                rc = game_mode_init(ctx->game->mode, NORMAL, NULL, "normal");
                return SUCCESS;
            }
        }
        else 
        {
            if (ctx->game->battle_ctx->status == BATTLE_IN_PROGRESS)
            {
                char *enemy_turn = enemy_run_turn(ctx->game->battle_ctx); 
                char *output_and_enemy_turn = strcat(output, enemy_turn);
                return callback_func(ctx, output_and_enemy_turn, callback_args);
            }
            else 
            {
                char *battle_over = print_battle_winner (ctx->game->battle_ctx->status, 42);
                char *output_and_battle_over = strcat(output, battle_over);
                callback_func(ctx, battle_over, callback_args);
                free(battle_over);
                rc = game_mode_init(ctx->game->mode, NORMAL, NULL, "normal");
                return SUCCESS;
            }
        }
    }
}

