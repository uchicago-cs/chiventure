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
    "     |   /                         EXAMPLE PROGRAM - QUESTS TEAM                                /\n"
    "     \\_/______________________________________________________________________________________/\n";

quest_t *quest;
npcs_in_room_t *npcs_in_room_2;
npcs_in_room_t *npcs_in_room_3;
npcs_in_room_t *npcs_in_room_4;
npcs_in_room_t *npcs_in_room_5;
npc_t *npc1;
npc_t *npc2;
npc_t *npc3;
npc_t *npc4;
npc_mov_t *npc1_movement;
npc_mov_t *npc2_movement;

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to this sample game of Chiventure!");

    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    room_t *room3 = room_new("room3", "This is room 3", "Exactly, this is the third room.");
    room_t *room4 = room_new("room4", "This is room 4", "Yes, this is the fourth room.");
    room_t *room5 = room_new("room5", "This is room 5", "Indeed, this is the fifth room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    add_room_to_game(game, room4);
    add_room_to_game(game, room5);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");
    create_connection(game, "room2", "room3", "EAST");
    create_connection(game, "room2", "room4", "WEST");
    create_connection(game, "room2", "room5", "SOUTH");

    item_t *emerald = item_new("EMERALD","It is an emerald",
                              "This item must be taken for the first mission. Steal it!");
    add_item_to_room(room2, emerald);

    item_t *BLUEPOTION = item_new("BLUE POTION","It is a bottle that holds a mysterious blue liquid",
                              "This item must be taken for second mission. Drink it!");
    add_item_to_room(room1, BLUEPOTION);
    
    item_t *GREENPILL = item_new("GREEN PILL","It is a green tablet. Could it be medicine?",
                              "This item must be taken for second mission. Take it!");
    add_item_to_room(room1, GREENPILL);

    item_t *NECKLACE = item_new("NECKLACE", "It is a diamond necklace that has royal significance",
                                "This item must be taken for another mission. Keep it!");
    add_item_to_room(room3, NECKLACE);

    item_t *HERB = item_new("HERB", "It is a herb plant that has medicinal properties", 
                                "This item can cure a bad cough");
    add_item_to_room(room4, HERB);

    add_action(emerald, "STEAL", "[You take the Emerald] "
                        "This is the object that the villager was talking about!",
                "You can't pickup the emerald.");

    add_action(BLUEPOTION, "SIP", "[You sip the Potion] You feel strong.",
                "You can't drink the POTION.");

    add_action(GREENPILL, "CONSUME", "[You take the Pill] You feel clever.",
                "You can't drink the PILL.");
    

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
        return "You have started the quest. There are two potions in front of you: BLUE and GREEN. Pick one";
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

    if (((strcmp(ctx->game->curr_room->room_id,"room2")) == 0) && ((get_quest_status(quest)) == 1))
    {
        move_npc_definite(npc1->movement);
        move_npc_definite(npc2->movement);
        char* id1 = strcpy(id1, npc1->npc_id);
        char* id2 = strcpy(id2, npc2->npc_id);
        char *output1 = strcat(id1,
        ": Get away from me you ogre. Your army of cockroaches have eaten all of my bread.\n");
        char *output2 = strcat(id2, ": But, Sire! My wife is ill. She needs your medicine.\n");
        char *thoughts = "You wonder if there is a way to solve their problems. Try exploring.";
        strcat(output1, output2);
        strcat(output1, thoughts);
        return output1;
    }
    else if (((strcmp(ctx->game->curr_room->room_id,"room3")) == 0) && ((get_quest_status(quest)) == 1))
    {
        //move_npc_definite(npc1_movement);
        item_t *item = malloc(sizeof(item_t));
        HASH_FIND(hh, ctx->game->all_items, "EMERALD", strlen("EMERALD"), item);

        npc_t *npc = malloc(sizeof(npc_t));
        HASH_FIND(hh, npcs_in_room_2->npc_list, "Villager-Jim", strlen("Villager-Jim"), npc);

        //complete_achievement(quest, item, npc);
        quest->achievement_tree->achievement->completed = 1;
        quest->status = 2;
        char* id1 = strcpy(id1,npc1->npc_id);
        char *output2 = strcat(id1,": Thank you for helping me resupply my shop. "
                    "Those cockroaches are so pesky. For your efforts I'd like to give you this emerald. ");

        return output2;
    }
    else if (((strcmp(ctx->game->curr_room->room_id,"room4")) == 0) && ((get_quest_status(quest)) == 1))
    {
        item_t *item = malloc(sizeof(item_t));
        HASH_FIND(hh, ctx->game->all_items, "POTION", strlen("POTION"), item);

        npc_t *npc = malloc(sizeof(npc_t));
        HASH_FIND(hh, npcs_in_room_2->npc_list, "Villager-Jim", strlen("Villager-Jim"), npc);

        quest->achievement_tree->lmostchild->achievement->completed = 1;

        if ((is_quest_completed(quest)) == 1)
        {
            item_t *reward = complete_quest(quest);
            add_item_to_player(ctx->game->curr_player, reward);
            char* id2 = strcpy(id2,npc1->npc_id);
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


quest_t *make_sample_quest(long int quest_id, item_t *reward,
                           npc_t *npc1, npc_t *npc2, npc_t *npc3, npc_t *npc4,
                           item_t *item1, item_t *item2, item_t *item3,
                           item_t *item4, item_t *item5)
{
    quest_t *quest = quest_new(quest_id, NULL, reward);

    
    mission_t *kill_dragon = mission_new(NULL, npc1); // kill dragon
    mission_t *stock_store = mission_new(item3, npc2); //stock store with bread
    mission_t *give_herb = mission_new(item4, npc3); //give herb
    mission_t *give_necklace = mission_new(item5, npc4); //give necklace
    mission_t *take_blue_potion = mission_new(item1, NULL);
    mission_t *take_green_pill = mission_new(item2, NULL);    

    achievement_t *achievement1 = achievement_new(take_blue_potion,
                 "Take blue potion");
    achievement_t *achievement2 = achievement_new(take_green_pill, 
                 "Take green pill");
    achievement_t *achievement3 = achievement_new(kill_dragon,"Kill the dragon");
    achievement_t *achievement4 = achievement_new(stock_store, "Stock the store");
    achievement_t *achievement5 = achievement_new(give_herb, "Heal the Sick");
    achievement_t *achievement6 = achievement_new(give_necklace, "Return the necklace");

    add_achievement_to_quest(quest, achievement1, "The first mission");
    add_achievement_to_quest(quest, achievement2, "The first mission");
    add_achievement_to_quest(quest, achievement3, "Take blue potion");
    add_achievement_to_quest(quest, achievement4, "Take green pill");
    add_achievement_to_quest(quest, achievement5, "Take green pill");
    add_achievement_to_quest(quest, achievement6, "Take green pill");

    return quest;
}


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    room_t *initial_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room1", strlen("room1"), initial_room);

    room_t *second_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room2", strlen("room2"), second_room);

    room_t *third_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room3", strlen("room3"), third_room);

    room_t *fourth_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room4", strlen("room4"), fourth_room);

    room_t *fifth_room;
    HASH_FIND(hh, ctx->game->all_rooms, "room5", strlen("room5"), fourth_room);

    
    char *npc_id1 = "Puff-Dragon";
    npc_t *npc1 = npc_new(npc_id1,"first npc","this is the npc that holds a branch of a quest",
                          NULL, NULL, false);

    char *npc_id2 = "Villager-Jim";
    npc_t *npc2 = npc_new(npc_id2,"second npc","this is the npc that holds a branch of a quest",
                          NULL, NULL, false);
   
    char *npc_id3 = "Ogre-Rick";
    npc_t *npc3 = npc_new(npc_id3,"third npc","this is the npc that holds a branch of a quest",
                          NULL, NULL, false);

    char *npc_id4 = "Princess Plum";
    npc_t *npc4 = npc_new(npc_id4,"fourth npc","this is the npc that holds a branch of a quest",
                          NULL, NULL, false);



    npcs_in_room_2 = npcs_in_room_new("room2");
    add_npc_to_room(npcs_in_room_2, npc2);
    add_npc_to_room(npcs_in_room_2, npc3);  

    npcs_in_room_5 = npcs_in_room_new("room5");
    add_npc_to_room(npcs_in_room_5, npc1);
    add_npc_to_room(npcs_in_room_5, npc4);

    npc1_movement = npc_mov_new(NPC_MOV_DEFINITE,second_room);
    extend_path_definite(npc1->movement,third_room);
    npc2_movement = npc_mov_new(NPC_MOV_DEFINITE,second_room);
    extend_path_definite(npc2->movement,fourth_room);

    item_t *item1 = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "BLUEPOTION", strlen("BLUEPOTION"), item1);

    item_t *item2 = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "GREENPILL", strlen("GREENPILL"), item2);

    item_t *item3 = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "BREAD", strlen("BREAD"), item3);

    item_t *item4 = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "HERB", strlen("HERB"), item4);

    item_t *item5 = malloc(sizeof(item_t));
    HASH_FIND(hh, ctx->game->all_items, "NECKLACE", strlen("NECKLACE"), item5);

    item_t *reward = item_new("KEY", "this is a key that unlocks all secrets",
    "Reward for completing the quest.");
    
    quest_t *quest = make_sample_quest(1, reward, npc1, npc2, npc3, npc4, item1, item2, item3, item4, item5);

    add_entry("QUEST", start_quest_operation, NULL, ctx->cli_ctx->table);

    add_entry("TALK", talk_to_npc, NULL, ctx->cli_ctx->table);

    action_type_t consume_action = {"CONSUME", ITEM};
    add_entry(consume_action.c_name, kind1_action_operation, &consume_action, ctx->cli_ctx->table);

    action_type_t drink_action = {"SIP", ITEM};
    add_entry(drink_action.c_name, kind1_action_operation, &drink_action, ctx->cli_ctx->table);

    

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
