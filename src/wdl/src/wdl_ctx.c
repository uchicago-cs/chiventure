#include "wdl/wdl_ctx.h"

/* See wdl_ctx_h for documentation */
wdl_ctx_t *new_wdl_ctx()
{
    wdl_ctx_t *ctx = calloc(1, sizeof(wdl_ctx_t));

    if(init_wdl_ctx(ctx) == FAILURE)
    {
        return NULL;
    }

    return ctx;
}

/* See wdl_ctx_h for documentation */
int init_wdl_ctx(wdl_ctx_t *ctx)
{
    if(ctx == NULL)
    {
        return FAILURE;
    }

    ctx->ht = NULL;
    ctx->obj = NULL;

    return SUCCESS;
}

/* See wdl_ctx_h for documentation */
int free_wdl_ctx(wdl_ctx_t *ctx)
{
    free_all_objstore(ctx->ht);

    free(ctx);

    return SUCCESS;
}
