#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "battle/battle_structs.h"
#include "battle/battle_state.h"
#include "battle/logic.h"

/* 
 * this tests if battle_over detects if the 
 * battle is over because of the player 
 */
Test(logic, battle_over_by_player)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 0;
    stat_t *estats = calloc(1, sizeof(stat_t));
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
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    stat_t *estats = calloc(1, sizeof(stat_t));
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
Test(logic, battle__not_over)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    stat_t *estats = calloc(1, sizeof(stat_t));
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
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->speed = 25;
    stat_t *estats = calloc(1, sizeof(stat_t));
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
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->speed = 50;
    stat_t *estats = calloc(1, sizeof(stat_t));
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
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->speed = 50;
    stat_t *estats = calloc(1, sizeof(stat_t));
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

Test(logic, find_item)
{
}

Test(logic, do_not_find_item)
{
}

Test(logic, award_xp)
{
    double xp_gain = 15;
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->xp = 100;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    int res = award_xp(p->stats, xp_gain);

    cr_assert_eq(res, 0, "award_xp did not return 0!");
    cr_assert_eq(p->stats->xp, 115, "award_xp did not award xp correctly!");
}
