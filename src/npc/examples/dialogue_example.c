#include "npc/dialogue.h"


// EXAMPLE PROGRAM ------------------------------------------------------------

/* Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    printf("\nWelcome to Chiventure's 'Dialogue Module' Mockup!\n\n\n");


    convo_t *c = convo_new();

    add_node(c, "1", "Pick an item: a sword or a shield?");
    add_node(c, "2a", "I see you prefer the path of offence. Do you prefer a longsword or a scimitar? Or do you change your mind?");
    add_node(c, "3a", "One longsword coming up.");
    add_node(c, "3b", "One scimitar coming up.");
    add_node(c, "2b", "Ah, I see you prefer the path of defence. Clever choice.");
    add_node(c, "2c", "A quest? I have one right here.");
    add_edge(c, "Sword", "1", "2a");
    add_edge(c, "Shield", "1", "2b");
    add_edge(c, "Do you have a quest?", "1", "2c");
    add_edge(c, "Longsword", "2a", "3a");
    add_edge(c, "Scimitar", "2a", "3b");
    add_edge(c, "I change my mind: I want a shield", "2a", "2b");

    add_quest(c, "2c", NULL);

    c->all_edges->next->next->next->edge->condition = (condition_t *) 1;

    int rc = -1;
    int player_response;
    char *ret_str;

    while (rc != 1) {
        if (rc < 0) ret_str = start_conversation(c, &rc, NULL);
        else ret_str = run_conversation_step(c, player_response, &rc, NULL);
        printf("%s", ret_str);
        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
        free(ret_str);
    }

    convo_free(c);
    
    return 0;
}