#include "wdl/wdl_common.h"
#include "wdl/objstore.h"
#include "game-state/game.h"

#ifndef INCLUDE_WDL_CTX_H
#define INCLUDE_WDL_CTX_H

typedef struct wdl_ctx
{
    //a hashtable of objstores containing all parsed objects from a wdl file
    objstore_t **ht;

    //A temporary measure while the parsing code is not yet finished enough
    //to remove libobj entirely
    obj_t *obj;

} wdl_ctx_t;

/*
 * new_wdl_ctx: creates a new wdl_ctx struct
 *
 * Parameters:
 *   - None
 *
 * Returns:
 *   - a pointer to a wdl_ctx_t
 */
wdl_ctx_t *new_wdl_ctx();

/*
 * init_wdl_ctx: initializes a new wdl_ctx struct
 *
 * Parameters:
 *   - ctx: a pointer to a wdl_ctx struct
 *
 * Returns:
 *   - SUCCESS upon success
 *   - FAILURE if fails
 */
int init_wdl_ctx(wdl_ctx_t *ctx);

/*
 * free_wdl_ctx: frees a wdl_ctx struct
 *
 * Parameters:
 *   - ctx: a pointer to a wdl_ctx struct
 *
 * Returns:
 *   - always SUCCESS
 */
int free_wdl_ctx(wdl_ctx_t *ctx);

#endif /* INCLUDE_WDL_CTX_H */
