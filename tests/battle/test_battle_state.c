#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_state.h"

/* Tests character_new() */
Test(battle_state, character_new)
{
    character_t *c;

    c = character_new("character_new_Name",PLAYER, NULL, NULL, NULL, NULL);

    cr_assert_not_null(c, "character_new() failed");

    cr_assert_str_eq(c->name, "character_new_Name", "character_new() didn't set name");
    cr_assert_eq(c->type, PLAYER, "character_new() didn't set type");
}

/* Tests character_init() */
Test(battle_state, character_init)
{
    character_t c;
    int rc;

    rc = character_init(&c, "character_init_Name",PLAYER, NULL, NULL, NULL, NULL);

    cr_assert_eq(rc, SUCCESS, "character_unit() failed");

    cr_assert_str_eq(c.name, "character_init_Name", "character_new() didn't set name");
    cr_assert_eq(c.type, PLAYER, "character_new() didn't set type");
}

/* Tests free_character() */
Test(battle_state, free_character)
{
    character_t *c;
    int rc;

    c = character_new("free_character_Name",PLAYER, NULL, NULL, NULL, NULL);

    cr_assert_not_null(c, "character_new() failed");

    rc = free_character(c);

    cr_assert_eq(rc, SUCCESS, "character_free() failed");
}

/* Tests free_characters() */
Test(battle_state, free_characters)
{
    character_t *c1;
	character_t *c2;
    int rc;

    c2 = character_new("free_characters_Name2",PLAYER, NULL, NULL, NULL, NULL);
    c1 = character_new("free_characters_Name1",PLAYER, NULL, NULL, NULL, c2);

    cr_assert_not_null(c1, "character_new() failed");

    rc = free_characters(c1);

    cr_assert_eq(rc, SUCCESS, "characters_free() failed");
}

/* Tests battle_new() */
Test(battle_state, battle_new)
{
    battle_t *b;
    character_t *p = character_new("battle_new_Player",PLAYER, NULL, NULL, NULL, NULL);
    character_t *e = character_new("battle_new_Enemy",ENEMY, NULL, NULL, NULL, NULL);

    b = battle_new(p, e, ENV_SNOW, ENEMY);

    cr_assert_not_null(b, "battle_new() failed");

    cr_assert_not_null(b->player, "battle_new() didn't set player");
    cr_assert_not_null(b->enemy, "battle_new() didn't set enemy");
    cr_assert_eq(b->environment, ENV_SNOW, "character_new() didn't set environment");
    cr_assert_eq(b->turn, ENEMY, "character_new() didn't set turn");
}

/* Tests battle_init() */
Test(battle_state, battle_init)
{
    battle_t b;
    character_t *p = character_new("battle_init_Player",PLAYER, NULL, NULL, NULL, NULL);
    character_t *e = character_new("battle_init_Enemy",ENEMY, NULL, NULL, NULL, NULL);
    int rc;

    rc = battle_init(&b, p, e, ENV_SNOW, ENEMY);

    cr_assert_eq(rc, SUCCESS, "character_unit() failed");

    cr_assert_not_null(b.player, "battle_new() didn't set player");
    cr_assert_not_null(b.enemy, "battle_new() didn't set enemy");
    cr_assert_eq(b.environment, ENV_SNOW, "character_new() didn't set environment");
    cr_assert_eq(b.turn, ENEMY, "character_new() didn't set turn");
}

/* Tests free_battle */
Test(battle_state, free_battle)
{
    battle_t *b;
    int rc;
    character_t *p = character_new("battle_new_Player",PLAYER, NULL, NULL, NULL, NULL);
    character_t *e = character_new("battle_new_Enemy",ENEMY, NULL, NULL, NULL, NULL);

    b = battle_new(p, e, ENV_SNOW, ENEMY);

    cr_assert_not_null(b, "battle_new() failed");

    rc = free_battle(b);

    cr_assert_eq(rc, SUCCESS, "battle_free() failed");
}
