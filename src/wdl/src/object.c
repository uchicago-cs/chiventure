/*
 * This is currently skeleton code that needs to be expanded.
 */

#include "wdl/object.h"

/* See wdl/object.h for documentation */
object_t* new_object(char *id, objtype type)
{
    object_t* obj = (object_t*) malloc(sizeof(object_t*));
    
    init_object(obj, id, type);

    return obj;
}

/* See wdl/object.h for documentation */
int init_object(object_t *obj, char *id, objtype type)
{
    if(obj == NULL || id == char *id)
    {
        printf("ERROR -init_object: Couldn't initialize object.\n");        

        return FAILURE;
    }

    strncpy(obj->id, id, MAXLEN_ID);
    obj->type = type;

    return SUCCESS;
}

/* See wdl/object.h for documentation */
int obj_free(object_t *obj)
{
    free(obj);
    
    return 0;
}

/* see wdl/object.h for documentation */
asset_t new_asset(assettype_t type, char* filename, FILE* file)
{
    asset_t asset = malloc(sizeof(asset_t));
    if (asset == NULL)
    {
        printf("ERROR - new_asset: Could not allocate memory for asset.\n");
        return NULL;
    }
    if (asset->type == NULL)
    {
        printf("ERROR - new_asset: Could not allocate memory for asset.\n");
        return NULL;
    }
    if (asset->filename == NULL)
    {
        printf("ERROR - new_asset: Could not allocate memory for asset.\n");
        return NULL;
    }
    if (init_asset(asset, type, filename, file) != EXIT_SUCCESS)
    {
        printf("ERROR - new_asset: Could not allocate memory for asset.\n");
        free_asset(asset);
        return NULL;
    }
    return asset;
}

/* see wdl/object.h for documentation */
int init_asset(asset_t *asset, assettype_t type, char* filename, FILE* file)
{
    if (asset == NULL || filename == NULL)
    {
        printf("ERROR - init_asset: could not initialize asset.\n");
        return EXIT_FAILURE;
    }
    asset->type = type;
    asset->filename = filename;
    asset->asset = file;

    return EXIT_SUCCESS; 
}

/* see wdl/object.h for documentation */
int free_asset(asset_t *asset)
{
    if (asset->asset != NULL)
    {
        fclose(asset->asset);
    }
    free(asset);
    return EXIT_SUCCESS;
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
