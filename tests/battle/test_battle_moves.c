#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "battle/battle_moves.h"


/* Tests test_move_bard */
Test(move, bard)
{
    move_t *move = test_move_bard();

    cr_assert_str_eq(move->info, "Diss track", "test_move_bard() didn't set class info");

    cr_assert_eq(move->id, 100, "test_move_bard() didn't set id");

    cr_assert_null(move->item, "test_move_bard() didn't set item to NULL");

    cr_assert(move->attack, "test_move_bard() didn't set attack to true");

    cr_assert_eq(move->damage, 15, "test_move_bard() didn't set damage");

    cr_assert_eq(move->defense, 0, "test_move_bard() didn't set defense");
}


/* Tests test_move_cleric */
Test(move, cleric)
{
    move_t *move = test_move_cleric();

    cr_assert_str_eq(move->info, "Divine smite", "test_move_cleric() didn't set class info");

    cr_assert_eq(move->id, 110, "test_move_cleric() didn't set id");

    cr_assert_null(move->item, "test_move_cleric() didn't set item to NULL");

    cr_assert(move->attack, "test_move_cleric() didn't set attack to true");

    cr_assert_eq(move->damage, 10, "test_move_cleric() didn't set damage");

    cr_assert_eq(move->defense, 0, "test_move_cleric() didn't set defense");
}


/* Tests test_move_paladin */
Test(move, paladin)
{
    move_t *move = test_move_paladin();

    cr_assert_str_eq(move->info, "360 no scope", "test_move_paladin() didn't set class info");

    cr_assert_eq(move->id, 120, "test_move_paladin() didn't set id");

    cr_assert_null(move->item, "test_move_paladin() didn't set item to NULL");

    cr_assert(move->attack, "test_move_paladin() didn't set attack to true");

    cr_assert_eq(move->damage, 20, "test_move_paladin() didn't set damage");

    cr_assert_eq(move->defense, 0, "test_move_paladin() didn't set defense");
}


/* Tests test_move_wizard */
Test(move, wizard)
{
    move_t *move = test_move_wizard();

    cr_assert_str_eq(move->info, "Magic, betches", "test_move_wizard() didn't set class info");

    cr_assert_eq(move->id, 130, "test_move_wizard() didn't set id");

    cr_assert_null(move->item, "test_move_wizard() didn't set item to NULL");

    cr_assert(move->attack, "test_move_wizard() didn't set attack to true");

    cr_assert_eq(move->damage, 10, "test_move_wizard() didn't set damage");

    cr_assert_eq(move->defense, 0, "test_move_wizard() didn't set defense");
}
