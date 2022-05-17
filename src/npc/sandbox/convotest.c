#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *name;
enum scene {wellMet, privacyVio, homeExpl, FightFlwr, FightStnd, Leave, ERROR};
char *scene_name(enum scene s)
{
    switch(s)
    {
    case 1:
        return "WellMet";
    case 2:
        return "PrivacyVio";
    case 3:
        return "HomeExpl";
    case 4:
        return "FightFlwr";
    case 5:
        return "FightStnd";
    case 6:
        return "Leave";
    default:
        return "ERROR";
    };
}


/*
 * Three functions to print given string in gold, yellow, or red respectively
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
 * Prints a string in NPC dialog format: gold by default and yellow for
 * text surrounded by #hashes# to denote dialog choices.
 * Parameters:
 *  - dialog: the string to be printed in NPC format
 * Returns: nothing
 */
void npc_print(char *dialog)
{
    char *divider = "#";
    char *to_print;
    char *remaining = strdup(dialog);
    int color = 1; /* Increments with each print; odd = gold, even = yel */
    while ((to_print = strtok_r(remaining, divider, &remaining)) != NULL)
    {
        if (color % 2 == 1)
            print_gold(to_print);
        else
            print_yellow(to_print);
        color++;
    }
}

/*
 * A struct to represent a conversation.
 * Includes:
 *  - node_count: the number of nodes the convo currently has
 *  - head[]: an array of node pointers (list of included nodes)
 *
 */
typedef struct convo
{
    int node_count;
    struct node *head[];
} convo_t;

/*
 * A struct to represent one scene in a conversation.
 * Includes:
 *  - tag: a marker of which node this is
 *  - dialog: a string of what the NPC says on arriving at the node
 *  - connection_count: the number of connections the node currently has
 *  - connections[]: an array of edge pointers (list of attached edges)
 *
 */
typedef struct node
{
    enum scene tag;
    char *dialog;
    int connection_count;
    struct edge *connections[];
} node_t;

/*
 * A struct to represent an edge to a node (Note: does not include source node)
 * Includes:
 *  - toward: points toward which node traversing this edge leads to
 *  - keyword: a string that the user's input must match to enter the edge
 *  - quip: a string of what the player's character says if they enter the edge
 *
 */
typedef struct edge
{
    node_t *toward;
    char *keyword;
    char *quip;
} edge_t;

/*
 * These are three utility functions to print a textual representation
 * of a given edge, node, or convo.
 *
 */
void print_edge(edge_t *e)
{
    printf("TO: %s\n  '%s' : %s\n",
           scene_name(e->toward->tag), e->keyword, e->quip);
}

void print_node(node_t *n)
{
    printf("%s:\n\t%s\n edges count: %d\n",
           scene_name(n->tag), n->dialog, n->connection_count);
    for(int i = 0; i < (int)n->connection_count; i++)
    {
        print_edge(n->connections[i]);
    }
    printf("\n");
}

void print_convo(convo_t *c)
{
    for(int i = 0; i < (int)c->node_count; i++)
    {
        print_node(c->head[i]);
    }
}

/*
 * A function to allocate a new convo struct
 * Returns:
 *  - A pointer to the new convo
 *
 */
convo_t *make_convo(int max_nodes)
{
    convo_t *c = (convo_t*)malloc(sizeof(convo_t) +
                                  max_nodes * sizeof(node_t*));
    c->node_count = 0;
    c->head[0] = NULL;
    return c;
}

/*
 * A function to allocate and initialize a new node struct
 * Parameters:
 *  - tag: a marker for the node's identity
 *  - dialog: a string of what the NPC says when the player reaches this node
 *  - max_edges: the maximum number of edges that can be added
 * Returns:
 *  - A pointer to the new node
 *
 */
node_t *make_node(enum scene tag, char *dialog, int max_edges)
{
    node_t *newnode = (node_t*)malloc(sizeof(node_t)
                                      + max_edges * sizeof(edge_t*));
    newnode->tag = tag;
    newnode->dialog = dialog;
    newnode->connections[0] = NULL;
    newnode->connection_count = 0;
    return newnode;
}
/*
 * Attaches a given node to the head list of a given convo.
 * Parameters:
 *  - c: the convo that the node is to be attached to
 *  - n: the node to be attached
 * Returns: Nothing
 */
void add_node(convo_t *c, node_t *n)
{
    c->head[c->node_count++] = n;
}

/*
 * Allocates and initializes an edge struct
 * Parameters:
 *  - toward: the node that traversing this edge will bring you to
 *  - keyword: a string that the user's input must match to enter the edge
 *  - quip: a string of what the player character should say
 *    when this edge is traversed
 * Returns:
 *  - A pointer to the new edge struct
 *
 */
edge_t *make_edge(node_t *toward, char *keyword, char *quip)
{
    edge_t *new_edge = (edge_t*)malloc(sizeof(edge_t));
    new_edge->toward = toward;
    new_edge->keyword = keyword;
    new_edge->quip = quip;
    return new_edge;
}
/*
 * Attaches a given edge to the connections list of a given node.
 * Parameters:
 *  - n: the node that the edge is to be attached to
 *  - edge: the (previously-made) edge to be attached
 * Returns: Nothing
 *
 */
void add_edge(node_t *n, edge_t *edge)
{
    n->connections[n->connection_count++] = edge;
}

/*
 * Compares the input to the keyword and returns index of matching edge
 * Parameters:
 *  - n: the node that player is currently on
 *  - input: the player-inputted command
 * Returns:
 *  - Index of the matching edge, -1 if it doesn't match any of the keywords
 *
 */
