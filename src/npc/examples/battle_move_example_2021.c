/*
 * This example program runs a full instance of chiventure with an in-memory
 * game. The CLI is monkey-patched to accept functions that serve to showcase
 * the movement and battle functionalities of the NPC, which unfortunately, we
 * didn't have time to integrate with the UI/CLI.
 *
 *  - ATTACK: This is a CLI operation that allows the player to attack all of
 *            the npcs present in a room at once. It removes 1 point of HP from
 *            every npc whose health is greater than their surrender level. If
 *            an npc is killed i.e. it's health is 0, then the player is
 *            informed that they can pick up the npc's items. If an npc
 *            surrenders, i.e. it's health is less than or equal to it's
 *            surrender level, then the player attacking will not remove that
 *            npc's health, and the player will be informed that the npc has
 *            surrendered. While this exact functionality (attacking all npcs
 *            at once) probably won't be added to chiventure, it showcases
 *            how we hope the surrender and dead-npc-looting and dead npc
 *            looting functionalities can be used in battles in the future.
 *
 *  - NPC:    This is a CLI operation that prints out all the NPCs in the
 *            current room to the CLI. It utilizes the backend of rooms_npc
 *            module while printing to chiventure's CLI. Specifically, it uses
 *            a field in the room_t struct called npcs, which contains a list
 *            of NPCs in the current room and the total number of them. For
 *            deatils about this field, see rooms_npc.h.
 *
 *  - ARENA:  This is a CLI operation that moves the player from the lobby to
 *            the arena room. Since the main focus of this example is not player
 *            movement but NPCs movements, there are only two rooms in this example,
 *            which are lobby and arena, and the action of moving between rooms are
 *            simplified with only a call to move_room() under game.h. The process of
 *            building a path between rooms is skipped here since it is not curcial to
 *            the example.
 *
 *  - LOBBY:  Similarly, this is a CLI operation that moves the player from the arena
 *            room back to the lobby after the battle. This operation is essentially
 *            a call to move_room() under game.h with a print statement indicating that
 *            the player is back to the lobby. The process of building a path between rooms
 *            is skipped here since it is not curcial to the example.
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

/* Global variables needed for the implementation of this example game */
room_t *lobby;
room_t *arena;
npc_t *friendly_fiona;
npc_t *hostile_harry;


/* Creates a sample class. Taken from test_class.c */
class_t *generate_sample_class()
{
    class_t *c;
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
stat_t *create_enemy_stats()
{
    stat_t *test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->accuracy = 100;
    test_stats->crit = 0;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;

    return test_stats;
}

/* Creates example moves. Taken from test_battle_ai.c */
move_t *create_enemy_moves()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = move_new(1, "earthquake", "", PHYS, NO_TARGET, NO_TARGET, 
                          SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    poke = move_new(2, "poke", "", PHYS, NO_TARGET, NO_TARGET,
                    SINGLE, 0, NULL, 40, 100, NULL, NULL, NULL, NULL);
    rock_throw = move_new(3, "rock throw", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 90, 100, NULL, NULL, NULL, NULL);
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
        return "Room not found! Error!\n";
    }

    /* This operation has to be called with one parameter */
    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }
}


/* a mokey-patched version of moving from lobby to arena */
char *move_to_arena_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if (game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to move.\n";
    }

    move_room(game, arena);

    if (lobby->npcs->num_of_npcs > 0)
    {
        add_npc_to_room(arena->npcs, friendly_fiona);
        add_npc_to_room(arena->npcs, hostile_harry);
        delete_npc_from_room(lobby->npcs, friendly_fiona);
        delete_npc_from_room(lobby->npcs, hostile_harry);
    }

    return "You are in the arena now";
}


/* Creates a sample convo for NPC Harry, taken from npc_example.c */
convo_t *create_sample_convo_harry()
{
    // Starting to build the conversation structure
    convo_t *c = convo_new();

    // Nodes
    add_node(c, "1", "Harry: Are your trying to pick a fight with me?");
    add_node(c, "2a", "Harry: You will regret this. Let's meet in the arena and "
             "I will show you no mercy.");
    add_node(c, "2b", "Harry: Then you better disappear RIGHT NOW!");

    // Edges
    add_edge(c, "Yeah what are you gonna do about it, huh?", "1", "2a", NULL);
    add_edge(c, "No, I am sorry sir.", "1", "2b", NULL);

    return c;
}


/* Creates a sample convo for NPC Fiona, taken from npc_example.c */
convo_t *create_sample_convo_fiona()
{
    // Starting to build the conversation structure
    convo_t *c = convo_new();

    // Nodes
    add_node(c, "1", "Fiona: Hey how are you doing?");
    add_node(c, "2a", "Fiona: I prefer peace, but I am happy to practice "
             "some battle skills with you in the arena.");
    add_node(c, "2b", "Fiona: I hope you have a good day too!");

    // Edges
    add_edge(c, "Let's have a fight.", "1", "2a", NULL);
    add_edge(c, "I am doing well, I hope you have a good day!", "1", "2b", NULL);

    return c;
}


