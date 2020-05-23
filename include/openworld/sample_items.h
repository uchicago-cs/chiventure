#ifndef _SAMPLE_ITEM_H
#define _SAMPLE_ITEM_H

#include "../game-state/game_state_common.h"
#include "../game-state/item.h"
#include "sample_items.h"

/*get_desc_item returns {item_id, short_desc, long_desc} given
* an item name. If it is one of the default item names then 
* return the default description strings, else return the name
* and set short_desc, long_desc to NULL (to hopefully be filled
* later down the line).
* Input:
*	- char *name: the name of the item
* Output:
*	- char **: an array of strings formatted as {item_id, short_desc, long_desc}
*/
char **get_desc_item(char *name);

/* item_list_new creates a new item_list_t struct
* (Surprisingly this isn't in game-state/item.h,
* but I use item_list_t's in my functions later on,
* so this had to be made. Short and sweet).
* Input: none
* Output: a calloc-ed empty item_list_t
*/
item_list_t *item_list_new();

/* item_list_free frees an item_list_t struct
* the complementary function to item_list_new.
* Input: a item_list_t*
* Output: none
*/
void item_list_free(item_list_t *llist);

/*add_items_to_llist adds n items to the linked list given a set
* of n descriptor strings. 
* Input:
*	- item_list_t *llist: a current list of items
*	- char **ids: an array of item_id strings 
*	- count: the length of ids
*
* Output:
*	- item_list_t: an  updated item list
*/
item_list_t *add_items_to_llist(item_list_t *llist, char **ids, int count);

/* get_allowed_items returns the subset of defined default items
* that are allowed for a given room name. If the room name doesn't
* have any default approved items, return the original item list.
* However, if the room name does have approved items, then add
* these additional items to whatever is in llist. If llist is NULL,
* then you'll return only the list of approved items. If for some reason
* you want to add additional items to the allowed items list, then you
* would pass these in through llist.
*
* Input:
*	- char *name: room name
*	- item_list_t *llist: an empty (or not empty) list of items
*
* Output:
*	- an updated llist
*/
item_list_t* get_allowed_items(char *name, item_list_t *llist);

#endif /* _SAMPLE_ITEM_H */
