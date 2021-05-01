/* Implementations of the mode struct */
#include <string.h>

#include "game-state/mode.h"


/* see mode.h */
int mode_init(mode_t *mode, mode_type_t curr_mode, 
              mode_operation run_mode, char* mode_ctx)
{
    assert(mode != NULL);
    strcpy(mode->mode_ctx, mode_ctx);
    mode->curr_mode = curr_mode;
    mode->mode_operation = run_mode;

    return SUCCESS;
}

/* see mode.h */
mode_t *mode_new(mode_type_t curr_mode, mode_operation run_mode, 
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
int mode_free(mode_t *mode)
{
    assert(mode != NULL);

    free(mode->mode_ctx);
    free(mode);

    return SUCCESS;
}

/* see mode.h */
int load_normal_mode(game_t *g)
{
    mode_t *mode = mode_new(NORMAL, NULL, "normal");

    if (mode == NULL)
    {
        return FAILURE;
    }

    g->mode = mode;

    return SUCCESS;
}
