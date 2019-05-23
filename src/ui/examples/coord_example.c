#include <stdio.h>
#include <stdlib.h>
#include "coordinate.h"
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

/* for basic testing of compilation
 * Will implement much more testing later
 */
int main()
{
    FILE *debug = open_ui_logfile();

    /* Hash must be initialized to NULL (see uthash documentation) */
    coord_record_t *coordmap = NULL;

    /* Initial room must be added prior to calling add_coord() function
     * because null hashmap cannot be sent into add_coord()
     */
    coord_record_t *cr = malloc(sizeof(coord_record_t));

    /* uthash requirement for struct keys */
    memset(cr, 0, sizeof(coord_record_t));

    cr->key.x = 0;
    cr->key.y = 0;

    room_t *initial = malloc(sizeof(room_t));
    initial->id = 123;
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coordinate_t), cr);
    if (coordmap != NULL) {
        fprintf(debug,"Added initial room to hashmap\n");
    }

    coord_record_t *test = find_coord(coordmap, 1, 2);
    if (test == NULL)
        fprintf(debug,
                "find_coord(): Correctly returns NULL when coord not found\n");
    else
        fprintf(debug,
                "find_coord(): Incorrect return result--should return NULL\n");

    room_t *r = malloc(sizeof(room_t));
    r->id = 456;

    /* Close file so that coordinate.c can write into it */
    fclose(debug);
    try_add_coord(coordmap, 5, 6, r);


    debug = open_ui_logfile();

    if (coordmap == NULL)
        fprintf(debug,"ERROR: try_add_coord() returned an empty hashmap\n");

    room_t *g = malloc(sizeof(room_t));
    g->id = 2;
    fclose(debug);

    try_add_coord(coordmap, -1, -2, g);

    debug = open_ui_logfile();

    /* This portion of the example tests to see if
     * sample room id's can be looked up using the
     * coordinate keys in the hash
     */
    coord_record_t *example = find_coord(coordmap, 5, 6);
    if (example == NULL)
        fprintf(debug,"Failure to find coord (%d, %d)\n", 5, 6);
    else
        fprintf(debug,"Found coordinate of room with room id %d\n",
                example->r->id);

    coord_record_t *ex2 = find_coord(coordmap, -1, -2);

    if (ex2 == NULL)
        fprintf(debug,"Failure to find coord (%d, %d)\n", -1, -2);
    else
        fprintf(debug,"Found coordinate of room with room id %d\n",
                ex2->r->id);

    room_t *z = malloc(sizeof(room_t));
    z->id = 3;

    /* When compiled and run, this portion of the example demonstrates to
     * future developers how the add_coord() function should block
     * double-assigning of coordinates. This is essential for the
     * DFS function in DFS.c
     */
    fprintf(debug,
            "Test to see if try_add_coord() correctly blocks double-assigning:\n");
    fprintf(debug,
            "(Should view an error message below:)\n");
    fclose(debug);

    try_add_coord(coordmap, 5, 6, z);
    free(r);
    free(g);
}

