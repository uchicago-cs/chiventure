#include "wdl/object.h"

/* See wdl/object.h for documentation */
object_t *new_object(char *id, objtype_t type)
{
    object_t* obj = calloc(1, sizeof(object_t));
    
    init_object(obj, id, type);

    return obj;
}

/* See wdl/object.h for documentation */
int init_object(object_t *obj, char *id, objtype_t type)
{
    if((obj == NULL) || (id == NULL))
    {
        fprintf(stderr, "ERROR -init_object: Couldn't initialize object.\n");        

        return FAILURE;
    }

    strncpy(obj->id, id, MAXLEN_ID);
    obj->type = type;
    obj->attrs = NULL;

    return SUCCESS;
}

/* See wdl/object.h for documentation */
int free_object(object_t *obj)
{
    free_attr_hash(&(obj->attrs));

    free(obj);
    
    return SUCCESS;
}

/* See wdl/object.h for documentation */
obj_attr_t *get_obj_attribute(object_t* obj, char *name)
{
    obj_attr_t *attr = find_attr(&(obj->attrs), name);

    if(attr == NULL)
    {
        return NULL;
    }

    return attr;
}

/* see wdl/object.h for documentation */
asset_t *new_asset(assettype_t type, char *filename)
{
    asset_t *asset = calloc(1, sizeof(asset_t));
    if (asset == NULL)
    {
        fprintf(stderr, 
                "ERROR - new_asset: Could not allocate memory for asset.\n");

        return NULL;
    }
    if (&(asset->type) == NULL)
    {
        fprintf(stderr,
               "ERROR - new_asset: Could not allocate memory for asset.\n");

        return NULL;
    }
    if (asset->filename == NULL)
    {
        fprintf(stderr, 
               "ERROR - new_asset: Could not allocate memory for asset.\n");

        return NULL;
    }
    if (init_asset(asset, type, filename) != SUCCESS)
    {
        fprintf(stderr,
                "ERROR - new_asset: Could not allocate memory for asset.\n");

        free_asset(asset);
        return NULL;
    }
    return asset;
}

/* see wdl/object.h for documentation */
int init_asset(asset_t *asset, assettype_t type, char *filename)
{
    if ((asset == NULL) || (filename == NULL))
    {
        fprintf(stderr,
                "ERROR - init_asset: could not initialize asset.\n");

        return FAILURE;
    }
    asset->type = type;
    asset->filename = filename;
    asset->asset = NULL;

    return SUCCESS; 
}

/* see wdl/object.h for documentation */
int free_asset(asset_t *asset)
{
    if (asset->asset != NULL)
    {
        fclose(asset->asset);
    }
    free(asset);
    return SUCCESS;
}

/* See wdl/object.h for documentation */
asset_t *get_asset(assettype_t type, char *filename)
{
    // To be implemented in future sprint.
    // Currently backlog issue #791
    return NULL;
}

/* See wdl/object.h for docomentation */
objtype_t str_to_objtype(char *type)
{
    if(strncmp(type,"NONE", MAXLEN_ID) == 0)
    {
        return TYPE_NONE;
    } else if (strncmp(type, "PLAYER", MAXLEN_ID) == 0)
    {
        return TYPE_PLAYER;
    } else if (strncmp(type, "ROOM", MAXLEN_ID) == 0)
    {
        return TYPE_ROOM;
    } else if (strncmp(type, "ITEM", MAXLEN_ID) == 0)
    {
        return TYPE_ITEM;
    } else if (strncmp(type, "ACTION", MAXLEN_ID) == 0)
    {
        return TYPE_ACTION;
    } else if (strncmp(type, "GCONDITION", MAXLEN_ID) == 0)
    {
        return TYPE_GCONDITION;
    } else if (strncmp(type, "NPC", MAXLEN_ID) == 0)
    {
        return TYPE_NPC;
    } else if (strncmp(type, "DIALOG", MAXLEN_ID) == 0)
    {
        return TYPE_DIALOG;
    } else {
        return TYPE_ERR;
    }
}
