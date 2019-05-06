/* In the absence of the Game State team's code, 
 * here are some of the theoretical structs we "operate" on.
 * We use these structs in our implementation of basic action commands.
*/

/* The NPC struct contains the dialogue NPC will say when talked to.
 * Parameters:
 * dialogue - a line of dialogue NPC will say when spoken to 
 */
struct NPC_struct {
    char *dialogue; 
}

/* The room struct contains a list of NPCs and objects in the room.
 * We weren't really sure what it would look like but gave a bare bones
 * summary here of what we might expect, given the functions we have planned.
 *  Parameters:
 * NPCs - linked list of pointers to NPC_structs
 * objects - linked list of pointers object_structs
 * overall_map - the map as an array ? (not sure how this would be implemented)
 */
struct room_struct {
	list_t *NPCs;
	list_t *objects;
    int *overall_map;
};


/* Our idea for how the object_struct should discriminate allowed vs disallowed commands
 * was that it should have an array of integers that are represented by our actions enumerated type.
 * Parameters:
 * allowed_actions - an integer ARRAY that contains ENUMERATED TYPE "actions" (see actionmanagement.h)
 * num_allowed_actions - keeps track of how many values are inside of the array, as is standard when dealing w arrays
 */
struct object_struct {
	int *allowed_actions;
	int num_allowed_actions;
};

/* The important thing to take away here is the fact that we have the inventory
 * as part of the player_struct! This is why we use player_struct as an input in our
 * function for altering the inventory. Note, we also assume the inventory uses
 * enumerated values for items. This is not necessary.
 * Parameters:
 * alive - specifies TRUE if player alive, FALSE if dead
 * inventory - array of enumerate type "items" 
 */
struct player_struct {
	bool alive;
    int *inventory; // an array of enumerated type ITEMS
};
