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
  path->path_id = path_id;
  path->conditions = NULL;
  return path;
}

/* See path.h */
int path_free(path_t *path) {
  //free(path->path_id);
  delete_all_conditions(path->conditions);
  free(path);
  return 1;
}

/* See path.h */
int add_path_to_hash(all_paths_t all_paths, int path_id, path_t *path) {
    path_t *s;
    HASH_FIND_INT(all_paths, &path_id, s);
    if (s != NULL) {
        printf("FATAL: path_id already used!\n");
        path(0);
    }
    HASH_ADD_INT(all_paths, path_id, s);
    return 1;
}

/* See path.h */
int delete_all_paths(all_paths_t paths) {
    path_t *current_path, *tmp;
    HASH_ITER(hh, paths, current_path, tmp) {
        HASH_DEL(paths, current_path);  /* delete it (paths advances to next) */
        path_free(current_path);             /* free it */
    }
    return 1;
}