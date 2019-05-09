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


int assign(int how_north, int how_east, room* room) {
	//if (room marked done)
	//Return success;
	//If (check_if_assigned(how_north, how_east, room->id or room)) {
	//checkassigned is true if the coord is a. Assigned already to b. A new room, not the same room
	//Return failure;


Set coord (how_north,how_east) (add to hash table and struct)
Mark room done

If (north exists)
	//don’t need to check if marked done-- it will check once it calls the fcn recursively
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
