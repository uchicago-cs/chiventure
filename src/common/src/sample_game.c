#include "sample_game.h"
#include "game.h" // to get game_t
#include "player.h" // to get player_t
#include "item.h" // to get item_t
#include "action_structs.h" // to get action_type_t
#include "actionmanagement.h" // for get_supported_actions
#include "string.h" // for strcmp


/* this is a function used to get the actions needed*/
action_type_t *search_supported_actions(list_action_type_t *head, char *query)
{
    list_action_type_t *temp;
    for (temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->act->c_name, query) == 0) {
            return temp->act;
        }
    }
    return NULL;
}

/* See sample_game.h */
game_t* create_sample_game()
{
    game_t *game = game_new("Welcome to sample game 1.0!\n");

    /* initialize sample rooms */
    room_t *room1 = room_new("room1", "A room", "room 1 used for the sample game");
    room_t *room2 = room_new("room2", "A room", "room 2 used for the sample game");
    create_connection(game, "room1", "room2", "right");
    create_connection(game, "room2", "room1", "left");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;

    /* initialize player */
    player_t *player1 = player_new("player1", 10);
    add_player_to_game(game, player1);
    game->curr_player = player1;

    /* initialize items */
    item_t *item_orb = item_new("orb", "magical orb", "an orb that can be held, placed, or tossed");
    item_t *item_table = item_new("table", "a regular table", "this table can have things placed on it");
    
    /* introduce actions */
    list_action_type_t *head = get_supported_actions();
    action_type_t *actiontype_take = search_supported_actions(head, "TAKE");
    action_type_t *actiontype_drop = search_supported_actions(head, "DROP");
    action_type_t *actiontype_puton = search_supported_actions(head, "PUT_ON");

    /* add valid actions to each item */
    // NOTE: I based this off *NEW* code from game-state/develop-actions
    // it will not work in this branch because develop-actions is not merged
    add_action(item_orb, "TAKE", 
               "You have placed the orb in your pocket.", "Can't perform that action!");
    add_action(item_orb, "DROP",
               "You have dropped the orb.", "Can't perform that action!");
    add_action(item_orb, "PUT_ON",
               "You have placed the orb on the table", "Can't perform that action!");
    add_action(item_table, "PUT_ON",
                "You have placed the orb on the table", "Can't perform that action!");

    /* add items to room */
    add_item_to_room(room1, item_orb);
    add_item_to_room(room2, item_table);

    return game;
}
