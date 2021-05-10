#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "game-state/item.h"
#include "playerclass/class_item_restriction.h"


/* TESTS */

/* Checking if add_restriction can successfully add a class as an attribute to an item */
void check_add_restriction(item_t* item, class_t* class) {

    int SIR_check = add_item_restriction(item, class);

    double proficiency = list_get_double_attr(item->class_multipliers, strndup(class->name, 100));

    cr_assert_eq(SIR_check, SUCCESS, "add_item_restriction() failed. Either class or item is null");

    cr_assert_eq(proficiency, 0.0, "add_item_restriction() failed. Class attribute not set to true" );
}

/* Checking adding restrictions with a wand item */
Test(class_item_restriction, add_wand) {
    item_t* wand = item_new("wand", " ", " ");
    item_init(wand, "wand", " ", " ");
    class_t* ranger = class_new("ranger", " ", " ", NULL, NULL, NULL);
    class_init(ranger, "ranger", " ", " ", NULL, NULL, NULL);
    class_t* rogue = class_new("rogue", " ", " ", NULL, NULL, NULL);
    class_init(rogue, "rogue", " ", " ", NULL, NULL, NULL);
    class_t* monk = class_new("monk", " ", " ", NULL, NULL, NULL);
    class_init(monk, "monk", " ", " ", NULL, NULL, NULL);
    check_add_restriction(wand, ranger);
    check_add_restriction(wand, rogue);
    check_add_restriction(wand, monk);
    item_free(wand);

}

/* Checking adding restrictions with a sword item */
Test(class_item_restriction, add_sword){
    item_t* sword = item_new("sword", " ", " ");
    item_init(sword, "sword", " ", " ");
    class_t* sorcerer = class_new("sorcerer", " ", " ", NULL, NULL, NULL);
    class_init(sorcerer, "sorcerer", " ", " ", NULL, NULL, NULL);
    class_t* druid = class_new("druid", " ", " ", NULL, NULL, NULL);
    class_init(druid, "druid", " ", " ", NULL, NULL, NULL);
    class_t* elementalist = class_new("elementalist", " ", " ", NULL, NULL, NULL);
    class_init(elementalist, "elementalist", " ", " ", NULL, NULL, NULL);
    check_add_restriction(sword, sorcerer);
    check_add_restriction(sword, druid);
    check_add_restriction(sword, elementalist);
    item_free(sword);

}

/* Checking adding restrictions with a bow item */
Test(class_item_restriction, add_bow){
    item_t* bow = item_new("bow", " ", " ");
    item_init(bow, "bow", " ", " ");
    class_t* sorcerer = class_new("sorcerer", " ", " ", NULL, NULL, NULL);
    class_init(sorcerer, "sorcerer", " ", " ", NULL, NULL, NULL);
    class_t* druid  = class_new("druid", " ", " ", NULL, NULL, NULL);
    class_init(druid, "druid", " ", " ", NULL, NULL, NULL);
    class_t* elementalist = class_new("elementalist", " ", " ", NULL, NULL, NULL);
    class_init(elementalist, "elementalist", " ", " ", NULL, NULL, NULL);
    check_add_restriction(bow, sorcerer);
    // check_add_restriction(bow, druid);
    // check_add_restriction(bow, elementalist);
    // item_free(bow);
}

/* Checking if is_restricted successfully returns whether or not a class is restricted */
void check_is_restricted(class_t* class, item_t* item, bool expected) {

    bool GCR_check = is_restricted(item, class);

    cr_assert_eq(GCR_check, expected, "is_restricted() did not correctly return if the class is restricted from item use");
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

    add_item_restriction(wand, ranger);
    add_item_restriction(sword, druid);

    check_is_restricted(druid, wand, false);
    check_is_restricted(ranger, wand, true);
    check_is_restricted(druid, sword, true);
    check_is_restricted(ranger, sword, false);
    item_free(wand);
}

/* Checking if remove_item_restriction successfully returns whether or not a class has been removed */
void check_remove_restriction(item_t* item, class_t* class){
    int SIR_check = remove_item_restriction(item, class);

    cr_assert_eq(SIR_check, SUCCESS, "remove_item_restriction() failed. Either class or item is null or this item is not currently restricted");
    
    bool GSA_val = list_contains_attribute(item->class_multipliers, strndup(class->name, 100));

    cr_assert_eq(GSA_val, false, "remove_item_restriction() did not correctly remove the class restriction");
}

/* Checking removing restrictions with a wand item */
Test(class_item_restriction, remove_wand){
    item_t* wand = item_new("wand", " ", " ");
    item_init(wand, "wand", " ", " ");
    class_t* ranger = class_new("ranger", " ", " ", NULL, NULL, NULL);
    class_init(ranger, "ranger", " ", " ", NULL, NULL, NULL);
    class_t* rogue = class_new("rogue", " ", " ", NULL, NULL, NULL);
    class_init(rogue, "rogue", " ", " ", NULL, NULL, NULL);
    class_t* monk = class_new("monk", " ", " ", NULL, NULL, NULL);
    class_init(monk, "monk", " ", " ", NULL, NULL, NULL);

    add_item_restriction(wand, ranger);
    add_item_restriction(wand, rogue);
    add_item_restriction(wand, monk);

    check_remove_restriction(wand, monk);
    check_remove_restriction(wand, rogue);
    check_remove_restriction(wand, ranger);

    item_free(wand);
}

/* Checking removing restrictions with a bow item */
Test(class_item_restriction, remove_bow){
    item_t* bow = item_new("bow", " ", " ");
    item_init(bow, "bow", " ", " ");
    class_t* sorcerer = class_new("sorcerer", " ", " ", NULL, NULL, NULL);
    class_init(sorcerer, "sorcerer", " ", " ", NULL, NULL, NULL);
    class_t* druid  = class_new("druid", " ", " ", NULL, NULL, NULL);
    class_init(druid, "druid", " ", " ", NULL, NULL, NULL);
    class_t* elementalist = class_new("elementalist", " ", " ", NULL, NULL, NULL);
    class_init(elementalist, "elementalist", " ", " ", NULL, NULL, NULL);

    add_item_restriction(bow, sorcerer);
    add_item_restriction(bow, druid);
    add_item_restriction(bow, elementalist);

    check_add_restriction(bow, sorcerer);
    check_add_restriction(bow, druid);
    check_add_restriction(bow, elementalist);

    item_free(bow);
}