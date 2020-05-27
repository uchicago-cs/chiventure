#include "../../../include/npc/dialogue.h"

/*
 * Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    print_red("\nWelcome to Chiventure's 'Dialog Module' Mockup!\n\n\n");

    printf("As the door creaks open, a strong musty scent smacks "
           "you in the face, filled with tones of mildew and copper. "
           "You step into a disheveled room which, while bare in some "
           "areas, seems to have plenty of valuables stacked in others. "
           "You can see an antique clock and a faberge egg, just for "
           "starters. A shabby man quickly rounds the corner into the room, "
           "alarmed by the unexpected guest. He looks upset with you.\n\n");

    /*
     * Starting to build the conversation structure:
     */

    convo_t *showcase_convo = convo();

    /*
     * Initialize each node with it's primary NPC dialog
     */
    node_t *WellMet = node_new("WellMet",
           "Mhm fine, that's wonderful, now go ahead and turn around and "
           "get outta #my house#.  You can't #come and go# as you wish.");
    node_t *PrivacyVio = node_new("PrivacyVio",
           "Woah, hey, y-you can't just walk in here and #poke around# "
           "the place without consulting #the owner#!!  Shouldn't I at "
           "least know #who you are#?!");
    node_t *HomeExpl = node_new("HomeExpl",
           "Yes, well, just because the #door's unlocked# and I'm a #bit "
           "messy# don't make it public property. Now take off and "
           "#leave#, or else I'm gonna #force# you to.");
    node_t *FightStnd = node_new("FightStnd",
           "As his arm flashes behind his back, "
           "the robber raises a knife to you.");
    node_t *FightFlwr = node_new("FightFlwr",
           "The last thing you heard before it all went dark was "
           "'NOO MY PRESSED FLOWER COLLECTION'");
    node_t *Leave = node_new("Leave",
           "As soon as your eyes glance to the doorway, the man's hands "
           "are at your back ushering you away. The door snaps shut and "
           "you hear the distinct click of a lock turning.");

    /*
     * Adding all edge options to each node:
     */
    add_edge(WellMet, edge_new(HomeExpl, "my house",
                      "Shucks, seemed abandoned to me."));
    add_edge(WellMet, edge_new(HomeExpl, "come and go",
                      "I'm not trying to take your home, I just thought "
                      "it would be a place to rest in some shade for a bit."));
    add_edge(PrivacyVio, edge_new(HomeExpl, "the owner",
                      "The owner? With the state of this place, "
		      "I'd have pegged you for more of a burglar, heh."));
    add_edge(PrivacyVio, edge_new(WellMet, "who you are",
                      "Just someone looking for someone to talk to."));
    add_edge(PrivacyVio, edge_new(FightFlwr, "poke around",
                      "Unperturbed by the smelly squatter, you continue "
		      "rifling for valuables in the piles. As you hum "
		      "patronizingly, angry footsteps quickly "
		      "approach your back."));
    add_edge(HomeExpl, edge_new(FightStnd, "door's unlocked",
                      "You walk over and pop a squat on the couch. "
                      "'You know what they say, open home, open heart!"));
    add_edge(HomeExpl, edge_new(FightStnd, "bit messy",
                      "Really doesn't smell too good either. In fact, the place "
                      "is looking a bit ransacked--"));
    add_edge(HomeExpl, edge_new(FightStnd, "force",
                      "Hey, give it your best shot."));
    add_edge(HomeExpl, edge_new(Leave, "leave",
                      "Jeez fine.."));

    /*
     * Adding the nodes to the mockup:
     */
    node_append(showcase_convo, WellMet);
    node_append(showcase_convo, PrivacyVio);
    node_append(showcase_convo, HomeExpl);
    node_append(showcase_convo, FightStnd);
    node_append(showcase_convo, FightFlwr);
    node_append(showcase_convo, Leave);

    /*
     * Functions for testing:
     */

    run_convo(showcase_convo);
}
