/*
 * Header file for loading item object into game struct
 */

#ifndef INCLUDE_LOAD_ITEM_H
#define INCLUDE_LOAD_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <parse.h>

/*
 * Function to load a single item into the item_t struct
 *
 * input: 
 *   - a wdl item object as defined above
 * output: 
 *   - a pointer to the item_t struct that has been loaded 
 */
item_t* load_item(wdl_item_t* item);



#endif /* INCLUDE_LOAD_ITEM_H */
