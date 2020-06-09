#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "game-state/room.h"
#include "npc/rooms-npc.h"
#include "quests/quests_state.h"

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
    "     |   /                         EXAMPLE PROGRAM - RPG-NPC TEAM                               /\n"
    "     \\_/______________________________________________________________________________________/\n";

quest_t *quest;
npcs_in_room_t *npcs_in_room_1;
npcs_in_room_t *npcs_in_room_3;
npc_mov_t *npc1_movement;

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to this sample game of Chiventure!");

    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    room_t *room3 = room_new("room3", "This is room 3", "Exactly, this is the third room.");
    room_t *room4 = room_new("room4", "This is room 4", "Yes, this is the fourth room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    add_room_to_game(game, room4);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");
    create_connection(game, "room2", "room3", "EAST");
    create_connection(game, "room3", "room4", "EAST");

    item_t *emerald = item_new("EMERALD","It is an emerald",
                              "This item must be taken for the first mission. Steal it!");
    add_item_to_room(room2, emerald);

    item_t *POTION = item_new("POTION","It is a bottle that holds a mysterious liquid",
                              "This item must be taken for second mission. Drink it!");
    add_item_to_room(room4, POTION);

    add_action(emerald, "STEAL", "[You take the Emerald] "
                        "This is the object that the villager was talking about!",
                "You can't pickup the emerald.");

    add_action(POTION, "SIP", "[You sip the Potion] Suddenly you realize how you got here.",
                "You can't drink the POTION.");
    
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}


/* Defines a new CLI operation that starts a quest by giving a hint */
char *start_quest_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! You start a quest if you're not in a room!\n";
    }

    if(tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    start_quest(quest);

    if(quest->status == 1)
    {
        return "You have started the quest. Begin by speaking to the villager over there.";
    }
    else
    {
        return "Failed to start the quest";
    }
}

char *talk_to_npc(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
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

    if (((strcmp(ctx->game->curr_room->room_id,"room1")) == 0) && ((get_quest_status(quest)) == 1))
    {
        move_npc_definite(npc1_movement);
        char* id = strcpy(id,npc1_movement->npc_id);
        char *output1 = strcat(id,
        ": I see you have started the quest, go to room2 to find the secret item, then "
            "come meet me in room3 to complete the first mission.");
        return output1;
    }
    else if (((strcmp(ctx->game->curr_room->room_id,"room3")) == 0) && ((get_quest_status(quest)) == 1))
    {
        //move_npc_definite(npc1_movement);
        item_t *item = malloc(sizeof(item_t));
        HASH_FIND(hh, ctx->game->all_items, "EMERALD", strlen("EMERALD"), item);

        npc_t *npc = malloc(sizeof(npc_t));
        HASH_FIND(hh, npcs_in_room_1->npc_list, "Villager-Jim", strlen("Villager-Jim"), npc);

        //complete_achievement(quest, item, npc);
        quest->achievement_list->achievement->completed = 1;
        quest->status = 2;
        char* id1 = strcpy(id1,npc1_movement->npc_id);
        char *output2 = strcat(id1,": Congratulations on completing "
                    "the first achievement of this quest. "
                    "Now onto the next, continue through that door into the next room "
                    "to continue.");

        return output2;
    }
    else if (((strcmp(ctx->game->curr_room->room_id,"room4")) == 0) && ((get_quest_status(quest)) == 2))
    {
        item_t *item = malloc(sizeof(item_t));
        HASH_FIND(hh, ctx->game->all_items, "POTION", strlen("POTION"), item);

        npc_t *npc = malloc(sizeof(npc_t));
        HASH_FIND(hh, npcs_in_room_1->npc_list, "Villager-Jim", strlen("Villager-Jim"), npc);

        quest->achievement_list->next->achievement->completed = 1;

        if ((is_quest_completed(quest)) == 1)
        {
            item_t *reward = complete_quest(quest);
            add_item_to_player(ctx->game->curr_player, reward);
            char* id2 = strcpy(id2,npc1_movement->npc_id);
            char* output3 = strcat(id2, ": Congratulations"
            " on completing the quest, your reward is a key that should "
            "help you on your adventure. You will find it in your inventory.");
            return output3;
        }
        else
        {
            return "So close yet so far";
        }
    }
    else
    {
        return "There is no one to talk to!";
    }
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();
    
    object_t *obj = obj_t_str("Villager-Jim", "lua");
    npc_t *npc1 = npc_new(obj,"first npc","this is the npc that holds the quest",
                          100,NULL);
    npcs_in_room_1 = npcs_in_room_new("room1");
    add_npc_to_room(npcs_in_room_1, npc1);
    npcs_in_room_3 = npcs_in_room_new("room3");

    room_t *initial_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room1", strlen("room1"), initial_room);

    room_t *third_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room3", strlen("room3"), third_room);

    room_t *last_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room4", strlen("room4"), last_room);

    npc1_movement = npc_mov_new("Villager-Jim",NPC_MOV_DEFINITE,initial_room);
    extend_path_definite(npc1_movement,third_room);
    extend_path_definite(npc1_movement,last_room);

    item_t *item1 = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "EMERALD", strlen("EMERALD"), item1);

    item_t *item2 = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "POTION", strlen("POTION"), item2);

    item_t *reward = item_new("KEY", "this is a key that unlocks all secrets",
    "Reward for completing the quest.");
    quest = quest_new(1, NULL, reward);
    mission_t *mission1 = mission_new(item1,npc1);
    mission_t *mission2 = mission_new(item2,npc1);
    achievement_t *achievement1 = achievement_new(mission1);
    achievement_t *achievement2 = achievement_new(mission2);
    add_achievement_to_quest(quest, achievement1);
    add_achievement_to_quest(quest, achievement2);

    add_entry("QUEST", start_quest_operation, NULL, ctx->table);

    add_entry("TALK", talk_to_npc, NULL, ctx->table);

    action_type_t steal_action = {"STEAL", ITEM};
    add_entry(steal_action.c_name, kind1_action_operation, &steal_action, ctx->table);

    action_type_t drink_action = {"SIP", ITEM};
    add_entry(drink_action.c_name, kind1_action_operation, &drink_action, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
