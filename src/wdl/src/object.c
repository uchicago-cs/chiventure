/*
 * This is currently skeleton code that needs to be expanded.
 */

#include "wdl/object.h"

/* See wdl/object.h for documentation */
object_t* new_object(char *id, objtype_t type)
{
    return NULL;
}

/* See wdl/object.h for documentation */
int init_object(object_t *obj, char *id, objtype_t type)
{
    return 0;
}

/* See wdl/object.h for documentation */
int object_free(object_t *obj)
{
    return 0;
}

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
object_t* get_object_wdl(objtype_t type, char* id)
{
    return NULL;
}

/* See wdl/object.h for documentation */
object_t* get_object(char* type, char* id)
{
    return NULL;
}

/* See wdl/object.h for documentation */
obj_attr_t* get_obj_attribute(object_t* obj, char* name)
{
    return NULL;
}

/* See wdl/object.h for documentation */
asset_t* get_asset(assettype_t type, char* filename)
{
     return NULL;
}
