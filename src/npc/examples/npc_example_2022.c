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
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "cli/operations.h"
#include "common/ctx.h"
#include "ui/ui.h"
#include "npc/npc.h"
#include "game-state/game.h"

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
    "     |    __________________________________________________________________________________|____\n"
    "     |   /                                                                                      /\n"
    "     |  /                          EXAMPLE PROGRAM - NPC TEAM 2022                             /\n"
    "     \\_/______________________________________________________________________________________/\n";

/* Global variables needed for the implementation of this example game */
npc_t *friendly_fiona;
npc_t *hostile_harry;
npc_t *wandering_william;
npc_t *speedy_sonic;
npc_t *brainy_borja;


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


/* Adds all of a game's NPCs to the rooms they were initialized to start in.
 * This should be run once a game has been created and all of the NPCs
 * and rooms have been added to the game. */
int add_all_npcs_to_their_rooms(game_t *game)
{
    npc_t *elt, *tmp;
    room_t *room;
    char *npc_room_id;
    int rt = SUCCESS;
    HASH_ITER(hh, game->all_npcs, elt, tmp)
    {
        if (elt->movement != NULL)
        {
            npc_room_id = elt->movement->track;
            HASH_FIND(hh, game->all_rooms, npc_room_id, strlen(npc_room_id), room);
            if (room != NULL)
            {
                assert(add_npc_to_room(room->npcs, elt) == SUCCESS);
            }
            else
            {
                rt++;
            }
        }
        else
        {
            rt++;
        }
    }
    return rt;
}

/* a monkey-patched version of finding an NPC in the game */
char *find_npc_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if (tokens[1] == NULL)
    {
        return "You need to specify an NPC to find\n";
    }
    char *npc_id = tokens[1];
    case_insensitize(npc_id);
    npc_t *npc;
    HASH_FIND(hh, game->all_npcs, npc_id, strlen(npc_id), npc);
    char *str;
    if (npc == NULL)
    {
        sprintf(str, "%s is not an existing NPC", npc_id);
    }
    else
    {
        if (npc->npc_battle != NULL && get_npc_hp(npc) <= 0)
        {
            sprintf(str, "%s's body is in the %s", npc->npc_id, npc->movement->track);
        }
        else
        {
            sprintf(str, "%s is in the %s", npc->npc_id, npc->movement->track);
        }
    }
    return str;
}

/* Creates a sample convo for NPC Harry, taken from npc_example.c */
convo_t *create_sample_convo_harry()
{
    // Starting to build the conversation structure
    convo_t *c = convo_new();

    // Nodes
    add_node(c, "1", "Harry: Are your trying to pick a fight with me?");
    add_node(c, "2a", "Harry: You will regret this. Let's meet outside and "
             "I will show you no mercy.");
    node_t *battle_node1 = get_node(c->all_nodes, "2a");
    add_action_to_node(battle_node1, MOVE_ROOM, "harry move to arena");

    add_node(c, "2b", "Well, you are not welcome here. Let's meet in the arena and "
             "I will show you no mercy.");
    node_t *battle_node2 = get_node(c->all_nodes, "2b");
    add_action_to_node(battle_node2, MOVE_ROOM, "harry move to arena");

    // Edges
    add_edge(c, "What does it matter to you, old man?", "1", "2a", NULL);
    add_edge(c, "I am just passing through, I don't want any trouble.", "1", "2b", NULL);

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
             "some battle skills with you outside.");
    node_t *hostile_node = get_node(c->all_nodes, "2a");
    add_action_to_node(hostile_node, MAKE_HOSTILE, "fiona battle");
    add_action_to_node(hostile_node, MOVE_ROOM, "fiona move to arena");

    add_node(c, "2b", "Fiona: I hope you have a good day too!");

    // Edges
    add_edge(c, "Let's have a fight.", "1", "2a", NULL);
    add_edge(c, "I am doing well, I hope you have a good day!", "1", "2b", NULL);

    return c;
}


