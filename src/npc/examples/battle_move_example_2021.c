/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * The CLI is monkey-patched to accept functions that serve to showcase the movement
 * and battle functionalities of the NPC.
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "npc/npc.h"

const char *banner =
    "    ________________________________________________________________________________________\n"
    "  / \\                                                                                      \\\n"
    " |   |                                                                                      |\n"
    "  \\_ |     ██████╗██╗  ██╗██╗██╗   ██╗███████╗███╗   ██╗████████╗██╗   ██╗██████╗ ███████╗  |\n"
    "     |    ██╔════╝██║  ██║██║██║   ██║██╔════╝████╗  ██║╚══██╔══╝██║   ██║██╔══██╗██╔════╝  |\n"
    "     |    ██║     ███████║██║██║   ██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║██████╔╝█████╗    |\n"
    "     |    ██║     ██╔══██║██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ██║   ██║██╔══██╗██╔══╝    |\n"
    "     |    ╚██████╗██║  ██║██║ ╚████╔╝ ███████╗██║ ╚████║   ██║   ╚██████╔╝██║  ██║███████╗  |\n"
    "     |     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝  |\n"
    "     |     _________________________________________________________________________________|_____\n"
    "     |    /                                                                                      /\n"
    "     |   /                         EXAMPLE PROGRAM - NPC_1 TEAM 2021                            /\n"
    "     \\_/______________________________________________________________________________________/\n";


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

/* Makes sure the game is loaded */
char *check_game(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if (game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! Look for Jim if you're not in a room!\n";
    }

    /* This operation has to be called with one parameter */
    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }
}

/* Defines a new CLI operation that prints a list of npcs in a room, or says that there are none. */
char *npcs_in_room_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to check items.\n";
    }

    npc_t *npc_tmp, *npc_elt;
    int i = 0;
    HASH_ITER(hh, game->curr_room->npcs->npc_list, npc_elt, npc_tmp)
    {   
        i++;
        print_to_cli(ctx, npc_elt->npc_id);
    }

    if (i >= 1) {
        return "These are the NPCs in the room";
    }
    else {
        return "There are no NPC in the room";
    }
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);

    /* Create the initial room */
    room_t *room1 = room_new("room1", "This is room 1", 
                             "The first room in this house is disheveled, "
                             "yet seems to be stacked with valuables. "
                             "You spot a faberge egg and an antique "
                             "clock, for starters.");

    /* Initialize npcs_in_room_t field in room_t */
    npcs_in_room_t *npcs = npcs_in_room_new("room1");
    room1->npcs = npcs;

    add_room_to_game(game, room1);
    game->curr_room = room1;

    /* Create two items */
    item_t *egg = item_new("EGG", "It is a faberge egg.",
                           "The jewelled artifact shimmers through a thick "
                           "layer of dust. It looks far too expensive for "
                           "its surroundings.");
    add_item_to_room(room1, egg);

    item_t *clock = item_new("CLOCK", "It is an antique grandfather clock.",
                             "The clocks hands are stuck at precisely 8:52. "
                             "It towers over everything but you.");
    add_item_to_room(room1, clock);

    /* Create a friendly npc */
    char *npc_id1 = "Friendly Fiona";
    class_t *class1 = generate_test_class();
    npc_mov_t *movement1 = npc_mov_new(NPC_MOV_DEFINITE, room1);
    npc_t *friendly_fiona = npc_new(npc_id1, 
                                    "Friendly Fiona is a friendly woman named" 
				    "Fiona.", "Friendly Fiona won't fight you" 
				    "unless you attack her first, and she'll"
				    "surrender quickly", class1, movement1, true);
    /* Add battle info to friendly npc */
    stat_t *stats1 = create_enemy_stats();
    move_t *moves1 = create_enemy_moves();
    add_battle_to_npc(friendly_fiona, 100, stats1, moves1, BATTLE_AI_GREEDY,
		      CONDITIONAL_FRIENDLY, 98);
    
    /* Create a hostile npc */
    char *npc_id2 = "Hostile Harry";
    class_t *class2 = generate_test_class();
    npc_mov_t *movement2 = npc_mov_new(NPC_MOV_DEFINITE, room1);
    npc_t *hostile_harry = npc_new(npc_id2,
                                   "Hostile Harry is a hostile man named"
                                   "Harry.", "Hostile Harry will attack you"
                                   "first, and he won't surrender until he"
                                   "literally dies", class2, movement2, true);
    /* Add battle info to hostile npc */
    stat_t *stats2 = create_enemy_stats();
    move_t *moves2 = create_enemy_moves();
    add_battle_to_npc(hostile_harry, 10, stats2, moves2, BATTLE_AI_GREEDY,
                      HOSTILE, 0);
	
	/* Add items to hostile npc */
	item_t *elixir = item_new("ELIXIR","This is an elixir.",
                   "This is an elixir. Effects: energize and stun.");
    add_item_to_npc(hostile_harry, elixir);

    item_t *potion = item_new("POTION","This is a health potion.",
                   "This potion will increase your health. Feel free to take it.");
    add_item_to_npc(hostile_harry, potion);
    
    /* Add the npcs to the game */
    add_npc_to_game(game, friendly_fiona);
    add_npc_to_game(game, hostile_harry);

    /* Add the npcs to room1 */
    add_npc_to_room(room1->npcs, friendly_fiona);
    add_npc_to_room(room1->npcs, hostile_harry);
    
    /* Free default game and replace it with ours */
    game_free(ctx->game);
    ctx->game = game;

    return ctx;
}


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add the new operations
     * (not handled by action management, as that code
     * currently only supports items) */
    add_entry("NPC", npcs_in_room_operation, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
