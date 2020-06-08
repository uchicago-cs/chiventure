#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "game-state/room.h"
#include "npc/rooms-npc.h"
#include "quests/quests_state.h"

const char *banner =
    "    ________________________________________________________________________________________\n"
    "  / \\                                                                                       \\\n"
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

typedef struct revised_chiventure_ctx {
    chiventure_ctx_t *ctx;
    npcs_in_room_t *npcs_in_room1;
    npcs_in_room_t *npcs_in_room2;
    npcs_in_room_t *npcs_in_room3;
    quest_t *quest;
} revised_chiventure_ctx_t;

typedef char *revised_operation(char *tokens[TOKEN_LIST_SIZE], revised_chiventure_ctx_t *revised_ctx);

// Lookup entry for hashtable, using uthash.
typedef struct revised_lookup_entry
{
    char *name; // key
    revised_operation *operation_type;
    action_type_t *action;
    UT_hash_handle hh;
} revised_lookup_t;


void revised_add_entry(char *command_name, revised_operation *associated_operation, action_type_t *action, revised_lookup_t **table)
{
    revised_lookup_t *t = malloc(sizeof(revised_lookup_t));
    char *newname = malloc(sizeof(char) * (strlen(command_name) + 1));
    strcpy(newname, command_name);
    t->name = newname;
    t->operation_type = associated_operation;
    t->action = action;
    HASH_ADD_KEYPTR(hh, *table, t->name, strlen(t->name), t);
}

revised_chiventure_ctx_t *revised_ctx_new(chiventure_ctx_t *ctx, npcs_in_room_t *room1,npcs_in_room_t *room2,
                                            npcs_in_room_t *room3, quest_t *quest)
{
    revised_chiventure_ctx_t *revised_ctx = malloc(sizeof(revised_chiventure_ctx_t));
    revised_ctx->ctx = ctx;
    revised_ctx->npcs_in_room1 = room1;
    revised_ctx->npcs_in_room2 = room2;
    revised_ctx->npcs_in_room3 = room3;
    revised_ctx->quest = quest;

    return revised_ctx;
}

/* Creates a sample in-memory game */
revised_chiventure_ctx_t *create_sample_ctx()
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
                              "This item must be collected for the quest");
    add_item_to_room(room2, emerald);

    add_action(emerald, "STEAL", "This is the object that the vilalger was talking about!",
                "You can't pickup the emerald.");


    npc_t *npc1 = npc_new("npc1","first npc","this is the npc that holds the quest",
                          100,NULL);
    npcs_in_room_t *npcs_in_room_1 = npcs_in_room_new("room1");
    add_npc_to_room(npcs_in_room_1,npc1);
    //MERGE THIS TO ACTUALLY AN NPC IN A ROOM

    npcs_in_room_t *npcs_in_room_2 = npcs_in_room_new("room2");
    //MERGE THIS TO ACTUALLY AN NPC IN A ROOM

    npcs_in_room_t *npcs_in_room_3 = npcs_in_room_new("room3");

    /* to create a quest */
    item_t *reward = item_new("KEY", "this is a key that unlocks all secrets",
    "Reward for completing the quest.");
    quest_t *quest = quest_new(1, NULL, reward);
    mission_t *mission = mission_new(emerald,npc1);
    achievement_t *achievement = achievement_new(mission);
    add_achievement_to_quest(quest, achievement);

    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    revised_chiventure_ctx_t *revised_ctx = revised_ctx_new(ctx, npcs_in_room_1, npcs_in_room_2,
                                            npcs_in_room_3, quest);

    return revised_ctx;
}


/* Defines a new CLI operation that starts a quest by giving a hint */
char *start_quest_operation(char *tokens[TOKEN_LIST_SIZE], revised_chiventure_ctx_t *revised_ctx)
{
    game_t *game = revised_ctx->ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! You start a quest if you're not in a room!\n";
    }

    if(tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    start_quest(revised_ctx->quest);

    if(revised_ctx->quest->status == 1)
    {
        return "You have started the quest. Begin by speaking to the villager over there.";
    }
    else
    {
        return "Failed to start the quest";
    }
}

char *talk_to_npc1(char *tokens[TOKEN_LIST_SIZE], revised_chiventure_ctx_t *revised_ctx)
{
    game_t *game = revised_ctx->ctx->game;
    if (game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! Look for Jim if you're not in a room!\n";
    }

    /* This operation has to be called with one parameter */
    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    //revised_ctx->ctx->game->curr_room->room_id;

    return "Villager: I see you have started the quest, go to room2 to find the secret item, then "
            "come meet me in room3 to complete the quest, and claim your reward.";
}

char *talk_to_npc2(char *tokens[TOKEN_LIST_SIZE], revised_chiventure_ctx_t *revised_ctx)
{
    game_t *game = revised_ctx->ctx->game;
    if (game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! Look for Jim if you're not in a room!\n";
    }

    /* This operation has to be called with one parameter */
    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }

    if ((get_quest_status(revised_ctx->quest)) == 1)
    {
        item_t *item;
        HASH_FIND(hh, game->all_items, "EMERALD", strlen("EMERALD"), item);

        npc_t *npc;
        HASH_FIND(hh, revised_ctx->npcs_in_room1->npc_list, "npc1", strlen("npc1"), npc);

        complete_achievement(revised_ctx->quest, item, npc);

        if ((is_quest_completed(revised_ctx->quest)) == 1)
        {
            item_t *reward = complete_quest(revised_ctx->quest);
            add_item_to_player(revised_ctx->ctx->game->curr_player, reward);
            return "Villager: Congratulations on completing the quest, your reward is a key that should "
                "help you on your adventure. You will find it in your inventory.";
        }
        else
        {
            return "So close yet so far";
        }
    }
    else
        return "You have not completed the quest.";
}

int main(int argc, char **argv)
{
    revised_chiventure_ctx_t *revised_ctx = create_sample_ctx();

    revised_add_entry("QUEST", start_quest_operation, NULL, revised_ctx->ctx->table);

    revised_add_entry("TALK1", talk_to_npc1, NULL, revised_ctx->ctx->table);

    revised_add_entry("TALK2", talk_to_npc2, NULL, revised_ctx->ctx->table);

    action_type_t steal_action = {"STEAL", ITEM};
    add_entry(steal_action.c_name, kind1_action_operation, &steal_action, revised_ctx->ctx->table);

    /* Start chiventure */
    start_ui(revised_ctx->ctx, banner);

    game_free(revised_ctx->ctx->game);

    return 0;
}
