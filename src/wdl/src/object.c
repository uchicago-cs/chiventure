#include "wdl/object.h"

/*
 * Helper function for
 * get_object_wdl: retrieves an object from a .wdz archive.
 *
 * params: 
 *   - type: the type of the object corresponding to its .wdz subfile.
 *   - id: the object's id.
 * 
 * returns:
 *   - a pointer to the requested object as a obj_t struct member.
 */
obj_t* get_object_wdl(objtype_t type, char* id)
{
    return NULL;
}

/* See wdl/object.h for documentation */
obj_t* get_object(char* type, char* id)
{
    return NULL;
}

/* See wdl/object.h for documentation */
attribute_t* get_obj_attribute(obj_t obj, char* name)
{
    return NULL;
}

/* See wdl/object.h for documentation */
asset_t* get_asset(assettype_t type, char* filename)
{
     return NULL;
}
