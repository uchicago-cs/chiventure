/*
 * This example program runs a full instance of chiventure with an in-memory
 * game. The CLI is monkey-patched to accept functions that serve to showcase
 * the movement and battle functionalities of the NPC, which unfortunately, we
 * didn't have time to integrate with the UI/CLI.
 *
 *  - ATTACK: This is a CLI operation that allows the player to attack one of
 *            the NPCs present in a room. It removes 1 point of HP from
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
npc_t *wandering_wilma;
npc_t *speedy_sonic;
npc_t *brainy_borja;
npc_t *peachs_barista;
room_t *crerar_first;
room_t *crerar_second;
room_t *crerar_209;
room_t *peachs_cafe;
room_t *outside;


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
    test_stats->surrender_level = 0;

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

/* a monkey-patched version of getting an NPC's long description */
char *who_is_npc_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    char *str = malloc(MAX_MSG_LEN);
    if (tokens[1] == NULL)
    {
        sprintf(str, "The (case-independent) WHO command is formatted as: "
                     "WHO *IS* *insert_NPC_name_here*");
    }
    else if (tokens[2] == NULL)
    {
        sprintf(str, "You need to specify an NPC to ask about");
    }
    else
    {
        char *npc_id = tokens[2];
        npc_t *npc;
        HASH_FIND(hh, game->all_npcs, npc_id, strlen(npc_id), npc);
        if (npc == NULL)
        {
            sprintf(str, "%s is not an existing NPC", npc_id);
        }
        else if (npc->long_desc == NULL)
        {
            sprintf(str, "%s does not have a description", npc_id);
        }
        else
        {
            sprintf(str, "%s", npc->long_desc);
        }
    }
    return str;
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
        room_t *room = find_room_from_game(game, npc->movement->track);
        if (npc->npc_battle != NULL && get_npc_hp(npc) <= 0)
        {
            sprintf(str, "%s's body is %s", npc->npc_id, room->short_desc);
        }
        else
        {
            sprintf(str, "%s is %s", npc->npc_id, room->short_desc);
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
    add_action_to_node(battle_node1, MOVE_ROOM, "harry move to outside");

    add_node(c, "2b", "Well, you are not welcome here. Catch me outside and "
             "I will show you no mercy.");
    node_t *battle_node2 = get_node(c->all_nodes, "2b");
    add_action_to_node(battle_node2, MOVE_ROOM, "harry move outside");

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
    add_action_to_node(hostile_node, MOVE_ROOM, "fiona move outside");

    add_node(c, "2b", "Fiona: I hope you have a good day too! Please, take my mace for good luck!");
    node_t *mace_node = get_node(c->all_nodes, "2b");
    add_action_to_node(mace_node, GIVE_ITEM, "mace");

    // Edges
    add_edge(c, "Let's have a fight.", "1", "2a", NULL);
    add_edge(c, "I am doing well, I hope you have a good day!", "1", "2b", NULL);

    return c;
}


/* Creates a sample convo for NPC wilma, taken from npc_example.c */
convo_t *create_sample_convo_wilma()
{
    // Starting to build the conversation structure
    convo_t *c = convo_new();

    // Nodes
    add_node(c, "1", "Wilma: Oh! hi! I'm Wilma!");
    node_t *node_1 = get_node(c->all_nodes, "1");
    add_action_to_node(node_1, PAUSE_MOVEMENT, "stop wilma");
    
    add_node(c, "2", "Wilma: Listen! I've had way way WAY too many coffees "
                      "today, so I insist you take this one I've just bought.");
    
    //add_node(c, "3", "Wilma: ");
    node_t *node_2 = get_node(c->all_nodes, "2");
    add_action_to_node(node_2, RESUME_MOVEMENT, "let wilma leave");

    // Edges
    add_edge(c, "Hello wilma!", "1", "2", NULL);

    return c;
}

/* Creates a sample convo for NPC Borja */
convo_t *create_sample_convo_borja()
{
    convo_t *c = convo_new();

    add_node(c, "1", "");
}



/* Defines a new CLI operation that removes 1 HP from the specified npc if they
 * are in the room, and their health is greater than their surrender_level */
