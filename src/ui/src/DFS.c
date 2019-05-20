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

/* create_valid_map:
 * Return values:
 * - Returns pointer to  hashmap of coordinates upon SUCCESS
 * - Returns NULL if unable to assign a valid coordinate system
 *   (This means create_valid_map returns NULL when assign() returns FAILURE)
 */

coord_record_t *create_valid_map(/*will pass in info from Game State*/)
{
  //Must set hash to NULL (see uthash documentation)
  coord_record_t *coordmap = NULL;

  //initial: Read initial room that player begins in out of Game State struct
  room_t *initial = NULL; /*dummy line of code, delete later*/

  /* Initial room must be added prior to calling assign() function  
   * because null hashmap cannot be sent into assign()
   */
  coord_record_t *cr = malloc(sizeof(coord_record_t));
  memset(cr, 0, sizeof(coord_record_t));

  /* Initial coordinate is arbitrarily set to be (0,0)
   */
  cr->key.x = 0;
  cr->key.y = 0;
  cr->r = initial;

  HASH_ADD(hh, coordmap, key, sizeof(coordinate_t), cr);

  /* Testing: Can be taken out later
   * if (coordmap != NULL)
   * fprintf(stderr,
   *    "check_valid_map() has successfully added initial room to hashmap\n");
   * else
   *  fprintf(stderr,"ERR: check_valid_map could not add initial room to hashmap\n");
   * --- end testing --- */

  
  /* Begin DFS search */
  int r =  assign(coordmap, 0, 0, initial);
  if (r == FAILURE)
    return NULL;
  return coordmap;
}


