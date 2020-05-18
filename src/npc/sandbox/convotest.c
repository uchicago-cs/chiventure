#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * I'm using some defined maxes (max number of nodes in a convo, 
 * and max number of edges to a node)... Again, this is something
 * that is worth considering refactoring, but I wasn't sure how
 * else to allocate the memory for a Node/Convo (they have flexible
 * array variables).  This might be a problem for WDL, not sure.
 */
#define MAXNODES 12
#define MAXEDGES 6

char* name;
enum scene {wellMet, privacyVio, homeExpl, FightFlwr, FightStnd, Leave, ERROR};
char* scene_name(enum scene s){
        switch(s){
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

void print_gold(char* str){
        printf("\033[0;33m");
        printf("%s", str);
        printf("\033[0m");
        return;
}

void print_yellow(char* str){
        printf("\033[1;33m");
        printf("%s", str);
        printf("\033[0m");
        return;
}

void print_red(char* str){
        printf("\033[0;31m");
        printf("%s", str);
        printf("\033[0m");
        return;
}

/*
 * A struct to represent a conversation.
 * Includes:
 *  - nodeCount: the number of Nodes the Convo currently has
 *  - head[]: an array of Node pointers (list of included Nodes)
 *
 */
typedef struct Convo{
        unsigned int nodeCount;
        struct Node* head[];
} Convo_t;

/*
 * A struct to represent one scene in a conversation.
 * Includes:
 *  - tag: a marker of which node this is
 *  - dialog: a string of what the NPC says on arriving at the Node
 *  - connectionCount: the number of connections the Node currently has
 *  - connections[]: an array of Edge pointers (list of attached Edges)
 *
 */
typedef struct Node{
        enum scene tag;
        char* dialog;
        unsigned int connectionCount;
        struct Edge* connections[];
} Node_t;

/*
 * A struct to represent an edge to a Node (Note: does not include source Node)
 * Includes:
 *  - toward: points toward which Node traversing this Edge leads to
 *  - keyword: a string that the user's input must match to enter the Edge
 *  - quip: a string of what the player's character says if they enter the Edge
 *
 */
typedef struct Edge{
        Node_t* toward;
        char* keyword;
        char* quip;
} Edge_t;

/*
 * These are three utility functions to print a textual representation
 * of a given Edge, Node, or Convo.
 *
 */
void print_edge(Edge_t* e){
        printf("TO:\n");// %s\n  '%s' : %s\n",
        print_gold(scene_name(e->toward->tag));
        print_red(e->keyword);
        print_yellow(e->quip);
}
void print_node(Node_t* n){
        printf("%s:\n\t%s\n Edges count: %d\n",
                        scene_name(n->tag), n->dialog, n->connectionCount);
        for(int i = 0; i < (int)n->connectionCount; i++)
                print_edge(n->connections[i]);
        printf("\n");
}
void print_convo(Convo_t* c)
{
        for(int i = 0; i < (int)c->nodeCount; i++)
        { 
          print_node(c->head[i]);
        }
}
/* 
 * A function to allocate a new Convo struct
 * Returns:
 *  - A pointer to the new Convo
 *
 */
Convo_t* make_convo()
{
        Convo_t* c = (Convo_t*) malloc(sizeof(Convo_t)
                        + MAXNODES * sizeof(Node_t*));
        c->nodeCount = 0;
        c->head[0] = NULL;
	return c;
}

/*
 * A function to allocate and initialize a new Node struct
 * Parameters:
 *  - tag: a marker for the Node's identity
 *  - dialog: a string of what the NPC says when the player reaches this Node
 * Returns:
 *  - A pointer to the new Node
 *
 */
Node_t* make_node(enum scene tag, char* dialog)
{
        Node_t* newNode = (Node_t*)malloc(sizeof(Node_t)
                        + MAXEDGES * sizeof(Edge_t*));
        newNode->tag = tag;
        newNode->dialog = dialog;
        newNode->connections[0] = NULL;
        newNode->connectionCount = 0;
        return newNode;
}
/*
 * Attaches a given Node to the head list of a given Convo.
 * Parameters:
 *  - c: the Convo that the Node is to be attached to
 *  - n: the Node to be attached
 * Returns: Nothing
 */
void add_node(Convo_t* c, Node_t* n)
{
        c->head[c->nodeCount++] = n;
}

/*
 * Allocates and initializes an Edge struct
 * Parameters:
 *  - toward: the Node that traversing this Edge will bring you to
 *  - keyword: a string that the user's input must match to enter the Edge
 *  - quip: a string of what the player character should say
 *    when this edge is traversed
 * Returns:
 *  - A pointer to the new Edge struct
 *
 */
Edge_t* make_edge(Node_t* toward, char* keyword, char* quip)
{
        Edge_t* newEdge = (Edge_t*)malloc(sizeof(Edge_t));
        newEdge->toward = toward;
        newEdge->keyword = keyword;
        newEdge->quip = quip;
        return newEdge;
}
/*
 * Attaches a given Edge to the connections list of a given node.
 * Parameters:
 *  - n: the Node that the Edge is to be attached to
 *  - edge: the (previously-made) Edge to be attached
 * Returns: Nothing
 *
 */
void add_edge(Node_t* n, Edge_t* edge)
{
        n->connections[n->connectionCount] = edge;
        n->connectionCount++;
}

/* 
 * Compares the input to the keyword and returns index of matching edge
 * Parameters:
 *  - n: the Node that player is currently on
 *  - input: the player-inputted command
 * Returns:
 *  - Index of the matching edge, -1 if it doesn't match any of the keywords
 *
 */
int read_input(Node_t* n, char* input)
{
    int i;
    for (i = 0; i < (int) n->connectionCount; i++)
    {
        if (!strcmp(strtok(input, "\n"), n->connections[i]->keyword))
        {
            return i;
        }
    }
    return -1;
}

/*
 * Traverses to the edge specified by the inputted index
 * Parameters:
 *  - n: the Node that the player is currently on
 * Returns: 
 *  - index on success, -1 otherwise
 *
 */
int traverse_edge(Node_t* n)
{
    char* input = malloc(30 * sizeof(char));
    fgets(input, 30, stdin);
    int index;
    index = read_input(n, input);
    if (index >= 0)
    {
        print_gold(n->connections[index]->quip);
        n = n->connections[index]->toward;
        print_yellow(n->dialog);
        return index;
    } else {
        print_red("invalid option, try again\n> ");
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
    print_red("Congrats on finishing the chiventure dialog showcase!\n");
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
void run_convo(Convo_t* c)
{
    print_red(c->head[0]->dialog);
    int i = 0;
    int index;
    while (c->head[i]->connectionCount != 0)
    {
        index = traverse_edge(c->head[i]);
        if (index != -1)
            c->head[i] = c->head[i]->connections[index]->toward;
    }
    end_convo();
}
/*In main, we will refacotr the previous showcase prgram to use these new structs.
*/
int main()
{
     system("clear");
     print_red("\nWelcome to Chiventure's 'Dialog Prototype' Showcase!\n\n\n");
     print_yellow("What's your name?");
     printf("\n> ");
     name = malloc(30 * sizeof(char));
     name = strtok(fgets(name, 30, stdin), "\n");
     printf("Hello  ");
     print_yellow(name);
     printf("\n\nAs the door creaks open, a strong musty scent smacks you in the face, filled with tones of mildew and copper.  You step into a disheveled room which, while bare in some areas, seems to have plenty of valuables stacked in others.  You can see an antique clock and a faberge egg, just for starters.  A shabby man quickly rounds the corner into the room, alarmed by the unexpected guest.  He looks upset with you.\n\n Hint-- try to 'talk to' or 'greet' shabby man (that's why you're here after all). Or else, I suppose you could just leave, or 'attack' shabby man instead.\n\n> ");
     char* c1 = malloc(30 * sizeof(char));
     fgets(c1, 30, stdin);

    Convo_t* ShowcaseConvo = make_convo(MAXNODES);
    //making nodes for the dialog
    Node_t* WellMet = make_node(1, "Mhm fine, nice to meet you, now please turn around and get outta my house.  You can't come and go as you wish.");
    Node_t* PrivacyVio = make_node(2, "Woah, hey, y-you can't just walk in here and poke around the place without consulting the owner!!  Shouldn't I at least know who you are?!");
    Node_t* HomeExpl = make_node(3, "Yes, well, just because the door's unlocked and I'm a bit messy don't make it public property. Now take off and leave, or else I'm gonna force you to.");
    Node_t* FightStnd = make_node(4, "The last thing you heard before it all went dark was 'NOO MY PRESSED FLOWER COLLECTION'");
    Node_t* FightFlwr = make_node(5, "As his arm flashes behind his back, the robber raises a knife to you.");
    Node_t* Leave = make_node(6, "As soon as your eyes glance to the doorway, the man's hands are at your back ushering you away.  The door snaps shut and you hear the distinct click of a lock turning.");
    //making edges for the showcase dialog
    add_edge(WellMet, make_edge(HomeExpl, "my house", "Shucks, seemed abandoned to me."));
    add_edge(WellMet, make_edge(HomeExpl, "come and go", "I'm not trying to take your home, I just thought it would be a place to rest in some shade for a bit."));
    add_edge(PrivacyVio, make_edge(HomeExpl, "the owner", "The owner? With the state of this place, I'd have pegged you for more of a burglar, heh."));
    add_edge(PrivacyVio, make_edge(WellMet, "who you are", "Hey I'm Dad"));
    add_edge(PrivacyVio, make_edge(FightFlwr, "poke around", "Unperturbed by the smelly squatter, you continue rifling for valuables in the piles. As you hum patronizingly, angry footsteps quickly approach your back."));
    add_edge(HomeExpl, make_edge(FightStnd, "door's unlocked", "You walk over and pop a squat on the couch. 'You know what they say, open home, open heart!"));
    add_edge(HomeExpl, make_edge(FightStnd, "bit messy", "Really doesn't smell too good either. In fact, the place is looking a bit ransacked--"));
    add_edge(HomeExpl, make_edge(FightStnd, "force", "Hey, give it your best shot."));
    add_edge(HomeExpl, make_edge(Leave, "leave", "Jeez fine.."));
    //adding nodes and edges to the dialog tree
    add_node(ShowcaseConvo, WellMet);
    add_node(ShowcaseConvo, PrivacyVio);
    add_node(ShowcaseConvo, HomeExpl);
    add_node(ShowcaseConvo, FightStnd);
    add_node(ShowcaseConvo, FightFlwr);
    add_node(ShowcaseConvo, Leave);

//    print_convo(ShowcaseConvo);
    run_convo(ShowcaseConvo);
}

