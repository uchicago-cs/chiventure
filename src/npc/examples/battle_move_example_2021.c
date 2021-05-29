/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * The CLI is monkey-patched to accept functions that serve to showcase the movement
 * and battle functionalities of the NPC.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* Global variables for this example game */
room_t *lobby;
room_t *arena;
npc_t *friendly_fiona;
npc_t *hostile_harry;

/* Creates a sample class. Taken from test_class.c */
class_t* generate_sample_class()
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

/* Defines a new CLI operation that prints a list of npcs in a room, or says 
 * that there are none. */
char *npcs_in_room_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to check NPCs.\n";
    }

    npc_t *npc_tmp, *npc_elt;
    int i = 0;
    HASH_ITER(hh, game->curr_room->npcs->npc_list, npc_elt, npc_tmp)
    {   
        i++;
	if (npc_elt->npc_battle->health > 0) 
	{
            print_to_cli(ctx, npc_elt->npc_id);
	}
    }

    if (i >= 1) {
        return "These are the NPCs in the room";
    }
    else {
        return "There is no NPC in the room";
    }
}

/* a mokey-patched version of moving from lobby to arena */
char *move_to_arena_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to move.\n";
    }

    move_room(game, arena);
    add_npc_to_room(arena->npcs, friendly_fiona);
    add_npc_to_room(arena->npcs, hostile_harry);
    delete_npc_from_room(lobby->npcs, friendly_fiona);
    delete_npc_from_room(lobby->npcs, hostile_harry);

    return "You are in the arena now";
}


/* a mokey-patched version of moving back from arena to lobby */
char *move_to_lobby_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to move.\n";
    }

    move_room(game, lobby);
    return "You are back to the lobby";
}

/* Defines a new CLI operation that removes 1 HP from the specified npc if they
 * are in the room, and their health is greater than their surrender_level */
char *attack_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to move.\n";
    }

    npc_t *npc_tmp, *npc_elt;
    HASH_ITER(hh, game->curr_room->npcs->npc_list, npc_elt, npc_tmp)
    {
        if (npc_elt->npc_battle->health == 0) 
	{
	    continue;
	} 
	else if (npc_elt->npc_battle->health == 1) 
	{
            change_npc_health(npc_elt, -1, 100);
            transfer_all_npc_items(npc_elt, game->curr_room);
            char message1[1000];
            sprintf(message1, "You killed %s. They've dropped their items, "
                    "which you can now take.", npc_elt->npc_id);
            print_to_cli(ctx, message1);
	} 
	else if (npc_elt->npc_battle->health <= 
		 npc_elt->npc_battle->surrender_level) 
	{ 
            char message2[1000];
            sprintf(message2, "%s has surrendered. You can no longer attack"
                    " them.", npc_elt->npc_id);
            print_to_cli(ctx, message2);
	} 
	else 
	{
            change_npc_health(npc_elt, -1, 100);
            char message3[1000];
            sprintf(message3, "%s has lost 1 HP. They now have %d HP left", 
                    npc_elt->npc_id, npc_elt->npc_battle->health);
            print_to_cli(ctx, message3);
	}
    }
    return "\n";
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);

    /* Initialize the lobby room */
    lobby = room_new("lobby", "This is lobby", 
                     "Fiona and Harry are in the lobby, "
                     "try talk to them, you can also request "
                     "to have a battle with them in the arena.");

    /* Initialize npcs_in_room_t field in room_t */
    lobby->npcs = npcs_in_room_new("lobby");

    add_room_to_game(game, lobby);
    game->curr_room = lobby;

    /* Initialize the arena */
    arena = room_new("arena", "This is arena", 
                     "Here is the arena you can engage in "
                     "battles with NPCs here.");

    /* Initialize npcs_in_room_t field in room_t */
    arena->npcs = npcs_in_room_new("arena");

    add_room_to_game(game, arena);
    

    /* Create a friendly npc */
    char *npc_id1 = "Friendly Fiona";
    class_t *class1 = generate_sample_class();
    npc_mov_t *movement1 = npc_mov_new(NPC_MOV_DEFINITE, lobby);
    extend_path_definite(movement1, arena);
    friendly_fiona = npc_new(npc_id1, 
                             "Friendly Fiona is a friendly woman named Fiona.", 
			     "Friendly Fiona won't fight you unless you attack"
			     " her first, and she'll surrender quickly", class1,
			     movement1, true);
    /* Add battle info to friendly npc */
    stat_t *stats1 = create_enemy_stats();
    move_t *moves1 = create_enemy_moves();
    add_battle_to_npc(friendly_fiona, 100, stats1, moves1, BATTLE_AI_GREEDY,
		      CONDITIONAL_FRIENDLY, 98);
    
    /* Create a hostile npc */
    char *npc_id2 = "Hostile Harry";
    class_t *class2 = generate_sample_class();
    npc_mov_t *movement2 = npc_mov_new(NPC_MOV_DEFINITE, lobby);
    extend_path_definite(movement2, arena);
    hostile_harry = npc_new(npc_id2,
                            "Hostile Harry is a hostile man named"
                            "Harry.", "Hostile Harry will attack you"
                            "first, and he won't surrender until he"
                            "literally dies", class2, movement2, true);
    /* Add battle info to hostile npc */
    stat_t *stats2 = create_enemy_stats();
    move_t *moves2 = create_enemy_moves();
    add_battle_to_npc(hostile_harry, 5, stats2, moves2, BATTLE_AI_GREEDY,
                      HOSTILE, 0);

    /* Add items to hostile npc */
    item_t *potion = item_new("POTION","This is a health potion.",
                              "This potion will increase your health. Feel"
			                  " free to take it.");
    add_item_to_npc(hostile_harry, potion);
    item_t *elixir = item_new("ELIXIR","This is an elixir.",
                              "This is an elixir. Effects: energize and stun.");
    add_item_to_npc(hostile_harry, elixir);
    
    
    /* Add the npcs to the game */
    add_npc_to_game(game, friendly_fiona);
    add_npc_to_game(game, hostile_harry);

    /* Add the npcs to lobby */
    add_npc_to_room(lobby->npcs, friendly_fiona);
    add_npc_to_room(lobby->npcs, hostile_harry);
    
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
    add_entry("ARENA", move_to_arena_operation, NULL, ctx->cli_ctx->table);
    add_entry("LOBBY", move_to_lobby_operation, NULL, ctx->cli_ctx->table);
    add_entry("ATTACK", attack_operation, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
