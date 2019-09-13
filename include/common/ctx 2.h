/*
 * Defines a context struct to store shared state
 */

#ifndef CHIVENTURE_CHIVENTURE_H
#define CHIVENTURE_CHIVENTURE_H


#include <ncurses.h>
#include "common.h"
#include "game-state/game.h"
#include "ui/ui_ctx.h"
#include "cli/cmd.h"

// Forward declaration
typedef struct ui_ctx ui_ctx_t;
typedef struct lookup_entry lookup_t;

/* A context struct encapsulating all the shared state in chiventure */
typedef struct chiventure_ctx {
    /* Add component-specific structs here */

    ui_ctx_t *ui_ctx;
    game_t *game;
    lookup_t **table;
} chiventure_ctx_t;


/*
 * Allocates and initializes a new chiventure context.
 *
 * Parameters:
 *  - filepath: path to yaml file to load game
 *
 * Returns:
 *  - A pointer to the context, or NULL if it cannot be allocated
 */
chiventure_ctx_t* chiventure_ctx_new(char *filepath);


/*
 * Initializes a chiventure context.
 *
 * Parameters:
 *  - ctx: A chiventure context. Must already point to allocated memory
 *  - filepath: filepath to yaml file to load game
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs.
 */
int chiventure_ctx_init(chiventure_ctx_t *ctx, char *filepath);


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
