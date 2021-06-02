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

    char *string;    
    int rc;
    battle_ctx_t *battle_ctx = ctx->game->battle_ctx;

    if (strcmp(parsed_input[0], "use") == 0) 
    {
        input += 4;
        move_t *move = find_player_move(battle_ctx, input);

        if (move == NULL) {
            return callback_func(ctx, "That Move does not exist.", callback_args);
        }

        string = battle_flow_move(battle_ctx, move, battle_ctx->game->battle->enemy->name);

    } else if (strcmp(parsed_input[0], "consume") == 0)
    {
        char *stringed_input = calloc(100, sizeof(char));
        for (int i = 1; parsed_input[i] != NULL; i++) 
        {
            strncat(stringed_input, parsed_input[i], 100);
            strncat(stringed_input, " ", 100);
        }

        battle_item_t *item = find_battle_item(battle_ctx->game->player->items, stringed_input);
        free(stringed_input);

        if (item == NULL) 
        {
            return callback_func(ctx, "That Item does not exist.", callback_args);
        }
        string = battle_flow_item(battle_ctx, item);

    } else if (strcmp(parsed_input[0], "list") == 0)
    {
        string = battle_flow_list(battle_ctx, parsed_input[1]);

    } else 
    {
        return callback_func(ctx, "Enter a valid battle command.", callback_args);
    }

    callback_func(ctx, string, callback_args);
    free(string);

    if (battle_ctx->status != BATTLE_IN_PROGRESS) 
    {
        char *battle_over = print_battle_winner (battle_ctx->status, 42);
        callback_func(ctx, battle_over, callback_args);
        free(battle_over);
        
        rc = game_mode_init(ctx->game->mode, NORMAL, NULL, "normal");
    }

    return SUCCESS;
}