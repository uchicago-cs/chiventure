/*
 * This file contains the functions needed to achieve Depth
 * First Search of a list of rooms
 *
 * See coordinate.h for coordiante struct reference.
 */

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "coordinate.h"

/*For now, the hash will be a global variable.
 * Can pass it around as an argument instead if we need to */
coord_record_t *coordmap;

int check_valid_map(/*may pass in info from WDL*/)
{
  //Set hash to NULL
  coordmap = NULL;
  
  //initial: Read initial room that player begins in out of WDL
  room_t *initial = NULL; /*dummy line of code, delete later*/
  
  //Coord for initial room arbitrarily set to be (0,0)
  int r =  assign(0, 0, initial);
  return r;
}

room_t *find_room(room_t *room, char* direction)
{

}

int assign(int how_north, int how_east, room_t* room) 
{
  while (SUCCESS) {
    
    //checks if the coordinate has already been assigned
    int x = add_coord(how_north, how_east, room);

    //returns SUCCESS if it has been assigned correctly, or failure if it has
    //already been assigned but to a different room id 
    if(x != SUCCESS)
      return FAILURE;

    //adds the coordinate to the hash_table



    room_t *find_room_north = find_room(room, 'north');
    if (find_room_north != NULL) {
      int north = assign(how_north+1, how_east, find_room_north);
      if (north == FAILURE) {
        return FAILURE;
      }
    } 

    room_t *find_room_east = find_room(room, 'east');
    if (find_room_east != NULL) {
      int east = assign(how_north, how_east+1, find_room_east);
      if (east == FAILURE) {
        return FAILURE;
      }
    }

 
    room_t *find_room_south = find_room(room, 'south');
    if (find_room_south != NULL) {
      int south = assign(how_north-1, how_east, find_room_south);
      if (south == FAILURE) {
        return FAILURE; 
      }
    }

    room_t *find_room_south = find_room(room, 'south');
    if (find_room_south != NULL) {
      int west = assign(how_north, how_east-1, find_room_south);
      if (west == FAILURE) {
        return FAILURE;
      }
    }

    return SUCCESS;
  }
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
  add_coord(0, 0, r);

  int initial = assign(0, 0, r);
  if (initial == SUCCESS)
    fprintf(stdout, "Successfully assigned coordinates");

  //coord_record_t *a = NULL;
  //coord_record_t *b = NULL;
  //  HASH_ITER(hh, coordmap, a, b);

  free(r);
}