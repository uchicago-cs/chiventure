#ifndef _PATH_H
#define _PATH_H

#include "room.h"

/* Adds a path to the given hashtable of paths
 *
 * Parameters:
 *  hashtable the path is added to
 *  path id
 *  pointer to the path
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_path_to_hash(path_hash_t* all_paths, char* direction, path_t *path);

/* Deletes a hashtable of paths
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of paths that need to be deleted
 * Returns:
 *  SUCCESS if successful
 */
int delete_all_paths(path_hash_t* paths);

#endif