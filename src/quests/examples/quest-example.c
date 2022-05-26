// #include <stdio.h>
// #include <cli/operations.h>
// #include "common/ctx.h"
// #include "ui/ui.h"
// #include "game-state/room.h"
// #include "game-state/stats.h"
// #include "npc/rooms-npc.h"
// #include "quests/quests_state.h"

// const char *banner =
//     "    ________________________________________________________________________________________\n"
//     "  / \\                                                                                      \\\n"
//     " |   |                                                                                      |\n"
//     "  \\_ |     ██████╗██╗  ██╗██╗██╗   ██╗███████╗███╗   ██╗████████╗██╗   ██╗██████╗ ███████╗  |\n"
//     "     |    ██╔════╝██║  ██║██║██║   ██║██╔════╝████╗  ██║╚══██╔══╝██║   ██║██╔══██╗██╔════╝  |\n"
//     "     |    ██║     ███████║██║██║   ██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║██████╔╝█████╗    |\n"
//     "     |    ██║     ██╔══██║██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ██║   ██║██╔══██╗██╔══╝    |\n"
//     "     |    ╚██████╗██║  ██║██║ ╚████╔╝ ███████╗██║ ╚████║   ██║   ╚██████╔╝██║  ██║███████╗  |\n"
//     "     |     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝  |\n"
//     "     |     _________________________________________________________________________________|_____\n"
//     "     |    /                                                                                      /\n"
//     "     |   /                         EXAMPLE PROGRAM - RPG-QUESTS TEAM                            /\n"
//     "     \\_/______________________________________________________________________________________/\n";


// player_t *player;
// quest_t *quest;
// npcs_in_room_t *npcs_in_room_1;
// npcs_in_room_t *npcs_in_room_4;
// npc_mov_t *npc1_movement;

// /* Creates a sample in-memory game */
// chiventure_ctx_t *create_sample_ctx()
// {
//     game_t *game = game_new("Welcome to this sample game of Chiventure!");

//     /* Create four rooms. room1 is the initial room */
//     room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
//     room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
//     room_t *room3 = room_new("room3", "This is room 3", "Exactly, this is the third room.");
//     room_t *room4 = room_new("room4", "This is room 4", "Yes, this is the fourth room.");
//     add_room_to_game(game, room1);
//     add_room_to_game(game, room2);
//     add_room_to_game(game, room3);
//     add_room_to_game(game, room4);
//     game->curr_room = room1;
//     create_connection(game, "room1", "room2", "NORTH");
//     create_connection(game, "room2", "room3", "EAST");
//     create_connection(game, "room3", "room4", "EAST");

//     item_t *emerald = item_new("EMERALD","It is an emerald",
//                               "This item must be taken for the first mission. Steal it!");
//     add_item_to_room(room2, emerald);

//     item_t *POTION = item_new("POTION","It is a bottle that holds a mysterious liquid",
//                               "This item must be taken for second mission. Drink it!");
//     add_item_to_room(room4, POTION);

//     add_action(emerald, "STEAL", "[You take the Emerald] "
//                         "This is the object that the villager was talking about!",
//                 "You can't pickup the emerald.");

//     add_action(POTION, "SIP", "[You sip the Potion] Suddenly you realize how you got here.",
//                 "You can't drink the POTION.");
    
//     chiventure_ctx_t *ctx = chiventure_ctx_new(game);

//     return ctx;
// }


// /* Defines a new CLI operation that starts a quest by giving a hint */
// char *start_quest_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
// {
//     game_t *game = ctx->game;
//     if(game == NULL || game->curr_room == NULL)
//     {
//         return "Room not found! Error! You start a quest if you're not in a room!\n";
//     }

//     if(tokens[1] != NULL)
//     {
//         return "I do not know what you mean.";
//     }

//     int started = start_quest(quest);

//     if(can_start_quest(quest, player) == 0)
//     {
//         return "You cannot start the quest yet! You are underleveled or don't have enough health.";
//     }

//     if(quest->status == 1)
//     {
//         return "You have started the quest. Begin by speaking to the villager over there.";
//     }
//     else
//     {
//         return "Failed to start the quest";
//     }
// }

// char *talk_to_npc(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
// {

//     game_t *game = ctx->game;
//     if (game == NULL || game->curr_room == NULL)
//     {
//         return "Room not found! Error!\n";
//     }

//     /* This operation has to be called with one parameter */
//     if (tokens[1] != NULL)
//     {
//         return "I do not know what you mean.";
//     }

//     if (((strcmp(ctx->game->curr_room->room_id,"room1")) == 0) && ((quest->status == 1))) {
//         move_npc_mov(npc1_movement);

//         char *output1 = strcat("Villager-Jim",
//         ": I see you have started the quest, go to room2 to find the secret item, then "
//             "come meet me in room3 to complete the first mission.");
//         return output1;
//     } else if (((strcmp(ctx->game->curr_room->room_id,"room2")) == 0) && ((quest->status == 1))) {
//         char *output2 = "Please find the secret item here.";
//         return output2;
//     } else if ((strcmp(ctx->game->curr_room->room_id,"room3") == 0) && (quest->status == 1)) {
//         //move_npc_mov(npc1_movement);
//         item_t *item = malloc(sizeof(item_t));
//         HASH_FIND(hh, ctx->game->all_items, "EMERALD", strlen("EMERALD"), item);

