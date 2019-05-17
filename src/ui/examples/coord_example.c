#include<stdio.h>
#include <stdlib.h>
#include "coordinate.h"
#include "assert.h"

/* for basic testing of compilation
 * Will implement much more testing later
 */
int main()
{
  /* Hash must be initialized to NULL (see uthash documentation) */
  coord_record_t *coordmap = NULL;

  /*Initial room must be added prior to calling add_coord() function
   * because null hashmap cannot be sent into add_coord()
   */
  coord_record_t *cr = malloc(sizeof(coord_record_t));
  memset(cr, 0, sizeof(coord_record_t));

  cr->key.x = 0;
  cr->key.y = 0;

  room_t *initial = malloc(sizeof(room_t));
  initial->id = 123;
  cr->r = initial;

  HASH_ADD(hh, coordmap, key, sizeof(coordinate_t), cr);
  if (coordmap != NULL)
    fprintf(stderr,"Added initial room to hashmap\n");
  
  coord_record_t *test = find_coord(coordmap, 1, 2);
  if (test == NULL)
    fprintf(stderr,
	    "find_coord(): Successfully returns NULL when not found\n");

  room_t *r = malloc(sizeof(room_t));
  r->id = 456;
  add_coord(coordmap, 5, 6, r);
  if (coordmap == NULL)
    fprintf(stderr,"ERROR: Add_coord() returned an empty hashmap\n");
  
  room_t *g = malloc(sizeof(room_t));
  g->id = 2;
  add_coord(coordmap, -1, -2, g);

  coord_record_t *example = find_coord(coordmap, 5, 6);
  if (example == NULL)
    fprintf(stderr,"Failure to find coord (%d, %d)\n", 5, 6);
  else
    fprintf(stderr,"Found coordinate of room with room id %d\n",
	    example->r->id);

  coord_record_t *ex2 = find_coord(coordmap, -1, -2);

  if (ex2 == NULL)
    fprintf(stderr,"Failure to find coord (%d, %d)\n", -1, -2);
  else
    fprintf(stderr,"Found coordinate of room with room id %d\n",
	    ex2->r->id);
  
  room_t *z = malloc(sizeof(room_t));
  z->id = 3;
  fprintf(stderr,
	  "Test to see if add_coord() correctly blocks double-assigning:\n");
  add_coord(coordmap, 5, 6, z);

  free(r);
  free(g);
}

