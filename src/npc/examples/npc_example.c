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
    convo_t *showcase_convo = convo_new("See ya later, sucker.");

    // Initialize each node with its NPC dialogue
    node_t *Root = node_new("Root", "Well, what do you want? To #talk#, "
           "#leave#, or continue to #break in#?");
    node_t *WellMet = node_new("WellMet",
           "Mhm fine, that's wonderful, now go ahead and turn around and "
           "get outta my #house#. You can't #come and go# as you wish.");
    node_t *PrivacyVio = node_new("PrivacyVio",
           "Woah, hey, y-you can't just walk in here and #poke around# "
           "the place without consulting #the owner#!!  Shouldn't I at "
           "least know #who you are#?!");
    node_t *HomeExpl = node_new("HomeExpl",
           "Yes, well, just because the #door's unlocked# and I'm a bit "
           "#messy# don't make it public property. Now take off and "
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

    // Adding all edge options to each node
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
    add_edge(HomeExpl, edge_new(FightStnd, "messy",
                      "Really doesn't smell too good either. In fact, the place "
                      "is looking a bit ransacked--"));
    add_edge(HomeExpl, edge_new(FightStnd, "door's unlocked",
                      "You walk over and pop a squat on the couch. "
                      "'You know what they say, open home, open heart!"));
    add_edge(HomeExpl, edge_new(FightStnd, "force",
                      "Hey, give it your best shot."));
    add_edge(HomeExpl, edge_new(Leave, "leave",
                      "Jeez fine.."));

    // Adding the nodes to the example
    append_node(showcase_convo, Root);
    append_node(showcase_convo, WellMet);
    append_node(showcase_convo, PrivacyVio);
    append_node(showcase_convo, HomeExpl);
    append_node(showcase_convo, FightStnd);
    append_node(showcase_convo, FightFlwr);
    append_node(showcase_convo, Leave);

    return showcase_convo;
}

/* Makes sure the game is loaded */
char *check_game(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! Look for Jim if you're not in a room!\n";
    }

    /* This operation has to be called with one parameter */
    if(tokens[1] != NULL)
    {
        return "I do not know what you mean.";
    }
}

/* Defines a new CLI operation that observes Jim and his house */
char *observe_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);

    return "As the door creaks open, a strong musty scent smacks "
           "you in the face, filled with tones of mildew and copper. "
           "You step into a disheveled room which seems to be stacked "
           "with valuables. You can see an antique clock and a faberge "
           "egg, just for starters. A shabby man quickly rounds the corner "
           "into the room, alarmed by the unexpected guest. He looks "
           "upset with you. Would you like to #engage#?";
}
    
/* Defines a new CLI operation that starts a conversation with Jim */
char *engage_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();
    
    return c->nodes->cur_node->dialogue;
}

/* Defines a new CLI operation that continues the conversation with Jim */
char *talk_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();

    print_to_cli(ctx, c->nodes->cur_node->edges->quip);
    
    return c->nodes->next->cur_node->dialogue;
}

/* Defines a new CLI operation that continues the conversation with Jim */
char *house_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();

    print_to_cli(ctx, c->nodes->next->cur_node->edges->quip);
    
    return c->nodes->next->next->next->cur_node->dialogue;
}

/* Defines a new CLI operation that continues the conversation with Jim */
char *messy_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    check_game(tokens, ctx);
   
    convo_t *c;
    c = create_sample_convo();

    print_to_cli(ctx, c->nodes->next->next->next->cur_node->edges->quip);
    
    return c->nodes->next->next->next->next->cur_node->dialogue;
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /* Create one npc */
    npc_t *jim = npc_new("jim", "Jim is a shabby man who lives in a shabby house.", 
            "You step into a disheveled room which seems to have stacks of valuables. "
            "A shabby man quickly rounds the corner into the room, "
            "alarmed by the unexpected guest. He looks upset with you.", 20, NULL);
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

    /* Monkeypatch the CLI to add a new operation
     * (not handled by action management) */
    add_entry("OBSERVE", observe_operation, NULL, ctx->table);
    add_entry("ENGAGE", engage_operation, NULL, ctx->table);
    add_entry("TALK", talk_operation, NULL, ctx->table);
    add_entry("HOUSE", house_operation, NULL, ctx->table);
    add_entry("MESSY", messy_operation, NULL, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
