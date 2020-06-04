#include <criterion/criterion.h>
#include "test_wdl.h"
#include "../../src/wdl/src/wdlparser.h"

Test(wdlparser, for_each)
{
    char* val = parse("../../../src/wdl/examples/wdz/test_game/test_game.wdz");
    cr_assert_eq(val, "action", "val is %s instead of 'actions'", val);
}