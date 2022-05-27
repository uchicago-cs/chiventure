#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/battle/battle_test_utility.h"

/* Tests move_init */
Test(move, init)
{
    move_t move;
    int rc;

    rc = move_init(&move, 1, "Getsuga", "Slash", PHYS, NO_TARGET, NO_TARGET, 7, 20, 
		    NULL, 50, 100, NULL, NULL, NULL, NULL);

    cr_assert_eq(rc, SUCCESS, "move_init() failed");

    cr_assert_eq(move.id, 1, "move_new() didn't set move id");

    cr_assert_str_eq(move.name, "Getsuga",
                     "move_new() didn't set move info");

    cr_assert_str_eq(move.info, "Slash",
		     "move_new() didn't set move info");

    cr_assert_eq(move.dmg_type, PHYS, "move_new() didn't set move id");

    cr_assert_eq(move.stat_mods, NO_TARGET, "move_new() didn't set move id");    

    cr_assert_eq(move.effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move.count, 7, "move_new() didn't set move id");

    cr_assert_eq(move.sp_cost, 20, "move_new() didn't set move id");

    cr_assert_null(move.req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(move.damage, 50, "move_new() didn't set move id");

    cr_assert_eq(move.accuracy, 100, "move_new() didn't set move id");    

    cr_assert_null(move.user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move.opponent_mods, "move_new() didn't set battle_item to NULL");
     
    cr_assert_null(move.prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move.next, "move_new() didn't set battle_item to NULL");
}

/* Tests move_new */
Test(move, new)
{
    move_t *move = move_new(1, "Getsuga", "Slash", PHYS, NO_TARGET, NO_TARGET, 7, 20,
		    NULL, 50, 100, NULL, NULL, NULL, NULL);

    cr_assert_not_null(move, "move_new() failed");

    cr_assert_eq(move->id, 1, "move_new() didn't set move id");

    cr_assert_str_eq(move->name, "Getsuga",
                     "move_new() didn't set move info");

    cr_assert_str_eq(move->info, "Slash",
                     "move_new() didn't set move info");

    cr_assert_eq(move->dmg_type, PHYS, "move_new() didn't set move id");

    cr_assert_eq(move->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->count, 7, "move_new() didn't set move id");

    cr_assert_eq(move->sp_cost, 20, "move_new() didn't set move id");

    cr_assert_null(move->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(move->damage, 50, "move_new() didn't set move id");

    cr_assert_eq(move->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(move->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->next, "move_new() didn't set battle_item to NULL");
}



/* Tests move_free */
Test(move, free)
{
    move_t *move;
    int rc;

    move = move_new(1, "Getsuga", "Slash", PHYS, NO_TARGET, NO_TARGET, 7, 20
		    ,NULL, 50, 100, NULL, NULL, NULL, NULL);

    cr_assert_not_null(move, "move_new() failed");

    rc = move_free(move);

    cr_assert_null(move->req_item, "move_free didn't free move battle_items");

    cr_assert_null(move->user_mods, "move_free didn't free move battle_items");

    cr_assert_null(move->opponent_mods, "move_free didn't free move battle_items");

    cr_assert_null(move->prev, "move_free didn't free move battle_items");

    cr_assert_null(move->next, "move_free didn't free move battle_items");

    cr_assert_eq(rc, SUCCESS, "move_free() failed");
}



/* Tests test_move_bard */
Test(move, bard)
{
    move_t *move = test_move_bard();

    cr_assert_eq(move->id, 100, "move_new() didn't set move id");

    cr_assert_str_eq(move->name, "",
                     "move_new() didn't set move info");

    cr_assert_str_eq(move->info, "Diss track",
                     "move_new() didn't set move info");

    cr_assert_eq(move->dmg_type, MAG, "move_new() didn't set move id");

    cr_assert_eq(move->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->count, 0, "move_new() didn't set move id");

    cr_assert_eq(move->sp_cost, 10, "move_new() didn't set move id");

    cr_assert_null(move->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(move->damage, 15, "move_new() didn't set move id");

    cr_assert_eq(move->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(move->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->next, "move_new() didn't set battle_item to NULL");
}	


/* Tests test_move_cleric */
Test(move, cleric)
{
    move_t *move = test_move_cleric();

    cr_assert_eq(move->id, 110, "move_new() didn't set move id");

    cr_assert_str_eq(move->name, "",
                     "move_new() didn't set move info");

    cr_assert_str_eq(move->info, "Divine smite",
                     "move_new() didn't set move info");

    cr_assert_eq(move->dmg_type, MAG, "move_new() didn't set move id");

    cr_assert_eq(move->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->count, 0, "move_new() didn't set move id");

    cr_assert_eq(move->sp_cost, 15, "move_new() didn't set move id");

    cr_assert_null(move->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(move->damage, 10, "move_new() didn't set move id");

    cr_assert_eq(move->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(move->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->next, "move_new() didn't set battle_item to NULL");
}


/* Tests test_move_paladin */
Test(move, paladin)
{
    move_t *move = test_move_paladin();

    cr_assert_eq(move->id, 120, "move_new() didn't set move id");

    cr_assert_str_eq(move->name, "",
                     "move_new() didn't set move info");

    cr_assert_str_eq(move->info, "360 no scope",
                     "move_new() didn't set move info");

    cr_assert_eq(move->dmg_type, PHYS, "move_new() didn't set move id");

    cr_assert_eq(move->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->count, 0, "move_new() didn't set move id");

    cr_assert_eq(move->sp_cost, 0, "move_new() didn't set move id");

    cr_assert_null(move->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(move->damage, 20, "move_new() didn't set move id");

    cr_assert_eq(move->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(move->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->next, "move_new() didn't set battle_item to NULL");
}


/* Tests test_move_wizard */
Test(move, wizard)
{
    move_t *move = test_move_wizard();

    cr_assert_eq(move->id, 130, "move_new() didn't set move id");

    cr_assert_str_eq(move->name, "",
                     "move_new() didn't set move info");

    cr_assert_str_eq(move->info, "Fireball",
                     "move_new() didn't set move info");

    cr_assert_eq(move->dmg_type, MAG, "move_new() didn't set move id");

    cr_assert_eq(move->stat_mods, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->effects, NO_TARGET, "move_new() didn't set move id");

    cr_assert_eq(move->count, 0, "move_new() didn't set move id");

    cr_assert_eq(move->sp_cost, 10, "move_new() didn't set move id");

    cr_assert_null(move->req_item, "move_new() didn't set battle_item to NULL");

    cr_assert_eq(move->damage, 10, "move_new() didn't set move id");

    cr_assert_eq(move->accuracy, 100, "move_new() didn't set move id");

    cr_assert_null(move->user_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->opponent_mods, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->prev, "move_new() didn't set battle_item to NULL");

    cr_assert_null(move->next, "move_new() didn't set battle_item to NULL");

}
