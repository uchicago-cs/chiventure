#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "openworld/autogenerate.h"
#include "game-state/path.h"


#define OUTPUT_BUFFER_SIZE 100

int delete_all_rooms2(room_hash_t **rooms)
{
    room_t *current_room, *tmp;
    HASH_ITER(hh, *rooms, current_room, tmp)
    {
        HASH_DEL(*rooms, current_room);  /* deletes (rooms advances to next) */
        room_free(current_room);             /* free it */
    }
    return SUCCESS;
}

int main(int argc, char **argv)
{   
    game_t *game = game_new("Geseki!");
    room_hash_t *rooms = NULL;
    room_t *room0 = room_new("room0", "", "");
    room_t *room1 = room_new("room1", "", "");
    room_t *room2 = room_new("room2", "", "");
    room_t *room3 = room_new("room3", "", "");

    /* Adding rooms to game*/
    add_room_to_game(game, room0);
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);

    HASH_DEL(game->all_rooms, room0);

    /* Make sure to comment out either 2) if you're testing 1) and vice versa. */

    /* 1) The one in core chiventure */
    // delete_all_rooms(game->all_rooms);

    /* 2) My modified version which takes a room_hash_t** parameter */
    delete_all_rooms2(&(game->all_rooms));

    add_room_to_game(game, room0);

    return 0;
}
