#include <criterion/criterion.h>
#include <stdio.h>

#include "playerclass/class_prefabs.h"

Test(class_prefabs, Warrior) {
    class_t *c = class_prefab_warrior();
    cr_assert_not_null(c, "Prefab class Warrior failed to be initialized (NULL)");
    cr_assert_not_null(c->name, "Prefab class Warrior failed to have name");
    cr_assert_not_null(c->shortdesc, "Prefab class Warrior failed to have short description");
    cr_assert_not_null(c->longdesc, "Prefab class Warrior failed to have long descriptionn");
}
