#include "npc/dialogue.h"


// EXAMPLE PROGRAM ------------------------------------------------------------

/* Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    printf("\nWelcome to Chiventure's 'Dialogue Module' Mockup!\n\n\n");

    convo_t *c = create_new_convo();

    add_node(c, "1", "Pick an item: a sword or a shield?");
    add_node(c, "2a", "I see you prefer the path of offence. Do you prefer a longsword or a scimitar? Or do you change your mind?");
    add_node(c, "3a", "One longsword coming up.");
    add_node(c, "3b", "One scimitar coming up.");
    add_node(c, "2b", "Ah, I see you prefer the path of defence. Clever choice.");
    add_edge(c, "Sword", "1", "2a");
    add_edge(c, "Shield", "1", "2b");
    add_edge(c, "Longsword", "2a", "3a");
    add_edge(c, "Scimitar", "2a", "3b");
    add_edge(c, "I change my mind: I want a shield", "2a", "2b");

    run_conversation(c);

    convo_free(c);
    
    return 0;

    // Starting to build the conversation structure

    // Initialize each node with its NPC dialogue

    // Adding all edge options to each node

    // Runs the conversation
}