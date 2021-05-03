// Documentation for objects to store parsed information from WDL

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "common/common.h"
#include "common/uthash.h"
#include "attributes.h"

#ifndef INCLUDE_OBJECT_H
#define INCLUDE_OBJECT_H

/*
 * objtype_t: possible types of objects. 
 * each corresponds to a file within a .wdz archive within the game/ subfolder.
 */
typedef enum objtype
{
    TYPE_ERR = -1,
    TYPE_NA = 0,
    TYPE_PLAYER = 1,
    TYPE_ROOM = 2,
    TYPE_ITEM = 3,
    TYPE_ACTION = 4,
    TYPE_GCONDITION = 5,
    TYPE_NPC = 6,
    TYPE_DIALOG = 7,
    TYPE_CUSTOM_SCRIPT = 8
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
 * object_t: a struct describing a .json object.
 */
typedef struct object
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
 *   - type: type of object
 *
 * returns:
 *   - A pointer to the newly created and initialized object on success
 *   - NULL on error
 *
 */
object_t *new_object(char *id, objtype_t type);

/*
 * Initializes a new object with indentifier id
 *
 * params:
 *   - obj: The object to initialize
 *   - id: The id for the object
 *   - type: type of object
 *
 * returns:
 *   - SUCCESS on successful initialization
 *   - FAILURE otherwise
 *
 */
int init_object(object_t *obj, char *id, objtype_t type);

/*
 * Frees an object
 *
 * params:
 *   - obj: The object to free
 *
 * returns:
 *   - always returns SUCCESS
 */
int free_object(object_t *obj);

/* get_obj_attribute: retrieve an attribute from an object
 *
 * params:
 *   - obj: the object holding the attribute
 *   - name: the attribute key
 *
 * returns:
 *   - a pointer to the requested attribute as an attribute_t struct member
 *   - NULL if the attribute is not found
 */
obj_attr_t *get_obj_attribute(object_t *obj, char *name);

/*
 * new_asset: creates a new asset with identifier filename
 *
 * params:
 *   - type: the type of asset being created
 *   - filename: the filename of the asset
 *
 * returns:
 *   - a pointer to the created asset on success
 *   - NULL if failure
 */
asset_t *new_asset(assettype_t type, char *filename);

/*
 * init_asset: initializes an asset with identifier filename
 *
 * params:
 *   - asset: the asset to be initialized
 *   - type: the type of asset being created
 *   - filename: the filename of the asset
 * 
 * returns:
 *   - SUCCESS on successful initialization
 *   - FAILURE otherwise
 */

int init_asset(asset_t *asset, assettype_t type, char *filename);

/*
 * free_asset: frees an asset
 *
 * params:
 *   - asset: the asset to be freed
 * 
 * returns:
 *   - always returns SUCCESS
 */

int free_asset(asset_t *asset);

/* get_asset: retrieves an asset from a .wdz archive
 *
 * params:
 *   - type: the type of the asset corresponding to its .wdz subfolder
 *   - filename: the filename of the asset
 *
 * returns:
 *   - a pointer to the requested asset as an asset_t struct member.
 *   - NULL if the attribute is not found
 */
asset_t *get_asset(assettype_t type, char *filename);

/*
 * Converts a string to an objtype_t
 *
 * Parameters:
 *   - type: a string representing the type
 *
 * Returns:
 *   - An objtype_t
 *
 */
objtype_t str_to_objtype(char *type);

#endif /* INCLUDE_OBJECT_H */
