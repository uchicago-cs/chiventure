#include "npc/dialogue.h"


// EXAMPLE PROGRAM ------------------------------------------------------------

/*
 * Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    printf("\nWelcome to Chiventure's 'Dialogue Module' Mockup!\n\n\n");

    printf("Dialogue Test\n\n");

    // Starting to build the conversation structure
    convo_t *c = convo_new();

    // Initialize each node with its NPC dialogue
    add_node(c, "1", "Test");
    add_node(c, "2", "Test2");
    // add_node(c, "3", "Test3");

    // Adding all edge options to each node
    add_edge(c, "Test 3", "1", "2");
    add_edge(c, "Test 4", "1", "2");

    // Runs the conversation
    run_conversation(c);

    convo_free(c);
}