#include<stdio.h>
#include <stdlib.h>
#include "coordinate.h"
#include "assert.h"

/* for basic testing of compilation
 * Will implement much more testing later
 */
int main()
{
  coord_record_t *coordmap = NULL;
  coordmap = find_coord(coordmap, 1, 2);
  if (coordmap == NULL)
    fprintf(stderr,
	    "find_coord: Successfully returns NULL when not found\n");

  room_t *r = malloc(sizeof(room_t));
  r->id = 1;
  add_coord(coordmap, 5, 6, r);
  if (coordmap == NULL)
    fprintf(stderr,"ERROR: Add_coord returned an empty hashmap\n");
  
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

