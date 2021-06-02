#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ui/ui_ctx.h"
#include "ui/coordinate.h"


coord_t *coord_new(int x, int y, int z)
{
    coord_t *c = malloc(sizeof(coord_t));
    assert(c != NULL);
    coord_init(c, x, y, z);
    return c;
}

// see coordinate.h for details
void coord_init(coord_t *c, int x, int y, int z)
{
    assert (c != NULL);
    c->x = x;
    c->y = y;
    c->z = z;
    return;
}

// see coordinate.h for details
coord_record_t *find_coord(coord_record_t *coordmap, int x, int y, int z)
{
    coord_t *key = malloc(sizeof(coord_t));
    assert (key != NULL);

    // Requirement for struct keys per uthash documentation
    memset(key, 0, sizeof(coord_t));
    coord_init(key, x, y, z);

    coord_record_t *cr = malloc(sizeof(coord_record_t));
    assert (cr != NULL);
    memset(cr, 0, sizeof(coord_record_t));
    HASH_FIND(hh, coordmap, key, sizeof(coord_t), cr);

    // Key no longer needed once comparison is made
    free(key);
    return cr;
}

// See coordinate.h for details
int try_add_coord(coord_record_t *coordmap, int x, int y, int z, room_t *r)
{
    assert(coordmap != NULL);
    assert(r != NULL);
    coord_record_t *cr = find_coord(coordmap, x, y, z);

    // File created for debug statments
    FILE *debug = fopen("ui_debug.txt", "a");

    /* Only runs if find_coord() does not find this coordinate key
     *  already existing in hashtable */
    if (cr == NULL)
    {
        fseek(debug, 0, SEEK_END);
        fprintf(debug,"Adding coord (%d, %d, %d) to hash\n", x, y, z);
        cr = malloc(sizeof(coord_record_t));

        // uthash requirement for struct keys
        memset(cr, 0, sizeof(coord_record_t));
        cr->key.x = x;
        cr->key.y = y;
        cr->key.z = z;
        cr->r = r;

        HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);
        
        /* This line caused tests in test_item_action.c and 
         * test_item_item_actions.c to fail for unknown reasons; 
         * see issue #621 */
        //fclose(debug);
        
        return SUCCESS;
    }
    else
    {
        assert(cr->r != NULL);
        // If assigned to itself, no conflicts
        // But this function should still return FAILURE
        // because no coordinates were added.
        if (strcmp(cr->r->room_id, r->room_id) == 0)
        {
            fclose(debug);
            return FAILURE;
        }

        fseek(debug, 0, SEEK_END);
        fprintf(debug,
                "ERROR: try_add_coord(): This coordinate has already been assigned.\n");
        fclose(debug);
        return FAILURE;
    }
}

//See coordinate.h for details
coord_record_t *get_test_coord_hash()
{
    // Sample Rooms
    room_t *room1 = room_new("One", "", "");
    room_t *room2 = room_new("Two", "", "");
    room_t *room3 = room_new("Three", "", "");
    room_t *room4 = room_new("Four", "", "");
    room_t *room5 = room_new("Five", "", "");
    room_t *room6 = room_new("Six", "", "");
    room_t *room7 = room_new("Seven", "", "");
    room_t *room8 = room_new("Eight", "", "");
    room_t *room9 = room_new("Nine", "", "");

    // Must set hash to NULL (see uthash documentation)
    coord_record_t *coordmap = NULL;

    coord_record_t *head = malloc(sizeof(coord_record_t));
    assert(head != NULL);
    memset(head, 0, sizeof(coord_record_t));

    // Initial coordinate is arbitrarily set to be (0,0,0)
    head->key.x = 0;
    head->key.y = 0;
    head->key.z = 0;
    head->r = room1;
    HASH_ADD(hh, coordmap, key, sizeof(coord_t), head);
    assert(coordmap != NULL);

    try_add_coord(coordmap, 0, 1, 0, room2);
    try_add_coord(coordmap, 0, 2, 0, room3);
    try_add_coord(coordmap, 1, 1, 0, room4);
    try_add_coord(coordmap, 1, 0, 0, room5);
    try_add_coord(coordmap, 2, 1, 0, room6);
    try_add_coord(coordmap, 0, 0, 1, room7);
    try_add_coord(coordmap, 0, 1, 1, room8);
    try_add_coord(coordmap, 0, 0, 2, room9);

    return coordmap;
}

/* See coordinate.h for documentation */
void set_player_loc(chiventure_ctx_t *ctx, int x, int y, int z)
{
    coord_t *pos = ctx->ui_ctx->player_loc;
    pos->x = x;
    pos->y = y;
    pos->z = z;

    return;
}
