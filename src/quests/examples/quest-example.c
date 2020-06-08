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
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");
    create_connection(game, "room2", "room3", "EAST");

    item_t *emerald = item_new("EMERALD","It is an emerald",
                              "This item must be taken for the quest. Steal it!");
    add_item_to_room(room2, emerald);

    add_action(emerald, "STEAL", "This is the object that the villager was talking about!",
                "You can't pickup the emerald.");
    
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
        return "Room not found! Error! Look for Jim if you're not in a room!\n";
    }

    /* This operation has to be called with one parameter */
    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    if (((strcmp(ctx->game->curr_room->room_id,"room1")) == 0) && ((get_quest_status(quest)) == 1))
    {
        move_npc_definite(npc1_movement);
        char *output1 = strcat(npc1_movement->npc_id,
        ": I see you have started the quest, go to room2 to find the secret item, then "
            "come meet me in room3 to complete the quest, and claim your reward.");
        return output1;
    }
    else if (((strcmp(ctx->game->curr_room->room_id,"room3")) == 0) && ((get_quest_status(quest)) == 1))
    {
        item_t *item = malloc(sizeof(item_t));
        HASH_FIND(hh, ctx->game->all_items, "EMERALD", strlen("EMERALD"), item);

        npc_t *npc = malloc(sizeof(npc_t));
        HASH_FIND(hh, npcs_in_room_1->npc_list, "npc1", strlen("npc1"), npc);

        //complete_achievement(quest, item, npc);
        quest->achievement_list->achievement->completed = 1;
        quest->status = 2;

        if ((is_quest_completed(quest)) == 1)
        {
            item_t *reward = complete_quest(quest);
            add_item_to_player(ctx->game->curr_player, reward);
            char *output2 = strcat(npc1_movement->npc_id,": Congratulations"
            " on completing the quest, your reward is a key that should "
            "help you on your adventure. You will find it in your inventory.");
            return output2;
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
    
    npc_t *npc1 = npc_new("npc1","first npc","this is the npc that holds the quest",
                          100,NULL);
    npcs_in_room_1 = npcs_in_room_new("room1");
    add_npc_to_room(npcs_in_room_1, npc1);
    npcs_in_room_3 = npcs_in_room_new("room3");

    room_t *initial_room = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_rooms, "room1", strlen("room1"), initial_room);

    room_t *final_room = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_rooms, "room3", strlen("room3"), final_room);

    npc1_movement = npc_mov_new("npc1",NPC_MOV_DEFINITE,initial_room);
    extend_path_definite(npc1_movement,final_room);

    item_t *item = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "EMERALD", strlen("EMERALD"), item);

    item_t *reward = item_new("KEY", "this is a key that unlocks all secrets",
    "Reward for completing the quest.");
    quest = quest_new(1, NULL, reward);
    mission_t *mission = mission_new(item,npc1);
    achievement_t *achievement = achievement_new(mission);
    add_achievement_to_quest(quest, achievement);

    add_entry("QUEST", start_quest_operation, NULL, ctx->table);

    add_entry("TALK", talk_to_npc, NULL, ctx->table);


    action_type_t steal_action = {"STEAL", ITEM};
    add_entry(steal_action.c_name, kind1_action_operation, &steal_action, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
