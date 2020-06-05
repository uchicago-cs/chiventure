#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_state.h"
#include "common/utlist.h"

/* Tests combatant_new() */
Test(battle_state, combatant_new)
{
    class_t* test_class = class_new("Bard", "Music boi",
				    "Charismatic, always has a joke or song ready",
				    NULL, NULL, NULL);

    combatant_t *c;

    c = combatant_new("combatant_new_Name", true, test_class, NULL, NULL, NULL, BATTLE_AI_GREEDY);

    cr_assert_not_null(c, "combatant_new() failed");

    cr_assert_str_eq(c->name, "combatant_new_Name", "combatant_new() didn't set name");
    cr_assert_eq(c->is_friendly, true, "combatant_new() didn't set type");
    cr_assert_eq(c->ai, BATTLE_AI_GREEDY, "combatant_new() didn't set AI");

    cr_assert_str_eq(c->class->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(c->class->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(c->class->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(c->class->attributes, "set_player() didn't set class attribute");
    cr_assert_null(c->class->stats, "set_player() didn't set class stats");
}

/* Tests combatant_init() */
Test(battle_state, combatant_init)
{
    combatant_t c;
    int rc;

    rc = combatant_init(&c, "combatant_init_Name",true, NULL, NULL, NULL, NULL, BATTLE_AI_RANDOM);

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

    c = combatant_new("combatant_free_Name", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NONE);

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

    c1 = combatant_new("combatant_free_Name2", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NONE);
    c2 = combatant_new("combatant_free_Name1", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NONE);
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
    combatant_t *p = combatant_new("battle_new_Player", true, NULL, NULL, NULL, NULL, NONE);
    combatant_t *e = combatant_new("battle_new_Enemy", true, NULL, NULL, NULL, NULL, NONE);

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
    combatant_t *p = combatant_new("battle_init_Player", true, NULL, NULL, NULL, NULL, NONE);
    combatant_t *e = combatant_new("battle_init_Enemy", true, NULL, NULL, NULL, NULL, NONE);
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
    combatant_t *p1 = combatant_new("battle_new_Player", true, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NONE);
    combatant_t *e1 = combatant_new("battle_new_Enemy", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NONE);
    combatant_t *e2 = combatant_new("battle_new_Enemy", false, NULL, calloc(1, sizeof(stat_t)), NULL, NULL, NONE);

    DL_APPEND(p, p1);
    combatant_t *e = NULL;
    DL_APPEND(e, e1);
    DL_APPEND(e, e2);

    b = battle_new(p, e, ENV_SNOW, ENEMY);

    cr_assert_not_null(b, "battle_new() failed");

    rc = battle_free(b);

    cr_assert_eq(rc, SUCCESS, "battle_free() failed");
}
