#include <stdlib.h>
#include "room.h"

/* See room.h */
path_t *path_new(room_t *dest, char *direction) {

    path_t *path = malloc(sizeof(path_t));
    memset(path, 0, sizeof(path_t));
    path->direction = malloc(MAX_ID_LEN * sizeof(char));
    path->dest = dest;
    path->through = NULL;
    // will need a function to add item pointer to through
    strncpy(path->direction, direction, MAX_ID_LEN);

    return path;
}

/* See room.h */
int path_free(path_t *path) {
    free(path->direction);
    // delete_all_conditions(path->conditions);
    free(path);
    //will need to free item associated with path
    return SUCCESS;
}

/* See room.h */
int delete_all_paths(path_hash_t* paths) {
    path_t *current_path, *tmp;
    HASH_ITER(hh, paths, current_path, tmp) {
        HASH_DEL(paths, current_path);  /* deletes (paths advances to next) */
        path_free(current_path);             /* free it */
    }
    return SUCCESS;
}
