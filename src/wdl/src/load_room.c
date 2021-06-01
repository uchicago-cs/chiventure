#include <stdio.h>
#include <string.h>

#include "wdl/load_room.h"
#include "cli/util.h"
#include "wdl/validate.h"

/* see load_rooms.h */
int add_rooms_to_game(obj_t *doc, game_t *g)
{
    // extract room object
    obj_t *rooms_obj = obj_get_attr(doc, "ROOMS", false);
    if (rooms_obj == NULL)
    {
        fprintf(stderr, "rooms list is empty\n");
        return FAILURE;
    }
    else if (list_type_check(rooms_obj, room_type_check) == FAILURE)
    {
        fprintf(stderr, "rooms failed typechecking\n");
        return FAILURE;
    }

    // while list of rooms exists, create new game_struct room, add room to game
    obj_t *curr, *tmp;
    HASH_ITER(hh, rooms_obj->data.obj.attr, curr, tmp)
    {
        // get id, short_desc, and long_desc
        char *id = curr->id;
        char *short_desc = obj_get_str(curr, "short_desc");
        char *long_desc = obj_get_str(curr, "long_desc");

        // create new game_state room
        room_t *room = room_new(id, short_desc, long_desc);

        // add room to game
        add_room_to_game(g, room);
    }

    return SUCCESS;
}

/* see load_rooms.h */
int add_connections_to_rooms(obj_t *doc, game_t *g)
{
    // extract room object
    obj_t *rooms_obj = obj_get_attr(doc, "ROOMS", false);

    // if rooms list is empty then return 1
    if (rooms_obj == NULL)
    {
        fprintf(stderr, "rooms list is empty\n");
        return FAILURE;
    }

    // while list of rooms exists, create new game_struct room, add room to game
    obj_t *curr, *tmp;
    HASH_ITER(hh, rooms_obj->data.obj.attr, curr, tmp)
    {
        // obtain room id
        char *id = curr->id;
        // get list of connections for the room
        obj_t *connections = connections_get_list(curr);

        // if connections list is empty then return 1
        if (connections == NULL)
        {
            fprintf(stderr, "connections list is empty\n");
            return FAILURE;
        }
        // iterate through connections list
        obj_t *conn_curr;
        DL_FOREACH(connections->data.lst, conn_curr)
        {
            // get id of room we are going to and direction
            char *to = obj_get_str(conn_curr, "to");
            char *direction = obj_get_str(conn_curr, "direction");

            // add connection to room in game
            int result = create_connection(g, id, to, direction);

            // if result is 1, then id doesn't exist, if result is 2, then
            // connection id (to) doesn't exist
            if (result == PATH_FAILURE)
            {
                fprintf(stderr, "add_path failed\n");
                return FAILURE;
            }
            else if (result == ID_FAILURE)
            {
                fprintf(stderr, "the source room with id %s does not exist\n",
                        id);
                return FAILURE;
            }
            else if (result == CONNECTIONS_FAILURE)
            {
                fprintf(stderr, "the connection room with id %s does not exist\n",
                        to);
                return FAILURE;
            }
            // else {
            //     printf("the connection between %s and %s in the direction %s"
            //            " was added successfully\n", id, to, direction);
            // }

        }
    }

    return SUCCESS;
}
