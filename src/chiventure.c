#include <stdio.h>
#include "ctx.h"
#include "ui.h"

const char *banner =
    "    ________________________________________________________________________________________\n"
    "  / \\                                                                                       \\\n"
    " |   |                                                                                      |\n"
    "  \\_ |     ██████╗██╗  ██╗██╗██╗   ██╗███████╗███╗   ██╗████████╗██╗   ██╗██████╗ ███████╗  |\n"
    "     |    ██╔════╝██║  ██║██║██║   ██║██╔════╝████╗  ██║╚══██╔══╝██║   ██║██╔══██╗██╔════╝  |\n"
    "     |    ██║     ███████║██║██║   ██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║██████╔╝█████╗    |\n"
    "     |    ██║     ██╔══██║██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ██║   ██║██╔══██╗██╔══╝    |\n"
    "     |    ╚██████╗██║  ██║██║ ╚████╔╝ ███████╗██║ ╚████║   ██║   ╚██████╔╝██║  ██║███████╗  |\n"
    "     |     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝  |\n"
    "     |   ___________________________________________________________________________________|___\n"
    "     |  /                                                                                      /\n"
    "     \\_/______________________________________________________________________________________/\n"
    
                    "RUN AWAY BEFORE THEY COME FOR YOU"
    ;


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = chiventure_ctx_new();

    /* Add calls to component-specific initializations here */
    game_t *game = ctx->game;
    player_t *plyr1 = player_new("player_one", 100);
    add_player_to_game(game, plyr1);
    room_t *room1 = room_new("room1", "you are in the room!", "This is the first room. There is an apple on the floor");
    room_t *room2 = room_new("room2", "you have exited into an alley", "You are in the alley. There is a grade report on the floor.");
    room_t *room3 = room_new("room3", "the end", "borja screams at u");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "north");
    create_connection(game, "room2", "room1", "south");
    create_connection(game, "room2", "room3", "to_borja");
    path_t *path = path_search(room1, "north");
    item_t *door = item_new("door", "yay", "this is a door");
    //path->through = door;
    create_connection(game, "room1", "room3", "east");
    item_t *apple = item_new("apple", "meow", "this is a blue apple");
    item_t *grades = item_new("report", "uhh", "jess: A, patrick: A, lindsey: A, yifan: A, anant: A");
    action_type_t *go = action_type_new("go", 2);
    action_type_new("pick_up", 1);
    add_item_to_room(room1, apple);
    add_item_to_room(room2, grades);
    set_int_attr(apple, "health", 50);
    start_ui(ctx, banner);
    

    return 0;
}
