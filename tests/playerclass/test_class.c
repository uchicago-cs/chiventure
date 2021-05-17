#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>

#include "playerclass/class.h"

/* Creates a sample class for testing 
 * 
 * Parameters: none
 * 
 * Returns: a class
 */

class_t* generate_test_class()
{
    class_t* c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
                " relying on physical strength and years of training to "
                "deal with any obstacle. Mechanically, the warrior focuses "
                "on up-close physical damage with weapons and survives enemy "
                "attacks using heavy armor.\n";

    c = class_new(name, shortdesc, longdesc, NULL, NULL, NULL);
    class_add_skills(c, inventory_new(5, 5), inventory_new(5, 5), skill_tree_new(3000, c->name, 15));
    return c;
}

/* Tests class_new */
Test(test_class, new)
{
    class_t* c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
                " relying on physical strength and years of training to "
                "deal with any obstacle. Mechanically, the warrior focuses "
                "on up-close physical damage with weapons and survives enemy "
                "attacks using heavy armor.\n";

    c = generate_test_class();

    cr_assert_not_null(c, "class_new failed");
    cr_assert_str_eq(c->name, name, "class_new didn't set name");
    cr_assert_str_eq(c->shortdesc, shortdesc, "class_new didn't set "
                                              "short description");
    cr_assert_str_eq(c->longdesc, longdesc, "class_new didn't set long "
                                            "description");
}

/* Tests class_init */
Test(test_class, init)
{
    class_t c;
    char *name, *shortdesc, *longdesc;
    int rc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
                " relying on physical strength and years of training to "
                "deal with any obstacle. Mechanically, the warrior focuses "
                "on up-close physical damage with weapons and survives enemy "
                "attacks using heavy armor.\n";

    rc = class_init(&c, name, shortdesc, longdesc, NULL, NULL, NULL);

    cr_assert_eq(rc, EXIT_SUCCESS, "class_init failed");
    cr_assert_str_eq(c.name, name, "class_init didn't set name");
    cr_assert_str_eq(c.shortdesc, shortdesc, "class_init didn't set "
                                             "short description");
    cr_assert_str_eq(c.longdesc, longdesc, "class_init didn't set long "
                                           "description");
}

/* Tests class_skills_init */
Test(test_class, skills_init)
{
    class_t* c = generate_test_class();

    cr_assert_not_null(c->skilltree, "class_init_skills didn't set skilltree");
    cr_assert_not_null(c->combat, "class_init_skills didn't set combat");
    cr_assert_not_null(c->noncombat, "class_init_skills didn't set noncombat");
}

/* Tests class_free */
Test(test_class, free)
{
    class_t *c;
    int rc;

    c = generate_test_class();

    cr_assert_not_null(c, "class_new failed");

    rc = class_free(c);

    cr_assert_eq(rc, EXIT_SUCCESS, "game_free() failed");

}
