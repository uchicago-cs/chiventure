#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "npc/npc_battle.h"
#include "battle/battle_common.h"
#include "battle/battle_moves.h"

/* Creates example stats. Taken from test_battle_ai.c */
stat_t* create_enemy_stats()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->defense = 20;
    test_stats->strength = 150;
    test_stats->dexterity = 10;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;

    return test_stats;
}

/* Creates + initializes a move. Taken from test_battle_ai.c */
move_t *create_move(int id, battle_item_t* item, bool attack, int damage, 
		    int defense)
 {
     move_t* move = (move_t*) calloc(1, sizeof(move_t));

     move->id = id;

     move->item = item;

     move->attack = attack;
     move->damage = damage;
     move->defense = defense;

     return move;
 }

/* Creates example moves. Taken from test_battle_ai.c */
move_t* create_enemy_moves()
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

/* Checks that npc_battle_new() properly mallocs and inits a new npc_battle 
 * struct */
Test(npc_battle, new)
{
    npc_battle_t *npc_battle;

    stat_t *stats = create_enemy_stats();
    move_t *moves = create_enemy_moves();

    npc_battle = npc_battle_new(100, stats, moves, BATTLE_AI_GREEDY, 
		                HOSTILE, 25);

    cr_assert_not_null(npc_battle, "npc_battle_new() failed");

    cr_assert_eq(100, npc_battle->health, 
		 "npc_battle_new() didn't set health");
    cr_assert_eq(stats, npc_battle->stats, 
		 "npc_battle_new() didn't set stats");
    cr_assert_eq(moves, npc_battle->moves, 
		 "npc_battle_new() didn't set moves");
    cr_assert_eq(BATTLE_AI_GREEDY, npc_battle->ai,
                 "npc_battle_new() didn't set ai");
    cr_assert_eq(HOSTILE, npc_battle->hostility_level,
		 "npc_battle_new() didn't set hostility_level");
    cr_assert_eq(25, npc_battle->surrender_level,
		 "npc_battle_new() didn't set surrender_level");
}

/* Checks that npc_battle_init() initialized the fields in the new npc_battle 
 * struct */
Test(npc_battle, init)
{
    npc_battle_t *npc_battle;

    stat_t *stats = create_enemy_stats();
    move_t *moves = create_enemy_moves();

    npc_battle = npc_battle_new(100, NULL, NULL, BATTLE_AI_GREEDY,
                                HOSTILE, 25);

    int res = npc_battle_init(npc_battle, 5, stats, moves, BATTLE_AI_NONE,
		              FRIENDLY, 0);

    cr_assert_eq(res, SUCCESS, "npc_battle_init() failed");

    cr_assert_eq(5, npc_battle->health,
	         "npc_battle_init() didn't initialize health");
    cr_assert_eq(stats, npc_battle->stats,
                 "npc_battle_init() didn't initialize stats");
    cr_assert_eq(moves, npc_battle->moves,
                 "npc_battle_init() didn't initialize moves");
    cr_assert_eq(BATTLE_AI_NONE, npc_battle->ai,
                 "npc_battle_init() didn't initialize ai");
    cr_assert_eq(FRIENDLY, npc_battle->hostility_level,
                 "npc_battle_init() didn't initialize hostility_level");
    cr_assert_eq(0, npc_battle->surrender_level,
                 "npc_battle_init() didn't initialize surrender_level");
}


/* Checks that npc_free() frees the given npc struct from memory */
Test(npc_battle, free)
{
    npc_battle_t *npc_battle;

    stat_t *stats = create_enemy_stats();
    move_t *moves = create_enemy_moves();

    npc_battle = npc_battle_new(100, stats, moves, BATTLE_AI_GREEDY,
                                HOSTILE, 25);

    cr_assert_not_null(npc_battle, "npc_battle_new() failed");

    int res = npc_battle_free(npc_battle);

    cr_assert_eq(res, SUCCESS, "npc_battle_free() failed");

}