int read_input(node_t *n, char *input)
{
    char *adj_input = strtok(input, "\n");
    if (adj_input == NULL)
    {
        return -1;
    }
    for (int i = 0; i < n->connection_count; i++)
    {
        if (!strcmp(adj_input, n->connections[i]->keyword))
        {
            return i;
        }
    }
    return -1;
}

/*
 * Traverses to the edge specified by the inputted index
 * Parameters:
 *  - n: the node that the player is currently on
 * Returns:
 *  - index on success, -1 otherwise
 *
 */
int traverse_edge(node_t *n)
{
    int buffer_size = 30;
    char *input = malloc(buffer_size * sizeof(char));
    fgets(input, buffer_size, stdin);
    int index;
    index = read_input(n, input);
    if (index >= 0)
    {
        printf("\n%s\n\n", n->connections[index]->quip);
        n = n->connections[index]->toward;
        npc_print(n->dialog);
        return index;
    }
    else
    {
        print_gold("The hell you say?\n");
        return -1;
    }
}

/*
 * Ends the conversation
 * Parameters:
 *  - None
 * Returns:
 *  - Nothing
 *
 */
void end_convo()
{
    print_red("\n\nCongrats on finishing the chiventure dialog showcase!\n");
    print_gold("Press ENTER to exit");
    getchar();
    exit(0);
}

/*
 * Runs the entire conversation until it reaches an end
 * Parameters:
 *  - c: A conversation
 * Returns:
 *  - Nothing, just runs through each node and asks for input
 *
 */
void run_convo(convo_t *c)
{
    int start_node = 1;
    npc_print(c->head[start_node]->dialog);
    int index;
    while (c->head[start_node]->connection_count != 0)
    {
        printf("\n\n> Talk about: ");
        index = traverse_edge(c->head[start_node]);
        if (index != -1)
        {
            c->head[start_node] =
                c->head[start_node]->connections[index]->toward;
        }
    }
    end_convo();
}

/*
 * Builds an in-memory fake game mock-up
 * to be run through and then executes functions to explore it
 */
int main()
{
    static const int MAX_NODES = 12;
    static const int MAX_EDGES = 6;

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

    convo_t *showcase_convo = make_convo(MAX_NODES);

    /*
     * Initialize each node with it's primary NPC dialog
     */
    node_t *WellMet = make_node(1,
                                "Mhm fine, that's wonderful, now go ahead and turn around and "
                                "get outta #my house#.  You can't #come and go# as you wish.",
                                MAX_EDGES);
    node_t *PrivacyVio = make_node(2,
                                   "Woah, hey, y-you can't just walk in here and #poke around# "
                                   "the place without consulting #the owner#!!  Shouldn't I at "
                                   "least know #who you are#?!",
                                   MAX_EDGES);
    node_t *HomeExpl = make_node(3,
                                 "Yes, well, just because the #door's unlocked# and I'm a #bit "
                                 "messy# don't make it public property. Now take off and "
                                 "#leave#, or else I'm gonna #force# you to.",
                                 MAX_EDGES);
    node_t *FightStnd = make_node(4,
                                  "As his arm flashes behind his back, "
                                  "the robber raises a knife to you.",
                                  MAX_EDGES);
    node_t *FightFlwr = make_node(5,
                                  "The last thing you heard before it all went dark was "
                                  "'NOO MY PRESSED FLOWER COLLECTION'",
                                  MAX_EDGES);
    node_t *Leave = make_node(6,
                              "As soon as your eyes glance to the doorway, the man's hands "
                              "are at your back ushering you away. The door snaps shut and "
                              "you hear the distinct click of a lock turning.",
                              MAX_EDGES);

    /*
     * Adding all edge options to each node:
     */
    add_edge(WellMet, make_edge(HomeExpl, "my house",
                                "Shucks, seemed abandoned to me."));
    add_edge(WellMet, make_edge(HomeExpl, "come and go",
                                "I'm not trying to take your home, I just thought "
                                "it would be a place to rest in some shade for a bit."));
    add_edge(PrivacyVio, make_edge(HomeExpl, "the owner",
                                   "The owner? With the state of this place, "
                                   "I'd have pegged you for more of a burglar, heh."));
    add_edge(PrivacyVio, make_edge(WellMet, "who you are",
                                   "Just someone looking for someone to talk to."));
    add_edge(PrivacyVio, make_edge(FightFlwr, "poke around",
                                   "Unperturbed by the smelly squatter, you continue "
                                   "rifling for valuables in the piles. As you hum "
                                   "patronizingly, angry footsteps quickly "
                                   "approach your back."));
    add_edge(HomeExpl, make_edge(FightStnd, "door's unlocked",
                                 "You walk over and pop a squat on the couch. "
                                 "'You know what they say, open home, open heart!"));
    add_edge(HomeExpl, make_edge(FightStnd, "bit messy",
                                 "Really doesn't smell too good either. In fact, the place "
                                 "is looking a bit ransacked--"));
    add_edge(HomeExpl, make_edge(FightStnd, "force",
                                 "Hey, give it your best shot."));
    add_edge(HomeExpl, make_edge(Leave, "leave",
                                 "Jeez fine.."));

    /*
     * Adding the nodes to the mockup:
     */
    add_node(showcase_convo, WellMet);
    add_node(showcase_convo, PrivacyVio);
    add_node(showcase_convo, HomeExpl);
    add_node(showcase_convo, FightStnd);
    add_node(showcase_convo, FightFlwr);
    add_node(showcase_convo, Leave);

    /*
     * Functions for testing:
     */

    run_convo(showcase_convo);
}

