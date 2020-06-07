// Documentation for objects to store parsed information from WDL

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "common/common.h"
#include "common/uthash.h"
#include "common/utlist.h"

#ifndef INCLUDE_OBJECT_H
#define INCLUDE_OBJECT_H

#define MAXLEN_ID 60 // ID strings for objects

/*
 * objtype_t: possible types of objects. 
 * each corresponds to a file within a .wdz archive within the game/ subfolder.
 */
typedef enum objtype
{
    TYPE_ERR = -1,
    TYPE_NONE = 0,
    TYPE_PLAYER = 1,
    TYPE_ROOM = 2,
    TYPE_ITEM = 3,
    TYPE_ACTION = 4,
    TYPE_GCONDITION = 5,
    TYPE_NPC = 6,
    TYPE_DIALOG = 7
} objtype_t;

/*
 * assettype_t: possible types of media assets.
 * each corresponds to a folder within a .wdz archive.	
 */
typedef enum assettype
{
    ASSET_ERR = -1, 
    ASSET_NONE = 0,
    ASSET_IMAGE = 1,
    ASSET_SOUND = 2
} assettype_t;

/*
 * obj_t: a struct describing a .json object.
 */
typedef struct obj
{
    // The id used to identify this object
    char id[MAXLEN_ID + 1];

    //the type of this object
    objtype_t type;

    //The object's attributes (a hash table)
    obj_attr_t *attrs;

} object_t;

/*
 * asset_t: a struct describing a media asset.
 */
typedef struct asset
{ 
    //the type of the asset corresonding to its .wdz subfolder
    assettype_t type;

    //the asset's filename
    char* filename;

    //a pointer to the asset file
    FILE* asset;
} asset_t;

/*
 * Creates a new object with an identifier id
 *
 * params:
 *   - id: The id for the object
 *
 * returns:
 *   - A pointer to the newly created and initialized object on success
 *   - NULL on error
 *
 */
object_t *new_object(char *id, objtype type);

/*
 * Initializes a new object with indentifier id
 *
 * params:
 *   - obj: The object to initialize
 *   - id: The id for the object
 *
 * returns:
 *   - SUCCESS on successful initialization
 *   - FAILURE otherwise
 *
 */
int init_object(object_t *obj, char *id, objtype type);

/*
 * Frees an object
 *
 * params:
 *   - obj: The object to free
 *
 * returns:
 *   - always returns SUCCESS
 */
int obj_free(object_t *obj);


/*
 * new_asset: creates a new asset with identifier filename
 *
 * params:
 *   - filename: the filename of the asset
 *
 * returns:
 *   - a pointer to the created asset
 *   - NULL if failure
 */

asset_t *new_asset(char* filename);

/*
 * init_asset: initializes an asset with identifier filename
 *
 * params:
 *   - asset: the asset to be initialized
 *   - filename: the filename of the asset
 * 
 * returns:
 *   - SUCCESS on successful initialization
 *   - FAILURE otherwise
 */

int init_asset(asset_t asset, char* filename);

/*
 * free_asset: frees an asset
 *
 * params:
 *   - asset: the asset to be freed
 * 
 * returns:
 *   - always returns SUCCESS
 */

int free_asset(asset_t asset);


/* 
 * get_object: retrieves an object from a .wdz archive
 *
 * params:
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id
 * 
 * returns:
 *   - a pointer to the requested object as a obj_t struct member.
 */
object_t* get_object(char* type, char* id);

/* get_obj_attribute: retrieve an attribute from an object
 *
 * params:
 *   - obj: the object holding the attribute
 *   - name: the attribute key
 *
 * returns:
 *   - a pointer to the requested attribute as an attribute_t struct member
 */
obj_attr_t* get_obj_attribute(object_t* obj, char* name);

/* get_asset: retrieves an asset from a .wdz archive
 *
 * params:
 *   - type: the type of the asset corresponding to its .wdz subfolder
 *   - filename: the filename of the asset
 *
 * returns:
 *   - a pointer to the requested asset as an asset_t struct member.
 */
asset_t* get_asset(assettype_t type, char* filename);

#endif /* INCLUDE_OBJECT_H */
