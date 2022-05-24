/* Team RPG-Openworld
*
* Gen-Structs header file
*
* gen_structs.h: This file: contains all of the necessary high level structs
* that are necessary for generating a room.
*
* Create the generation structs that will contain the necessary info for
* autogenerating a room
*
* See chiventure/src/openworld/gen_structs.c source code to see implementation.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game-state/game.h"
#include "game-state/game_state_common.h"

#ifndef GEN_STRUCTS_H
#define GEN_STRUCTS_H

/* -- STRUCTS -- */

/** itemspec_t struct
 * This struct specifies how and when an item should spawn for a specific room.
 * The struct contains:
 * - char *item_name: item name and hash key
 * - double spawn_chance: the probability of that item type spawning (0 ≤ p ≤ 1)
 * - unsigned int min_num: if the item spawns, the min quantity it will spawn with
 * - unsigned int max_num: if the item spawns, the max quantity it will spawn with
 *                         (min_num ≤ max_num)
 *   Each quantity in the prescribed interval has an equal chance of occurring.
 * - UT_hash_handle hh: hash handle for itemspec
 */
typedef struct itemspec {
    char *item_name; 
    double spawn_chance; 
    unsigned int min_num;
    unsigned int max_num;
    UT_hash_handle hh; 
} itemspec_t;

/* to differentiate between pointers to structs (above) and hash tables (below) */
typedef struct itemspec itemspec_hash_t; 

/* roomspec_t struct
* This struct will carry the necessary info for creating a room.
* The struct contains:
* - char *room_name: room name and hash key
* - char *short_desc: short description for room
* - char *long_desc: long description for room
* - int num_built: how many rooms of this type have been already built. An identifier.
* - item_hash_t *items: hash table of items in room
* - UT_hash_handle hh: hash handle for room spec
*/
typedef struct roomspec {
    char *room_name;
    char *short_desc;
    char *long_desc;
    int num_built;
    item_hash_t *items;
    itemspec_hash_t *itemspecs;
    UT_hash_handle hh;
} roomspec_t;

/* to differentiate between pointers to structs (above) and hash tables (below) */
typedef struct roomspec rspec_hash_t; 

/* specgraph_t struct
 * This struct functions as an adjacency matrix for the relationships between roomspec_t's
 * The struct contains:
 * - int num_roomspecs: The number of different roomspecs available in the game
 * - roomspec_t roomspecs: list of pointers to roomspecs corresponding to each node on specgraph
 * - int **edges: This is a pointer to a 2D array containing the information about the edges of the graph.
 *                Edges of graph represent the relationship between each roomspec (i.e. the adjacency matrix).
 *                These values will range from 0-5 and will be used to determine, for a room generated using the  
 *                room_autogenerate function, the probability that the roomspec associated with the newly generated 
 *                room will be a given roomspec. Thus, the higher the number, the more likely rooms of those roomspec 
 *                will appear next to each other.
 */

typedef struct specgraph {
    int num_roomspecs;
    roomspec_t **roomspecs;
    int **edges;
} specgraph_t;

/* gencontext_t struct
* This struct will carry the info for the generation algorithm
* The struct contains:
* - path_t *open_paths: the open path we are connecting the room to;
* - int level: this is the players current level
* - int num_open_paths: the number of openpaths that need to be generated in the room.
* - specgraph_t *specgraph: the llist of roomspect_t that each hold the room info.
*/
typedef struct gencontext {
    path_t *open_paths;
    int num_open_paths;
    int level;
    specgraph_t *specgraph;
} gencontext_t;


/* -- structs for level oriented generation -- */

/* encode maps between difficulty/rooms needed for level-oriented generation */
typedef struct roomlevel
{
    /* name of the room, hash key */
    char *room_name;        

    /* difficulty level of the room, possible value starts at 0 */
    int difficulty_level;       
       
    /* makes this structure hashable */
    UT_hash_handle hh;        
} roomlevel_t;

/* to differentiate between pointers to structs (above) and hash tables (below) */
typedef struct roomlevel roomlevel_hash_t; 


/* levelspec struct
 * This struct carries all the info needed for level-oriented generation */
typedef struct levelspec {
    /* An iterable hash table of roomlevels */
    roomlevel_t *roomlevels;

    /* number of player level thresholds */
    int num_thresholds;

    /* an array of player level thresholds;
     * each threshold is an inclusive lowerbound to the difficulty level of that index
     * e.g. {0, 5, 10}, 
     * player_level 0 to 4 is in level 0; player_level 5-9 is in level 1 etc. */  
    int *thresholds;
} levelspec_t;




/* -- FUNCTIONS -- */



/* GENCONTEXT */

/* init_gencontext
* Initializes a gencontext_t struct with the given paramaters. The gencontext
* must be pointing to some valid memory.
*
* parameters:
* - context: the gencontext* struct that we are initializing.
* - level: stores the players level.
* - openpaths: number of open paths to generate in the room
* - numnpcs: the number of npcs to generate in the room
* - specgraph: the specgraph we are choosing our roomspec from
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to initialize
*/
int init_gencontext(gencontext_t *context, path_t *open_paths, int level, int num_open_paths, specgraph_t *specgraph);

