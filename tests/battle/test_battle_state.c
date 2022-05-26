#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/battle/battle_test_utility.h"

/* Tests combatant_new() */
Test(battle_state, combatant_new)
{
    class_t* test_class = class_new("Bard", "Music boi",
				    "Charismatic, always has a joke or song ready",
				    NULL, NULL, NULL);

    combatant_t *c;

    c = combatant_new("combatant_new_Name", true, test_class, NULL, NULL, NULL, 
                    NULL, NULL, NULL, BATTLE_AI_GREEDY);

    cr_assert_not_null(c, "combatant_new() failed");

    cr_assert_str_eq(c->name, "combatant_new_Name", "combatant_new() didn't set name");
    cr_assert_eq(c->is_friendly, true, "combatant_new() didn't set type");
    cr_assert_eq(c->ai, BATTLE_AI_GREEDY, "combatant_new() didn't set AI");

    cr_assert_str_eq(c->class_type->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(c->class_type->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(c->class_type->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(c->class_type->attributes, "set_player() didn't set class attribute");
    cr_assert_null(c->class_type->base_stats, "set_player() didn't set class stats");
}

/* Tests combatant_init() */
Test(battle_state, combatant_init)
{
    combatant_t c;
    int rc;

    rc = combatant_init(&c, "combatant_init_Name",true, NULL, NULL, NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_RANDOM);

    cr_assert_eq(rc, SUCCESS, "combatant_unit() failed");

    cr_assert_str_eq(c.name, "combatant_init_Name", "combatant_new() didn't set name");
    cr_assert_eq(c.is_friendly, true, "combatant_new() didn't set type");
    cr_assert_eq(c.ai, BATTLE_AI_RANDOM, "combatant_new() didn't set AI");
}

/* Tests combatant_free() */
Test(battle_state, combatant_free)
{
    combatant_t *c;
    int rc;

    c = combatant_new("combatant_free_Name", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                    NULL, NULL, NULL, BATTLE_AI_NONE);

    cr_assert_not_null(c, "combatant_new() failed");

    rc = combatant_free(c);

    cr_assert_eq(rc, SUCCESS, "combatant_free() failed");
}

/* Tests combatant_free_all() */
Test(battle_state, combatant_free_all)
{
    combatant_t *head = NULL;
    combatant_t *c1;
    combatant_t *c2;
    int rc;

    c1 = combatant_new("combatant_free_Name2", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    c2 = combatant_new("combatant_free_Name1", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    DL_APPEND(head, c1);
    DL_APPEND(head, c2);

    cr_assert_not_null(c1, "combatant_new() failed");
    cr_assert_not_null(c2, "combatant_new() failed");
    rc = combatant_free_all(head);

    cr_assert_eq(rc, SUCCESS, "combatant_free_all() failed");
}

/* Tests battle_new() */
Test(battle_state, battle_new)
{
    battle_t *b;
    combatant_t *p = combatant_new("battle_new_Player", true, NULL, NULL, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("battle_new_Enemy", true, NULL, NULL, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);

    b = battle_new(p, e, ENV_SNOW, ENEMY);

    cr_assert_not_null(b, "battle_new() failed");

    cr_assert_not_null(b->player, "battle_new() didn't set player");
    cr_assert_not_null(b->enemy, "battle_new() didn't set enemy");
    cr_assert_eq(b->environment, ENV_SNOW, "battle_new() didn't set environment");
    cr_assert_eq(b->turn, ENEMY, "battle_new() didn't set turn");
}

/* Tests battle_init() */
Test(battle_state, battle_init)
{
    battle_t b;
    combatant_t *p = combatant_new("battle_init_Player", true, NULL, NULL, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e = combatant_new("battle_init_Enemy", true, NULL, NULL, NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    int rc;

    rc = battle_init(&b, p, e, ENV_SNOW, ENEMY);

    cr_assert_eq(rc, SUCCESS, "combatant_init() failed");

    cr_assert_not_null(b.player, "battle_init() didn't set player");
    cr_assert_not_null(b.enemy, "battle_init() didn't set enemy");
    cr_assert_eq(b.environment, ENV_SNOW, "battle_init() didn't set environment");
    cr_assert_eq(b.turn, ENEMY, "battle_init() didn't set turn");
}

/* Tests battle_free */
Test(battle_state, battle_free)
{
    battle_t *b;
    int rc;
    combatant_t *p = NULL;
    combatant_t *p1 = combatant_new("battle_new_Player", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e1 = combatant_new("battle_new_Enemy", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);
    combatant_t *e2 = combatant_new("battle_new_Enemy", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                                    NULL, NULL, NULL, BATTLE_AI_NONE);

    DL_APPEND(p, p1);
    combatant_t *e = NULL;
    DL_APPEND(e, e1);
    DL_APPEND(e, e2);

    b = battle_new(p, e, ENV_SNOW, ENEMY);

    cr_assert_not_null(b, "battle_new() failed");

    rc = battle_free(b);

    cr_assert_eq(rc, SUCCESS, "battle_free() failed");
}

/* Tests stat_changes_new() */
Test(stat_changes, stat_changes_new)
{
    stat_changes_t *sc;

    sc = stat_changes_new();

    cr_assert_not_null(sc, "stat_changes_new() failed");

    cr_assert_eq(sc->speed, 0, "stat_changes_new() didn't set speed correctly");
    cr_assert_eq(sc->phys_def, 0, "stat_changes_new() didn't set phys_def correctly");
    cr_assert_eq(sc->phys_atk, 0, "stat_changes_new() didn't set phys_atk correctly");
    cr_assert_eq(sc->mag_def, 0, "stat_changes_new() didn't set mag_def correctly");
    cr_assert_eq(sc->mag_atk, 0, "stat_changes_new() didn't set mag_atk correctly");
    cr_assert_eq(sc->crit, 0, "stat_changes_new() didn't set critical correctly");
    cr_assert_eq(sc->accuracy, 0, "stat_changes_new() didn't set accuracy correctly");
    cr_assert_eq(sc->max_sp, 0, "stat_changes_new() didn't set max_sp correctly");
    cr_assert_eq(sc->sp, 0, "stat_changes_new() didn't set sp correctly");
    cr_assert_eq(sc->hp, 0, "stat_changes_new() didn't set hp correctly");
    cr_assert_eq(sc->max_hp, 0, "stat_changes_new() didn't max_hp speed correctly");
    cr_assert_eq(sc->turns_left, -1, "stat_changes_new() didn't set turns_left correctly");
    cr_assert_null(sc->next, "stat_changes_new() didn't set next correctly");
    cr_assert_null(sc->prev, "stat_changes_new() didn't set prev correctly");

    stat_changes_free_node(sc);
}

/* Tests stat_changes_init() */
Test(stat_changes, stat_changes_init)
{
    stat_changes_t *sc;
    int rc;

    sc = calloc(1, sizeof(stat_changes_t));

    rc = stat_changes_init(sc);

    cr_assert_eq(rc, SUCCESS, "stat_changes_init() failed");

    cr_assert_eq(sc->speed, 0, "stat_changes_init() didn't set speed correctly");
    cr_assert_eq(sc->phys_def, 0, "stat_changes_init() didn't set phys_def correctly");
    cr_assert_eq(sc->phys_atk, 0, "stat_changes_init() didn't set phys_atk correctly");
    cr_assert_eq(sc->mag_def, 0, "stat_changes_init() didn't set mag_def correctly");
    cr_assert_eq(sc->mag_atk, 0, "stat_changes_init() didn't set mag_atk correctly");
    cr_assert_eq(sc->crit, 0, "stat_changes_init() didn't set critical correctly");
    cr_assert_eq(sc->accuracy, 0, "stat_changes_init() didn't set accuracy correctly");
    cr_assert_eq(sc->max_sp, 0, "stat_changes_init() didn't set max_sp correctly");
    cr_assert_eq(sc->sp, 0, "stat_changes_init() didn't set sp correctly");
    cr_assert_eq(sc->hp, 0, "stat_changes_init() didn't set hp correctly");
    cr_assert_eq(sc->max_hp, 0, "stat_changes_init() didn't max_hp speed correctly");
    cr_assert_eq(sc->turns_left, -1, "stat_changes_init() didn't set turns_left correctly");
    cr_assert_null(sc->next, "stat_changes_init() didn't set next correctly");
    cr_assert_null(sc->prev, "stat_changes_init() didn't set prev correctly");

    stat_changes_free_node(sc);
}

/* Tests stat_changes_free_node() */
Test(stat_changes, stat_changes_free_node)
{
    stat_changes_t *sc;
    int rc;

    sc = stat_changes_new();

    cr_assert_not_null(sc, "stat_changes_new() failed");

    rc = stat_changes_free_node(sc);

    cr_assert_eq(rc, SUCCESS, "stat_changes_free() failed");
}

/* Tests stat_changes_free_all() */
Test(stat_changes, stat_changes_free_all)
{
    stat_changes_t *head = NULL;
    stat_changes_t *sc1;
    stat_changes_t *sc2;
    int rc;

    head = stat_changes_new();
    sc1 = stat_changes_new();
    sc2 = stat_changes_new();
    stat_changes_append_node(head, sc1);
    stat_changes_append_node(head, sc2);

    cr_assert_not_null(sc1, "stat_changes_new() failed");
    cr_assert_not_null(sc2, "stat_changes_new() failed");
    rc = stat_changes_free_all(head);

    cr_assert_eq(rc, SUCCESS, "stat_changes_free_all() failed");
}

/* Tests stat_changes_append_node() */
Test(stat_changes, stat_changes_append_node)
{
    stat_changes_t *head;
    stat_changes_t *sc;
    int rc;

    head = stat_changes_new();
    sc = stat_changes_new();

    cr_assert_not_null(head, "stat_changes_new() failed");
    cr_assert_not_null(sc, "stat_changes_new() failed");
    rc = stat_changes_append_node(head, sc);

    cr_assert_eq(rc, SUCCESS, "stat_changes_append_node() failed");
    cr_assert_eq(head->next, sc, "head->next is not sc");
    cr_assert_eq(sc->prev, head, "sc->prev is not head");

    stat_changes_free_all(head);
}

/* Tests stat_changes_add_node */
Test(stat_changes, stat_changes_add_node)
{
    stat_changes_t *sc;
    int rc;

    sc = stat_changes_new();

    rc = stat_changes_add_node(sc);

    cr_assert_eq(rc, SUCCESS, "stat_changes_add_node() failed");
    cr_assert_not_null(sc->next, "stat_changes_append_node() failed");

    stat_changes_free_node(sc);
}

/* Tests stat_changes_remove_node() */
Test(stat_changes, stat_changes_remove_node)
{
    stat_changes_t *head = NULL;
    stat_changes_t *sc1;
    stat_changes_t *sc2;
    int rc;

    head = stat_changes_new();
    sc1 = stat_changes_new();
    sc2 = stat_changes_new();
    stat_changes_append_node(head, sc1);
    stat_changes_append_node(head, sc2);

    cr_assert_eq(head->next, sc1, "stat_changes_new() failed adding node 1");
    cr_assert_eq(sc1->next, sc2, "stat_changes_new() failed adding node 2");
    rc = stat_changes_remove_node(sc1);

    cr_assert_eq(rc, SUCCESS, "stat_changes_remove_node() failed");
    cr_assert_eq(head->next, sc2, "header node's next is not sc2");

    stat_changes_free_all(head);
}

/* Tests if stat_changes_turn_increment() decrements turns correctly */
Test(stat_changes, stat_changes_turn_increment_simple_decrement)
{
    stat_changes_t *sc;
    stat_changes_t *head;
    combatant_t *c;
    int rc;

    c = combatant_new("combatant_free_Name", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    head = stat_changes_new();
    sc = stat_changes_new();
    sc->turns_left = 2;

    stat_changes_append_node(head, sc);
    rc = stat_changes_turn_increment(head, c);

    cr_assert_eq(rc, SUCCESS, "stat_changes_turn_increment() failed");
    cr_assert_eq(sc->turns_left, 1, "stat_changes_turn_increment() turns left was not 1");

    stat_changes_free_node(sc);
}

/* Tests if stat_changes_turn_increment() removes stat changes correctly */
Test(stat_changes, stat_changes_turn_increment_complex_decrement)
{
    stat_changes_t *head;
    stat_changes_t *sc;
    combatant_t *c;
    int rc;

    c = combatant_new("combatant_free_Name", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    sc = stat_changes_new();
    head = stat_changes_new();

    c->stats->speed = 1;
    c->stats->phys_def = 1;
    c->stats->phys_atk = 1;
    c->stats->hp = 1;
    c->stats->max_hp = 1;
    c->stats->xp = 1;
    c->stats->level = 1;

    sc->speed = 1;

    stat_changes_append_node(head, sc);
    sc->turns_left = 1;

    rc = stat_changes_turn_increment(head, c);

    cr_assert_eq(rc, SUCCESS, "stat_changes_turn_increment() failed");
    cr_assert_null(head->next, "stat_changes_turn_increment() failed node removal");
    cr_assert_eq(c->stats->speed, 0, "stat_changes_turn_increment() stat undo failed");

    stat_changes_free_all(head);
}

/* Tests if stat_changes_undo() removes stat changes correctly */
Test(stat_changes, stat_changes_undo)
{
    stat_changes_t *sc;
    combatant_t *c;
    int rc;

    c = combatant_new("combatant_free_Name", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, 
                        NULL, NULL, NULL, BATTLE_AI_NONE);
    sc = stat_changes_new();

    c->stats->speed = 1;
    c->stats->phys_def = 1;
    c->stats->phys_atk = 1;
    c->stats->hp = 1;
    c->stats->max_hp = 1;
    c->stats->xp = 1;
    c->stats->level = 1;

    sc->speed = 1;

    rc = stat_changes_undo(sc, c);

    cr_assert_eq(rc, SUCCESS, "stat_changes_undo() failed");
    cr_assert_eq(c->stats->speed, 0, "stat_changes_undo() failed");

    stat_changes_free_node(sc);
}
