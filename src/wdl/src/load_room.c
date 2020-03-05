#include <stdio.h>
#include <string.h>

#include "wdl/load_room.h"

/* see load_rooms.h */
int add_rooms_to_game(obj_t *doc, game_t *g)
{
    // extract room object
    attr_list_t *rooms_obj = extract_objects(doc, "ROOMS");
    // if rooms list is empty then return 1
    if (rooms_obj == NULL)
    {
        fprintf(stderr, "rooms list is empty\n");
        return FAILURE;
    }

    // extract list of rooms and items
    attr_list_t *curr = rooms_obj;

    // while list of rooms exists, create new game_struct room, add room to game
    while (curr != NULL)
    {
        // get id, short_desc, and long_desc
        char *id = obj_get_str(curr->obj, "id");
        char *short_desc = obj_get_str(curr->obj, "short_desc");
        char *long_desc = obj_get_str(curr->obj, "long_desc");

        // create new game_state room
        room_t *room = room_new(id, short_desc, long_desc);

        // add room to game
        add_room_to_game(g, room);
        curr = curr->next;
    }

    return SUCCESS;
}

/* see load_rooms.h */
int add_connections_to_rooms(obj_t *doc, game_t *g)
{
    // extract room object
    attr_list_t *rooms_obj = extract_objects(doc, "ROOMS");

    // extract list of rooms and items
    attr_list_t *curr = rooms_obj;

    // if rooms list is empty then return 1
    if (curr == NULL)
    {
        fprintf(stderr, "rooms list is empty\n");
        return FAILURE;
    }

    // while list of rooms exists, create new game_struct room, add room to game
    while (curr != NULL)
    {
        // obtain room id
        char *id = obj_get_str(curr->obj, "id");
        // get list of connections for the room
        attr_list_t *conn_curr = connections_get_list(curr->obj);

        // if connections list is empty then return 1
        if (conn_curr == NULL)
        {
            fprintf(stderr, "connections list is empty\n");
            return FAILURE;
        }
        // iterate through connections list
        while (conn_curr != NULL)
        {
            // get id of room we are going to and direction
            char *to = obj_get_str(conn_curr->obj, "to");
            char *direction = obj_get_str(conn_curr->obj, "direction");

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

            conn_curr = conn_curr->next;
        }

        curr = curr->next;
    }

    return SUCCESS;
}
