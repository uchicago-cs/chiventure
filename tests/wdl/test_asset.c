#include <criterion/criterion.h>
#include "test_wdl.h"
#include "wdl/object.h"

Test(asset, new_asset_type_failure)
{
    int *val = NULL;

    asset_t *asset = new_asset(val, "test");

    cr_assert_null(asset, "new_asset was not null");
}

Test(asset, new_asset_name_failure)
{
    asset_t *asset = new_asset(0, NULL);

    cr_assert_null(asset, "new_asset() was not null");
}

Test(asset, new_asset_success)
{
    asset_t *asset = new_asset(0, "test");
    cr_assert_not_null(asset, "new_asset() failed to allocate memory");
    cr_assert_eq(asset->type, 0, "new_asset() failed to set type");
    cr_assert_str_eq(asset->filename, "test", 
                     "new_asset() failed to set filename");
    cr_assert_null(asset->asset, "new_asset() failed to set asset");
}

Test(asset, init_asset)
{
    asset_t *asset = malloc(sizeof(asset_t));
    int res = init_asset(asset, 0, "test");
    cr_assert_eq(res, EXIT_SUCCESS, "init_asset() failed");
    cr_assert_not_null(asset, "init_asset() failed");
    cr_assert_eq(asset->type, 0, "init_asset() failed");
    cr_assert_str_eq(asset->filename, "test", "init_asset() failed");
    cr_assert_null(asset->asset, "init_asset() failed");
}

Test(asset, free_asset)
{
    asset_t asset = malloc(sizeof(asset_t));
    init_asset(asset, 0, "test", NULL);
    int res = free_asset(asset);
    cr_assert_eq(res, EXIT_SUCCESS, "free_asset() failed");
}