/* Creates a sample convo for NPC William, taken from npc_example.c */
convo_t *create_sample_convo_william()
{
    // Starting to build the conversation structure
    convo_t *c = convo_new();

    // Nodes
    add_node(c, "1", "William: Hi! I'm William");
    node_t *node_1 = get_node(c->all_nodes, "1");
    add_action_to_node(node_1, PAUSE_MOVEMENT, "stop william");
    
    add_node(c, "2", "William: Well, I better get moving, bye!");
    node_t *node_2 = get_node(c->all_nodes, "2");
    add_action_to_node(node_2, RESUME_MOVEMENT, "let william leave");

    // Edges
    add_edge(c, "Hello William!", "1", "2", NULL);

    return c;
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
    if (strcmp(game->curr_room->room_id, "outside") != 0)
    {
        return "It's not a good idea to start a fight in a Library, you should go outside.\n";
    }
    if (tokens[1] == NULL)
    {
        return "You must identify someone to attack\n";
    }
    else
    {
        char *str = malloc(MAX_MSG_LEN);
        char *npc_id = tokens[1];
        case_insensitize(npc_id);
        npc_t *npc = get_npc_in_room(ctx->game->curr_room, npc_id);
        if (npc == NULL) 
        {
            return "No one by that name wants to fight here.\n";
        }
        if (npc->hostility_level != HOSTILE || npc->npc_battle == NULL) 
        {
            sprintf(str, "%s does not want to fight", npc_id);
            return str;
        }
        else if (get_npc_hp(npc) <= 0)
        {
            return "There's no point in beating a dead horse.\n";
        }
        else
        {
            if (npc->npc_battle->stats->hp == 1)
            {
                change_npc_hp(npc, -1);
                assert(transfer_all_npc_items(npc, game->curr_room) == SUCCESS);
                sprintf(str, "You killed %s. They've dropped their items, "
                        "which you can now take.", npc->npc_id);
                return str;
            }
            else if (npc->npc_battle->stats->hp <= npc->npc_battle->stats->surrender_level) 
            { 
                sprintf(str, "%s has surrendered. You can no longer attack "
                          "them.", npc->npc_id);
                return str;
            }
            else
            {
                change_npc_hp(npc, -1);
                sprintf(str, "%s has lost 1 HP. They now have %d HP left", 
                        npc->npc_id, npc->npc_battle->stats->hp);
                return str;
            }
        }
    }
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);

    room_t *crerar_first = room_new("crerar lib floor 1",
                                    "The first floor of Crerar Library",
                                    "The first floor of the John Crerar Library, "
                                    "head EAST to go outside, "
                                    "UP is the 2nd floor, where Room 209 is located, "
                                    "and SOUTH is the Peaches Cafe.");
    room_t *crerar_second = room_new("crerar lib floor 2",
                                     "The second floor of Crerar Library",
                                     "The second floor of the John crerar Library, "
                                     "to the SOUTH lies Room 209, "
                                     "and DOWN is the first floor of Crerar");
    room_t *crerar_209 = room_new("room 209", "This is Room 209 of Crerar Library",
                                  "This is Room 209 of the John Crerar Library, "
                                  "better known as Borja's Office. "
                                  "To the NORTH is the rest of second floor of Crerar.");
    room_t *peachs_cafe = room_new("peach's cafe", "Peach's Cafe at University",
                                    "This is Peach's Cafe inside of the John Crerar "
                                    "Library, to the NORTH is the first floor of "
                                    "Crerar, and head EAST to go outside.");
    room_t *outside = room_new("outside", "Outside of the John Crerar Library",
                               "Outside of the John Crerar Library is a great "
                               "place for, among other things, settling scores. "
                               "Go WEST to go back inside the John Crerar Library");

    path_t *crerar_first_path = path_new(outside, "east");
    assert(add_path_to_room(crerar_first, crerar_first_path) == SUCCESS);
    crerar_first_path = path_new(crerar_second, "up");
    assert(add_path_to_room(crerar_first, crerar_first_path) == SUCCESS);
    crerar_first_path = path_new(peachs_cafe, "south");
    assert(add_path_to_room(crerar_first, crerar_first_path) == SUCCESS);

    path_t *crerar_second_path = path_new(crerar_first, "down");
    assert(add_path_to_room(crerar_second, crerar_second_path) == SUCCESS);
    crerar_second_path = path_new(crerar_209, "south");
    assert(add_path_to_room(crerar_second, crerar_second_path) == SUCCESS);

    path_t *crerar_209_path = path_new(crerar_second, "north");
    assert(add_path_to_room(crerar_209, crerar_209_path) == SUCCESS);

    path_t *peachs_path = path_new(crerar_first, "north");
    assert(add_path_to_room(peachs_cafe, peachs_path) == SUCCESS);
    peachs_path = path_new(outside, "east");
    assert(add_path_to_room(peachs_cafe, peachs_path) == SUCCESS);
    
    path_t *outside_path = path_new(crerar_first, "west");
    assert(add_path_to_room(outside, outside_path) == SUCCESS);

    crerar_first->npcs = npcs_in_room_new(crerar_first->room_id);
    crerar_second->npcs = npcs_in_room_new(crerar_second->room_id);
    crerar_209->npcs = npcs_in_room_new(crerar_209->room_id);
    peachs_cafe->npcs = npcs_in_room_new(peachs_cafe->room_id);
    outside->npcs = npcs_in_room_new(outside->room_id);

    assert(add_room_to_game(game, crerar_first) == SUCCESS);
    assert(add_room_to_game(game, crerar_second) == SUCCESS);
    assert(add_room_to_game(game, crerar_209) == SUCCESS);
    assert(add_room_to_game(game, outside) == SUCCESS);
    assert(add_room_to_game(game, peachs_cafe) == SUCCESS);

    game->curr_room = crerar_first;

    /* Create a friendly npc */
    char *npc_id1 = "FIONA";
    class_t *class1 = generate_sample_class();
    npc_mov_t *movement1 = npc_mov_new(NPC_MOV_DEFINITE, NPC_MOV_ALLOWED, crerar_second->room_id, 0);
    extend_path_definite(movement1, outside->room_id);
    friendly_fiona = npc_new(npc_id1,
                             "Friendly Fiona is a friendly woman named Fiona.",
                             "Friendly Fiona won't fight you unless you attack "
                             "her first, and she'll surrender quickly", class1,
                             movement1, CONDITIONAL_FRIENDLY);

    /* Add battle info to friendly npc */
    stat_t *fiona_stats = create_enemy_stats();
    fiona_stats->hp = 100;
    fiona_stats->max_hp = 100;
    fiona_stats->surrender_level = 95;

    move_t *moves1 = create_enemy_moves();
    add_battle_to_npc(friendly_fiona, fiona_stats, moves1, BATTLE_AI_GREEDY,
		              CONDITIONAL_FRIENDLY, NULL, NULL, NULL, NULL, NULL);

    /* Add dialogue to conditional-friendly npc */
    convo_t *c_fiona = create_sample_convo_fiona();
    add_convo_to_npc(friendly_fiona, c_fiona);


    /* Create a hostile npc */
    char *npc_id2 = "HARRY";
    class_t *class2 = generate_sample_class();
    npc_mov_t *movement2 = npc_mov_new(NPC_MOV_DEFINITE, NPC_MOV_ALLOWED, peachs_cafe->room_id, 0);
    extend_path_definite(movement2, outside->room_id);
    hostile_harry = npc_new(npc_id2,
                            "Hostile Harry is a hostile man named"
                            "Harry.", "Hostile Harry will attack you"
                            "first, and he won't surrender until he"
                            "literally dies", class2, movement2, HOSTILE);
    /* Add battle info to hostile npc */
    stat_t *stats2 = create_enemy_stats();
    stats2->hp = 5;
    stats2->max_hp = 5;
    move_t *moves2 = create_enemy_moves();
    add_battle_to_npc(hostile_harry, stats2, moves2, BATTLE_AI_GREEDY,
                      HOSTILE, NULL, NULL, NULL, NULL, NULL);

    /* Add items to hostile npc */
    item_t *potion = item_new("POTION","This is a health potion.",
                              "This potion will increase your health. Feel "
                              "free to take it.");
    agent_t *potion_ag = malloc(sizeof(agent_t));
    potion_ag->item = potion;
    assert(add_action(potion_ag, "take", "You now have a potion",
                      "potion could not be taken") == SUCCESS);
    add_item_to_npc(hostile_harry, potion);

    item_t *elixir = item_new("ELIXIR","This is an elixir.",
                              "This is an elixir. Effects: energize and stun.");
    agent_t *elixir_ag = malloc(sizeof(agent_t));
    elixir_ag->item = elixir;
    assert(add_action(elixir_ag, "take", "You now have an elixir",
                      "elixir could not be taken") == SUCCESS);
    add_item_to_npc(hostile_harry, elixir);

    /* Add dialogue to hostile npc */
    convo_t *c_harry = create_sample_convo_harry();
    add_convo_to_npc(hostile_harry, c_harry);


    npc_mov_t *movement3 = npc_mov_new(NPC_MOV_INDEFINITE, NPC_MOV_ALLOWED, outside->room_id, 5);
    extend_path_indefinite(movement3, peachs_cafe->room_id, 5);
    extend_path_indefinite(movement3, crerar_first->room_id, 5);
    extend_path_indefinite(movement3, crerar_second->room_id, 5);
    extend_path_indefinite(movement3, crerar_209->room_id, 5);
    wandering_william = npc_new("william", "wandering william is friendly",
     "wandering william is just a jolly good fellow who likes to wander between"
     "rooms", class2, movement3, FRIENDLY);
    convo_t *c_william = create_sample_convo_william();
    assert(add_convo_to_npc(wandering_william, c_william) == SUCCESS);
    

    npc_mov_t *sonic_mov = npc_mov_new(NPC_MOV_INDEFINITE, NPC_MOV_ALLOWED, outside->room_id, 1);
    extend_path_indefinite(sonic_mov, peachs_cafe->room_id, 2);
    extend_path_indefinite(sonic_mov, crerar_first->room_id, 2);
    extend_path_indefinite(sonic_mov, crerar_second->room_id, 2);
    extend_path_indefinite(sonic_mov, crerar_209->room_id, 1);
    speedy_sonic = npc_new("sonic", "sonic the hedgehog", "sonic the hedgehog is very fast", class2, sonic_mov, FRIENDLY);


    npc_mov_t *borja_mov = npc_mov_new(NPC_MOV_DEFINITE, NPC_MOV_ALLOWED, crerar_209->room_id, 0);
    extend_path_definite(borja_mov, peachs_cafe->room_id);
    extend_path_definite(borja_mov, outside->room_id);
    brainy_borja = npc_new("borja", "Professor Borja Sotomayor", "Borja Sotomayor is an Associate Senior Instructional Professor in the Department of Computer Science, "
                           "where he teaches intro CS, software development, computer networks, and distributed systems.", class2, borja_mov, CONDITIONAL_FRIENDLY);


    /* Add the npcs to the game */
    assert(add_npc_to_game(game, friendly_fiona) == SUCCESS);
    assert(add_npc_to_game(game, hostile_harry) == SUCCESS);
    assert(add_npc_to_game(game, wandering_william) == SUCCESS);
    assert(add_npc_to_game(game, speedy_sonic) == SUCCESS);
    assert(add_npc_to_game(game, brainy_borja) == SUCCESS);

    /* Add the npcs to lobby */
    assert(add_all_npcs_to_their_rooms(game) == SUCCESS);

    /* Free default game and replace it with ours */
    game_free(ctx->game);
    ctx->game = game;

    return ctx;
}

/* Runs all (included) time-dependent functions every second
*
* Parameters:
*   - game: Pointer to the game being run
*
* Returns
*   - nothing
*/
void *time_dependent_functions(void *game)
{
    pthread_detach(pthread_self());

    game_t *g;
    g = (game_t *) game;

    while (g != NULL)
    {
        /* This is where you add functions that should be run every second */
        move_indefinite_npcs_if_needed(g->all_npcs, g->all_rooms);
        sleep(1);
    }
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add the new operations */
    add_entry("NPC", npcs_in_room_operation, NULL, ctx->cli_ctx->table);
    add_entry("ATTACK", attack_operation, NULL, ctx->cli_ctx->table);
    add_entry("FIND", find_npc_operation, NULL, ctx->cli_ctx->table);

    pthread_t time_thread;
    int rc = pthread_create(&time_thread, NULL, time_dependent_functions, (void *) ctx->game);
    if (rc)
    {
		printf("\nERROR: return code from pthread_create is %d\n", rc);
        exit(1);
    }

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}

