#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/battle/battle_test_utility.h"

/*
 * This tests to ensure that a target exists within a list of targets
 */
Test(battle_logic, target_exists)
{
    combatant_t *phead = NULL;
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL, NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;

    c1 = combatant_new("Goblin Gary", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");

    battle_t *b = battle_new(phead, ehead, ENV_NONE, PLAYER);
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
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL, NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;

    c1 = combatant_new("Goblin Gary", false, NULL, calloc(1, sizeof(stat_t)), NULL, 
                        NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, calloc(1, sizeof(stat_t)), NULL, 
                        NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");

    battle_t *b = battle_new(phead, ehead, ENV_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    combatant_t *res = check_target(b, "Goblin John");

    cr_assert_null(res, "check_target() failed!");

    battle_free(b);
}

/*
 * this tests if battle_over detects if the
 * battle is over because of the battle_player
 */
Test(battle_logic, battle_over_by_battle_player)
{
    combatant_t *phead = NULL;
    combatant_t *ehead = NULL;

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 0;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 10;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("Enemy", false, NULL, estats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    cr_assert_not_null(e, "combatant_new() failed");

    DL_APPEND(phead, p);
    DL_APPEND(ehead, e);

    battle_t *b = battle_new(phead, ehead, ENV_NONE, PLAYER);

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

    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("Enemy", false, NULL, estats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e1 = combatant_new("Enemy", false, NULL, estats1, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e2 = combatant_new("Enemy", false, NULL, estats2, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);

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

    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("Enemy", false, NULL, estats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e1 = combatant_new("Enemy", false, NULL, estats1, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e2 = combatant_new("Enemy", false, NULL, estats2, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
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
 * is faster than the battle_player
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
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;
    c1 = combatant_new("Goblin Gary", false, NULL, estats2, NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, estats, NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);

    battle_t *b = battle_new(phead, ehead, ENV_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    turn_t res = goes_first(b);

    cr_assert_eq(res, ENEMY, "goes_first() failed!");

    battle_free(b);
}

/*
 * Tests goes_first to see if it detects that the player
 * is faster than the enemy
 */
Test(battle_logic, battle_player_goes_first)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->speed = 50;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->speed = 25;
    stat_t *estats2 = calloc(1, sizeof(stat_t));
    estats2->speed = 15;

    combatant_t *phead = NULL;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, 
                                   NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;
    c1 = combatant_new("Goblin Gary", false, NULL, estats, NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, estats2, NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);

    battle_t *b = battle_new(phead, ehead, ENV_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    turn_t res = goes_first(b);

    cr_assert_eq(res, PLAYER, "goes_first() failed!");

    battle_free(b);
}

/*
 * Since the battle_player and enemy can have the same speed,
 * then the battle_player will go first
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
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");
    DL_APPEND(phead, p);

    combatant_t *ehead = NULL;
    combatant_t *c1;
    combatant_t *c2;
    c1 = combatant_new("Goblin Gary", false, NULL, estats, NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("Orc John", false, NULL, estats2, NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");
    DL_APPEND(ehead, c1);
    DL_APPEND(ehead, c2);

    battle_t *b = battle_new(phead, ehead, ENV_NONE, PLAYER);
    cr_assert_not_null(b, "battle_new() failed");

    turn_t res = goes_first(b);

    cr_assert_eq(res, PLAYER, "goes_first() failed!");

    battle_free(b);
}

/*
 * Finds a battle_item according to it's name within a list of battle_items (inventory)
 */
Test(battle_logic, find_battle_item)
{

    battle_item_t *head = NULL;
    battle_item_t *i1;
    battle_item_t *i2;

    i1 = calloc(1, sizeof(battle_item_t));
    i1->name = "item";
    i2 = calloc(1, sizeof(battle_item_t));
    i2->name = "item";
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    battle_item_t *found = find_battle_item(head, "item");
    cr_assert_eq(found->name, "item", "find_battle_item() failed!");
}

/*
 * Searches for a battle_item that does not exist in a list of battle_items (inventory)
 */
Test(battle_logic, do_not_find_item)
{
    battle_item_t *head = NULL;
    battle_item_t *i1;
    battle_item_t *i2;

    i1 = calloc(1, sizeof(battle_item_t));
    i1->name = "item";
    i2 = calloc(1, sizeof(battle_item_t));
    i2->name = "item";
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    battle_item_t *found = find_battle_item(head, "item2");
    cr_assert_null(found, "find_battle_item() failed!");
}
/* This test will need to be changed to and instead should call get_random_equip_weapon() */
/*
Test(battle_logic, use_battle_weapon)
{
    stat_t *player_stats = calloc(1, sizeof(stat_t));
    player_stats->max_hp= 1000;
    
    stat_t *enemy_stats = calloc(1, sizeof(stat_t));
    enemy_stats->max_hp= 1000;
    enemy_stats->hp = 100;
    enemy_stats->phys_atk = 90;
    enemy_stats->phys_def = 80;
    battle_item_t *weapon = get_random_default_weapon();

    combatant_t *player = combatant_new("player", true, NULL, player_stats, NULL, weapon, 
                                        NULL, NULL, NULL, BATTLE_AI_NONE);

    combatant_t *enemy = combatant_new("enemy", false, NULL, enemy_stats, NULL, NULL, 
                                        NULL, NULL, NULL, BATTLE_AI_NONE);

    battle_t *battle = calloc(1, sizeof(battle_t));
    battle->player = player;
    battle->enemy = enemy;
    
    int expected_hp = battle->enemy->stats->hp + weapon->hp;
    int expected_strength = battle->enemy->stats->phys_atk + weapon->attack;
    int expected_defense = battle->enemy->stats->phys_def + weapon->defense; 
    use_battle_item(player, battle, weapon->name);
    cr_assert_eq(battle->enemy->stats->hp, expected_hp, "consume_battle_weapon() does correctly set enemy hp after use. Actual: %d, Expected: %d", battle->enemy->stats->hp,expected_hp);
    cr_assert_eq(battle->enemy->stats->phys_atk, expected_strength, "consume_battle_weapon() does correctly set enemy physical attack after use");
    cr_assert_eq(battle->enemy->stats->phys_def, expected_defense, "consume_battle_weapon() does correctly set enemy physical defense after use");
}
*/

/*
 * this tests to see if the battle_player tries consuming a battle_item,
 * then it should do two things:
 * 1. Find the battle_item and mark it as found and used
 * 2. make changes to status as seen fit
 */
Test(battle_logic, consume_an_battle_item)
{
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    pstats->max_hp = 20;
    pstats->phys_def = 15;
    pstats->phys_atk = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");

    battle_item_t *i1 = calloc(1, sizeof(battle_item_t));
    stat_changes_t *changes = stat_changes_new();
    changes->phys_atk = 0;
    changes->phys_def = 0;
    changes->hp = 10;
    i1->attributes = changes;

    int res = consume_battle_item(p, i1);

    cr_assert_eq(res, 0, "consume_battle_item() does not return 0!");
    cr_assert_eq(p->stats->hp, 20, "consume_battle_item() failed for hp!");
    cr_assert_eq(p->stats->phys_def, 15, "consume_battle_item() failed for physical defense!");
    cr_assert_eq(p->stats->phys_atk, 15, "consume_battle_item() failed for physical attack!");

    combatant_free(p);
}

/*
 * This is simialr to the test above except there are now two battle_items in
 * the battle_player's inventory that the function has to go through
 */
Test(battle_logic, uses_battle_item_correctly)
{
    battle_item_t *head = NULL;
    battle_item_t *i1;
    battle_item_t *i2;

    i1 = calloc(1, sizeof(battle_item_t));
    stat_changes_t *changes1 = stat_changes_new();
    i1->id = 100;
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 20;
    i1->attributes = changes1;
    i1->quantity = 2;
    i1->name = "ITEM1";
    
    i2 = calloc(1, sizeof(battle_item_t));
    i2->id = 101;
    stat_changes_t *changes2 = stat_changes_new();
    changes2->phys_atk = 101;
    changes2->phys_def = 0;
    changes2->hp = 20;
    i2->attributes = changes2;
    i2->quantity = 2;
    i2->name = "ITEM2";
    
    DL_APPEND(head, i1);
    DL_APPEND(head, i2);

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 15;
    pstats->max_hp = 25;
    pstats->phys_def = 15;
    pstats->phys_atk = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL,head, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");

    battle_t *battle = calloc(1, sizeof(battle_t));
    battle->player = p;
    int res = use_battle_item(p, battle, "ITEM1");

    cr_assert_eq(res, SUCCESS, "use_battle_item() failed!");
    cr_assert_eq(p->stats->hp, 25, "use_battle_item() failed for hp!");
    cr_assert_eq(p->stats->phys_def, 15, "use_battle_item() failed for physical defense!");
    cr_assert_eq(p->stats->phys_atk, 15, "use_battle_item() failed for physical attack!");
}

/*
 * Ensures that nothing is done if the player has an empty inventory
 */
Test(battle_logic, inventory_empty)
{
    combatant_t *p = combatant_new("Player", true, NULL, NULL, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    battle_t *battle = calloc(1, sizeof(battle_t));
    battle->player = p;
    int res = use_battle_item(p, battle, "item1");
    cr_assert_eq(res, FAILURE, "use_battle_item() has failed!");
}

/*
 * Attempts to use a battle_item but there is no more of that said battle_item
 */
Test(battle_logic, no_more_battle_items)
{
    battle_item_t *head = NULL;
    battle_item_t *i1;
    battle_item_t *i2;

    i1 = calloc(1, sizeof(battle_item_t));
    stat_changes_t *changes1 = stat_changes_new();
    i1->id = 100;
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 10;
    i1->attributes = changes1;
    i1->quantity = 0;
    i1->name = "ITEM1";
    
    i2 = calloc(1, sizeof(battle_item_t));
    i2->id = 101;
    stat_changes_t *changes2 = stat_changes_new();
    changes2->phys_atk = 101;
    changes2->phys_def = 0;
    changes2->hp = 20;
    i2->attributes = changes2;
    i2->quantity = 2;
    i2->name = "ITEM2";

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 15;
    pstats->max_hp = 25;
    pstats->phys_def = 15;
    pstats->phys_atk = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, head, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    battle_t *battle = calloc(1, sizeof(battle_t));
    battle->player = p;
    cr_assert_not_null(p, "combatant_new() failed");

    int res = use_battle_item(p, battle, "item1");

    cr_assert_eq(res, FAILURE, "use_battle_item() has failed!");
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
    combatant_t *p = combatant_new("Player", true, test_class, pstats, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    int res = award_xp(p->stats, xp_gain);

    cr_assert_eq(res, 0, "award_xp() did not return 0!");
    cr_assert_eq(p->stats->xp, 115, "award_xp() did not award xp correctly!");

    cr_assert_str_eq(p->class_type->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(p->class_type->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(p->class_type->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(p->class_type->attributes, "set_player() didn't set class attribute");
    cr_assert_null(p->class_type->base_stats, "set_player() didn't set class stats");
}

/*
 * Tests stat_changes_add_item_node to make sure that it correctly adds a used item's
 * stats to its struct
 */
Test(stat_changes, add_item_node)
{
    battle_item_t *i1 = calloc(1, sizeof(battle_item_t));
    stat_changes_t *changes1 = stat_changes_new();
    i1->id = 100;
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 10;
    i1->attributes = changes1;

    stat_changes_t *sc;
    int rc;

    sc = stat_changes_new();

    rc = stat_changes_add_item_node(sc, i1);

    cr_assert_eq(rc, SUCCESS, "stat_changes_add_item_node failed");
    cr_assert_not_null(sc->next, "stat_changes_add_item_node() failed to add a new node");
    cr_assert_eq(sc->next->phys_def, 0, "stat_changes_add_item_node() failed for physical defense!");
    cr_assert_eq(sc->next->phys_atk, 0, "stat_changes_add_item_node() failed for physical attack!");
    cr_assert_eq(sc->next->hp, 10, "stat_changes_add_item_node() failed for hp!");

    stat_changes_free_all(sc);
}

Test(battle_logic, remove_single_item)
{
    battle_item_t *i1 = calloc(1, sizeof(battle_item_t));
    char *name = calloc(5, sizeof(char));
    char *d = calloc(15, sizeof(char));
    strcpy(name, "item");
    strcpy(d, "description");
    i1 = calloc(1, sizeof(battle_item_t));
    stat_changes_t *changes1 = stat_changes_new();
    i1->id = 100;
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 10;
    i1->attributes = changes1;
    i1->quantity = 1;
    i1->name = name;
    i1->description = d;

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    pstats->max_hp = 20;
    pstats->phys_atk = 15;
    pstats->phys_def = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, i1, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");

    battle_t *battle = calloc(1, sizeof(battle_t));
    battle->player = p;

    int res = use_battle_item(p, battle, "item");

    cr_assert_eq(res, SUCCESS, "use_battle_item() failed!");
    cr_assert_null(p->items, "remove_battle_item() failed");

    combatant_free(p);
}

Test(battle_logic, remove_item_of_multiple)
{
    
    battle_item_t *i1 = calloc(1, sizeof(battle_item_t));
    stat_changes_t *changes1 = stat_changes_new();
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 10;
    i1->attributes = changes1;
    i1->quantity = 1;
    i1->id = 100;
    i1->name = calloc(6, sizeof(char));
    strcpy(i1->name, "item1");
    i1->description = calloc(15, sizeof(char));
    strcpy(i1->description, "description");

    battle_item_t *i2 = calloc(1, sizeof(battle_item_t));
    i2->id = 101;
    stat_changes_t *changes2 = stat_changes_new();
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 15;
    i2->attributes = changes2;
    i2->quantity = 1;
    i2->name = calloc(6, sizeof(char));
    strcpy(i2->name, "item2");
    i2->description = calloc(15, sizeof(char));
    strcpy(i2->description, "description");

    i1->next = i2;
    i1->prev = NULL;
    i2->prev = i1;
    i2->next = NULL;

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    pstats->max_hp = 20;
    pstats->phys_def = 15;
    pstats->phys_atk = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, i1, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");

    battle_t *battle = calloc(1, sizeof(battle_t));
    battle->player = p;

    int res1 = use_battle_item(p, battle, "item1");
    cr_assert_eq(res1, SUCCESS, "use_battle_item() failed!");
    cr_assert_eq(p->items, i2, "remove_battle_item() failed");
    cr_assert_null(p->items->next, "remove_battle_item() failed");

    int res2 = use_battle_item(p, battle, "item2");
    cr_assert_eq(res2, SUCCESS, "use_battle_item() failed!");
    cr_assert_null(p->items, "remove_battle_item() failed");

    combatant_free(p);
}

Test(battle_logic, remove_last_item_of_multiple)
{
    battle_item_t *i1 = calloc(1, sizeof(battle_item_t));
    stat_changes_t *changes1 = stat_changes_new();
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 10;
    i1->attributes = changes1;
    i1->quantity = 1;
    i1->id = 100;
    i1->name = calloc(6, sizeof(char));
    strcpy(i1->name, "item1");
    i1->description = calloc(15, sizeof(char));
    strcpy(i1->description, "description");

    battle_item_t *i2 = calloc(1, sizeof(battle_item_t));
    i2->id = 101;
    stat_changes_t *changes2 = stat_changes_new();
    changes1->phys_atk = 0;
    changes1->phys_def = 0;
    changes1->hp = 15;
    i2->attributes = changes2;
    i2->quantity = 1;
    i2->name = calloc(6, sizeof(char));
    strcpy(i2->name, "item2");
    i2->description = calloc(15, sizeof(char));
    strcpy(i2->description, "description");  

    i1->next = i2;
    i2->prev = i1;

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 10;
    pstats->max_hp = 20;
    pstats->phys_def = 15;
    pstats->phys_atk = 15;
    combatant_t *p = combatant_new("Player", true, NULL, pstats, NULL, i1, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    cr_assert_not_null(p, "combatant_new() failed");

    battle_t *battle = calloc(1, sizeof(battle_t));
    battle->player = p;

    int res2 = use_battle_item(p, battle, "item2");
    cr_assert_eq(res2, SUCCESS, "use_battle_item() failed!");
    cr_assert_eq(p->items, i1, "remove_battle_item() failed");
    cr_assert_null(p->items->next, "remove_battle_item() failed");

    int res1 = use_battle_item(p, battle, "item1");
    cr_assert_eq(res1, SUCCESS, "use_battle_item() failed!");
    cr_assert_null(p->items, "remove_battle_item() failed");

    combatant_free(p);
}
