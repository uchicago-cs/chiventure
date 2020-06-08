#include <criterion/criterion.h>
#include "wdl/wdl_ctx.h"

Test(wdl_ctx, new)
{
    wdl_ctx_t *ctx = wdl_ctx_new();

    cr_assert_not_null(ctx, "wdl_ctx_new() failed");

    cr_assert_null(ctx->ht, "wdl_ctx_new() failed to set ht");
    cr_assert_null(ctx->game, "wdl_ctx_new() failed to set game");
}

Test(wdl_ctx, init)
{
    wdl_ctx_t *ctx = malloc(sizeof(wdl_ctx_t));

    int rc = init_wdl_ctx(ctx);

    cr_assert_eq(rc, 0, "wdl_ctx_init() failed");

    cr_assert_null(ctx->ht, "wdl_ctx_init() failed to set ht");
    cr_assert_null(ctx->game, "wdl_ctx_init() failed to set game");
}

Test(wdl_ctx, free)
{
    wdl_ctx_t *ctx = wdl_ctx_new();
    
    int rc = wd_ctx_free(ctx);

    cr_assert_eq(rc, 0, "wdl_ctx_free() failed");
}
