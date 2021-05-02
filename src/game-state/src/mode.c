/* Implementations of the mode struct */
#include <string.h>

#include "game-state/mode.h"


/* see mode.h */
int game_mode_init(game_mode_t *mode, mode_type_t curr_mode, 
                   mode_operation run_mode, char* mode_ctx)
{
    assert(mode != NULL);
    strcpy(mode->mode_ctx, mode_ctx);
    mode->curr_mode = curr_mode;
    mode->mode_operation = run_mode;

    return SUCCESS;
}

/* see mode.h */
game_mode_t *game_mode_new(mode_type_t curr_mode, mode_operation run_mode, 
                           char* mode_ctx);
{
    mode_t *mode;
    mode = malloc(sizeof(mode_t));
    memset(mode, 0, sizeof(mode_t));
    mode->mode_ctx = malloc(MAX_ID_LEN * sizeof(char));

    int check = mode_init(mode, curr_mode, run_mode, mode_ctx);

    if (mode == NULL || mode->ctx == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return mode;
}

/* see mode.h */
int game_mode_free(game_mode_t *mode)
{
    assert(mode != NULL);

    free(mode->mode_ctx);
    free(mode);

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
