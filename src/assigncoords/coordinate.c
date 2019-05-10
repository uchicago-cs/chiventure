#include<stdio.h>
#include <stdlib.h>
#include "coordinate.h"
#include "assert.h"

coord_record_t *coordmap;

void coord_init(coordinate_t *c, int x, int y)
{
  assert (c != NULL);
  c->x = x;
  c->y = y;
  return;
}

/* find_coord:
 * See coordinate.h for more details
 * Returns NULL if coord not found in hash
 */
coord_record_t *find_coord(int x, int y)
{
  coordinate_t key;
  coord_init(&key, x, y);
  coord_record_t *cr = NULL;
  HASH_FIND(hh, coordmap, &key, sizeof(coord_record_t), cr);
  return cr;
}

/* add_coord:
 * - Implementation  Will use HASH_FIND to check uniqueness
 *   If unique, creates a new coord_key_t and add to map using HASH_ADD
 */
void add_coord(int x, int y, room_t *r)
{
  coordinate_t key;
  coord_record_t *cr = find_coord(x, y);

  if (cr == NULL) {
    fprintf(stderr,"Adding coord (%d, %d) to hash\n", x, y);
    
    /* Only runs if find_coord does not find coord
    already existing in hashtable */
    coord_init(&key, x, y);
    cr = malloc(sizeof(coord_record_t));
    //uthash warning to use  memset when key is a structure
    memset(cr, 0, sizeof(coord_record_t));
    
    cr->key = key;
    cr->r = r;
    HASH_ADD(hh, coordmap, key, sizeof(coord_record_t), cr); 
  }
  
  return;
}

/* for basic testing of compilation
 *Will implement much more testing later
 */
int main()
{
  coordmap = NULL;
  coordmap = find_coord(1, 2);
  if (coordmap == NULL)
    fprintf(stdout,
	    "find_coord: Successfully returns NULL when not found\n");

  room_t *r = malloc(sizeof(room_t));
  r->id = 1;
  add_coord(5, 6, r);

  coord_record_t *example = find_coord(5, 6);
  if (example == NULL)
    fprintf(stderr,"Failure to add coord\n");
  else
    fprintf(stdout,"Found coordinate of room with room id %d",
	    example->r->id);
	    
  free(r);
}

