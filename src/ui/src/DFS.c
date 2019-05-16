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

//#define NORTH "north"
//#define EAST "east"

/* Dummy function:
 * We will use the hashing functions provided by game state
 * to access these paths in each room
 */
room_t *find_room(room_t *curr, char *direction)
{
  /*
  if (curr->hash == NULL) {
    fprintf(stderr, "No adjacent rooms\n");
    return NULL;
    }*/
  room_t *adj = NULL;
  /*  
  room_hash_t *head = curr->hash;
  else
    HASH_FIND_STR(head, direction, adj);
  */
  return adj;
}


int assign(coord_record_t *coordmap, int how_north,
	   int how_east, room_t* room) 
{
  while (SUCCESS) {
        //checks if the coordinate has already been assigned
    int x = add_coord(coordmap, how_north, how_east, room);

    //returns SUCCESS if it has been assigned correctly, or failure if it has
    //already been assigned but to a different room id 
    if(x != SUCCESS)
      return FAILURE;



    /* TO-DO: 
     * We will find a better way to implement this so that
     * we do not need to malloc this string every time we 
     * call the assign fcn.
     * Also, this would change if game state decides to
     * use ENUMS instead of STRING keys for the hash*/


    char *north = (char*) malloc(6 * sizeof(char));
    strcpy(north, "north");
    
    room_t *find_room_north = find_room(room, north);
    if (find_room_north != NULL) {
      int north = assign(coordmap, how_north+1, how_east, find_room_north);
      if (north == FAILURE) {
        return FAILURE;
      }
    } 
    char *east = (char*) malloc(5*sizeof(char));
    strcpy(east, "east");
    
    room_t *find_room_east = find_room(room, east);
    if (find_room_east != NULL) {
      int east = assign(coordmap, how_north, how_east+1, find_room_east);
      if (east == FAILURE) {
        return FAILURE;
      }
    }

    char *south = (char*) malloc(6*sizeof(char));
    strcpy(south, "south");

    room_t *find_room_south = find_room(room, south);
    if (find_room_south != NULL) {
      int south = assign(coordmap, how_north-1, how_east, find_room_south);
      if (south == FAILURE) {
        return FAILURE; 
      }
    }

    char *west = (char*) malloc(6*sizeof(char));
    strcpy(west, "west");
    
    room_t *find_room_west = find_room(room, west);
    if (find_room_south != NULL) {
      int west = assign(coordmap, how_north, how_east-1, find_room_west);
      if (west == FAILURE) {
        return FAILURE;
      }
    }

    return SUCCESS;
  }
}

int check_valid_map(/*may pass in info from WDL*/)
{
  //Set hash to NULL
  coord_record_t *coordmap = NULL;

  //initial: Read initial room that player begins in out of WDL
  room_t *initial = NULL; /*dummy line of code, delete later*/

  //Coord for initial room arbitrarily set to be (0,0)
  int r =  assign(coordmap, 0, 0, initial);
  return r;
}


/* Cannot fully test this function without Game State's hash structs
 * and functions for finding items in hash. We realized that rewriting all
 * of these for testing would be reinventing the wheel and will
 * make writing extensive tests a seperate Sprint 3 task (once game state
 * structs have been merged to master) */

/*
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
*/
