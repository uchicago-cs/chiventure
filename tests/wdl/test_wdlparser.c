#include <criterion/criterion.h>
#include "test_wdl.h"
#include "../../src/wdl/src/wdlparser.h"

Test(wdlparser, for_each)
{
    char *path = strdup("../../../src/wdl/examples/wdz/test_game/test_game.wdz");
    int val = parse(path);
    cr_assert_eq(val, 5, "val is %d instead of 5", val);
}