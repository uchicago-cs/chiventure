#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_logic.h"
#include "battle/battle_state.h"
#include "battle/battle_structs.h"

/*
 * This tests to ensure that a target exists within a list of targets
 */
Test(battle_logic, target_exists)
{
    combatant_t *phead = NULL;
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;

    c1 = combatant_new("Goblin Gary", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");

    battle_t *b = battle_new(phead, ehead, ENV_BATTLE_AI_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    combatant_t *res = check_target(b, "Orc John");

    cr_assert_not_null(res, "check_target() failed!");

    battle_free(b);
}

/*
 * This tests to ensure that a target is not found when it does not exist
 * within a list of targets
 */
Test(battle_logic, target_does_not_exist)
{
    combatant_t* phead = NULL;
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;

    c1 = combatant_new("Goblin Gary", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");

    battle_t *b = battle_new(phead, ehead, ENV_BATTLE_AI_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    combatant_t *res = check_target(b, "Goblin John");

    cr_assert_null(res, "check_target() failed!");

    battle_free(b);
}

/*
 * this tests if battle_over detects if the
 * battle is over because of the player
 */
Test(battle_logic, battle_over_by_player)
{
    combatant_t *phead = NULL;
    combatant_t *ehead = NULL;

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 0;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 10;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("Enemy", false, NULL, estats, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    DL_APPEND(phead, p);
    DL_APPEND(ehead, e);

    battle_t *b = battle_new(phead, ehead, ENV_BATTLE_AI_NONE, PLAYER);

    battle_status_t res = battle_over(b);

    cr_assert_eq(res, BATTLE_VICTOR_ENEMY, "battle_over() failed!");

    battle_free(b);
}

/*
 * this tests if battle_over detects if the
 * battle is over because of the enemy at 0 hp
 */
Test(battle_logic, battle_over_by_enemy)
{
    combatant_t *phead = NULL;
    combatant_t *ehead = NULL;

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 0;
    stat_t *estats1 = calloc(1, sizeof(stat_t));
    estats1->hp = 0;
    stat_t *estats2 = calloc(1, sizeof(stat_t));
    estats2->hp = 0;

    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("Enemy", false, NULL, estats, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e1 = combatant_new("Enemy", false, NULL, estats1, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e2 = combatant_new("Enemy", false, NULL, estats2, NULL, NULL, BATTLE_AI_NONE);

    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");
    cr_assert_not_null(e1, "combatant_new() failed");
    cr_assert_not_null(e2, "combatant_new() failed");

    DL_APPEND(phead, p);
    DL_APPEND(ehead, e);
    DL_APPEND(ehead, e1);
    DL_APPEND(ehead, e2);

    battle_t *b = battle_new(phead, ehead, ENV_WATER, PLAYER);

    battle_status_t res = battle_over(b);

    cr_assert_eq(res, BATTLE_VICTOR_PLAYER, "battle_over() failed!");

    battle_free(b);
}

/*
 * this tests if battle_over detects if the
 * battle is not over
 */
Test(battle_logic, battle_not_over)
{
    combatant_t *phead = NULL;
    combatant_t *ehead = NULL;

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 15;
    stat_t *estats1 = calloc(1, sizeof(stat_t));
    estats1->hp = 12;
    stat_t *estats2 = calloc(1, sizeof(stat_t));
    estats2->hp = 13;

    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("Enemy", false, NULL, estats, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e1 = combatant_new("Enemy", false, NULL, estats1, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e2 = combatant_new("Enemy", false, NULL, estats2, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");
    cr_assert_not_null(e1, "combatant_new() failed");
    cr_assert_not_null(e2, "combatant_new() failed");

    DL_APPEND(phead, p);
    DL_APPEND(ehead, e);
    DL_APPEND(ehead, e1);
    DL_APPEND(ehead, e2);

    battle_t *b = battle_new(phead, ehead, ENV_WATER, PLAYER);

    battle_status_t res = battle_over(b);

    cr_assert_eq(res, BATTLE_IN_PROGRESS, "battle_over() failed!");

    battle_free(b);
}

/*
 * Tests goes_first to see if it detects that the enemy
 * is faster than the player
 */
Test(battle_logic, enemy_goes_first)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->speed = 25;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->speed = 50;
    stat_t *estats2 = calloc(1, sizeof(stat_t));
    estats2->speed = 15;

    combatant_t *phead = NULL;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;
    c1 = combatant_new("Goblin Gary", false, NULL, estats2, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, estats, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);

    battle_t *b = battle_new(phead, ehead, ENV_BATTLE_AI_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    turn_t res = goes_first(b);

    cr_assert_eq(res, ENEMY, "goes_first() failed!");

    battle_free(b);
}

/*
 * Tests goes_first to see if it detects that the player
 * is faster than the enemy
 */
Test(battle_logic, player_goes_first)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->speed = 50;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->speed = 25;
    stat_t *estats2 = calloc(1, sizeof(stat_t));
    estats2->speed = 15;

    combatant_t *phead = NULL;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;
    c1 = combatant_new("Goblin Gary", false, NULL, estats, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, estats2, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);

    battle_t *b = battle_new(phead, ehead, ENV_BATTLE_AI_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    turn_t res = goes_first(b);

    cr_assert_eq(res, PLAYER, "goes_first() failed!");

    battle_free(b);
}

/*
 * Since the player and enemy can have the same speed,
 * then the player will go first
 */
Test(battle_logic, same_speed)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->speed = 50;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->speed = 50;
    stat_t *estats2 = calloc(1, sizeof(stat_t));
    estats2->speed = 45;

    combatant_t *phead = NULL;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;
    c1 = combatant_new("Goblin Gary", false, NULL, estats, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, estats2, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);

    battle_t *b = battle_new(phead, ehead, ENV_BATTLE_AI_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    turn_t res = goes_first(b);

    cr_assert_eq(res, PLAYER, "goes_first() failed!");

    battle_free(b);
}

/*
 * Finds an item according to it's id number within a list of items (inventory)
 */
Test(battle_logic, find_item)
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

/*
 * Searches for an item that does not exist in a list of items (inventory)
 */
Test(battle_logic, do_not_find_item)
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
    cr_assert_null(found, "find_item() failed!");
}

/*
 * this tests to see if the player tries consuming an item,
 * then it should do two things:
 * 1. Find the item and mark it as found and used
 * 2. make changes to status as seen fit
 */
Test(battle_logic, consume_an_item)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    pstats->max_hp = 20;
    pstats->defense = 15;
    pstats->strength = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, BATTLE_AI_NONE);
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

/*
 * This is simialr to the test above except there are now two items in
 * the player's inventory that the function has to go through
 */
Test(battle_logic, uses_item_correctly)
{
    item_t *head = NULL;
    item_t *i1;
    item_t *i2;

    i1 = calloc(1, sizeof(item_t));
    i1->id = 100;
    i1->attack = 0;
    i1->defense = 0;
    i1->hp = 10;
    i1->quantity = 1;

    i2 = calloc(1, sizeof(item_t));
    i2->id = 101;
    i2->attack = 0;
    i2->defense = 0;
    i2->hp = 20;
    i2->quantity = 2;
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 15;
    pstats->max_hp = 25;
    pstats->defense = 15;
    pstats->strength = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, head, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");

    int res = use_item(p, 100);

    cr_assert_eq(res, SUCCESS, "use_item() failed!");
    cr_assert_eq(p->stats->hp, 25, "use_item() failed for hp!");
    cr_assert_eq(p->stats->defense, 15, "use_item() failed for defense!");
    cr_assert_eq(p->stats->strength, 15, "use_item() failed for strength!");
    cr_assert_eq(i1->quantity, 0, "use_item() failed for item quantity!");
}

/*
 * Ensures that nothing is done if the player has an empty inventory
 */
Test(battle_logic, inventory_empty)
{
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    int res = use_item(p, 100);
    cr_assert_eq(res, FAILURE, "use_item() has failed!");
}

/*
 * Attempts to use an item but there is no more of that said item
 */
Test(battle_logic, no_more_items)
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
    i2->attack = 0;
    i2->defense = 0;
    i2->hp = 20;
    i2->quantity = 2;
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 15;
    pstats->max_hp = 25;
    pstats->defense = 15;
    pstats->strength = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, head, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");

    int res = use_item(p, 100);

    cr_assert_eq(res, FAILURE, "use_item() has failed!");
}

/*
 * This check to see if xp is awarded correctly at the end of a battle
 */
Test(battle_logic, award_xp)
{
    class_t* test_class = class_new("Bard", "Music boi",
				    "Charismatic, always has a joke or song ready",
				    NULL, NULL, NULL);

    double xp_gain = 15;
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->xp = 100;
    combatant_t *p = combatant_new("Player", true, test_class, pstats, NULL, NULL, BATTLE_AI_NONE);
    int res = award_xp(p->stats, xp_gain);

    cr_assert_eq(res, 0, "award_xp() did not return 0!");
    cr_assert_eq(p->stats->xp, 115, "award_xp() did not award xp correctly!");

    cr_assert_str_eq(p->class->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(p->class->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(p->class->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(p->class->attributes, "set_player() didn't set class attribute");
    cr_assert_null(p->class->stats, "set_player() didn't set class stats");
}