char *attack_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    char *str = malloc(MAX_MSG_LEN);
    if (game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        sprintf(str, "Error! We need a loaded room to attack.");
    }
    else if (strcmp(game->curr_room->room_id, "outside") != 0)
    {
        sprintf(str, "It's not a good idea to start a fight in a Library, you should go outside.");
    }
    else if (tokens[1] == NULL)
    {
        sprintf(str, "You must identify someone to attack");
    }
    else
    {
        char *npc_id = tokens[1];
        case_insensitize(npc_id);
        npc_t *npc = get_npc_in_room(ctx->game->curr_room, npc_id);
        if (npc == NULL) 
        {
            sprintf(str, "No one by that name wants to fight here.");
        }
        else if (npc->hostility_level != HOSTILE || npc->npc_battle == NULL) 
        {
            sprintf(str, "%s does not want to fight", npc_id);
            return str;
        }
        else if (get_npc_hp(npc) <= 0)
        {
            sprintf(str, "There's no point in beating a dead horse.");
        }
        else if (npc->npc_battle->stats->hp <= npc->npc_battle->stats->surrender_level) 
        { 
            sprintf(str, "%s has surrendered. You can no longer attack them.",
                    npc->npc_id);
        }
        else
        {
            char *weapon_id = NULL;
            item_t *weapon = NULL;
            attribute_t *attack_att = NULL;
            int multiplier = 1;
            if (tokens[3] != NULL)
            {
                weapon_id = case_insensitized_string(tokens[3]);
                HASH_FIND(hh, game->curr_player->inventory, weapon_id, strlen(weapon_id), weapon);
                if (weapon != NULL)
                {
                    attack_att = get_attribute(weapon, "attack");
                    if ((attack_att != NULL) && (attack_att->attribute_tag == INTEGER))
                    {
                        multiplier = attack_att->attribute_value.int_val;
                    }
                    else
                    {
                        sprintf(str, "You cannot attack with this item");
                        return str;
                    }
                }
                else
                {
                    sprintf(str, "You do not have this item: %s", weapon_id);
                    return str;
                }
            }
            if (npc->npc_battle->stats->hp <= multiplier)
            {
                change_npc_hp(npc, (-1) * (npc->npc_battle->stats->hp));
                assert(transfer_all_npc_items(npc, game->curr_room) == SUCCESS);
                sprintf(str, "You killed %s. They've dropped their items, "
                        "which you can now take.", npc->npc_id);
            }
            else
            {
                change_npc_hp(npc, (-1) * multiplier);
                sprintf(str, "%s has lost %d HP. They now have %d HP left", 
                        npc->npc_id, multiplier, npc->npc_battle->stats->hp);
            }
        }
    }
    return str;
}

