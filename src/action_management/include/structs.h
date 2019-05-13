/* In the absence of the Game State team's code, 
 * here are some theoretical structs containing our needed components.
 * We use these structs in our implementation of basic action commands.
*/


/* A NPC struct containing:
 * - dialogue: a line of dialogue NPC will say when spoken to 
 */
struct npc_struct {
    char *dialogue; 
};


/*  A room struct containing:
 * - NPCs: linked list of pointers to NPC_structs
 * - objects: linked list of pointers to object_structs
 * - overall_map: a 2D array that would allow us to use x y coordinates
 */
struct room_struct {
    list_t *npcs;
    list_t *objects;
    int **overall_map;
};


/* An object struct containing:
 * - allowed_actions: an integer array that contains enumerated "actions" 
 * - num_allowed_actions: the number of elements in the allowed_actions array
 */
struct object_struct {
    int *allowed_actions;
    int num_allowed_actions;
};


/* A player struct containing:
 * - inventory: an inventory struct containing all items in inventory
 */
struct player_struct {
    struct inventory_struct *inventory;
};
