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
typedef struct rooms_level
{
    /* name of the room, hash key */
    char *room_name;        

    /* difficulty level of the room, possible value starts at 0 */
    int difficulty_level;       
       
    /* makes this structure hashable */
    UT_hash_handle hh;        
} rooms_level_t;


/* difficulty level scale */
typedef struct difficulty_level_scale 
{
    /* number of difficulty levels */
    int num_of_levels;  

    /* an array of threshold for levels, for example, [0, 5, 10] */  
    int *thresholds;
} difficulty_level_scale_t;




/* -- FUNCTIONS -- */



/* GENCONTEXT */

/* init_gencontext
* Initializes a gencontext_t struct with the given paramaters. The gencontext
* must be pointing to some valid memory.
*
* parameters:
i* - context: the gencontext* struct that we are initializing.
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
* Free's a speclist_t struct and returns whether or not it was successful
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
* Free's all speclist's from the given list
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



/* ROOMS_LEVEL */

/* init_rooms_level
 * Initializes a rooms_level_t struct with the given paramaters. The rooms_level_t
 * must be pointing to some valid memory.
 *
 * Parameters:
 * - map: the pointer to the rooms_level_t we are initializing
 * - room_name: the room name
 * - difficulty_level: difficulty level of the room
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to initialize
 */
int init_rooms_level(rooms_level_t *map, char *room_name, int difficulty_level);


/* rooms_level_new
 * Creates a rooms_level_t struct with the given paramaters.
 *
 * Parameters:
 * - room_name: the room name
 * - difficulty_level: difficulty level of the room
 *
 * Returns:
 * rooms_level_t *map - the new rooms_level_t
 * NULL - if failed to create a rooms_level_t
 */
rooms_level_t* rooms_level_new(char *room_name, int difficulty_level);


/* rooms_level_free
 * Free's a rooms_level_t struct and returns whether or not it was successful
 *
 * Parameters:
 * - map: the pointer to the rooms_level_t we are freeing
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to free
 */
int rooms_level_free(rooms_level_t *map);


/* add_rooms_to_hash
 * Add an array of room names of a difficulty level
 * to the hash table of room names 
 * 
 * Parameters:
 * - rooms: pointer to the room hash table
 * - char *names[]: an array of room names, for example {“school”}
 * - int difficulty_level: difficulty_level
 *
 * Side effects:
 * - Changes input rooms_level_t to hold the newly added room(s),
 *   allocated on the heap
 */
void add_rooms_to_hash(rooms_level_t **rooms, 
                       const char *names[], 
                       int difficulty_level);



/* DIFFICULTY_LEVEL_SCALE */

/* init_difficulty_level_scale_t
 * Initializes a difficulty_level_scale_t struct with the given paramaters. 
 * The difficulty_level_scale_t must be pointing to some valid memory.
 *
 * Parameters:
 * - scale: the pointer to the difficulty_level_scale_t we are initializing
 * - num_of_levels: the number of difficulty levels
 * - thresholds: an integer array of threshold for difficulty levels
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to initialize
 */
int init_difficulty_level_scale(difficulty_level_scale_t *scale, 
                                int num_of_levels, int *thresholds);


/* difficulty_level_scale_new
 * Creates a difficulty_level_scale_t struct with the given paramaters.
 *
 * Parameters:
 * - num_of_levels: the number of difficulty levels
 * - thresholds: an integer array of threshold for difficulty levels
 *
 * Returns:
 * difficulty_level_scale_t *scale - the new difficulty_level_scale_t
 * NULL - if failed to create a difficulty_level_scale_t
 */
difficulty_level_scale_t* difficulty_level_scale_new(int num_of_levels, int *thresholds);


/* difficulty_level_scale_free
 * Free's a difficulty_level_scale_t struct and returns whether or not it was successful
 *
 * Parameters:
 * - scale: the pointer to the difficulty_level_scale_t we are freeing
 *
 * Returns:
 * SUCCESS - for SUCCESS
 * FAILURE - if failed to free
 */
int difficulty_level_scale_free(difficulty_level_scale_t *scale);


#endif
