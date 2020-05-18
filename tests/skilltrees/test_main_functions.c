#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltrees.h"

// First test for skilltrees
Test(main_functions, test1)
{
    print("Hello\n");
    cr_assert_eq(1, 1, "Failed to equalize 1 with 1");
}
