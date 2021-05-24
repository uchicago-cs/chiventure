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
    cr_assert_eq(50, npc_battle->stats->speed, 
		 "npc_battle_new() didn't set speed for stats");
    cr_assert_eq(npc_battle->moves, moves, 
		 "npc_battle_new() didn't set moves");
    cr_assert_eq(25, npc_battle->surrender_level,
		 "npc_battle_new() didn't set surrender_level");
}
