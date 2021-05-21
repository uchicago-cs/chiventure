/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * The CLI is monkey-patched to accept functions that serve to showcase dialogue.
 * Unfortunately, we did not have time to integrate the dialogue module with the
 * UI/CLI of chiventure, though the backend is functional, as this will show.
 *
 *  - OBSERVE: This is a CLI-level operation that prints out the description of
 *             the created NPC. Someday, we hope chiventure will allow the look
 *             operation to take an NPC and return its description, though at
 *             the moment it is only compatible with items.
 *  - ENGAGE/TALK/HOUSE/MESSY:
 *             These are CLI-level operations that print a player quip (except
 *             on Root) and return an NPC dialogue to be printed to the CLI.
 *             They utlize the backend of the dialogue module while printing to
 *             chiventure's CLI. For a more thorough example of what dialogue
 *             should eventually look like in chiventure, see dialogue_example. 
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "npc/npc.h"

const char *banner = "THIS IS AN NPC EXAMPLE PROGRAM";

/* Creates a sample convo */
convo_t *create_sample_convo()
{
    // Starting to build the conversation structure
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
    add_edge(c, "I just want to talk.", "1", "2a");
    add_edge(c, "I think I'll have a quick look around.", "1", "2b");
    add_edge(c, "<Leave>", "1", "2c");
    add_edge(c, "Seemed abandoned to me.", "2a", "3a");
    add_edge(c, "I'm not trying to take your home, I just thought it would be "
        "a place to rest in some shade for a bit.", "2a", "3a");
    add_edge(c, "<Leave>", "2a", "2c");
    add_edge(c, "I'm Leo.", "2b", "2a");
    add_edge(c, "The owner? With the state of this place, I'd have pegged you "
        "for more of a burglar, heh.", "2b", "4");
    add_edge(c, "<Leave>", "3a", "2c");
    add_edge(c, "Give it your best shot.", "3a", "4");

    return c;
}

/* Makes sure the game is loaded */
char *check_game(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if (game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! Look for Jim if you're not in a room!\n";
    }

    /* This operation has to be called with one parameter */
    if (tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }
}

/* Returns the node in the convo at the given index (starting at 0) */
node_t *get_node_ex(convo_t *c, int index)
{
    node_list_t *curr = c->all_nodes;
    int count = 0;
    while (curr != NULL)
    {
        if (count == index)
        {
            return curr->node;
        }
        count++;
        curr = curr->next;
    }
    return NULL;
}

/* Defines a new CLI operation that observes Jim and his house */
char *observe_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);

    return "As the door creaks open, a strong musty scent smacks "
           "you in the face, filled with tones of mildew and copper. "
           "In steps a shabby man, alarmed by the unexpected guest. "
           "He looks upset with you. Would you like to talk?";
}
    
/* Defines a new CLI operation that starts a conversation with Jim */
/* char *engage_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();
    
    node_t *n = get_node(c, 0);
    return n->npc_dialogue;
} */

/* Defines a new CLI operation that continues the conversation with Jim */
char *sample_talk_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();

    node_t *n1 = get_node_ex(c, 0);
    print_to_cli(ctx, n1->npc_dialogue);
    print_to_cli(ctx, "\n");

    char buf[255];
    edge_list_t *curr_edge = n1->edges;
    while (curr_edge != NULL) {
        sprintf(buf, "%d. %s", curr_edge->option_number, curr_edge->edge->quip);
        print_to_cli(ctx, buf);
        curr_edge = curr_edge->next;
    }
    
    return "\n";
}

/* Defines a new CLI operation that continues the conversation with Jim */
/* char *house_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();

    node_t *n1 = get_node(c, 1);
    print_to_cli(ctx, n1->edges->quip);
    
    node_t *n2 = get_node(c, 3);
    return n2->dialogue;
} */

/* Defines a new CLI operation that continues the conversation with Jim */
/* char *messy_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();

    node_t *n1 = get_node(c, 3);
    print_to_cli(ctx, n1->edges->quip);
    
    node_t *n2 = get_node(c, 4);
    return n2->dialogue;
} */

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    /* Create the initial room */
    room_t *room1 = room_new("room1", "This is room 1", 
                             "The first room in this house is disheveled, "
                             "yet seems to be stacked with valuables. "
                             "You spot a faberge egg and an antique "
                             "clock, for starters.");
    add_room_to_game(game, room1);
    game->curr_room = room1;

    /* Create two items */
    item_t *egg = item_new("EGG", "It is a faberge egg.",
                           "The jewelled artifact shimmers through a thick "
                           "layer of dust. It looks far too expensive for "
                           "its surroundings.");
    add_item_to_room(room1, egg);

    item_t *clock = item_new("CLOCK", "It is an antique grandfather clock.",
                             "The clocks hands are stuck at precisely 8:52. "
                             "It towers over everything but you.");
    add_item_to_room(room1, clock);

    /* Create one npc */
    char *npc_id = "jim";
    npc_t *jim = npc_new(npc_id, 
                         "Jim is a shabby man who lives in a shabby house.", 
                         "Jim looks just as suspicious as his house. His "
                         "beard appears to be half shaved, and his eyes "
                         "constantly dart all around.", 20, NULL, NULL);
    //add_npc_to_game(game, jim);
    convo_t *c = create_sample_convo();
    add_convo_to_npc(jim, c);

    /* Free default game and replace it with ours */
    game_free(ctx->game);
    ctx->game = game;

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add the new operations
     * (not handled by action management, as that code
     * currently only supports items) */
    add_entry("OBSERVE", observe_operation, NULL, ctx->table);
    add_entry("TALK", sample_talk_operation, NULL, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
