#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "player.h"


//same issue—need to figure out way to create defined structs that can be called
/*
Test(player, init) {
    player_t *playerone = malloc(sizeof(player_t));
    player_init(playerone, 100);
    cr_assert_not_null(playerone, "player_init failed");
    cr_assert_eq(playerone->health, 100, "player_init failed: health");
    cr_assert_eq(playerone->level, 1, "player_init failed: level");
    cr_assert_eq(playerone->xp, 0, "player_init failed: xp");
    cr_assert_not_null(playerone->inventory, "player_init failed: inventory");
    cr_assert_not_null(playerone->clothes, "player_init failed: clothes");
}

Test(player, health_change)
{
    player_t *playerone = malloc(sizeof(player_t));
    player_init(playerone, 100);
    health_change(plyr, -50);
    cr_assert_eq(plyr->health, 50, "health change failed");
}
*/
