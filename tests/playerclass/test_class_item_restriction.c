#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "game-state/item.h"
#include "playerclass/class_item_restriction.h"


/* TESTS */

/*Checking if set_restriction can successfully add a class as an attribute to an item*/
void check_set_restriction(item_t* item, class_t* class) {

    int SIR_check = set_item_restriction(item, class);
    bool GSA_val= get_bool_attr(item, class->name);

    cr_assert_eq(SIR_check, SUCCESS, "Set_item_restriction() failed. Either class or item is null");

    cr_assert_not_null(GSA_val, "Set_item_restriction() failed. Attribute of class type not created");

    cr_assert_eq(GSA_val, true, "Set_item_restriction() failed. Class attribute not set to true" );
}

/*Checking restrictions with a wand item*/
Test(class_item_restriction, set_wand) {
    item_t* wand = item_new("wand", " ", " ");
    item_init(wand, "wand", " ", " ");
    class_t* ranger = class_new("ranger", " ", " ", NULL, NULL, NULL);
    class_init(ranger, "ranger", " ", " ", NULL, NULL, NULL);
    class_t* rogue = class_new("rogue", " ", " ", NULL, NULL, NULL);
    class_init(rogue, "rogue", " ", " ", NULL, NULL, NULL);
    class_t* monk = class_new("monk", " ", " ", NULL, NULL, NULL);
    class_init(monk, "monk", " ", " ", NULL, NULL, NULL);
    check_set_restriction(wand, ranger);
    check_set_restriction(wand, rogue);
    check_set_restriction(wand, monk);

}

/*Checking restrictions with a sword item*/
Test(class_item_restriction, set_sword) {
    item_t* sword = item_new("sword", " ", " ");
    item_init(sword, "sword", " ", " ");
    class_t* sorcerer = class_new("sorcerer", " ", " ", NULL, NULL, NULL);
    class_init(sorcerer, "sorcerer", " ", " ", NULL, NULL, NULL);
    class_t* druid = class_new("druid", " ", " ", NULL, NULL, NULL);
    class_init(druid, "druid", " ", " ", NULL, NULL, NULL);
    class_t* elementalist = class_new("elementalist", " ", " ", NULL, NULL, NULL);
    class_init(elementalist, "elementalist", " ", " ", NULL, NULL, NULL);
    check_set_restriction(sword, sorcerer);
    check_set_restriction(sword, druid);
    check_set_restriction(sword, elementalist);

}

/*Checking restrictions with a bow item*/
Test(class_item_restriction, set_bow) {
    item_t* bow = item_new("bow", " ", " ");
    item_init(bow, "bow", " ", " ");
    class_t* sorcerer = class_new("sorcerer", " ", " ", NULL, NULL, NULL);
    class_init(sorcerer, "sorcerer", " ", " ", NULL, NULL, NULL);
    class_t* druid  = class_new("druid", " ", " ", NULL, NULL, NULL);
    class_init(druid, "druid", " ", " ", NULL, NULL, NULL);
    class_t* elementalist = class_new("elementalist", " ", " ", NULL, NULL, NULL);
    class_init(elementalist, "elementalist", " ", " ", NULL, NULL, NULL);
    check_set_restriction(bow, sorcerer);
    check_set_restriction(bow, druid);
    check_set_restriction(bow, elementalist);

}

/*Checking if get_class_restrictions successfully returns whether or not a class is restricted*/
void check_get_restriction(class_t* class, item_t* item, int expected) {

    bool GCR_check = get_class_restriction(item, class);

    cr_assert_eq(GCR_check, expected, "get_class_restriction() did not correctly return if the class is restricted from item use");
}

Test(class_item_restriction, get) {
    item_t* wand = item_new("wand", " ", " ");
    item_init(wand, "wand", " ", " ");
    item_t* sword = item_new("sword", " ", " ");
    item_init(sword, "sword", " ", " ");
    class_t* ranger = class_new("ranger", " ", " ", NULL, NULL, NULL);
    class_init(ranger, "ranger", " ", " ", NULL, NULL, NULL);
    class_t* druid  = class_new("druid", " ", " ", NULL, NULL, NULL);
    class_init(druid, "druid", " ", " ", NULL, NULL, NULL);

    set_item_restriction(wand, ranger);
    set_item_restriction(sword, druid);

    check_get_restriction(ranger, wand, true);
    check_get_restriction(druid, sword, true);
    check_get_restriction(ranger, sword, false);
}


