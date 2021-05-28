/*
 * This example program runs a full instance of chiventure with an in-memory 
 * game.
 *
 * The CLI is monkey-patched to accept functions that serve to showcase movement
 * and battle functionality.
 *
 * Unfortunately, we did not have time to integrate movement or battles with
 * the UI/CLI of chiventure, but the backend is functional as shown in this
 * example.
 *
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "npc/npc.h"

const char *banner = "THIS IS AN NPC EXAMPLE PROGRAM";

// Making the npcs -------------------------------------------------------------

/* Creates a sample class. Taken from test_class.c */
class_t* generate_test_class()
{
    class_t* c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
                " relying on physical strength and years of training to "
                "deal with any obstacle. Mechanically, the warrior focuses "
                "on up-close physical damage with weapons and survives enemy "
                "attacks using heavy armor.\n";

    c = class_new(name, shortdesc, longdesc, NULL, NULL, NULL);

}

/* Creates a sample npc_mov struct. Taken from test_npc_move.c */
npc_mov_t *generate_test_npc_mov()
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room);
}

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
move_t *create_move_(int id, battle_item_t* item, bool attack, int damage,
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
    earthquake = create_move_(1, NULL, true, 100, 0);
    poke = create_move_(2, NULL, true, 40, 0);
    rock_throw = create_move_(3, NULL, true, 90, 0);
    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw);
    return head;
}

/* Creates an example "friendly" npc to battle */
npc_t* friendly_npc()
{
    class_t* c = generate_test_class();
    npc_mov_t* m = generate_test_npc_mov();
    npc_t* npc = npc_new("friendly", "friendly npc", "friendly npc", c, m, 
		         true);

    add_battle_to_npc(npc, 100, stats, moves, BATTLE_AI_GREEDY,
		      CONDITIONAL_FRIENDLY, 99);
}

/* Creates an example "friendly" npc to battle */
npc_t* hostile_npc()
{
    class_t* c = generate_test_class();
    npc_mov_t* m = generate_test_npc_mov();
    npc_t* npc = npc_new("hostile", "hostile npc", "hostile npc", c, m,
                         true);

    add_battle_to_npc(npc, 10, stats, moves, BATTLE_AI_GREEDY,
                      HOSTILE, 0);
}
