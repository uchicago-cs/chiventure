#include <criterion/criterion.h>
#include "test_wdl.h"
#include "wdlparser.h"

Test(wdlparser, for_each)
{
    char *path = strdup("../../../src/wdl/examples/wdz/test_game.wdz");
    int val = parse_wdz(path);
    cr_assert_eq(val, 5, "val is %d instead of 5", val);
}