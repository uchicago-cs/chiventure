#include <stdlib.h>
#include "path.h"

/* See path.h */
int delete_all_conditions(condition_t *conditions) {
    condition_t *elt, *tmp;
    LL_FOREACH_SAFE(conditions, elt, tmp) {
        LL_DELETE(conditions, elt);
        free(elt);
    }
    return 1;
}

/* See path.h */
path_t *path_new(char *path_id) {
    path_t *path = malloc(sizeof(path_t));
    path->path_id = malloc(MAX_ID_LEN * sizeof(char));
    path->conditions_list = NULL;

    strcpy(path->path_id, path_id);

    return path;
}

/* See path.h */
int path_free(path_t *path) {
    free(path->path_id);
    delete_all_conditions(path->conditions_list);
    free(path);
    return 1;
}

/* See path.h */
int add_path_to_hash(path_hash_t all_paths, char *path_id, path_t *path) {
    path_t *s;
    HASH_FIND_STR(all_paths, path_id, s);
    if (s != NULL) {
        printf("FATAL: path_id already used!\n");
        exit(1);
    }
    HASH_ADD_STR(all_paths, path_id, path);
    return 1;
}

/* See path.h */
int delete_all_paths(path_hash_t paths) {
    path_t *current_path, *tmp;
    HASH_ITER(hh, paths, current_path, tmp) {
        HASH_DEL(paths, current_path);  /* delete it (paths advances to next) */
        path_free(current_path);             /* free it */
    }
    return 1;
}


/* Get list of paths from room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  pointer to hashtable of paths from room
 */
path_t *list_paths(room_t *room) {
  return room->paths;
}

//returns path to given room given hashtable of paths and room id
path_t *path_to_room(path_hash_t paths, char* room_id) {
  path_t *path;
  HASH_FIND_STR(paths, room_id, path);
  return path;
}

/* FOR ACTION MANAGEMENT
* go through hashtable of attributes
* check path for equal
* see item.h for fxn that checks equality
*/