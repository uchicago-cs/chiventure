#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "battle/logic.h"

/* 
 * this tests if battle_over detects if the 
 * battle is over because of the player 
 */
Test(logic, battle_over_by_player)
{
    stats_t *pstats = calloc(sizeof(stats_t));
    pstats->hp = 0;
    stats_t *estats = calloc(sizeof(stats_t));
    estats->hp = 10;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    combatant_t *e = combatant_new("Enemy", false, estats, NULL, NULL);

    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    int res = battle_over(p, e);

    cr_assert_eq(res, 2, "battle_over failed!");

    combatant_free(p);
    combatant_free(e);
}

/* 
 * this tests if battle_over detects if the 
 * battle is over because of the enemy
 */
Test(logic, battle_over_by_enemy)
{
    stats_t *pstats = calloc(sizeof(stats_t));
    pstats->hp = 10;
    stats_t *estats = calloc(sizeof(stats_t));
    estats->hp = 0;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    combatant_t *e = combatant_new("Enemy", false, estats, NULL, NULL);

    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    int res = battle_over(p, e);

    cr_assert_eq(res, 1, "battle_over failed!");

    combatant_free(p);
    combatant_free(e);
}

/* 
 * this tests if battle_over detects if the 
 * battle is not over
 */
Test(logic, battle_over_by_enemy)
{
    stats_t *pstats = calloc(sizeof(stats_t));
    pstats->hp = 10;
    stats_t *estats = calloc(sizeof(stats_t));
    estats->hp = 10;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    combatant_t *e = combatant_new("Enemy", false, estats, NULL, NULL);

    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    int res = battle_over(p, e);

    cr_assert_eq(res, 0, "battle_over failed!");

    combatant_free(p);
    combatant_free(e);
}

/* 
 * Tests goes_first to see if it detects that the enemy
 * is faster than the player 
 */
Test(logic, enemy_goes_first)
{
    stats_t *pstats = calloc(sizeof(stats_t));
    pstats->speed = 25;
    stats_t *estats = calloc(sizeof(stats_t));
    estats->speed = 50;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    combatant_t *e = combatant_new("Enemy", false, estats, NULL, NULL);

    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    int res = goes_first(p->stats->speed, e->stats->speed);

    cr_assert_eq(res, 1, "goes_first failed!");

    combatant_free(p);
    combatant_free(e);
}

/* 
 * Tests goes_first to see if it detects that the player
 * is faster than the enemy 
 */
Test(logic, player_goes_first)
{
    stats_t *pstats = calloc(sizeof(stats_t));
    pstats->speed = 50;
    stats_t *estats = calloc(sizeof(stats_t));
    estats->speed = 25;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    combatant_t *e = combatant_new("Enemy", false, estats, NULL, NULL);

    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    int res = goes_first(p->stats->speed, e->stats->speed);

    cr_assert_eq(res, 0, "goes_first failed!");

    combatant_free(p);
    combatant_free(e);
}

/* 
 * Since the player and enemy can have the same speed,
 * then the player will go first
 */
Test(logic, same_speed)
{
    stats_t *pstats = calloc(sizeof(stats_t));
    pstats->speed = 50;
    stats_t *estats = calloc(sizeof(stats_t));
    estats->speed = 50;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    combatant_t *e = combatant_new("Enemy", false, estats, NULL, NULL);

    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    int res = goes_first(p->stats->speed, e->stats->speed);

    cr_assert_eq(res, 0, "goes_first failed!");

    combatant_free(p);
    combatant_free(e);
}



