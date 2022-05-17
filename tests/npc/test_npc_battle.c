#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game-state/game.h"
#include "npc/npc_battle.h"
#include "battle/battle_common.h"
#include "battle/battle_moves.h"

/* Creates example stats. Taken from test_battle_ai.c */
stat_t *create_enemy_stats1()
{
    stat_t *test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_def = 10;
    test_stats->mag_atk = 10;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->sp = 50;
    test_stats->max_sp = 50;

    return test_stats;
}

/* Creates example stats. Taken from test_battle_ai.c */
stat_t *create_enemy_stats2()
{
    stat_t *test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_def = 10;
    test_stats->mag_atk = 10;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->sp = 50;
    test_stats->max_sp = 50;

    return test_stats;
}

/* Creates + initializes a move. Taken from test_battle_ai.c */
move_t *create_move(int id, battle_item_t* item, bool attack, int damage,
                    int defense)
{
    move_t *move = (move_t*) calloc(1, sizeof(move_t));

    move->id = id;

    move->item = item;

    move->attack = attack;
    move->damage = damage;
    move->defense = defense;

    return move;
}

/* Creates example moves. Taken from test_battle_ai.c */
move_t *create_enemy_moves1()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = create_move(1, NULL, true, 100, 0);
    poke = create_move(2, NULL, true, 40, 0);
    rock_throw = create_move(3, NULL, true, 90, 0);
    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw);
    return head;
}

/* Creates example moves. Taken from test_battle_ai.c */
move_t *create_enemy_moves2()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = create_move(1, NULL, true, 100, 0);
    DL_APPEND(head, earthquake);
    return head;
}

/* Checks that npc_battle_new() properly mallocs and inits a new npc_battle
 * struct */
Test(npc_battle, new)
{
    npc_battle_t *npc_battle;

    stat_t *stats = create_enemy_stats1();
    move_t *moves = create_enemy_moves1();

    npc_battle = npc_battle_new(stats, moves, BATTLE_AI_GREEDY, HOSTILE);

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

    stat_t *stats1 = create_enemy_stats1();
    move_t *moves1 = create_enemy_moves1();
    stat_t *stats2 = create_enemy_stats2();
    move_t *moves2 = create_enemy_moves2();

    npc_battle = npc_battle_new(stats1, moves1, BATTLE_AI_GREEDY, HOSTILE);
    cr_assert_not_null(npc_battle, "npc_battle_new() failed");
    
    int res = npc_battle_init(npc_battle, stats2, moves2, BATTLE_AI_NONE, 
                              FRIENDLY);

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

    stat_t *stats = create_enemy_stats1();
    move_t *moves = create_enemy_moves1();

    npc_battle = npc_battle_new(stats, moves, BATTLE_AI_GREEDY, HOSTILE);

    cr_assert_not_null(npc_battle, "npc_battle_new() failed");

    int res = npc_battle_free(npc_battle);

    cr_assert_eq(res, SUCCESS, "npc_battle_free() failed");

}