//         npc_t *npc = malloc(sizeof(npc_t));
//         HASH_FIND(hh, npcs_in_room_1->npc_list, "Villager-Jim", strlen("Villager-Jim"), npc);

//         //complete_task(quest, item, npc);
//         quest->task_tree->task->completed = 1;
//         quest->status = 2;

//         char *output3 = strcat("Villager-Jim",": Congratulations on completing "
//                     "the first task of this quest. "
//                     "Now onto the next, continue through that door into the next room "
//                     "to continue.");

//         return output3;
//     } else if ((strcmp(ctx->game->curr_room->room_id,"room4") == 0) && (quest->status == 2)) {
//         item_t *item = malloc(sizeof(item_t));
//         HASH_FIND(hh, ctx->game->all_items, "POTION", strlen("POTION"), item);

//         npc_t *npc = malloc(sizeof(npc_t));
//         HASH_FIND(hh, npcs_in_room_1->npc_list, "Villager-Jim", strlen("Villager-Jim"), npc);

//         quest->task_tree->lmostchild->task->completed = 1;

//         if ((is_quest_completed(quest)) == 1)
//         {
//             reward_t *reward = complete_quest(quest);
//             add_item_to_player(ctx->game->curr_player, reward->item);
//             change_xp(ctx->game->curr_player, reward->xp);

//             char* output3 = strcat("Villager-Jim", ": Congratulations"
//             " on completing the quest, your reward is a key that should "
//             "help you on your adventure. You will find it in your inventory.");
//             return output3;
//         }
//         else
//         {
//             return "So close yet so far";
//         }
//     }
//     else
//     {
//         return "There is no one to talk to!";
//     }
// }

// /* Get a big reward for finishing all the passive quests */
// quest_t *make_passive_quest(char *quest_id, reward_t *reward, stat_req_t *stat_req)
// {
//     quest_t *quest = quest_new(quest_id, NULL, reward, stat_req);

//     passive_mission_t *p_mission1 = passive_mission_new(50, 1000000, 1000000);
//     passive_mission_t *p_mission2 = passive_mission_new(100, 1000000, 1000000);
//     passive_mission_t *p_mission3 = passive_mission_new(150, 1000000, 1000000);

//     mission_t *fifty_xp;
//     fifty_xp->a_mission = NULL;
//     fifty_xp->p_mission = p_mission1;

//     mission_t *hundred_xp;
//     hundred_xp->a_mission = NULL;
//     hundred_xp->p_mission = p_mission2;

//     mission_t *hundred_fifty_xp;
//     hundred_fifty_xp->a_mission = NULL;
//     hundred_fifty_xp->p_mission = p_mission3;

//     task_t *task1 = task_new(fifty_xp, "Get 50 xp", NULL);
//     task_t *task2 = task_new(hundred_xp, "Get 100 xp", NULL);
//     task_t *task3 = task_new(hundred_fifty_xp, "Get 150 xp", NULL);

//     add_task_to_quest(quest, task1, "The first mission");
//     add_task_to_quest(quest, task2, "Get 50 xp");
//     add_task_to_quest(quest, task3, "Get 100 xp");

//     return quest;
// }

// quest_t *make_sample_quest(char *quest_id, reward_t *reward, stat_req_t *stat_req,
//                            npc_t *npc1, npc_t *npc2, item_t *item1, item_t *item2,
//                            room_t *room3, room_t *room4)
// {
//     quest_t *quest = quest_new(quest_id, NULL, reward, stat_req);

//     active_mission_t *a_mission1 = active_mission_new(NULL, npc1, NULL, NULL);
//     active_mission_t *a_mission2 = active_mission_new(item1, NULL, NULL, room3);
//     active_mission_t *a_mission3 = active_mission_new(NULL, NULL, NULL, room4);
//     active_mission_t *a_mission4 = active_mission_new(item2, NULL, npc2, NULL); //outcome 1 (slay wolf, get potion)
//     active_mission_t *a_mission5 = active_mission_new(NULL, NULL, NULL, NULL); //outcome 2 (die to wolf)
//     active_mission_t *a_mission6 = active_mission_new(NULL, NULL, npc2, NULL); //outcome 3 (negotiate with wolf)

//     mission_t *meet_npc;
//     meet_npc->a_mission = a_mission1;
//     meet_npc->p_mission = NULL;

//     mission_t *get_emerald;
//     get_emerald->a_mission = a_mission2;
//     get_emerald->p_mission = NULL;

//     mission_t *go_to_room4;
//     go_to_room4->a_mission = a_mission3;
//     go_to_room4->p_mission = NULL;

//     mission_t *fight_wolf;
//     fight_wolf->a_mission = a_mission4;
//     fight_wolf->p_mission = NULL;

