#include "../../../include/game-state/item.h"

/* Notes

   Holding off on defining classes because to use them within the CLASS RESTRICTIONS
   attribute, we would need a set_array_attr.
   Currently just hardcoding class names within restrictions

   Not implementing both class restrictions and allowances (as initially planned)
   due to potential redundancy; those not restricted should be allowed to use the item

*/

/* CLASSES*/
typedef struct classes {
	char* type;
} classes_t;


void wand_restrictions() {
	/* WAND RESTRICTIONS*/

	item_t *wand = item_new("wand", "A stick used to conduct magic", "A stick of many possible materials – wood, metal, plastic – used by certain players to conduct magic");

	item_init(wand, "wand", "A stick used to conduct magic","A stick of many possible materials – wood, metal, plastic – used by certain players to conduct magic");

	int wand_class_restrict = set_str_attr(wand,"CLASS RESTRICTIONS", "ranger, rogue, monk");

	//Checking to see if setting worked
	printf("Wand Class Restrictions: %s \n", get_str_attr(wand, "CLASS RESTRICTIONS"));
}

void sword_restrictions() {

	/* SWORD RESTRICTIONS */
	item_t *sword = item_new("sword","A sharp metal blade","A sharp metal blade that can be used by certain players to make opponents go 'OWEE'");

	item_init(sword, "sword", "A sharp metal blade","A sharp metal blade that can be used by certain players to make opponents go 'OWEE'");

	int sword_class_restrict = set_str_attr(sword,"CLASS RESTRICTIONS", "sorcerer, druid, elementalist");

	//Checking to see if setting worked
	printf("Sword Class Restrictions: %s \n", get_str_attr(sword, "CLASS RESTRICTIONS"));

}

void bow_restrictions() {
	/* BOW RESTRICTIONS */
	item_t *bow = item_new("bow", "A bendy stick and string used in tandem with arrows", "A bendy stick and string used in tandem with arrows to make opponents and prey go 'OWEE'");

	item_init(bow, "bow", "A bendy stick and string used in tandem with arrows", "A bendy stick and string used in tandem with arrows to make opponents and prey go 'OWEE'");

	int bow_class_restrict = set_str_attr(bow,"CLASS RESTRICTIONS", "sorcerer, druid, elementalist");

	//Checking to see if setting worked
	printf("Bow Class Restrictions: %s \n", get_str_attr(bow, "CLASS RESTRICTIONS"));
}

int main() {
	wand_restrictions();
	sword_restrictions();
	bow_restrictions();
}
