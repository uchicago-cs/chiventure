#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "room.h"

Test(player, init) {
    player_t *playerone = malloc(sizeof(player_t));
    player_init(playerone, 100);
    cr_assert_not_null(playerone, "player_init failed");
    cr_asser_eq(playerone->health, 100, "player_init health failed");
}