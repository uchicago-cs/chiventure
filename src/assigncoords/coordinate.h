/*
 * A two-dimensional coordinate data structure
 * and corresponding hashmap
 */

#ifndef INCLUDE_COORDINATE_H_
#define INCLUDE_COORDINATE_H_

#include<stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "uthash.h"

/*Dummy room struct */
typedef struct {
  int id;
} room_t;

/* A coordinate in two-dimensional space */
typedef struct {
    int x;
    int y;
} coordinate_t;

/* Structure to make coordinate hashable
 * Defines a coordinate_t as the key
 */
typedef struct coord_record {
  coordinate_t key;
  room_t *r;
  UT_hash_handle hh;
} coord_record_t;


void coord_init(coordinate_t *c, int x, int y);


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
 */
coord_record_t *find_coord(int x, int y);

/* add_coord:
 * - Implementation  Will use HASH_FIND to check uniqueness
 *   If unique, creates a new coord_key_t and add to map using HASH_ADD
 */
void add_coord(int x, int y, room_t *r);

#endif /* INCLUDE_COORDINATE_H_ */
