#include "npc/dialogue.h"


// BASIC PRINTING FUNCTIONS ---------------------------------------------------

/*
 * Three functions to print given string in gold, yellow, or red respectively.
 */
void print_gold(char *str)
{
    printf("\033[0;33m");
    printf("%s", str);
    printf("\033[0m");
    return;
}

void print_yellow(char *str)
{
    printf("\033[1;33m");
    printf("%s", str);
    printf("\033[0m");
    return;
}

void print_red(char *str)
{
    printf("\033[0;31m");
    printf("%s", str);
    printf("\033[0m");
    return;
}

/*
 * Prints a string in NPC dialogue format: gold by default and yellow for
 * text surrounded by #hashes# to denote dialogue choices.
 * 
 * Parameters:
 *  - dialogue: the string to be printed in NPC format
 * 
 * Returns: None.
 */
void npc_print(char *dialogue)
{
    char *divider = "#";
    char *to_print;
    char *remaining = strdup(dialogue);
    int color = 1; /* Increments with each print; odd = gold, even = yel */
    while ((to_print = strtok_r(remaining, divider, &remaining)) != NULL) {
        if (color % 2 == 1)
            print_gold(to_print);
        else
            print_yellow(to_print);
        color++;
    }
}


// DIALOGUE TRAVERSAL FUNCTIONS -----------------------------------------------

/*
 * Ends the conversation, exiting npc dialogue mode.
 * 
 * Parameters:
 *  - farewell: ending string of convo
 *  - say: true if farewell should print, false otherwise
 * 
 * Returns: None.
 */
void end_convo(char *farewell, bool say)
{
    if (say)
    {
        npc_print(farewell);
        printf("\n");
    }
    exit(0);
}

/*
 * Compares the input to the keyword and returns index of matching edge.
 * 
 * Parameters:
 *  - n: the node that player is currently on
 *  - input: the player-inputted command
 *  - farewell: ending string of convo
 * 
 * Returns:
 *  - pointer to the matching edge on success, NULL otherwise
 */
edge_t *read_input(node_t *n, char *input, char *farewell)
{
    char *adj_input = strtok(input, "\n");

    if (strcmp(adj_input, "ignore") == 0)
    {
        end_convo(farewell, true);
    }

    edge_t *res;

    HASH_FIND(hh, n->edges, adj_input, strlen(adj_input), res);

    return res;
}

/*
 * Asks for input and traverses to the edge specified by the input's index.
 * Prints player quip, moves to new node, prints npc's dialogue at that node.
 * 
 * Parameters:
 *  - n: the node that the player is currently on
 *  - farewell: ending string of convo
 * 
 * Returns:
 *  - pointer to the new curent node on success, NULL otherwise
 */
node_t *traverse_edge(node_t *n, char *farewell)
{
    char *input = malloc(MAX_KEY_LEN);
    fgets(input, MAX_KEY_LEN, stdin);

    edge_t *e;
    e = read_input(n, input, farewell);

    if (e != NULL) {
        printf("\n%s\n\n", e->quip);
        n = e->toward;
        npc_print(n->dialogue);
        return n;
    } 
    else 
    {
        print_gold("What?\n");
        return NULL;
    }
}

/*
 * Runs the entire conversation until it reaches an end.
 * 
 * Parameters:
 *  - c: the conversation to be run
 * 
 * Returns: None.
 */
void run_convo(convo_t *c)
{
    npc_print(c->nodes->cur_node->dialogue);
    npc_print(" Or, you could #ignore# me.");
    node_t *cur;
    printf("\n\n%d\n\n", c->nodes->cur_node->connection_count);
    while (c->nodes->cur_node->connection_count != 0) 
    {
        printf("\nCurrent node is %s\n", c->nodes->cur_node->node_id);
        printf("\n\n> Talk about: ");
        printf("\n%d\n", c->nodes->cur_node->connection_count);
        cur = traverse_edge(c->nodes->cur_node, c->farewell);
        if (cur != NULL) 
        {
            c->nodes->cur_node = cur;
        }
    }
    end_convo(c->farewell, false);
}


// EXAMPLE PROGRAM ------------------------------------------------------------

/*
 * Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    system("clear");

    print_red("\nWelcome to Chiventure's 'Dialogue Module' Mockup!\n\n\n");

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

    convo_t *showcase_convo = convo_new("See ya later.");

    /*
     * Initialize each node with it's primary NPC dialog
     */
    node_t *Root = node_new("Root", "Well, what do you want? To #talk#, "
           "#leave#, or continue to #break in#?");
    node_t *WellMet = node_new("WellMet",
           "Mhm fine, that's wonderful, now go ahead and turn around and "
           "get outta #my house#. You can't #come and go# as you wish.");
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
    add_edge(Root, edge_new(WellMet, "talk", "I just want to talk."));
    add_edge(Root, edge_new(Leave, "leave", "Wait, this isn't my house!"));
    add_edge(Root, edge_new(PrivacyVio, "break in",
                            "I think I'll have a quick look around."));
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
    append_node(showcase_convo, Root);
    append_node(showcase_convo, WellMet);
    append_node(showcase_convo, PrivacyVio);
    append_node(showcase_convo, HomeExpl);
    append_node(showcase_convo, FightStnd);
    append_node(showcase_convo, FightFlwr);
    append_node(showcase_convo, Leave);

    /*
     * Functions for testing:
     */

    run_convo(showcase_convo);
}