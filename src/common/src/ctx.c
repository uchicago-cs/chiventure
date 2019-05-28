#include <stdlib.h>
#include "ctx.h"

/* See ctx.h */
chiventure_ctx_t* chiventure_ctx_new()
{
    chiventure_ctx_t *ctx;
    int rc;

    ctx = malloc(sizeof(chiventure_ctx_t));

    if(ctx == NULL)
    {
        return NULL;
    }

    rc = chiventure_ctx_init(ctx);
    if(rc != SUCCESS)
    {
        return NULL;
    }

    return ctx;
}

/* See ctx.h */
int chiventure_ctx_init(chiventure_ctx_t *ctx)
{
    assert(ctx != NULL);

    /* Add calls to component-specific initialization here */

    return SUCCESS;
}

/* See ctx.h */
int chiventure_ctx_free(chiventure_ctx_t *ctx)
{
    assert(ctx != NULL);

    /* Add calls to component-specific freeing functions here */

    free(ctx);

    return SUCCESS;
}