/* gencontext_new
* Creates a new gencontext_t* based off the given parameters.
*
* parameters:
* - level: stores the players level.
* - openpaths: number of open paths to generate in the room
* - numnpcs: the number of npcs to generate in the room
* - specgraph: the specgraph we are choosing our roomspec from
*
* returns:
* gencontext_t *contextnew - the new gencontext
* NULL - if fails to create a new gencontext.
*/
gencontext_t* gencontext_new(path_t *open_paths, int level, int num_openpaths, specgraph_t *specgraph);

/* gencontext_free
* Frees a gencontext_t* and returns whether or not it was successful
*
* parameters:
* - context: gencontext_t* that we are attempting to fre
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to free
*/
int gencontext_free(gencontext_t *context);

/* ITEMSPEC */

/** init_itemspec
 * Initializes an itemspec_t struct with the given parameters. 
 * 
 * parameters:
 * - itemspec: the pointer to the itemspec we are initializing. Must point to some valid memory.
 *             Its item_name array must be long enough to fit the given name.
 * - item_name: the item name. 
 * - spawn_chance: probability of the item type (for every room instance generated from the roomspec)
 *                 must be in [0, 1]
 * - min_num: the min quantity with which the item occurs, IF it occurs. 
 *            Must be ≤ max_num.
 * - max_num: the max quantity with which the item occurs, IF it occurs.
 *            Must be ≥ min_num
 * 
 * returns:
 * - SUCCESS - for success
 * - FAILURE - if failed to initalize and/or any parameter requirements were violated
 */
int init_itemspec(itemspec_t *itemspec, char *item_name, double spawn_chance, 
                                        unsigned int min_num, unsigned int max_num);

/** itemspec_new
 * Creates a new itemspec_t struct with the given parameters. 
 * 
 * parameters:
 * - item_name: the item name. 
 * - spawn_chance: probability of the item type (for every room instance generated from the roomspec)
 *                 must be in [0, 1]
 * - min_num: the min quantity with which the item occurs, IF it occurs. 
 *            Must be ≤ max_num.
 * - max_num: the max quantity with which the item occurs, IF it occurs.
 *            Must be ≥ min_num
 * 
 * returns:
 * itemspec_t* - the new itemspec
 * NULL - if failed to create a new itemspec and/or any parameter requirements were violated.
 */
itemspec_t *itemspec_new(char *item_name, double spawn_chance, 
                         unsigned int min_num, unsigned int max_num);

/** itemspec_free
 * Frees an itemspec_t* and its contents and returns whether or not it was successful.
 * 
 * parameters:
 * - itemspec: itemspec_t* that we are attempting to free
 * returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to free
 */
int itemspec_free(itemspec_t *itemspec);




/* ROOMSPEC */

/* init_roomspec
* Initializes a roomspec_t struct with the given paramaters. The roomspec
* must be pointing to some valid memory.
*
* parameters:
* - spec: the pointer to the roomspec_t we are initializing
* - room_name: the room name
* - short_desc: the short description
* - long_desc: the long description
* - items: ptr to the hash table of the items
* NOTE: Does not affect itemspec hash. Must manually add itemspecs to hash using HASH_ADD_KEYPTR.
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to initialize
*/
int init_roomspec(roomspec_t *spec, char *room_name, char *short_desc, char *long_desc, item_hash_t *items);

/* roomspec_new
* Creates a new roomspec_t* based off the given parameters.
*
* parameters:
* - room_name: the room name
* - short_desc: the short description
* - long_desc: the long description
* - items: ptr to the hash table of the items
* NOTE: Initializes itemspec hash to NULL. Must manually add itemspecs to hash using HASH_ADD_KEYPTR.
*
* returns:
* roomspec_t *roomspecnew - the new roomspec
* NULL - if fails to create a new roomspec.
*/
roomspec_t* roomspec_new(char *room_name, char *short_desc, char *long_desc, item_hash_t *items);

/* roomspec_free
* Frees a roomspec_t* and returns whether or not it was succesful.
*
* parameters:
* - spec: roomspec_t* that we are attempting to free
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to free
*/
int roomspec_free(roomspec_t *spec);

/* edges_init
* Initializes an edges struct within a specgraph struct based on given parameters
*
* parameters:
* - edges: The pointer to the 2D array of edges to be initialized
* - inp_array: 1D array of edges that will be used for initialized the 2D array
* - num_rows: Number of rows in the 2D array
* - num_cols: Number of columns in the 2D array
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to intialize
*/
int edges_init(int** edges, int* inp_array, int num_rows, int num_cols);

/* edges_new
* Creates a new edges 2D array based off the given parameters.
*
* parameters:
* - inp: 1D array of integers containing the edges (Should be length num_rows * num_cols)
* - num_rows: Number of rows in the output 2d array of edges
* - num_cols: Number of columns in the output 2d array of edges
*
* returns:
* roomspec_t *roomspecnew - the new roomspec
* NULL - if fails to create a new roomspec.
*/
int** edges_new(int* inp, int num_rows, int num_cols);

