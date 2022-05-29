#include <stdio.h>
#include "action_management/action_structs.h"
#include "action_management/actionmanagement.h"
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "game-state/game.h"
#include "../src/custom-actions/include/interface.h"
#include "skilltrees/skilltree.h"
#include "game-state/room.h"
#include "playerclass/class.h"
#include "quests/quest.h"
#include "quests/quests_cli.h"

const char* banner =
" ▄▄▄       ▄████▄  ▄▄▄█████▓ ██▓ ▒█████   ███▄    █     ███▄ ▄███▓ ▄▄▄       ███▄    █  ▄▄▄        ▄████ ▓█████  ███▄ ▄███▓▓█████  ███▄    █ ▄▄▄█████▓\n"
"▒████▄    ▒██▀ ▀█  ▓  ██▒ ▓▒▓██▒▒██▒  ██▒ ██ ▀█   █    ▓██▒▀█▀ ██▒▒████▄     ██ ▀█   █ ▒████▄     ██▒ ▀█▒▓█   ▀ ▓██▒▀█▀ ██▒▓█   ▀  ██ ▀█   █ ▓  ██▒ ▓▒\n"
"▒██  ▀█▄  ▒▓█    ▄ ▒ ▓██░ ▒░▒██▒▒██░  ██▒▓██  ▀█ ██▒   ▓██    ▓██░▒██  ▀█▄  ▓██  ▀█ ██▒▒██  ▀█▄  ▒██░▄▄▄░▒███   ▓██    ▓██░▒███   ▓██  ▀█ ██▒▒ ▓██░ ▒░\n"
"░██▄▄▄▄██ ▒▓▓▄ ▄██▒░ ▓██▓ ░ ░██░▒██   ██░▓██▒  ▐▌██▒   ▒██    ▒██ ░██▄▄▄▄██ ▓██▒  ▐▌██▒░██▄▄▄▄██ ░▓█  ██▓▒▓█  ▄ ▒██    ▒██ ▒▓█  ▄ ▓██▒  ▐▌██▒░ ▓██▓ ░ \n"
" ▓█   ▓██▒▒ ▓███▀ ░  ▒██▒ ░ ░██░░ ████▓▒░▒██░   ▓██░   ▒██▒   ░██▒ ▓█   ▓██▒▒██░   ▓██░ ▓█   ▓██▒░▒▓███▀▒░▒████▒▒██▒   ░██▒░▒████▒▒██░   ▓██░  ▒██▒ ░ \n"
" ▒▒   ▓▒█░░ ░▒ ▒  ░  ▒ ░░   ░▓  ░ ▒░▒░▒░ ░ ▒░   ▒ ▒    ░ ▒░   ░  ░ ▒▒   ▓▒█░░ ▒░   ▒ ▒  ▒▒   ▓▒█░ ░▒   ▒ ░░ ▒░ ░░ ▒░   ░  ░░░ ▒░ ░░ ▒░   ▒ ▒   ▒ ░░   \n"
"  ▒   ▒▒ ░  ░  ▒       ░     ▒ ░  ░ ▒ ▒░ ░ ░░   ░ ▒░   ░  ░      ░  ▒   ▒▒ ░░ ░░   ░ ▒░  ▒   ▒▒ ░  ░   ░  ░ ░  ░░  ░      ░ ░ ░  ░░ ░░   ░ ▒░    ░    \n"
"  ░   ▒   ░          ░       ▒ ░░ ░ ░ ▒     ░   ░ ░    ░      ░     ░   ▒      ░   ░ ░   ░   ▒   ░ ░   ░    ░   ░      ░      ░      ░   ░ ░   ░      \n"
"      ░  ░░ ░                ░      ░ ░           ░           ░         ░  ░         ░       ░  ░      ░    ░  ░       ░      ░  ░         ░          \n"
"          ░                                                                                                                                           \n";

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    /* Create five rooms. room1 is the initial room */
    room_t *room1 = room_new("Ryerson 251", "This is Ryerson 251", 
                             "Ah, Ryerson. There's a CS class here. Only one exit north.");
    room_t *room2 = room_new("Borja's Office", "This is Borja's Office", 
                             "A neat(?) office for Borja. A rolex watch gleams on his desk. There are exits north and south.");
    room_t *room3 = room_new("Crerar 390", "This is Crerar 390", 
                             "The famed CS discussion room. There are exits south, east, and west.");
    room_t *room4 = room_new("Peach's", "This is Peach's Cafe", 
                             "Crerar's very own coffee shop There's a bar of soap in here, for some reason. Also, there is an exit west.");
    room_t *room5 = room_new("The Void", "This is the Void.", 
                             "A pulsing black hole in Crerar's basement. There is no escape. But there is... a trophy?");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    add_room_to_game(game, room4);
    add_room_to_game(game, room5);
    game->curr_room = room1;

    //room 1 connections
    create_connection(game, "Ryerson 251", "Borja's Office", "north");

    //room 2 connections
    create_connection(game, "Borja's Office", "Crerar 390", "north");
    create_connection(game, "Borja's Office", "Ryerson 251", "south");

    //room 3 connections
    create_connection(game, "Crerar 390", "Peach's", "east");
    create_connection(game, "Crerar 390", "The Void", "west");
    create_connection(game, "Crerar 390", "Borja's Office", "south");

    //room 4 connections
    create_connection(game, "Peach's", "Crerar 390", "west");    


    player_t *player = player_new("Borja");

    //creating stats
    stats_global_t *player_health = stats_global_new("max_health", 100);
    stats_t* player_health_stat = stats_new(player_health, 100);
    stats_global_t *player_intelligence = stats_global_new("intelligence", 9001);
    stats_t* player_intelligence_stat = stats_new(player_intelligence, 9001);
    stats_global_t *player_coding = stats_global_new("coding_skills", 5000);
    stats_t* player_coding_stat = stats_new(player_coding, 4999);
    stats_global_t *player_strength = stats_global_new("battle_strength", 10000);
    stats_t* player_strength_stat = stats_new(player_strength, 768);
    stats_global_t *player_charm = stats_global_new("charm", 5000);
    stats_t* player_charm_stat = stats_new(player_charm, 4000);

    //adding to player and game hashtables
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_health->name, strlen(player_health->name), player_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_health_stat->key, strlen(player_health_stat->key), player_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_intelligence->name, strlen(player_intelligence->name), player_intelligence);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_intelligence_stat->key, strlen(player_intelligence_stat->key), player_intelligence_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_coding->name, strlen(player_coding->name), player_coding);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_coding_stat->key, strlen(player_coding_stat->key), player_coding_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_strength->name, strlen(player_strength->name), player_strength);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_strength_stat->key, strlen(player_strength_stat->key), player_strength_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_charm->name, strlen(player_charm->name), player_charm);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_charm_stat->key, strlen(player_charm_stat->key), player_charm_stat);
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id, strlen(player->player_id), player);

    //Adding skills to skilltree and adding skilltree to class
    player->player_class = class_new("Vampire", "Vampire", "Feeds on Students",
                              NULL, NULL, NULL); //Add Stats Htbl to 2nd NULL?
    skill_t *skill1 = skill_new(1002, ACTIVE, "Teach", "Educate the blossoming new generation", 10, 100, NULL, NULL);
    skill_t *skill2 = skill_new(1002, ACTIVE, "Suck Blood", "No one knows how or when this happens", 10, 100, NULL, NULL);
    skill_t *skill3 = skill_new(1002, ACTIVE, "Code", "Develop a new Heroku App", 10, 100, NULL, NULL);
    skill_t *skill4 = skill_new(1002, ACTIVE, "Hire TA", "Spawn new senior software developers", 10, 100, NULL, NULL);
    skill_t *skill5 = skill_new(1002, ACTIVE, "Tweet", "Call on alums to complain about software developemnt", 10, 100, NULL, NULL);
    char **classes = malloc(sizeof(char*));
    classes[0] = "Borja";
    skill_node_t *skill_node1 = skill_node_new(skill1, 0, 0, classes, 0, 0);
    skill_node_t *skill_node2 = skill_node_new(skill2, 0, 0, classes, 0, 0);
    skill_node_t *skill_node3 = skill_node_new(skill3, 0, 0, classes, 0, 0);
    skill_node_t *skill_node4 = skill_node_new(skill4, 0, 0, classes, 0, 0);
    skill_node_t *skill_node5 = skill_node_new(skill5, 0, 0, classes, 0, 0);
    skill_tree_t *skill_tree = skill_tree_new(1001, "", 5);
    skill_tree_node_add(skill_tree, skill_node1);
    skill_tree_node_add(skill_tree, skill_node2);
    skill_tree_node_add(skill_tree, skill_node3);
    skill_tree_node_add(skill_tree, skill_node4);
    skill_tree_node_add(skill_tree, skill_node5);

    // add quests to player
    quest_t *quest1 = quest_new("Give your first lecture", NULL, NULL);
    quest_t *quest2 = quest_new("Perform vampire shenanigans", NULL, NULL);
    quest_t *quest3 = quest_new("Hold Wednesday Office Hours", NULL, NULL);
    task_t *task1 = task_new("Polish your teeth", NULL, NULL, NULL);
    task_t *task2 = task_new("Suck blood", NULL, NULL, NULL);
    task_t *task3 = task_new("Code", NULL, NULL, NULL);
    mission_t *mission2 = mission_new("Polish only your sharp teeth for that shine", COLLECT_ITEM);
    task1->mission = mission2;
    task_tree_t *task_tree1 = malloc(sizeof(task_tree_t));
    task_tree_t *task_tree2 = malloc(sizeof(task_tree_t));
    task_tree_t *task_tree3 = malloc(sizeof(task_tree_t));
    task_tree1->task = task1;
    task_tree2->task = task2;
    task_tree3->task = task3;
    task_tree1->parent = NULL;
    task_tree2->parent = task_tree1;
    task_tree3->parent = task_tree1;
    task_tree2->rsibling = task_tree3;
    task_tree3->rsibling = NULL;
    task_tree1->lmostchild = task_tree2;
    task_tree2->lmostchild = NULL;
    task_tree3->lmostchild = NULL;
    quest2->task_tree = task_tree1;

    HASH_ADD_KEYPTR(hh, game->all_quests, quest1->quest_id, strlen(quest1->quest_id), quest1);
    HASH_ADD_KEYPTR(hh, game->all_quests, quest2->quest_id, strlen(quest2->quest_id), quest2);
    HASH_ADD_KEYPTR(hh, game->all_quests, quest3->quest_id, strlen(quest3->quest_id), quest3);
    

    // add items to inventory
    item_t *sword = item_new("A sword", "A sword", "A sword");
    add_item_to_player(player, sword, game);

    item_t *laptop = item_new("Laptop ", "Laptop ", "Laptop ");
    add_item_to_player(player, laptop, game);

    item_t *glasses = item_new("Glasses", "Glasses",
                      "Jinkies Borja can't see without these");
    add_item_to_player(player, glasses, game);

    item_t *ring = item_new("Ring   ", "Ring   ", "Ring   ");
    add_item_to_player(player, ring, game);

    item_t *tape = item_new("Tape   ", "Tape   ", "Tape   ");
    add_item_to_player(player, tape, game);

    item_t *clock = item_new("Clock  ", "Clock  ", "Clock  ");
    add_item_to_player(player, clock, game);

    item_t *compass = item_new("Compass", "Compass", "Compass");
    add_item_to_player(player, compass, game);

    item_t *gum = item_new("Gum    ", "Gum    ", "Gum    ");
    add_item_to_player(player, gum, game);
    
    item_t *gas = item_new("Gas    ", "Gas    ", "Gas    ");
    add_item_to_player(player, gas, game);

    item_t *milk = item_new("Milk   ", "Milk   ", "Milk   ");
    add_item_to_player(player, milk, game);

    item_t *banana = item_new("Banana ", "Banana ", "Banana ");
    add_item_to_player(player, banana, game);

    item_t *pp_up = item_new("PP Up  ", "PP Up  ",
                    "It raises the PP of a selected move by 1/5 "
                    "of the move's base PP");
    add_item_to_player(player, pp_up, game);

    item_t *pp_max = item_new("PP Max ", "PP Max ", "PP Max ");
    add_item_to_player(player, pp_max, game);

    item_t *bands = item_new("Bands  ", "Bands  ", "Bands  ");
    add_item_to_player(player, bands, game);

    item_t *candy = item_new("Candy  ", "Candy  ", "Candy  ");
    add_item_to_player(player, candy, game);
    
    item_t *iron = item_new("Iron   ", "Iron   ", "Iron   ");
    add_item_to_player(player, iron, game);

    // add items to room
    item_t *soap = item_new("Soap", "Soap   ", "Soap   ");
    add_item_to_room(room4, soap);
    agent_t *s = (agent_t*)(malloc(sizeof(agent_t)));
    s->item = soap; 
    add_action(s, "take", "You take the soap. It has cleansed you.", "You do not take the soap.");

    item_t *rolex = item_new("Rolex", "Rolex  ", "Rolex  ");
    add_item_to_room(room2, rolex); 
    agent_t *r = (agent_t*)(malloc(sizeof(agent_t)));
    r->item = rolex; 
    add_action(r, "take", "You take Borja's watch. It looks better on you.", 
                              "You're not clean enough to touch Borja's watch. Is there soap around here?");

    item_t *end_item = item_new("Trophy", "Trophy ", "Trophy ");
    add_item_to_room(room5, end_item); 
    agent_t *ei = (agent_t*)(malloc(sizeof(agent_t)));
    ei->item = end_item; 
    add_action(ei, "take", "You take the trophy. You win the demo!", 
                              "You do not take the trophy. Loser.");
    
    player->player_class->skilltree = skill_tree;
    
    add_player_to_game(game, player);
    game->curr_player = player;

    // Add inventory conditions to game
    game_action_t *take_rolex = get_action(r, "take");
    add_action_inventory_condition(take_rolex, player, soap);

    game_action_t *take_trophy = get_action(ei, "take");
    add_action_inventory_condition(take_trophy, player, rolex);

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);
    game = ctx->game;
    
    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();


    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}