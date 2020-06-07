/*
 * This is currently skeleton code that needs to be expanded.
 */

#include "wdl/object.h"

/* See wdl/object.h for documentation */
object_t* new_object(char *id, objtype_t type)
{
    object_t* obj = (object_t*) malloc(sizeof(object_t*));
    
    init_object(obj, id, type);

    return obj;
}

/* See wdl/object.h for documentation */
int init_object(object_t *obj, char *id, objtype_t type)
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

/* See wdl/objstore.h for documentation */
obj_attr_t* get_obj_attribute(object_t* obj, char* name)
{
    return NULL;
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

/* See wdl/object.h for documentation */
asset_t* get_asset(assettype_t type, char* filename)
{
     return NULL;
}

/* See wdl/object.h for docomentation */
objtype_t strToOType(char *type)
{
    if(strcmp(type,"NONE"))
    {
        return TYPE_NONE;
    } else if (strcmp(type, "PLAYER"))
    {
        return TYPE_PLAYER;
    } else if (strcmp(type, "ROOM"))
    {
        return TYPE_ROOM;
    } else if (strcmp(type, "ITEM"))
    {
        return TYPE_ITEM;
    } else if (strcmp(type, "ACTION"))
    {
        return TYPE_ACTION;
    } else if (strcmp(type, "GCONDITION"))
    {
        return TYPE_GCONDITION;
    } else if (strcmp(type, "NPC"))
    {
        return TYPE_NPC;
    } else if (strcmp(type, "DIALOG"))
    {
        return TYPE_DIALOG;
    } else {
        return TYPE_ERR;
    }
}
