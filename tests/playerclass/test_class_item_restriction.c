#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "game-state/item.h"
#include "playerclass/class_item_restriction.h"

/* HARDCODED ITEMS USED IN TESTS*/

item_t* create_wand() {

	item_t *wand = item_new("wand", "A stick used to conduct magic", "A stick of many possible materials  wood, metal, plastic  used by certain players to conduct magic");

	item_init(wand, "wand", "A stick used to conduct magic","A stick of many possible materials – wood, metal, plastic  used by certain players to conduct magic");

	return wand;
}

item_t* create_sword() {

	item_t *sword = item_new("sword","A sharp metal blade","A sharp metal blade that can be used by certain players to make opponents go 'OWEE'");

	item_init(sword, "sword", "A sharp metal blade","A sharp metal blade that can be used by certain players to make opponents go 'OWEE'");

	return sword;
}

item_t* create_bow() {

	item_t *bow = item_new("bow", "A bendy stick and string used in tandem with arrows", "A bendy stick and string used in tandem with arrows to make opponents and prey go 'OWEE'");

	item_init(bow, "bow", "A bendy stick and string used in tandem with arrows", "A bendy stick and string used in tandem with arrows to make opponents and prey go 'OWEE'");
}

item_t* wand = create_wand();
item_t* sword = create_sword();
item_t* bow = create_bow();

/*HARDCODED CLASSES*/

class_t* create_class(char* name) {
	class_t* class = class_new(name, " ", " ", NULL, NULL, NULL, NULL, NULL);
	class_init(class, name, " ", " ", NULL, NULL, NULL, NULL, NULL);
	return class;
}

class_t* ranger = create_class("ranger");
class_t* rogue = create_class("rogue");
class_t* monk = create_class("monk");
class_t* sorcerer = create_class("sorcerer");
class_t* druid = create_class("druid");
class_t* elementalist = create_class("elementalist");


/* TESTS */

void_check_set_restriction(class_t* class, item_t* item) {

	int SIR_check = set_item_restriction(item, class);
	char* GSA_val= get_str_attr(item, class->name);

	cr_assert_eq(SIR_check, SUCCESS, "Set_item_restriction() failed. Either class or item is null");

	cr_assert_not_null(GSA_val, "Set_item_restriction() failed. Attribute of class type not created");

	cr_assert_eq(GSA_val, "True", "Set_item_restriction() failed. Class attribute not set to true" );
}

Test(class_item_restriction, set_wand) {
	set_item_restriction(wand, ranger);
	set_item_restriction(wand, rogue);
	set_item_restriction(wand, monk);

}

Test(class_item_restriction, set_sword) {
	set_item_restriction(sword, sorcerer);
	set_item_restriction(sword, druid);
	set_item_restriction(sword, elementalist);

}

Test(class_item_restriction, set_bow) {
	set_item_restriction(bow, sorcerer);
	set_item_restriction(bow, druid);
	set_item_restriction(bow, elementalist);

}

void_check_get_restriction(class_t* class, item_t* item, int expected) {

	int GCR_check = get_class_restriction(item, class);

	cr_assert_eq(GCR_check, expected, "get_class_restriction() did not correctly return if the class is restricted from item use");
}

Test(class_item_restriction, get_bow) {
	void_check_get_restriction(ranger, wand, true);
	void_check_get_restriction(druid, sword, true);
	void_check_get_restriction(ranger, sword, false);
}



