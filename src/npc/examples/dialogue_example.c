#include "npc/dialogue.h"


// EXAMPLE PROGRAM ------------------------------------------------------------

/* Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    printf("\nWelcome to Chiventure's 'Dialogue Module' Mockup!\n\n\n");


    convo_t *c1 = create_new_convo();

    add_node(c1, "1", "Pick an item: a sword or a shield?");
    add_node(c1, "2a", "I see you prefer the path of offence. Do you prefer a longsword or a scimitar? Or do you change your mind?");
    add_node(c1, "3a", "One longsword coming up.");
    add_node(c1, "3b", "One scimitar coming up.");
    add_node(c1, "2b", "Ah, I see you prefer the path of defence. Clever choice.");
    add_edge(c1, "Sword", "1", "2a");
    add_edge(c1, "Shield", "1", "2b");
    add_edge(c1, "Longsword", "2a", "3a");
    add_edge(c1, "Scimitar", "2a", "3b");
    add_edge(c1, "I change my mind: I want a shield", "2a", "2b");

    int rc = -1;
    int player_response;

    while (rc != 1) {
        if (rc < 0) printf("%s", start_conversation(c1, &rc));
        else printf("%s", run_conversation_step(c1, player_response, &rc));
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
    }

    convo_free(c1);
    
    return 0;
}