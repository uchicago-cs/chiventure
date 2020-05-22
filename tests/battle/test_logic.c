#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "battle/battle_structs.h"
#include "battle/battle_state.h"
#include "battle/logic.h"

Test(logic, target_exists)
{
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL);
    combatant_t *head = NULL;
    combatant_t *c1;
    combatant_t *c2;

    c1 = combatant_new("Goblin Gary", true, calloc(1, sizeof(stat_t)), NULL, NULL);
    c2 = combatant_new("Orc John", true, calloc(1, sizeof(stat_t)), NULL, NULL);
    DL_APPEND(head, c1);
    DL_APPEND(head, c2);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");

    battle_t *b = battle_new(p, head, ENV_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    int res = check_target(b, "Orc John");
    cr_assert_eq(res, 0, "check_target() failed!");

    combatant_free_all(head);
    battle_free(b);
}

Test(logic, target_does_not_exist)
{
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL);
    combatant_t *head = NULL;
    combatant_t *c1;
    combatant_t *c2;

    c1 = combatant_new("Goblin Gary", true, calloc(1, sizeof(stat_t)), NULL, NULL);
    c2 = combatant_new("Orc John", true, calloc(1, sizeof(stat_t)), NULL, NULL);
    DL_APPEND(head, c1);
    DL_APPEND(head, c2);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");

    battle_t *b = battle_new(p, head, ENV_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    int res = check_target(b, "Goblin John");
    cr_assert_eq(res, 1, "check_target() failed!");

    combatant_free_all(head);
    battle_free(b);
}

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

    cr_assert_eq(res, 2, "battle_over() failed!");

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

    cr_assert_eq(res, 1, "battle_over() failed!");

    combatant_free(p);
    combatant_free(e);
}

/* 
 * this tests if battle_over detects if the 
 * battle is not over
 */
Test(logic, battle_not_over)
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

    cr_assert_eq(res, 0, "battle_over() failed!");

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

    cr_assert_eq(res, 1, "goes_first() failed!");

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

    cr_assert_eq(res, 0, "goes_first() failed!");

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

    cr_assert_eq(res, 0, "goes_first() failed!");

    combatant_free(p);
    combatant_free(e);
}

Test(logic, find_item)
{
    
    item_t *head = NULL;
    item_t *i1;
    item_t *i2;

    i1 = calloc(1, sizeof(item_t));
    i1->id = 100;
    i2 = calloc(1, sizeof(item_t));
    i2->id = 101;
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    item_t *found = find_item(head, 100);
    cr_assert_eq(found->id, 100, "find_item() failed!");
}

Test(logic, do_not_find_item)
{
    item_t *head = NULL;
    item_t *i1;
    item_t *i2;

    i1 = calloc(1, sizeof(item_t));
    i1->id = 100;
    i2 = calloc(1, sizeof(item_t));
    i2->id = 101;
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    item_t *found = find_item(head, 102);
    cr_assert_not_null(found, "find_item() failed!");
}

Test(logic, consume_an_item)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    pstats->max_hp = 20;
    pstats->defense = 15;
    pstats->strength = 15;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    cr_assert_not_null(p, "combatant_new() failed");

    item_t *i1 = calloc(1, sizeof(item_t));
    i1->id = 100;
    i1->attack = 0;
    i1->defense = 0;
    i1->hp = 10;

    int res = consume_item(p, i1);

    cr_assert_eq(res, 0, "consume_item() does not return 0!");
    cr_assert_eq(p->stats->hp, 20, "consume_item() failed for hp!");
    cr_assert_eq(p->stats->defense, 15, "consume_item() failed for defense!");
    cr_assert_eq(p->stats->strength, 15, "consume_item() failed for strength!");

    combatant_free(p);
    free(i1);
}

Test(logic, uses_item_correctly)
{
    item_t *head = NULL;
    item_t *i1;
    item_t *i2;

    item_t *i1 = calloc(1, sizeof(item_t));
    i1->id = 100;
    i1->attack = 0;
    i1->defense = 0;
    i1->hp = 10;
    i1->quantity = 1;
    item_t *i2 = calloc(1, sizeof(item_t));
    i2->id = 101;
    i1->attack = 0;
    i1->defense = 0;
    i1->hp = 20;
    i2->quantity = 2;
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 15;
    pstats->max_hp = 25;
    pstats->defense = 15;
    pstats->strength = 15;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    cr_assert_not_null(p, "combatant_new() failed");

    int res = player_use_item(p, head, 100);

    cr_assert_eq(res, 0, "player_use_item() does not return 0!");
    cr_assert_eq(p->stats->hp, 25, "player_use_item() failed for hp!");
    cr_assert_eq(p->stats->defense, 15, "player_use_item() failed for defense!");
    cr_assert_eq(p->stats->strength, 15, "player_use_item() failed for strength!");
    cr_assert_eq(i1->quantity, 0, "player_use_item() failed for item quantity!");
}

Test(logic, inventory_empty)
{
    int res = player_use_item(NULL, NULL, 100);
    cr_assert_eq(res, 1, "player_use_item() has failed!");
}

Test(logic, no_more_items)
{
    item_t *head = NULL;
    item_t *i1;
    item_t *i2;

    i1 = calloc(1, sizeof(item_t));
    i1->id = 100;
    i1->attack = 0;
    i1->defense = 0;
    i1->hp = 10;
    i1->quantity = 0;

    i2 = calloc(1, sizeof(item_t));
    i2->id = 101;
    i1->attack = 0;
    i1->defense = 0;
    i1->hp = 20;
    i2->quantity = 2;
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 15;
    pstats->max_hp = 25;
    pstats->defense = 15;
    pstats->strength = 15;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    cr_assert_not_null(p, "combatant_new() failed");

    int res = player_use_item(p, head, 100);

    cr_assert_eq(res, 2, "player_use_item() has failed!");
}

Test(logic, award_xp)
{
    double xp_gain = 15;
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->xp = 100;
    combatant_t *p = combatant_new("Player", true, pstats, NULL, NULL);
    int res = award_xp(p->stats, xp_gain);

    cr_assert_eq(res, 0, "award_xp() did not return 0!");
    cr_assert_eq(p->stats->xp, 115, "award_xp() did not award xp correctly!");
}
