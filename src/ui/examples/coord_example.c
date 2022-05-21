#include <stdio.h>
#include <stdlib.h>
#include "ui/coordinate.h"
#include "assert.h"

/* open_ui_logfile():
 * Several calls to fopen are needed in
 * the example -- created this function  so that
 * it's easy to rename the file if needed
 */
FILE *open_ui_logfile()
{
    FILE * debug = fopen("ui_debug.txt", "a");
    return debug;
}

int main()
{
    FILE *debug = open_ui_logfile();

    // Hash must be initialized to NULL (see uthash documentation)
    coord_record_t *coordmap = NULL;

    /* Initial room must be added prior to calling try_add_coord() function
     * because null hashmap cannot be sent into try_add_coord()
     */
    coord_record_t *cr = malloc(sizeof(coord_record_t));

    // uthash requirement for struct keys
    memset(cr, 0, sizeof(coord_record_t));

    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;
    room_t *initial = malloc(sizeof(room_t));
    initial->room_id = "123";
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);
    if (coordmap != NULL) {
        fprintf(debug,"Added initial room to hashmap\n");
    }

    coord_record_t *test = find_coord(coordmap, 1, 2, 0);
    if (test == NULL) {
        fprintf(debug,
                "find_coord(): Correctly returns NULL when coord not found\n");
    } else {
        fprintf(debug,
                "find_coord(): Incorrect return result--should return NULL\n");
    }

    room_t *r = malloc(sizeof(room_t));
    r->room_id = "456";

    // Close file so that coordinate.c can write into it
    fclose(debug);
    try_add_coord(coordmap, 5, 6, 7, r);


    debug = open_ui_logfile();

    if (coordmap == NULL) {
        fprintf(debug,"ERROR: try_add_coord() returned an empty hashmap\n");
    }

    room_t *g = malloc(sizeof(room_t));
    g->room_id = "2";
    fclose(debug);

    try_add_coord(coordmap, -1, -2, 0, g);

    debug = open_ui_logfile();

    /* This portion of the example tests to see if
     * sample room id's can be looked up using the
     * coordinate keys in the hash
     */
    coord_record_t *example = find_coord(coordmap, 5, 6, 7);
    if (example == NULL) {
        fprintf(debug,"Failure to find coord (%d, %d, %d)\n", 5, 6, 7);
    } else {
        fprintf(debug,"Found coordinate of room with room id %s\n",
                example->r->room_id);
    }

    coord_record_t *ex2 = find_coord(coordmap, -1, -2, 0);

    if (ex2 == NULL)
        fprintf(debug,"Failure to find coord (%d, %d, %d)\n", -1, -2, 0);
    else
        fprintf(debug,"Found coordinate of room with room id %s\n",
                ex2->r->room_id);

    room_t *z = malloc(sizeof(room_t));
    z->room_id = "3";

    /* When compiled and run, this portion of the example demonstrates to
     * future developers how the try_add_coord() function should block
     * double-assigning of coordinates. This is essential for the
     * DFS function in DFS.c
     */
    fprintf(debug,
            "Test to see if try_add_coord() correctly blocks double-assigning:\n");
    fprintf(debug,
            "(Should view an error message below:)\n");
    fclose(debug);

    try_add_coord(coordmap, 5, 6, 7, z);
    free(r);
    free(g);
    free(z);
}

