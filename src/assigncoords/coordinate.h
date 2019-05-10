/*
 * A two-dimensional coordinate data structure
 */

#ifndef INCLUDE_COORDINATE_H_
#define INCLUDE_COORDINATE_H_

#include <stdbool.h>
#include "common.h"
#include "uthash.h"

/* A coordinate in two-dimensional space */
typedef struct {
    double x;
    double y;
} coordinate_t;

/* Structure to make coordinate hashable
 * Defines a coordinate_t as the key
 */
typedef struct coord_record {
  coordinate_t key;
  //room *r;
  UT_hash_handle hh;
} coord_record_t;

/* find_coord
 * - Implementation will use HASH_FIND to find coord_record
 *
 * Returns:
 *
 * - returns coord_record_t struct (contains room pointer) if room exists 
 * - returns NULL if key not in hash
 *
 * NOTE:
 * - call this function (once it's implemented) in DFS to check
 * whether we have assigned a room a coord yet
 *
 * NOTE:
 *
 * perhaps I will make the arguments int x, int y instead. I can just
 * assemble them into a coordinate in this function, making one less
 * step for you in DFS
 */
coord_record_t *find_coord(coordinate_t c);

/* add_coord:
 * - Implementation  Will use HASH_FIND to check uniqueness
 *   If unique, creates a new coord_key_t and add to map using HASH_ADD
 */
void add_coord(coordinate_t c, room *r);




#endif /* INCLUDE_COORDINATE_H_ */
