#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "battle/battle_moves.h"


/* Tests move_init */
Test(move, init)
{
    move_t move;
    int rc;

    rc = move_init(&move, "Diss track", 1, NULL, true, 10, 0);

    cr_assert_eq(rc, SUCCESS, "move_init() failed");

    cr_assert_str_eq(move.info, "Diss track",
                     "move_new() didn't set move info");

    cr_assert_null(move.item, "move_new() didn't set item to NULL");

    cr_assert_eq(move.id, 1, "move_new() didn't set move id");

    cr_assert_eq(move.attack, true, "move_new() didn't set type");

    cr_assert_eq(move.damage, 10, "move_new() didn't set move damage");

    cr_assert_eq(move.defense, 0, "move_new() didn't set move defense");
}

/* Tests move_new */
Test(move, new)
{
    move_t *move = move_new("Diss track", 1, NULL, true, 10, 0);

    cr_assert_not_null(move, "move_new() failed");

    cr_assert_str_eq(move->info, "Diss track",
                     "move_new() didn't set move info");

    cr_assert_null(move->item, "move_new() didn't set item to NULL");

    cr_assert_eq(move->id, 1, "move_new() didn't set move id");

    cr_assert_eq(move->attack, true, "move_new() didn't set type");

    cr_assert_eq(move->damage, 10, "move_new() didn't set move damage");

    cr_assert_eq(move->defense, 0, "move_new() didn't set move defense");

}



/* Tests move_free */
Test(move, free)
{
    move_t *move;
    int rc;

    move = move_new("Diss track", 1, NULL, true, 10, 0);

    cr_assert_not_null(move, "move_new() failed");

    rc = move_free(move);

    cr_assert_null(move->item, "move_free didn't free move items");

    cr_assert_eq(rc, SUCCESS, "move_free() failed");
}



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
