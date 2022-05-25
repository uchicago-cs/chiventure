#include "npc/dialogue.h"
#include "game-state/item.h"
#include "game-state/player.h"
#include "game-state/game.h"
#include "game-state/mode.h"


// EXAMPLE PROGRAM ------------------------------------------------------------

/* Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    printf("\nWelcome to Chiventure's 'Dialogue Module' Mockup!\n\n\n");

    // Step 1: Setting up the game, player, and item
    game_t *g = game_new("game");
    player_t *p = player_new("player");
    room_t *r = room_new("room", "short", "long");
    npc_t *stranger = npc_new("stranger", "short", "long", NULL, NULL, 0);
    item_t *item1 = item_new("scimitar_handle", "a handle of a curved sword",
                             "looks intricate");
    item_t *item2 = item_new("scimitar_blade", "a blade of a curved sword",
                             "looks sharp");

    g->curr_player = p;
    g->curr_room = r;
    g->mode = game_mode_new(NORMAL, NULL, "stranger"); // mode is needed for
    // the GIVE_ITEM action
    // to work properly
    add_player_to_game(g, p);
    // This code should be uncommented once NPC structs can support two
    // hash tables
    // add_npc_to_game(g, stranger);
    add_room_to_game(g, r);
    add_npc_to_room(r->npcs, stranger);
    add_item_to_game(g, item1);
    add_item_to_game(g, item2);
    add_item_to_npc(stranger, item1);
    add_item_to_npc(stranger, item2);

    // Step 2: Create the conditions
    condition_t *cond = NULL;
    LL_APPEND(cond, inventory_condition_new(p, item1));
    LL_APPEND(cond, inventory_condition_new(p, item2));

    // Step 3: Conversation 1
    convo_t *c1 = convo_new();

    add_node(c1, "1", "Do you want a scimitar blade?");
    add_node(c1, "2a", "Here you go. Do you want a scimitar handle?");
    add_node(c1, "3a", "Here you go.");
    add_node(c1, "3b", "Your loss.");
    add_node(c1, "2b", "Your loss.");
    add_edge(c1, "Yes", "1", "2a", NULL);
    add_edge(c1, "No", "1", "2b", NULL);
    add_edge(c1, "Yes", "2a", "3a", NULL);
    add_edge(c1, "No", "2a", "3b", NULL);

    add_give_item(c1, "2a", "scimitar_blade");
    add_give_item(c1, "3a", "scimitar_handle");

    // Step 4: Conversation 2
    convo_t *c2 = convo_new();

    add_node(c2, "1", "Pick an item: a sword or a shield?");
    add_node(c2, "2a", "I see you prefer the path of offence. What weapon "
             "did you want? Or do you change your mind?");
    add_node(c2, "2b", "Ah, I see you prefer the path of defence. Clever choice.");
    add_node(c2, "2c", "A quest? I have one right here.");
    add_node(c2, "3a", "One longsword coming up.");
    add_node(c2, "3b", "If you have a blade and handle, I can make one for you.");
    add_node(c2, "4", "Wonderful. Here's your scimitar.");
    add_edge(c2, "Sword", "1", "2a", NULL);
    add_edge(c2, "Shield", "1", "2b", NULL);
    add_edge(c2, "Do you have a quest?", "1", "2c", NULL);
    add_edge(c2, "A longsword", "2a", "3a", NULL);
    add_edge(c2, "Can you make me a scimitar?", "2a", "3b", NULL);
    add_edge(c2, "I change my mind: I want a shield", "2a", "2b", NULL);
    add_edge(c2, "I have them right here!", "3b", "4", cond);
    add_edge(c2, "Nevermind..", "3b", "2a", NULL);

    add_start_quest(c2, "2c", 1234);
    add_take_item(c2, "4", "scimitar_blade");
    add_take_item(c2, "4", "scimitar_handle");

    // Step 5: Execute conversations
    int rc = -1;
    int player_response;
    char *ret_str;

    printf("Stranger:\n");
    while (rc != 1)
    {
        if (rc < 0) ret_str = start_conversation(c1, &rc, g);
        else ret_str = run_conversation_step(c1, player_response, &rc, g);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    rc = -1;

    printf("Stranger: (again)\n");
    while (rc != 1)
    {
        if (rc < 0) ret_str = start_conversation(c1, &rc, g);
        else ret_str = run_conversation_step(c1, player_response, &rc, g);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    rc = -1;

    printf("\nSteve the 'Smith:\n");
    while (rc != 1)
    {
        if (rc < 0) ret_str = start_conversation(c2, &rc, g);
        else ret_str = run_conversation_step(c2, player_response, &rc, g);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    rc = -1;

    printf("\nSteve the 'Smith: (again)\n");
    while (rc != 1)
    {
        if (rc < 0) ret_str = start_conversation(c2, &rc, g);
        else ret_str = run_conversation_step(c2, player_response, &rc, g);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    // Step 7: Free allocated memory
    convo_free(c1);
    convo_free(c2);
    game_free(g);

    return 0;
}
