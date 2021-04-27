#include <criterion/criterion.h>
#include <stdio.h>

#include "playerclass/class_prefabs.h"

Test(class_prefabs, Warrior) {
    class_t *c = class_prefab_warrior();
    cr_assert_not_null(c, "Prefab class Warrior failed to initialized (NULL)");
}
