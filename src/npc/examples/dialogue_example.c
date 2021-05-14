#include "npc/dialogue.h"
#include "game-state/item.h"
#include "game-state/player.h"
#include "game-state/game.h"


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
    item_t *item = item_new("egg", "round", "looks like it's just been laid");

    g->curr_player = p;
    add_item_to_game(g, item);

    // Step 2: Create the condition
    condition_t *cond = inventory_condition_new(p, item);

    // Step 3: Conversation 1
    convo_t *c1 = convo_new();

    add_node(c1, "1", "Do you want an egg?");
    add_node(c1, "2a", "Enjoy.");
    add_node(c1, "2b", "Sure.");
    add_edge(c1, "Yes", "1", "2a", NULL);
    add_edge(c1, "No", "1", "2b", NULL);

    add_item(c1, "2a", "egg");

    // Step 4: Conversation 2
    convo_t *c2 = convo_new();

    add_node(c2, "1", "I'll make you an omelette if you have an egg.");
    add_node(c2, "2a", "Bon appetit.");
    add_node(c2, "2b", "That's too bad.");
    add_edge(c2, "I have one right here!", "1", "2a", cond);
    add_edge(c2, "I don't have one...", "1", "2b", NULL);

    // Step 5: Conversation 3
    convo_t *c3 = convo_new();

    add_node(c3, "1", "Are you ready for the grand egg quest?");
    add_node(c3, "2a", "May the force be with you.");
    add_node(c3, "2b", "...");
    add_edge(c3, "Yes", "1", "2a", NULL);
    add_edge(c3, "No", "1", "2b", NULL);

    add_quest(c3, "2a", "sample");

    // Step 6: Execute conversations
    int rc = -1;
    int player_response;
    char *ret_str;

    printf("NPC 1:\n");
    while (rc != 1) {
        if (rc < 0) ret_str = start_conversation(c1, &rc, g);
        else ret_str = run_conversation_step(c1, player_response, &rc, g);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    rc = -1;

    printf("\nNPC 2:\n");
    while (rc != 1) {
        if (rc < 0) ret_str = start_conversation(c2, &rc, g);
        else ret_str = run_conversation_step(c2, player_response, &rc, g);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    rc = -1;

    printf("\nNPC 3:\n");
    while (rc != 1) {
        if (rc < 0) ret_str = start_conversation(c3, &rc, g);
        else ret_str = run_conversation_step(c3, player_response, &rc, g);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    // Step 7: Free allocated memory
    convo_free(c1);
    convo_free(c2);
    convo_free(c3);

    return 0;


    /*
    convo_t *c = convo_new();

    add_node(c, "1", "Pick an item: a sword or a shield?");
    add_node(c, "2a", "I see you prefer the path of offence. What weapon "
             "did you want? Or do you change your mind?");
    add_node(c, "2b", "Ah, I see you prefer the path of defence. Clever choice.");
    add_node(c, "2c", "A quest? I have one right here.");
    add_node(c, "3a", "One longsword coming up.");
    add_node(c, "3b", "If you can find me a handle, I can make one for you.");
    add_node(c, "4", "Wonderful. Here's your scimitar.");
    add_edge(c, "Sword", "1", "2a", NULL);
    add_edge(c, "Shield", "1", "2b", NULL);
    add_edge(c, "Do you have a quest?", "1", "2c", NULL);
    add_edge(c, "A longsword", "2a", "3a", NULL);
    add_edge(c, "Do you have a scimitar?", "2a", "3b", NULL);
    add_edge(c, "I change my mind: I want a shield", "2a", "2b", NULL);
    add_edge(c, "I have one right here!", "3b", "4", cond);
    add_edge(c, "Nevermind.", "3b", "2a", NULL);

    add_quest(c, "2c", "test");
    add_item(c, "2b", "Shield");
    add_item(c, "3a", "Longsword");
    add_item(c, "4", "Scimitar");
    */
}
