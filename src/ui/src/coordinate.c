#include<stdio.h>
#include <stdlib.h>
#include "coordinate.h"
#include "assert.h"

//coord_record_t *coordmap;

void coord_init(coordinate_t *c, int x, int y)
{
  assert (c != NULL);
  c->x = x;
  c->y = y;
  return;
}

/* find_coord:
 *
 * See coordinate.h for more details
 * Returns NULL if coord not found in hash
 */
coord_record_t *find_coord(coord_record_t *coordmap, int x, int y)
{
  coordinate_t *key = malloc(sizeof(coordinate_t));
  memset(key, 0, sizeof(coordinate_t));
  coord_init(key, x, y);

  coord_record_t *cr = malloc(sizeof(coord_record_t));
  memset(cr, 0, sizeof(coord_record_t));
  HASH_FIND(hh, coordmap, key, sizeof(coordinate_t), cr);

  return cr;
}

/* add_coord:
 * Parameters:
 * - coordmap is both an in and out parameter
 * - x, y are the respective coordinates. They will be bundled
 *  into a coordinate key for hashing
 * - r is a pointer to the room to assign the coords to
 *
 * Return value:
 * - returns SUCCESS if does not find coordinate and add its
 * - returns FAILURE if it finds coordinate already and 
 *   the coord is mapped to a different room
 */
int add_coord(coord_record_t *coordmap, int x, int y, room_t *r)
{
  coord_record_t *cr = find_coord(coordmap, x, y);
  /* Only runs if find_coord does not find coord
    already existing in hashtable */
  
  if (cr == NULL) {
    fprintf(stderr,"Adding coord (%d, %d) to hash\n", x, y);

    cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));    
    cr->key.x = x;
    cr->key.y = y;
    cr->r = r;
    HASH_ADD(hh, coordmap, key, sizeof(coordinate_t), cr); 
    if (coordmap != NULL)
      fprintf(stderr, "Coordmap nonempty\n");
    return SUCCESS;
  }

  else {
    if (cr->r->id == r->id)
      return SUCCESS;
  }
  fprintf(stderr,
	  "add_coord(): This coordinate has already been assigned.\n");  
  return FAILURE;
}

/* for basic testing of compilation
 * Will implement much more testing later
 */

/* This compiles but has been moved to coord_example.c 
 * in ../examples/

int main()
{
  coordmap = NULL;
  coordmap = find_coord(1, 2);
  if (coordmap == NULL)
    fprintf(stderr,
	    "find_coord: Successfully returns NULL when not found\n");

  room_t *r = malloc(sizeof(room_t));
  r->id = 1;
  add_coord(5, 6, r);

  room_t *g = malloc(sizeof(room_t));
  g->id = 2;
  add_coord(-1, -2, g);

  coord_record_t *example = find_coord(5, 6);
  if (example == NULL)
    fprintf(stderr,"Failure to find coord (%d, %d)\n", 5, 6);
  else
    fprintf(stderr,"Found coordinate of room with room id %d\n",
	    example->r->id);

  coord_record_t *ex2 = find_coord(-1, -2);

  if (ex2 == NULL)
    fprintf(stderr,"Failure to find coord (%d, %d)\n", -1, -2);
  else
    fprintf(stderr,"Found coordinate of room with room id %d\n",
	    ex2->r->id);
  
  room_t *z = malloc(sizeof(room_t));
  z->id = 3;
  fprintf(stderr,
	  "Test to see if add_coord() correctly blocks double-assigning:\n");
  add_coord(5, 6, z);

  free(r);
  free(g);
}

*/
