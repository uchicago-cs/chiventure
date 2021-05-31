#include <stdlib.h>
#include "game-state/game_action.h"
#include "game-state/room.h"
#include "cli/util.h"

/* See room.h */
path_t *path_new(room_t *dest, char *direction)
{
    path_t *path = malloc(sizeof(path_t));
    memset(path, 0, sizeof(path_t));
    path->direction = malloc(MAX_ID_LEN * sizeof(char));
    path->dest = dest;
    path->conditions = NULL;
    path->through = NULL;
    // will need a function to add item pointer to through
    strncpy(path->direction, direction, MAX_ID_LEN);
    case_insensitize(path->direction);
    
    return path;
}

/* See room.h */
int path_new_conditions(path_t *path, list_action_type_t *act)
{
    LL_APPEND(path->conditions, act);
    return SUCCESS;
}    

/* See room.h */
int path_free(path_t *path)
{
    free(path->direction);
    
    free(path);
    //will need to free item associated with path
    return SUCCESS;
}

/* See room.h */
int delete_all_paths(path_hash_t* paths)
{
    path_t *current_path, *tmp;
    HASH_ITER(hh, paths, current_path, tmp)
    {
        HASH_DEL(paths, current_path);  /* deletes (paths advances to next) */
        path_free(current_path);             /* free it */
    }
    return SUCCESS;
}

/* See room.h */
int remove_condition(path_t *path, list_action_type_t *a)
{
    int check;
    check = delete_action(&path->conditions, a);

    if (path->conditions == NULL) {
	get_attribute(path->through, "OPEN")->attribute_value.bool_val = true;
    }
    a->act->room = NULL;
    a->act->direction = NULL;
    return check;
}

