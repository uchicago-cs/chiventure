#include "common/sample_game.h"
#include "game-state/game.h" // to get game_t
#include "game-state/player.h" // to get player_t
#include "game-state/item.h" // to get item_t
#include "game-state/condition.h" // for conditions
#include "action_management/action_structs.h" // to get action_type_t
#include "game-state/game_action.h" // to get game_action_t
#include "action_management/actionmanagement.h" // for get_supported_actions
#include "string.h" // for strcmp


/* this is a function used to get the actions needed*/
action_type_t *search_supported_actions(list_action_type_t *head, char *query)
{
    list_action_type_t *temp;
    for (temp = head; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->act->c_name, query) == 0)
            return temp->act;
    }
    return NULL;
}

/* See sample_game.h */
game_t* create_sample_game()
{
    game_t *game = game_new("Welcome to sample game 1.0!\n");

    /* initialize sample rooms */
    room_t *room1 = room_new("room1", "A small room", "A small room. There's a shiny orb in here.");
    room_t *room2 = room_new("room2", "A slightly larger room", "A slightly larger room. There's a table in here.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    create_connection(game, "room1", "room2", "right");
    create_connection(game, "room2", "room1", "left");
    game->curr_room = room1;

    /* initialize player */
    player_t *player1 = player_new("player1");
    add_player_to_game(game, player1);
    game->curr_player = player1;

    /* initialize items */
    item_t *item_orb = item_new("orb", "magical orb", "an orb that can be held, placed, or tossed");
    agent_t *agent_orb = malloc(sizeof(agent_t));
    agent_orb->item = item_orb;
    agent_orb->npc = NULL;

    item_t *item_table = item_new("table", "a regular table", "this table can have things placed on it");
    agent_t *agent_table = malloc(sizeof(agent_t));
    agent_table->item = item_table;
    agent_table->npc = NULL;

    /* introduce actions */
    list_action_type_t *head = get_supported_actions();
    action_type_t *actiontype_take = search_supported_actions(head, "TAKE");
    action_type_t *actiontype_drop = search_supported_actions(head, "DROP");
    action_type_t *actiontype_puton = search_supported_actions(head, "PUT");

    /* add valid actions to each item */
    // NOTE: I based this off *NEW* code from game-state/develop-actions
    // it will not work in this branch because develop-actions is not merged
    add_action(agent_orb, "TAKE",
               "You have placed the orb in your pocket.", "Can't perform that action!");
    add_action(agent_orb, "DROP",
               "You have dropped the orb.", "Can't perform that action!");
    add_action(agent_orb, "PUT",
               "You have placed the orb on the table", "Can't perform that action!");
    add_action(agent_table, "PUT",
               "You have placed the orb on the table", "Can't perform that action!");

    /* add items to room */
    add_item_to_room(room1, agent_orb->item);
    add_item_to_room(room2, agent_table->item);
    free(agent_orb);
    free(agent_table);
    return game;

}

game_t *create_sample_game_cp()
{
    // first room
    room_t *dorm_t;
    char *room_id = "dorm";
    char *short_desc = "college dorm";
    char *long_desc = "there are clothes and empty ramen cups everywhere";
    dorm_t = room_new(room_id, short_desc, long_desc);

    // first room's items
    item_t *ramen_t;
    char *i_item_id = "ramen";
    char *i_short_desc = "cup ramen";
    char *i_long_desc = "has already been eaten";
    ramen_t = item_new(i_item_id, i_short_desc, i_long_desc);
    add_item_to_room(dorm_t, ramen_t);

    item_t *shirt_t;
    char *s_item_id = "shirt";
    char *s_short_desc = "shirt";
    char *s_long_desc = "looks unwashed";
    shirt_t = item_new(s_item_id, s_short_desc, s_long_desc);
    add_item_to_room(dorm_t, shirt_t);

    // second room
    room_t *dungeon_t;
    char *d_room_id = "dungeon";
    char *d_short_desc = "dungeon";
    char *d_long_desc = "there are skull and bones in all the jail cells";
    dungeon_t = room_new(d_room_id, d_short_desc, d_long_desc);

    // second room's items
    item_t *skull_t;
    char *sk_item_id = "skull";
    char *sk_short_desc = "skull";
    char *sk_long_desc = "looks pretty old";
    skull_t = item_new(sk_item_id, sk_short_desc, sk_long_desc);
    add_item_to_room(dungeon_t, skull_t);

    // one player
    player_t *chad_t;
    chad_t = player_new("Chad");

    game_t *g_t_orig = game_new("Welcome to Chiventure");

    add_room_to_game(g_t_orig, dorm_t);
    move_room(g_t_orig, dorm_t);
    add_room_to_game(g_t_orig, dungeon_t);
    create_connection(g_t_orig, "dorm", "dungeon", "east");
    create_connection(g_t_orig, "dungeon", "dorm", "west");
    add_player_to_game(g_t_orig, chad_t);
    set_curr_player(g_t_orig, chad_t);

    return g_t_orig;
}

game_t *create_sample_game_gs()
{
    game_t *game = game_new("Welcome to sample game game-state!\n");

    /* initialize sample rooms */
    room_t *room1 = room_new("ryerson","ryerson", "You are in a barn. There is nothing in the room. A path leads north.");
    room_t *room2 = room_new("bartlett", "bartlett",
                             "There is an apple in the room. An exit to the west and to the south.");
    room_t *room3 = room_new("reg", "reg",
                             "No apples. Exit to the east, and a road leads west. There is a path southwest.");
    room_t *room4 = room_new("kersten", "kersten", "Wrong path mate, try again. Go back east.");
    room_t *room5 = room_new("crerar", "crerar", "A borja screams at you. You're late.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    add_room_to_game(game, room4);
    add_room_to_game(game, room5);
    create_connection(game, "ryerson", "bartlett", "north");
    create_connection(game, "bartlett", "ryerson", "south");
    create_connection(game, "bartlett", "reg", "west");
    create_connection(game, "reg", "bartlett", "east");
    create_connection(game, "reg", "kersten", "west");
    create_connection(game, "kersten", "reg", "east");
    create_connection(game, "reg", "crerar", "southwest");
    game->curr_room = room1;

    /* initialize player */
    player_t *player1 = player_new("lydia");
    add_player_to_game(game, player1);
    game->curr_player = player1;

    /* initialize items */
    item_t *apple = item_new("apple", "a regular apple", "an apple that can only be eaten or thrown");
    agent_t *agent_apple = malloc(sizeof(agent_t));
    agent_apple->item = apple;
    agent_apple->npc = NULL;

    item_t *macintosh = item_new("macintosh", "a magical apple", "this apple has computing power");
    agent_t *agent_macintosh = malloc(sizeof(agent_t));
    agent_macintosh->item = macintosh;
    agent_macintosh->npc = NULL;

    item_t *table = item_new("table", "a magical table", "wow! there's a table");
    agent_t *agent_table = malloc(sizeof(agent_t));
    agent_table->item = table;
    agent_table->npc = NULL;

    /* introduce actions */
    list_action_type_t *head = get_supported_actions();
    action_type_t *actiontype_take = search_supported_actions(head, "TAKE");
    action_type_t *actiontype_drop = search_supported_actions(head, "DROP");
    action_type_t *actiontype_puton = search_supported_actions(head, "PUT");
    action_type_t *actiontype_consume= search_supported_actions(head, "CONSUME");

    /* add valid actions to each item */
    // NOTE: I based this off *NEW* code from game-state/develop-actions
    // it will not work in this branch because develop-actions is not merged
    add_action(agent_apple, "CONSUME",
               "*Crunch Crunch*", "It looks... off.");
    add_action(agent_apple, "TAKE",
               "You have taken the apple.", "Can't perform that action!");
    add_action(agent_apple, "DROP",
               "Explain yourself.", "Can't perform that action!");
    add_action(agent_macintosh, "TAKE",
               "You have taken the macintosh", "Can't perform that action!");
    add_action(agent_macintosh, "PUT",
               "You have put the macintosh on the table", "Can't perform that action!");
    add_action(agent_table, "PUT",
               "You have put the macintosh on the table", "Can't perform that action!");
    set_str_attr(agent_apple->item, "ripeness", "very_sour");
    attribute_value_t *ripe;
    ripe->str_val = "ripe";

    /* conditions */
    condition_t *cond = attribute_condition_new(agent_apple->item, "ripeness", ripe);
    add_condition(game, get_action(agent_apple, "CONSUME"), cond);

    /* add items to room */
    add_item_to_room(room2, agent_apple->item);
    add_item_to_room(room3, agent_macintosh->item);
    add_item_to_room(room5, agent_table->item);

    free(agent_apple);
    free(agent_macintosh);
    free(agent_table);

    return game;
}
