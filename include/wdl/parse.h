/*
 * Header file for wdl/yaml parsing functions and related utilities
 */

#ifndef INCLUDE_PARSE_H
#define INCLUDE_PARSE_H

#include "validate.h"
#include "wdl_common.h"

/* Helper function for creating doc object from defined FILE_PATH */
obj_t *get_doc_obj(char *fpath);

/*
 * extract_objects()
 * extracts the a list of objects associated with an attribute of the primary object;
 * used to get a list of rooms, items, and players
 * note that this function will only return if it determines all the objects are valid
 *
 * Parameters:
 *  - obj: The document object
 *  - str: the attribute asssociated with the desired objects
 *
 * Returns:
 *  - a list of objects
 *  - null if attribute does not have associated objects, or if no such attribute exists
 */
obj_t *extract_objects(obj_t *obj, char *str);


// /* Given a room id and the list of all items in a game returns
//  * a list with all the items in that room */
// obj_t* get_items_in_room(char* room_id, obj_t* all_items);


/*
 * get_item_actions()
 * gets a list of actions assoiciated with a given item
 *
 * parameters:
 *  - item: the item for which to get the actions
 *
 * returns:
 *  - a linked list of type-checked action attributes
 *  - a null if any of the actions are malformed or if no actions are present
 */
obj_t *get_item_actions(obj_t *item);

/*
 * get_npc_dialogue()
 * gets the dialogue object assoiciated with an NPC
 *
 * parameters:
 *  - npc: the NPC
 *
 * returns:
 *  - a dialogue object containing two components: "nodes" and "edges"
 *  - a null if any of the components are malformed or if no dialogue is present
 */
obj_t *get_npc_dialogue(obj_t *npc);

#endif /* INCLUDE_PARSE_H */
