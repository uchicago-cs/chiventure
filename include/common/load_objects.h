#include "wdl/wdl_ctx.h"
#include "wdl/wdl_common.h"

#ifndef INCLUDE_LOAD_OBJECT_H
#define INCLUDE_LOAD_OBJECT_H

/*
 * load_object: takes parsed wdl objects and converts them into game objects
 *
 * Parameters:
 *   - ctx: A wdl_ctx object containing a hashtable of wdl objects
 *
 * Returns:
 *   - A pointer to a game object that has been filled with the appropriate
 *     objects
 */
game_t *load_objects(wdl_ctx_t *ctx);

#endif /* INCLUDE_LOAD_OBJECT_H */
