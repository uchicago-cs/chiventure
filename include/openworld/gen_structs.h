/* gen_structs.h: This file: contains all of the necessary high level structs
* that are necessary for generating a room.
*
* Create the generation structs that will contain the necessary info for
* autogenerating a room
*
* See chiventure/src/openworld/gen_structs.c source code to see implementation.
*/
#ifndef _GEN_STRUCTS_H
#define _GEN_STRUCTS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game-state/game.h"
#include "game-state/game_state_common.h"
#include "sample_npc.h"
/* -- STRUCTS -- */

/* roomspec_t struct
* This struct will carry the necessary info for creating a room.
* The struct contains:
* - char *room_name: room name and hash key
* - char *short_desc: short description for room
* - char *long_desc: long description for room
* - item_hash_t *items: hash table of items in room
* - UT_hash_handle hh: hash handle for room spec
*/
typedef struct roomspec {
    char *room_name;
    char *short_desc;
    char *long_desc;
    int num_built;
    item_hash_t *items;
    npc_t *possible_npcs;
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
int init_roomspec(npc_t *possible_npcs, roomspec_t *spec, char *room_name, char *short_desc, char *long_desc, item_hash_t *items);

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
roomspec_t* roomspec_new(npc_t *possible_npcs,char *room_name, char *short_desc, char *long_desc, item_hash_t *items);

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
#endif