//     mission_t *die_to_wolf;
//     die_to_wolf->a_mission = a_mission5;
//     die_to_wolf->p_mission = NULL;

//     mission_t *negotiate;
//     negotiate->a_mission = a_mission6;
//     negotiate->p_mission = NULL;


//     task_t *task1 = task_new(meet_npc, "Meet the NPC quest giver", NULL);
//     task_t *task2 = task_new(get_emerald, "Get the emerald", NULL);
//     task_t *task3 = task_new(go_to_room4, "Go to room 4", NULL);
//     task_t *task4 = task_new(fight_wolf, "Fight the wolf", NULL);
//     task_t *task5 = task_new(die_to_wolf, "Die to wolf", NULL);
//     task_t *task6 = task_new(negotiate, "Negotiate with wolf", NULL);

//     add_task_to_quest(quest, task1, "The first mission");
//     add_task_to_quest(quest, task2, "Meet the NPC quest giver");
//     add_task_to_quest(quest, task3, "Get the emerald");
//     add_task_to_quest(quest, task4, "Go to room 4");
//     add_task_to_quest(quest, task5, "Go to room 4");
//     add_task_to_quest(quest, task6, "Go to room 4");

//     return quest;
// }

// int main(int argc, char **argv)
// {
//     chiventure_ctx_t *ctx = create_sample_ctx();

//     room_t *initial_room;
//     HASH_FIND(hh, ctx->game->all_rooms, "room1", strlen("room1"), initial_room);

//     room_t *second_room;
//     HASH_FIND(hh, ctx->game->all_rooms, "room2", strlen("room2"), second_room);

//     room_t *third_room;
//     HASH_FIND(hh, ctx->game->all_rooms, "room3", strlen("room3"), third_room);

//     room_t *last_room;
//     HASH_FIND(hh, ctx->game->all_rooms, "room4", strlen("room4"), last_room);

//     char *npc_id = "Villager-Jim";
//     npc_t *npc1 = npc_new(npc_id,"first npc","this is the npc that holds the quest",
//                           NULL, NULL, false);

//     char *npc_id2 = "Big Bad Wolf";
//     npc_t *npc2 = npc_new(npc_id2, "second npc", "this is the npc to kill", NULL, NULL, true);

//     npcs_in_room_1 = npcs_in_room_new("room1");
//     add_npc_to_room(npcs_in_room_1, npc1);
//     npcs_in_room_4 = npcs_in_room_new("room4");
//     add_npc_to_room(npcs_in_room_4, npc2); //Need to fight the wolf to get potion

//     npc1_movement = npc_mov_new(NPC_MOV_DEFINITE,initial_room, 0);
//     extend_path_definite(npc1_movement,third_room);
//     extend_path_definite(npc1_movement,last_room);


//     reward_t *reward_if_kill = reward_new(50, item_new("KEY", "this is a key that unlocks all secrets",
//     "Reward for completing the quest."));
//     reward_t *reward_if_negotiate = reward_new(100, NULL);

//     item_t *item1 = malloc(sizeof(item_t));
//     HASH_FIND(hh, ctx->game->all_items, "EMERALD", strlen("EMERALD"), item1);

//     item_t *item2 = malloc(sizeof(item_t));
//     HASH_FIND(hh, ctx->game->all_items, "POTION", strlen("POTION"), item2);

//     stat_req_t *stat_req = stat_req_new(5, 2);

//     quest_t *quest = make_sample_quest("Quest 0", reward_if_kill, stat_req, npc1, npc2, item1, item2, third_room, last_room);

//     reward_t *reward_passive = reward_new(0, item_new("Portal Gun", "this gun can create portals on special walls",
//     "Reward for completing passive missions."));

//     stat_req_t *stat_req_passive = stat_req_new(0, 0);
//     quest_t *quest_passive = make_passive_quest("Quest 1", reward_passive, stat_req_passive);
//     /*quest layout: start in room1 -> go to room2 -> go to room3 -> get emerald -> go to room4 -> fight wolf and WIN -> get potion -> meet npc for reward
//                                                                                                 / |
//                                                                                                /  |
//                                                                                               /   v
//                                                                                              /    fight wolf and lose -> die
//                                                                                             |
//                                                                                             |
//                                                                                             v
//                                                                                             negotiate with wolf and wolf takes potion -> npc gives xp instead  */
    


//     add_entry("QUEST", start_quest_operation, NULL, ctx->cli_ctx->table);

//     add_entry("TALK", talk_to_npc, NULL, ctx->cli_ctx->table);

//     action_type_t steal_action = {"STEAL", ITEM};
//     add_entry(steal_action.c_name, kind1_action_operation, &steal_action, ctx->cli_ctx->table);

//     action_type_t drink_action = {"SIP", ITEM};
//     add_entry(drink_action.c_name, kind1_action_operation, &drink_action, ctx->cli_ctx->table);

//     /* Start chiventure */
//     start_ui(ctx, banner);

//     game_free(ctx->game);

//     return 0;
// }

int main(int argc, char **argv) {
    return 0;
}