int create_crerar()
{
    // Let's make (a smol) Crerar!
    crerar_first = room_new("crerar lib floor 1",
                                    "on the first floor of Crerar Library",
                                    "The first floor of the John Crerar Library, "
                                    "head EAST to go outside, "
                                    "UP is the 2nd floor, where Room 209 is located, "
                                    "and SOUTH is the Peaches Cafe.");
    crerar_second = room_new("crerar lib floor 2",
                                     " on the second floor of Crerar Library",
                                     "The second floor of the John crerar Library, "
                                     "to the SOUTH lies Room 209, "
                                     "and DOWN is the first floor of Crerar");
    crerar_209 = room_new("room 209", "in Room 209 of Crerar Library",
                                  "This is Room 209 of the John Crerar Library, "
                                  "better known as Borja's Office. "
                                  "To the NORTH is the rest of second floor of Crerar.");
    peachs_cafe = room_new("peach's cafe", "in Peach's Cafe at University",
                                    "This is Peach's Cafe inside of the John Crerar "
                                    "Library, to the NORTH is the first floor of "
                                    "Crerar, and head EAST to go outside.");
    outside = room_new("outside", "outside of the John Crerar Library",
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

    return SUCCESS;
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

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);

    assert(create_crerar() == SUCCESS);

    assert(add_room_to_game(game, crerar_first) == SUCCESS);
    assert(add_room_to_game(game, crerar_second) == SUCCESS);
    assert(add_room_to_game(game, crerar_209) == SUCCESS);
    assert(add_room_to_game(game, outside) == SUCCESS);
    assert(add_room_to_game(game, peachs_cafe) == SUCCESS);

    game->curr_room = outside;
    game->start_desc = "You are outside of the John Crerar Library, LOOK "
                       "around for more.";

    /* Create a friendly npc */
    char *npc_id1 = "FIONA";
    class_t *class1 = generate_sample_class();
    npc_mov_t *movement1 = npc_mov_new(NPC_MOV_DEFINITE, NPC_MOV_ALLOWED,
                                       crerar_second->room_id, 0);
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

    item_t *mace = item_new("MACE", "This is mace.",
                              "This is mace, it does damage.");
    assert(add_attribute_to_hash(mace, int_attr_new("attack", 5)) == SUCCESS);
    agent_t *mace_ag = malloc(sizeof(agent_t));
    mace_ag->item = mace;
    assert(add_action(mace_ag, "take", "You now have some mace, use it wisely",
                      "the MACE could not be taken") == SUCCESS);
    add_item_to_npc(friendly_fiona, mace);

    /* Add dialogue to conditional-friendly npc */
    convo_t *c_fiona = create_sample_convo_fiona();
    add_convo_to_npc(friendly_fiona, c_fiona);


    /* Create a hostile npc */
    char *npc_id2 = "HARRY";
    class_t *class2 = generate_sample_class();
    npc_mov_t *movement2 = npc_mov_new(NPC_MOV_DEFINITE, NPC_MOV_ALLOWED,
                                       peachs_cafe->room_id, 0);
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


    npc_mov_t *movement3 = npc_mov_new(NPC_MOV_INDEFINITE, NPC_MOV_ALLOWED,
                                       outside->room_id, 5);
    extend_path_indefinite(movement3, peachs_cafe->room_id, 5);
    extend_path_indefinite(movement3, crerar_first->room_id, 5);
    extend_path_indefinite(movement3, crerar_second->room_id, 5);
    extend_path_indefinite(movement3, crerar_209->room_id, 5);
    wandering_wilma = npc_new("wilma", "wandering wilma is friendly",
     "wandering wilma is just a jolly good fellow who likes to wander between"
     "rooms", class2, movement3, FRIENDLY);
    convo_t *c_wilma = create_sample_convo_wilma();
    assert(add_convo_to_npc(wandering_wilma, c_wilma) == SUCCESS);
    

    npc_mov_t *sonic_mov = npc_mov_new(NPC_MOV_INDEFINITE, NPC_MOV_ALLOWED,
                                       outside->room_id, 1);
    class_t *sonic_class = generate_sample_class();
    sonic_class->base_stats = NULL;
    stats_global_t *global_speed = stats_global_new("speed", 10000);
    stats_t *sonic_speed = stats_new(global_speed, 5000);
    HASH_ADD(hh, sonic_class->base_stats, key, strlen(sonic_speed->key), sonic_speed);
/*    extend_path_indefinite(sonic_mov, peachs_cafe->room_id, 2);
    extend_path_indefinite(sonic_mov, crerar_first->room_id, 2);
    extend_path_indefinite(sonic_mov, crerar_second->room_id, 2);
    extend_path_indefinite(sonic_mov, crerar_209->room_id, 1); */
    speedy_sonic = npc_new("sonic", "sonic the hedgehog",
                           "sonic the hedgehog is very fast",
                           sonic_class, sonic_mov, FRIENDLY);
    assert(auto_gen_movement(speedy_sonic, get_all_rooms(game)) == SUCCESS);

    npc_mov_t *borja_mov = npc_mov_new(NPC_MOV_DEFINITE, NPC_MOV_ALLOWED,
                                       crerar_209->room_id, 0);
    extend_path_definite(borja_mov, peachs_cafe->room_id);
    extend_path_definite(borja_mov, outside->room_id);
    brainy_borja = npc_new("borja", "Professor Borja Sotomayor",
                           "Borja Sotomayor is an Associate Senior "
                           "Instructional Professor in the Department of "
                           "Computer Science, where he teaches intro CS, "
                           "software development, computer networks, and "
                           "distributed systems.", class2, borja_mov,
                           CONDITIONAL_FRIENDLY);
    stat_t *borja_stats = create_enemy_stats();
    borja_stats->hp = 1000;
    borja_stats->max_hp = 1000;
    assert(add_battle_to_npc(brainy_borja, borja_stats, NULL, BATTLE_AI_RANDOM,
            CONDITIONAL_FRIENDLY, NULL, NULL, NULL, NULL, NULL) == SUCCESS);

    
    npc_mov_t *peachs_barista_mov = npc_mov_new(NPC_MOV_DEFINITE, NPC_MOV_RESTRICTED,
                                                peachs_cafe->room_id, 0);
    peachs_barista = npc_new("peach's barista", "The barista / cashier at Peach's Cafe",
                             "This is the barista at Peach's on University inside "
                             "of the John Crerar Library, you can ",
                             class2, peachs_barista_mov, FRIENDLY);


    /* Add the npcs to the game */
    assert(add_npc_to_game(game, friendly_fiona) == SUCCESS);
    assert(add_npc_to_game(game, hostile_harry) == SUCCESS);
    assert(add_npc_to_game(game, wandering_wilma) == SUCCESS);
    assert(add_npc_to_game(game, speedy_sonic) == SUCCESS);
    assert(add_npc_to_game(game, brainy_borja) == SUCCESS);

    /* Add the npcs to their rooms */
    assert(add_all_npcs_to_their_rooms(game) == SUCCESS);

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
    add_entry("ATTACK", attack_operation, NULL, ctx->cli_ctx->table);
    add_entry("FIND", find_npc_operation, NULL, ctx->cli_ctx->table);
    add_entry("WHO", who_is_npc_operation, NULL, ctx->cli_ctx->table);

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

