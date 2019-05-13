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

int assign(int how_north, int how_east, room* room) {
  while
  if((find_coord(int x, int y)) != NULL){
    return SUCCESS;
  } else {
    return FAILURE; 
  }
 )
	//if (room marked done)
	//Return success;
	//If (check_if_assigned(how_north, how_east, room->id or room)) {
	//checkassigned is true if the coord is a. Assigned already to b. A new room, not the same room
	//Return failure;


  
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


