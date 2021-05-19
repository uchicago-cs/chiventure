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
    UT_hash_handle hh;
} roomspec_t;

/* speclist_t struct
* This struct functions as a llist of all the roomspec_t's
* The struct contains:
* - roomspec_t *spec: pointer to some room specification
* - speclist_t *next: pointer to the next part of the list.
*/
typedef struct speclist {
    roomspec_t *spec;
    struct speclist *prev;
    struct speclist *next;
} speclist_t;

/* gencontext_t struct
* This struct will carry the info for the generation algorithm
* The struct contains:
* - path_t *open_paths: the open path we are connecting the room to;
* - int level: this is the players current level
* - int num_open_paths: the number of openpaths that need to be generated in the room.
* - speclist_t *speclist: the llist of roomspect_t that each hold the room info.
*/
typedef struct gencontext {
    path_t *open_paths;
    int num_open_paths;
    int level;
    speclist_t *speclist;
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
* - speclist: the speclist we are choosing our roomspec from
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to initialize
*/
int init_gencontext(gencontext_t *context, path_t *open_paths, int level, int num_open_paths, speclist_t *speclist);

/* gencontext_new
* Creates a new gencontext_t* based off the given parameters.
*
* parameters:
* - level: stores the players level.
* - openpaths: number of open paths to generate in the room
* - numnpcs: the number of npcs to generate in the room
* - speclist: the speclist we are choosing our roomspec from
*
* returns:
* gencontext_t *contextnew - the new gencontext
* NULL - if fails to create a new gencontext.
*/
gencontext_t* gencontext_new(path_t *open_paths, int level, int num_openpaths, speclist_t *speclist);

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
*
* returns:
* roomspec_t *roomspecnew - the new roomspec
* NULL - if fails to create a new roomspec.
*/
roomspec_t* roomspec_new(char *room_name, char *short_desc, char *long_desc, item_hash_t *items);

/* roomspec_free
* Frees a gencontext_t* and returns whether or not it was succesful.
*
* parameters:
* - spec: roomspec_t* that we are attempting to free
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to free
*/
int roomspec_free(roomspec_t *spec);

/* SPECLIST */

/* init_speclist
* Initializes a speclist_t struct with the given paramaters. The speclist
* must be pointing to some valid memory.
*
* parameters:
* - list: the pointer to the speclist_t we are initializing
* - spec: the pointer to the roomspec_t
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to initialize
*/
int init_speclist(speclist_t *list, roomspec_t *spec);


/* speclist_new
* Creates a speclist_t struct with the given paramaters.
*
* parameters:
* - spec: the pointer to the roomspec_t
*
* returns:
* speclist_t *listnew = the new speclist
* NULL - if failed to create a speclist
*/
speclist_t* speclist_new(roomspec_t *spec);

/* speclist_free
* Frees a speclist_t struct and returns whether or not it was successful
*
* parameters:
* - list: the pointer to the speclist_t we are freeing
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to free
*/
int speclist_free(speclist_t *list);

/* speclist_free_all
* Frees all speclist's from the given list
* However, this function will not free the roomspec's inside of speclist
*
* parameters:
* - list: the speclist we are freeing from and onward.
*
* returns:
* SUCCESS - for SUCCESS
* FAILURE - if failed to free
*/
int speclist_free_all(speclist_t *list);



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
