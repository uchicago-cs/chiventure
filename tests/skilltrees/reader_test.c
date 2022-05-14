#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "skilltrees/inventory.h"
#include "skilltrees/effect.h"
#include "test_init.h"

/* Test reader_effect_new */
Test(reader_test, reader_effect_new_test)

/* Test reader_effect_init */
Test(reader_test, reader_effect_init_test)

/* Test reader_effect_free */
Test(reader_test, reader_effect_free_test)

/* Test stat_reader_effect_new */
Test(reader_test, stat_reader_effect_new_test)

/* Test stat_reader_effect_init */
Test(reader_test, stat_reader_effect_init_test)

/* Test stat_reader_effect_free */
Test(reader_test, stat_reader_effect_free_test)

/* Test attr_reader_effect_new */
Test(reader_test, attr_reader_effect_new_test)

/* Test attr_reader_effect_init */
Test(reader_test, attr_reader_effect_init_test)

/* Test attr_reader_effect_free */
Test(reader_test, attr_reader_effect_free_test)

/* Test execute_reader_effect */
Test(reader_test, execute_reader_effect_test)

/* Test execute_attr_reader_effect */
Test(reader_test, execute_attr_reader_effect_test)

/* Test execute_stat_reader_effect */
Test(reader_test, execute_stat_reader_effect_test)