/* a mokey-patched version of moving back from arena to lobby */
char *move_to_lobby_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if (game == NULL || game->curr_room == NULL)
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
    if (game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to attack.\n";
    }
    if (game->curr_room == arena)
    {
        npc_t *npc_tmp, *npc_elt;

        HASH_ITER(hh, game->curr_room->npcs->npc_list, npc_elt, npc_tmp) 
        {
            if (npc_elt->npc_battle->stats->hp == 0) 
            {
	            continue;
	        } 
            else if (npc_elt->npc_battle->stats->hp == 1) 
            {
                change_npc_hp(npc_elt, -1);
                transfer_all_npc_items(npc_elt, game->curr_room);
                char message1[1000];
                sprintf(message1, "You killed %s. They've dropped their items, "
                        "which you can now take.", npc_elt->npc_id);
                print_to_cli(ctx, message1);
            } else if (npc_elt->npc_battle->stats->hp <= npc_elt->npc_battle->stats->surrender_level) { 
                char message2[1000];
                sprintf(message2, "%s has surrendered. You can no longer attack "
                          "them.", npc_elt->npc_id);
                print_to_cli(ctx, message2);
             }
            else
            {
                change_npc_hp(npc_elt, -1);
                char message3[1000];
                sprintf(message3, "%s has lost 1 HP. They now have %d HP left", 
                        npc_elt->npc_id, npc_elt->npc_battle->stats->hp);
                print_to_cli(ctx, message3);
            }
        }
    } 
    else 
    {
        print_to_cli(ctx, "You can't attack unless you're in the arena.");
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
                     "try talk to them.");

    /* Initialize npcs_in_room_t field in room_t */
    lobby->npcs = npcs_in_room_new("lobby");
    add_room_to_game(game, lobby);
    game->curr_room = lobby;

    /* Initialize the arena */
    arena = room_new("arena", "This is arena",
                     "Here is the arena, you can engage in "
                     "battles with NPCs here.");

    /* Initialize npcs_in_room_t field in room_t */
    arena->npcs = npcs_in_room_new("arena");
    add_room_to_game(game, arena);


    /* Create a friendly npc */
    char *npc_id1 = "FIONA";
    class_t *class1 = generate_sample_class();
    npc_mov_t *movement1 = npc_mov_new(NPC_MOV_DEFINITE, lobby->room_id, 0);
    extend_path_definite(movement1, arena->room_id);
    friendly_fiona = npc_new(npc_id1,
                             "Friendly Fiona is a friendly woman named Fiona.",
                             "Friendly Fiona won't fight you unless you attack "
                             "her first, and she'll surrender quickly", class1,
                             movement1, CONDITIONAL_FRIENDLY);

    /* Add battle info to friendly npc */
    stat_t *stats1 = create_enemy_stats();
    move_t *moves1 = create_enemy_moves();
    add_battle_to_npc(friendly_fiona, stats1, moves1, BATTLE_AI_GREEDY,
		              CONDITIONAL_FRIENDLY, NULL, NULL, NULL, NULL, NULL);

    /* Add dialogue to friendly npc */
    convo_t *c_fiona = create_sample_convo_fiona();
    add_convo_to_npc(friendly_fiona, c_fiona);

    /* Create a hostile npc */
    char *npc_id2 = "HARRY";
    class_t *class2 = generate_sample_class();
    npc_mov_t *movement2 = npc_mov_new(NPC_MOV_DEFINITE, lobby->room_id, 0);
    extend_path_definite(movement2, arena->room_id);
    hostile_harry = npc_new(npc_id2,
                            "Hostile Harry is a hostile man named"
                            "Harry.", "Hostile Harry will attack you"
                            "first, and he won't surrender until he"
                            "literally dies", class2, movement2, HOSTILE);
    /* Add battle info to hostile npc */
    stat_t *stats2 = create_enemy_stats();
    move_t *moves2 = create_enemy_moves();
    add_battle_to_npc(hostile_harry, stats2, moves2, BATTLE_AI_GREEDY,
                      HOSTILE, NULL, NULL, NULL, NULL, NULL);

    /* Add items to hostile npc */
    item_t *potion = item_new("POTION","This is a health potion.",
                              "This potion will increase your health. Feel "
                              "free to take it.");
    add_item_to_npc(hostile_harry, potion);
    item_t *elixir = item_new("ELIXIR","This is an elixir.",
                              "This is an elixir. Effects: energize and stun.");
    add_item_to_npc(hostile_harry, elixir);

    /* Add dialogue to hostile npc */
    convo_t *c_harry = create_sample_convo_harry();
    add_convo_to_npc(hostile_harry, c_harry);


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

    /* Monkeypatch the CLI to add the new operations */
    add_entry("NPC", npcs_in_room_operation, NULL, ctx->cli_ctx->table);
    add_entry("ARENA", move_to_arena_operation, NULL, ctx->cli_ctx->table);
    add_entry("LOBBY", move_to_lobby_operation, NULL, ctx->cli_ctx->table);
    add_entry("ATTACK", attack_operation, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
