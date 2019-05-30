#include <stdlib.h>
#include "path.h"


/* See path.h */
int delete_all_conditions(condition_list_t conditions) {
    condition_t *elt, *tmp;
    LL_FOREACH_SAFE(conditions, elt, tmp) {
        LL_DELETE(conditions, elt);
        free(elt);
    }
    return SUCCESS;
}

/* See path.h */
path_t *path_new(char *direction) {
    path_t *path = malloc(sizeof(path_t));
    memset(path, 0, sizeof(path_t));
    path->direction = malloc(MAX_ID_LEN * sizeof(char));
    path->conditions = NULL;

    strcpy(path->direction, direction);

    return path;
}

/* See path.h */
int path_free(path_t *path) {
    free(path->direction);
    delete_all_conditions(path->conditions);
    free(path);
    return SUCCESS;
}

/* See path.h */
int add_path_to_hash(path_hash_t all_paths, char *direction, path_t *path) {
    path_t *s;
    HASH_FIND_STR(all_paths, direction, s);
    if (s != NULL) {
        printf("FATAL: direction already used!\n");
        exit(1);
    }
    HASH_ADD_STR(all_paths, direction, path);
    return SUCCESS;
}

/* See path.h */
int add_condition_to_path(path_t *path, condition_t *condition) {
    LL_PREPEND(path->conditions, condition);
    return SUCCESS;
}

/* See path.h */
int delete_all_paths(path_hash_t paths) {
    path_t *current_path, *tmp;
    HASH_ITER(hh, paths, current_path, tmp) {
        HASH_DEL(paths, current_path);  /* delete it (paths advances to next) */
        path_free(current_path);             /* free it */
    }
    return SUCCESS;
}

/* TO-DO
* FOR WDL
* Figure out way to create path struct
*/