/* edges_free
* Frees a edges* and returns whether or not it was succesful.
*
* parameters:
* - edges: edges** that we are attempting to free
* - num_rows: Number of rows in edges 2D array
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to free
*/
int edges_free(int** edges, int num_rows);

/* SPECGRAPH */

/* init_specgraph
* Initializes a specgraph_t struct with the given paramaters. The specgraph
* must be pointing to some valid memory.
*
* parameters:
* - specgraph_t *specgraph: the pointer to the specgraph_t we are initializing
* - int num_roomspecs: the number of roomspecs in the graph
* - roomspec_t **roomspecs: An array of pointers to the roomspecs 
* - int **edges: A pointer to a 2D array representing the weights in the adjacency matrix
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to initialize
*/
int specgraph_init(specgraph_t *specgraph, int num_roomspecs, roomspec_t **roomspecs, int **edges);

/* specgraph_new
* Creates a new heap-allocated specgraph_t struct with the given paramaters.
*
* parameters:
* - int num_roomspecs: the number of roomspecs in the graph
* - roomspec_t **roomspecs: An array of pointers to the roomspecs 
* - int **edges: A pointer to a 2D array representing the weights in the adjacency matrix
*
* returns:
* specgraph_t *specgraph = the new specgraph
* NULL - if failed to create a specgraph
*/
specgraph_t* specgraph_new(int num_roomspecs, roomspec_t **roomspecs, int **edges);

/* specgraph_free
* Frees a specgraph_t struct and all associated memory and returns whether or not it was successful
*
* parameters:
* - specgraph: the pointer to the specgraph_t we are freeing
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to free
*/
int specgraph_free(specgraph_t *specgraph);

/* roomlevel */

/* init_roomlevel
 * Initializes a roomlevel_t struct with the given paramaters. The roomlevel_t
 * must be pointing to some valid memory.
 *
 * Parameters:
 * - map: the pointer to the roomlevel_t we are initializing
 * - room_name: the room name
 * - difficulty_level: difficulty level of the room
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to initialize
 */
int init_roomlevel(roomlevel_t *map, char *room_name, int difficulty_level);


/* roomlevel_new
 * Creates a roomlevel_t struct with the given paramaters.
 *
 * Parameters:
 * - room_name: the room name
 * - difficulty_level: difficulty level of the room
 *
 * Returns:
 * roomlevel_t *map - the new roomlevel_t
 * NULL - if failed to create a roomlevel_t
 */
roomlevel_t* roomlevel_new(char *room_name, int difficulty_level);


/* roomlevel_free
 * Frees a roomlevel_t struct and returns whether or not it was successful
 *
 * Parameters:
 * - map: the pointer to the roomlevel_t we are freeing
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to free
 */
int roomlevel_free(roomlevel_t *map);


/* add_roomlevel_to_hash
 * Add a room name of a difficulty level
 * to the hash table of room names 
 * 
 * Parameters:
 * - roomlevels: pointer to the room hash table
 * - name: a room name
 * - difficulty_level: difficulty_level
 *
 * Side effects:
 * - If (and only if) the name is not already in use in the hash,
 *   hashes a roomlevel_t of given name/level to the table. Otherwise,
 *   return FAILURE.
 * 
 * Returns:
 * SUCCESS - successfully added room
 * FAILURE - failed to add room
 */
int add_roomlevel_to_hash(roomlevel_t **roomlevels, char *name, int difficulty_level);

/* Should add a delete_roomlevel_from_hash() function */



/* LEVELSPEC */

/* init_levelspec
 * Initializes a levelspec_t struct with the given player level threshold info. 
 * The levelspec_t must be pointing to some valid memory.
 * NOTE: Does not affect roomlevels hash. Must use add_roomlevel_to_hash() to alter this field.
 *
 * Parameters:
 * - levelspec: the pointer to the levelspec_t we are initializing
 * - num_thresholds: the number of player level thresholds
 * - thresholds: the integer array of player level thresholds
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to initialize
 */
int init_levelspec(levelspec_t *levelspec, int num_thresholds, int *thresholds);


/* levelspec_new
 * Creates a levelspec_t struct with the given player level threshold info. 
 * The levelspec_t must be pointing to some valid memory.
 * NOTE: Initializes the roomlevels to NULL. Must use add_roomlevel_to_hash() to alter this field.
 *
 * Parameters:
 * - num_thresholds: the number of player level thresholds
 * - thresholds: the integer array of player level thresholds
 *
 * Returns:
 * - the new levelspec (success)
 * - NULL (failure)
 */
levelspec_t *levelspec_new(int num_thresholds, int *thresholds);



/* levelspec_free
 * Frees a levelspec_t struct and returns whether or not it was successful
 * NOTE: Frees roomlevels hash table and its contents.
 *
 * Parameters:
 * - levelspec: the pointer to the levelspec_t we are freeing
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to free
 */
int levelspec_free(levelspec_t *levelspec);


#endif
