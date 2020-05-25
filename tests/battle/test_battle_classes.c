#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "battle/battle_classes.h"

/* define max size of class info strings */
static const int MAX_CLASS_INFO_LEN = 100;

/* Tests new_class() */
Test(class, new)
{
    char *test_str;
    test_str = "Test description";

    class_t* class;
    class = new_class(CLASS_BARD, test_str, STAT_STRENGTH, 3.0);

    cr_assert_not_null(class, "new_class() failed");

    cr_assert_str_eq(class->info, test_str, "new_class() didn't set info");
}


/* Tests init_class() */
Test(class, init)
{
    class_t class;
    int rc;

    char *test_str;
    test_str = "Test description";

    rc = init_class(&class, CLASS_BARD, test_str, STAT_STRENGTH, 3.0);

    cr_assert_eq(rc, 0, "init_class() failed");

    cr_assert_str_eq(class.info, test_str, "init_class() didn't set info");
}

/* tests that memory allocated for class has been freed */
Test(class, free)
{
    class_t *class;
    int rc;

    char *test_str;
    test_str = "Test description";

    class = new_class(CLASS_BARD, test_str, STAT_STRENGTH, 3.0);

    cr_assert_not_null(class, "new_class() failed");

    rc = class_free(class);

    cr_assert_eq(rc, 0, "class_free() failed");
}

/* Test make_test_bard */
Test(class, bard)
{
    class_t *bard = make_test_bard();

    cr_assert_eq(bard->class_type, CLASS_BARD,
                 "make_test_bard() didn't set class type");

    cr_assert_str_eq
    (bard->info, "Charismatic, always has a joke, song, or moving speech ready",
		         "make_test_bard() didn't set class info");

    cr_assert_eq(bard->stats, STAT_CHARISMA,
                 "make_test_bard() didn't set stat bonus type");

    cr_assert_eq(bard->bonus, 2.0,
                 "make_test_bard() didn't set stat bonus value");
}


/* Test make_test_cleric */
Test(class, cleric)
{
    class_t *cleric = make_test_cleric();

    cr_assert_eq(cleric->class_type, CLASS_CLERIC,
                 "make_test_cleric() didn't set class type");

    cr_assert_str_eq(cleric->info,
                 "Fueled by divine inspiration, devout to the craft",
                 "make_test_cleric() didn't set class info");

    cr_assert_eq(cleric->stats, STAT_STRENGTH,
                 "make_test_cleric() didn't set stat bonus type");

    cr_assert_eq(cleric->bonus, 2.0,
                 "make_test_cleric() didn't set stat bonus value");
}


/* Test make_test_paladin */
Test(class, paladin)
{
    class_t *paladin = make_test_paladin();

    cr_assert_eq(paladin->class_type, CLASS_PALADIN,
                 "make_test_paladin() didn't set class type");

    cr_assert_str_eq(paladin->info,
                 "Driven and committed to justice",
                 "make_test_paladin() didn't set class info");

    cr_assert_eq(paladin->stats, STAT_DEXTERITY,
                 "make_test_paladin() didn't set stat bonus type");

    cr_assert_eq(paladin->bonus, 2.0,
                 "make_test_paladin() didn't set stat bonus value");
}


/* Test make_test_wizard */
Test(class, wizard)
{
    class_t *wizard = make_test_wizard();

    cr_assert_eq(wizard->class_type, CLASS_WIZARD,
                 "make_test_wizard() didn't set class type");

    cr_assert_str_eq(wizard->info,
                 "Draws power from nature",
                 "make_test_wizard() didn't set class info");

    cr_assert_eq(wizard->stats, STAT_SPEED,
                 "make_test_wizard() didn't set stat bonus type");

    cr_assert_eq(wizard->bonus, 2.0,
                 "make_test_wizard() didn't set stat bonus value");
}
