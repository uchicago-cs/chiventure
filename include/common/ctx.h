/*
 * Defines a context struct to store shared state
 */

#ifndef CHIVENTURE_CHIVENTURE_H
#define CHIVENTURE_CHIVENTURE_H


#include "common.h"
#include "cli/cli_ctx.h"
#include "game-state/game.h"


// Forward declaration
typedef struct ui_ctx ui_ctx_t;
typedef struct cli_ctx cli_ctx_t;
typedef struct lookup_entry lookup_t;
typedef struct game game_t;

/* A context struct encapsulating all the shared state in chiventure */
typedef struct chiventure_ctx {
    /* Add component-specific structs here */

    ui_ctx_t *ui_ctx;
    cli_ctx_t *cli_ctx;
    game_t *game;
    obj_t *obj_store;
} chiventure_ctx_t;


/*
 * Allocates and initializes a new chiventure context.
 *
 * Parameters:
 *  - game: The game to be run in this context.
 *          If NULL, an empty game is created that simply
 *          warns the user they need to load a game.
 *
 * Returns:
 *  - A pointer to the context, or NULL if it cannot be allocated
 */
chiventure_ctx_t* chiventure_ctx_new(game_t *game);


/*
 * Initializes a chiventure context.
 *
 * Parameters:
 *  - ctx: A chiventure context. Must already point to allocated memory
 *  - game: The game to be run in this context.
 *          If NULL, an empty game is created that simply
 *          warns the user they need to load a game.
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs.
 */
int chiventure_ctx_init(chiventure_ctx_t *ctx, game_t *game);


/*
 * Frees a chiventure context.
 *
 * Parameters:
 *  - ctx: A heap-allocated chiventure context.
 *
 * Returns:
 *  - Always returns 0.
 */
int chiventure_ctx_free(chiventure_ctx_t *ctx);

#endif //CHIVENTURE_CHIVENTURE_H
