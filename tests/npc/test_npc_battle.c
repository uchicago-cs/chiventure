#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/battle/battle_test_utility.h"

/* Checks that npc_battle_new() properly mallocs and inits a new npc_battle
 * struct */
Test(npc_battle, new)
{
    npc_battle_t *npc_battle;

    stat_t *stats = create_enemy_stats_v1();
    move_t *moves = create_enemy_moves_v1();

    stat_changes_t *dagger_changes = stat_changes_new();
    dagger_changes->phys_atk = 20;
    dagger_changes->phys_def = 5;
    dagger_changes->hp = 0;                        

    battle_item_t *dagger = create_battle_item(1, 20, "A hearty dagger sure to take your breath away... for good", "Dagger", true, 
		    dagger_changes);

    npc_battle = npc_battle_new(stats, moves, BATTLE_AI_GREEDY, 
		                HOSTILE, make_new_warrior_class(), dagger,
                        NULL, NULL, NULL);


    cr_assert_not_null(npc_battle, "npc_battle_new() failed");

    cr_assert_eq(stats, npc_battle->stats, 
                 "npc_battle_new() didn't set stats");
    cr_assert_eq(moves, npc_battle->moves, 
		         "npc_battle_new() didn't set moves");
    cr_assert_eq(BATTLE_AI_GREEDY, npc_battle->ai,
                 "npc_battle_new() didn't set ai");
    cr_assert_eq(HOSTILE, npc_battle->hostility_level,
		         "npc_battle_new() didn't set hostility_level");
}

/* Checks that npc_battle_init() initialized the fields in the new npc_battle
 * struct */
Test(npc_battle, init)
{
    npc_battle_t *npc_battle;

    stat_t *stats1 = create_enemy_stats_v1();
    move_t *moves1 = create_enemy_moves_v1();
    stat_t *stats2 = create_enemy_stats_v2();
    move_t *moves2 = create_enemy_moves_v2();

    stat_changes_t *dagger_changes = stat_changes_new();
    dagger_changes->phys_atk = 20;
    dagger_changes->phys_def = 5;
    dagger_changes->hp = 0;                        

    battle_item_t *dagger = create_battle_item(1, 20, "A hearty dagger sure to take your breath away... for good", "Dagger", true, 
		    dagger_changes);

    npc_battle = npc_battle_new(stats1, moves1, BATTLE_AI_GREEDY,
                                HOSTILE, make_new_warrior_class(),
                                dagger, NULL, NULL, NULL);
    cr_assert_not_null(npc_battle, "npc_battle_new() failed");

    int res = npc_battle_init(npc_battle, stats2, moves2, BATTLE_AI_NONE,
		                FRIENDLY, make_new_warrior_class(), dagger,
                        NULL, NULL, NULL);


    cr_assert_eq(res, SUCCESS, "npc_battle_init() failed");

    cr_assert_eq(stats2, npc_battle->stats,
                 "npc_battle_init() didn't initialize stats");
    cr_assert_eq(moves2, npc_battle->moves,
                 "npc_battle_init() didn't initialize moves");
    cr_assert_eq(BATTLE_AI_NONE, npc_battle->ai,
                 "npc_battle_init() didn't initialize ai");
    cr_assert_eq(FRIENDLY, npc_battle->hostility_level,
                 "npc_battle_init() didn't initialize hostility_level");
}


/* Checks that npc_free() frees the given npc struct from memory */
Test(npc_battle, free)
{
    npc_battle_t *npc_battle;

    stat_t *stats = create_enemy_stats_v1();
    move_t *moves = create_enemy_moves_v1();

    stat_changes_t *dagger_changes = stat_changes_new();
    dagger_changes->phys_atk = 20;
    dagger_changes->phys_def = 5;
    dagger_changes->hp = 0;                        
    battle_item_t *dagger = create_battle_item(1, 20, "A hearty dagger sure to take your breath away... for good", "Dagger", true, 
		    dagger_changes);


    npc_battle = npc_battle_new(stats, moves, BATTLE_AI_GREEDY,
                                HOSTILE, make_new_warrior_class(),
                                dagger, NULL, NULL, NULL);

    cr_assert_not_null(npc_battle, "npc_battle_new() failed");

    int res = npc_battle_free(npc_battle);

    cr_assert_eq(res, SUCCESS, "npc_battle_free() failed");

}
