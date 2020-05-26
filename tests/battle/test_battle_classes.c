#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../src/battle/src/battle_classes.c"
#include "../../include/battle/battle_classes.h"


/* Tests new_class() */
Test(class, new)
{
    char *test_str;
    test_str = "Test description";

    class_t* class;
    class = new_class(CLASS_BARD, test_str, STR, 3.0);

    cr_assert_not_null(class, "new_class() failed");

    cr_assert_eq(class->class, CLASS_BARD, "new_class() didn't set class type");

    cr_assert_str_eq(class->info, test_str, "new_class() didn't set info");

    cr_assert_eq(class->stats, 1, "new_class() didn't set stat bonus type");

    cr_assert_eq(class->bonus, 3.0, "new_class() didn't set stat bonus value");
}


/* Tests init_class() */
Test(class, init)
{
    class_t class;
    int rc;

    char *test_str;
    test_str = "Test description";

    rc = init_class(&class, CLASS_BARD, test_str, STR, 3.0);

    cr_assert_eq(rc, 0, "init_class() failed");

    cr_assert_eq(class.cl, BARD, "init_class() didn't set class type");

    cr_assert_str_eq(class.info, test_str, "init_class() didn't set info");

    cr_assert_eq(class.st, 1, "init_class() didn't set stat bonus type");

    cr_assert_eq(class.bonus, 3.0, "init_class() didn't set stat bonus value");
}


/* Test make_test_bard */
Test(class, bard)
{
    class_t *bard = make_test_bard();
    
    cr_assert_eq(bard->cl, BARD, "make_test_bard() didn't set class type");

    cr_assert_str_eq(bard->info,
                 "Charismatic, always has a joke, song, or moving speech ready", 
		 "make_test_bard() didn't set class info");
   
    cr_assert_eq(bard->st, CHRSMA, "make_test_bard() didn't set stat bonus type");

    cr_assert_eq(bard->bonus, 2.0, "make_test_bard() didn't set stat bonus value");
}


/* Test make_test_cleric */
Test(class, cleric)
{
    class_t *cleric = make_test_cleric();
    
    cr_assert_eq(cleric->cl, CLERIC, "make_test_cleric() didn't set class type");

    cr_assert_str_eq(cleric->info,
                 "Fueled by divine inspiration, devout to the craft",
                 "make_test_cleric() didn't set class info");
   
    cr_assert_eq(cleric->st, STR, "make_test_cleric() didn't set stat bonus type");

    cr_assert_eq(cleric->bonus, 2.0, "make_test_cleric() didn't set stat bonus value");
}


/* Test make_test_paladin */
Test(class, paladin)
{
    class_t *paladin = make_test_paladin();
    
    cr_assert_eq(paladin->cl, PALADIN, "make_test_paladin() didn't set class type");

    cr_assert_str_eq(paladin->info,
                 "Driven and committed to justice",
                 "make_test_paladin() didn't set class info");
   
    cr_assert_eq(paladin->st, DEX, "make_test_paladin() didn't set stat bonus type");

    cr_assert_eq(paladin->bonus, 2.0, "make_test_paladin() didn't set stat bonus value");
}


/* Test make_test_wizard */
Test(class, wizard)
{
    class_t *wizard = make_test_wizard();
    
    cr_assert_eq(wizard->cl, WIZARD, "make_test_wizard() didn't set class type");

    cr_assert_str_eq(wizard->info,
                 "Draws power from nature",
                 "make_test_wizard() didn't set class info");
   
    cr_assert_eq(wizard->st, SPD, "make_test_wizard() didn't set stat bonus type");

    cr_assert_eq(wizard->bonus, 2.0, "make_test_wizard() didn't set stat bonus value");
}


