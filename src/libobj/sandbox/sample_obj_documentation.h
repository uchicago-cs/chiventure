// sample documentation

#include "../../../include/common/uthash.h"
#include "stdbool.h"
#include <stdio.h>
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
    // these had to be changed from TYPE_ERR because C was throwing error about uniqueness of the enums
    ASSET_ERR = -1, 
    ASSET_NONE = 0,
    ASSET_IMAGE = 1,
    ASSET_SOUND = 2
} assettype_t;

typedef struct obj obj_t; // forward declaration so attribute_t can use

/* attribute_t
 * 
 * params:
 *   - id: the attribute's id.
 *   - data: the information stored in the attribute.
 *   -
 */
typedef struct attribute
{
    //the id for the attribute
    char id[MAXLEN_ID + 1];
    
    //data stored in the attribute
    union
    {
        bool b;
        char c;
        char *s;
	char **sl;
        int i;
        obj_t *o;
    } data;
    
    // Required uthash identifier for making the hash table
    UT_hash_handle hh;

} attribute_t;

/* obj_t: a struct describing a .json object. 
 * 
 * params:
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id.
 *   - hh: the uthash hash handle of the object.
 *   - attributelist: a linked list of the object's attributes.
 */
typedef struct obj
{
    // The id used to identify this object
    char id[MAXLEN_ID + 1];

    //the type of this object
    objtype_t type;

    //The object's attributes (a hash table)
    attribute_t *attrs;

} obj_t;

/* asset_t: a struct describing a media asset.
 * params:
 *   - type: the type of the asset corresponding to its .wdz subfolder.
 *   - filename: the asset's filename.
 *   - asset: a pointer to the asset file.
 */
typedef struct asset
{ 
    assettype_t type;
    char* filename;
    FILE* asset;
} asset_t;

/*
 * get_object_wdl: (MEANT FOR WDL TEAM) retrieves an object from a .wdz archive.
 *
 * params: 
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id.
 * 
 * returns:
 *   - a pointer to the requested object as a obj_t struct member.
 */
obj_t* get_object_wdl(objtype_t type, char* id);

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
    
obj_t* get_object(char* type, char* id);

/* get_obj_attribute: retrieve an attribute from an object
 *
 * params:
 *   - obj: the object holding the attribute
 *   - name: the attribute key
 *
 * returns:
 *   - a pointer to the requested attribute as an attribute_t struct member
 */
attribute_t* get_obj_attribute(obj_t obj, char* name);

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
