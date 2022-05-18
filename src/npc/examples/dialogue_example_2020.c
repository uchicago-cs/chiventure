#include "npc/dialogue.h"


// EXAMPLE PROGRAM ------------------------------------------------------------

/* Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    printf("\nWelcome to Chiventure's 'Dialogue Module' Mockup!\n\n\n");

    printf("As the door creaks open, a strong musty scent smacks "
           "you in the face, filled with tones of mildew and copper. "
           "You step into a disheveled room which, while bare in some "
           "areas, seems to have plenty of valuables stacked in others. "
           "You can see an antique clock and a faberge egg, just for "
           "starters. A shabby man quickly rounds the corner into the room, "
           "alarmed by the unexpected guest. He looks upset with you.\n");

    // Creating the convo
    convo_t *c = convo_new();

    // Creating the nodes
    add_node(c, "1", "NPC: What do you want?");
    add_node(c, "2a", "NPC: Mhm fine, that's wonderful, now go ahead and turn "
             "around and get outta my house. You can't come and go as you wish.");
    add_node(c, "2b", "NPC: Woah, hey, y-you can't just walk in here and poke "
             "around the place without consulting the owner!! Shouldn't I at "
             "least know who you are?!");
    add_node(c, "2c", "As soon as your eyes glance to the doorway, the man's "
             "hands are at your back ushering you away. The door snaps shut and "
             "you hear the distinct click of a lock turning.");
    add_node(c, "3a", "NPC: Yes, well, just because the door's unlocked and I'm "
             "a bit messy don't make it public property. Now take off and leave, "
             "or else I'm gonna force you to.");
    add_node(c, "4", "As his arm flashes behind his back, the robber raises "
             "a knife to you.");

    // Adding the edges
    add_edge(c, "I just want to talk.", "1", "2a", NULL);
    add_edge(c, "I think I'll have a quick look around.", "1", "2b", NULL);
    add_edge(c, "<Leave>", "1", "2c", NULL);
    add_edge(c, "Seemed abandoned to me.", "2a", "3a", NULL);
    add_edge(c, "I'm not trying to take your home, I just thought it would be "

        "a place to rest in some shade for a bit.", "2a", "3a", NULL);
    add_edge(c, "<Leave>", "2a", "2c", NULL);
    add_edge(c, "I'm Leo.", "2b", "2a", NULL);
    add_edge(c, "The owner? With the state of this place, I'd have pegged you "
        "for more of a burglar, heh.", "2b", "4", NULL);
    add_edge(c, "<Leave>", "3a", "2c", NULL);
    add_edge(c, "Give it your best shot.", "3a", "4", NULL);

    // Running the conversation
    int rc = -1;
    int player_response;


    while (rc != 1) 
    {
        if (rc < 0) printf("%s", start_conversation(c, &rc, NULL));
        else printf("%s", run_conversation_step(c, player_response, &rc, NULL));

        if (rc != 1) scanf("%d", &player_response);
        printf("\n");
    }

    // Free the convo
    convo_free(c);

    return 0;
}
