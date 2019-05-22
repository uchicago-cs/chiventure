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
 * - coordmap is both an in and out parameter, so must be non-NULL
 * - x, y are the respective coordinates. They will be bundled
 *  into a coordinate key for hashing
 * - r is a pointer to the room to assign the coords to
 *
 * Return value:
 * - returns SUCCESS if does not find coordinate and add its
 * - returns FAILURE if it finds coordinate already and 
 *   the coord is mapped to a different room
 *
 * Note:
 * - Printing debug statements to a seperate txt file
 *
 * Info on struct keys from uthash guide:
 * https://troydhanson.github.io/uthash/userguide.html#_structure_keys
 */
int add_coord(coord_record_t *coordmap, int x, int y, room_t *r)
{
  coord_record_t *cr = find_coord(coordmap, x, y);

  /* File created for debug statments */
  FILE *debug = fopen("ui_debug.txt", "a");  

  /* Only runs if find_coord does not find coord
   *  already existing in hashtable */
  if (cr == NULL) {
    fseek(debug, 0, SEEK_END);
    fprintf(debug,"Adding coord (%d, %d) to hash\n", x, y);
    cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));    //uthash requirement for struct keys
    cr->key.x = x;
    cr->key.y = y;
    cr->r = r;
    HASH_ADD(hh, coordmap, key, sizeof(coordinate_t), cr); 
    fclose(debug);
    return SUCCESS;
  }
  
  else {
    /* If assigned to itself, no conflicts */
    if (cr->r->id == r->id){
      fclose(debug);
      return SUCCESS;
    }

    fseek(debug, 0, SEEK_END);    
    fprintf(debug,
	    "ERROR: add_coord(): This coordinate has already been assigned.\n");  
    fclose(debug);
    return FAILURE;
  }
}
  
