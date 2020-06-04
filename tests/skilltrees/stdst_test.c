#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/stdst.h"
#include "skilltrees/inventory.h"
#include "effect_t.h"

Test(blah, a)
{
    printf("%s\n",effect_defuse_bomb("yee"));
    cr_assert_eq(0, 1, "3333");
    
}