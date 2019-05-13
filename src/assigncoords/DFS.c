/*
 * This file contains the functions needed to achieve Depth
 * First Search of a list of rooms
 *
 * See coordinate.h for coordiante struct reference.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "utils.h"
#include "coordinate.h"

/*For now, the hash will be a global variable.
 * Can pass it around as an argument instead if we need to */
coord_record_t *coordmap;

int begin_depth_first_search(/*may pass in info from WDL*/)
{
  //Set hash to NULL
  coordmap = NULL;
  
  //initial: Read initial room that player begins in out of WDL
  room *initial = NULL; /*dummy line of code, delete later*/
  
  //Coord for initial room arbitrarily set to be (0,0)
  int r =  assign(0, 0, initial);
  return r;
}



int assign(int how_north, int how_east, room* room) 
{
  while (SUCCESS) {
    
    //checks if the coordinate has already been assigned
    coord_record_t *coord_information = find_coord(how_north, how_east);
    int = add_coord(how_north, how_east, coord_information);

    //returns SUCCESS if it has been assigned correctly, or failure if it has
    //already been assigned but to a different room id 
    if(int == SUCCESS){
      return SUCCESS;
    } else {
      return FAILURE; 
      break();
    }

    //adds the coordinate to the hash_tablex

    coord_record_t *north_room = find_coord(how_north+1, how_east);
    if (north_room != NULL) {
      int north = assign(how_north+1, how_east, north_room->r);
      if (north == FAILURE) {
        return FAILURE;
        break(); 
      }
    } 

    coord_record_t *east_room = find_coord(how_north, how_east+1);
    if (east_room != NULL) {
      int east = assign(how_north, how_east+1, east_room->r);
      if (east == FAILURE) {
        return FAILURE;
        break(); 
      }
    }

    coord_record_t *south_room = find_coord(how_north-1, how_east);
    if (south_room != NULL) {
      int south = assign(how_north+1, how_east, south_room->r);
      if (south == FAILURE) {
        return FAILURE;
        break(); 
      }
    }

    coord_record_t *west_room = find_coord(how_north, how_east-1);
    if (west_room != NULL) {
      int west = assign(how_north+1, how_east, south_room->r);
      if (west == FAILURE) {
        return FAILURE;
        break(); 
      }
    }

    break;
  }
  
  return SUCCESS;
}
 


  
Set coord (how_north,how_east) (add to hash table and struct)
Mark room done


If (north exists)
	//dont need to check if marked done-- it will check once it calls the fcn recursively
Int = assign(how_north+1, how_east north room pointer);
If int = 0

If (east exists)
assign(how north, how_east +1, east room)
If (south exists)

assign(how_north -1, how_east, south room id);

If (west exists)
Recursive call: assign(how_north, how_east - 1, west room id);




	Return success
 
  }


