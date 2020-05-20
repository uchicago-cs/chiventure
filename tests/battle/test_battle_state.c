#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_state.h"

/* Tests combatant_new() */
Test(battle_state, combatant_new)
{
    combatant_t *c;

    c = combatant_new("combatant_new_Name", true, NULL, NULL, NULL);

    cr_assert_not_null(c, "combatant_new() failed");

    cr_assert_str_eq(c->name, "combatant_new_Name", "combatant_new() didn't set name");
    cr_assert_eq(c->is_friendly, true, "combatant_new() didn't set type");
}

/* Tests combatant_init() */
Test(battle_state, combatant_init)
{
    combatant_t c;
    int rc;

    rc = combatant_init(&c, "combatant_init_Name",true, NULL, NULL, NULL);

    cr_assert_eq(rc, SUCCESS, "combatant_unit() failed");

    cr_assert_str_eq(c.name, "combatant_init_Name", "combatant_new() didn't set name");
    cr_assert_eq(c.is_friendly, true, "combatant_new() didn't set type");
}

/* Tests combatant_free() */
Test(battle_state, combatant_free)
{
    combatant_t *c;
    int rc;

    c = combatant_new("combatant_free_Name", true, calloc(1, sizeof(stats_t)), NULL, NULL);

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

    c1 = combatant_new("combatant_free_Name2", true, calloc(1, sizeof(stats_t)), NULL, NULL);
    c2 = combatant_new("combatant_free_Name1", true, calloc(1, sizeof(stats_t)), NULL, NULL);
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
    combatant_t *p = combatant_new("battle_new_Player", true, NULL, NULL, NULL);
    combatant_t *e = combatant_new("battle_new_Enemy", true, NULL, NULL, NULL);

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
    combatant_t *p = combatant_new("battle_init_Player", true, NULL, NULL, NULL);
    combatant_t *e = combatant_new("battle_init_Enemy", true, NULL, NULL, NULL);
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
    combatant_t *p = combatant_new("battle_new_Player", true, calloc(1, sizeof(stats_t)), NULL, NULL);
    combatant_t *e = combatant_new("battle_new_Enemy", false, calloc(1, sizeof(stats_t)), NULL, NULL);

    b = battle_new(p, e, ENV_SNOW, ENEMY);

    cr_assert_not_null(b, "battle_new() failed");

    rc = battle_free(b);

    cr_assert_eq(rc, SUCCESS, "battle_free() failed");
}
