#include<stdio.h>
#include "coordinate.h"


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
coord_record_t *find_coord(coordinate_t key)
{
  coord_record_t *cr;
  HASH_FIND(hh, coordmap, &key, sizeof(coordinate_t), &cr);
  //....
  //....
  //....
  return NULL;
}

/* add_coord:
 * - Implementation  Will use HASH_FIND to check uniqueness
 *   If unique, creates a new coord_key_t and add to map using HASH_ADD
 */
void add_coord(coordinate_t c, room *r)
{
  return;
}
