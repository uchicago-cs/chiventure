/* Implementations of the mode struct */
#include <string.h>

#include "game-state/mode.h"
#include "cli/parser.h"


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
int run_conversation_mode(char *input, cli_callback callback_func, 
                          void *callback_args, chiventure_ctx_t *ctx)
{
    char **parsed_input = parse(input);
    if (parsed_input == NULL)
    {
        return FAILURE;
    }
    
    int option;
    option = atoi(parsed_input[0]);

    /* currently, npcs are not stored by chiventure so that must be
       fixed before this function can be fully implemented */
    /* This assumes that game has an all_npcs hash table field */
    npc_t *npc;
    HASH_FIND_STR(ctx->game->all_npcs, ctx->mode->mode_ctx, npc);

    if ((option <= 0) || (option > npc->dialogue->cur_node->num_edges) || 
        parsed_input[1] != NULL) //assumes convo_t has cur_node field
    {
        return callback_func(ctx, "Enter a valid dialogue option.", callback_args);
    }

    char *outstring = (char*)malloc(1000 * sizeof(char)); //use a BUFLEN
    run_conversation_step(npc->dialogue, option, outstring);

    int rc = callback_func(ctx, outstring, callback_args);

    free(outstring);

    /* If conversation over, switches back to normal mode */
    if (npc->dialogue->cur_node->num_edges == 0)
    {
        rc = game_mode_init(ctx->game->mode, NORMAL, NULL, "normal");
    }

    return SUCCESS;
}


