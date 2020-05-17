/* 
 * Defines a player class struct to store base class information.
 * 
 * For more information see class.h
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "playerclass/class.h"
#include "common/utlist.h"

/* See class.h */
class_t* class_new(char* name, char* shortdesc, char* longdesc,
                   obj_t* attr, stats_t* stat)
{
    int rc;
    class_t* c = (class_t*) malloc(
        sizeof(class_t)
    );
    
    if(c == NULL)
    {
        error("Could not allocate space for class_new.\n");
        return NULL;
    }
    
    rc = class_init(c, name, shortdesc, longdesc, attr, stat);

    if (rc == EXIT_FAILURE){
        error("Could not initalize values for class_new.\n");
    }

    return c;
}

/* See class.h */
int class_init(class_t* class, char* name, char* shortdesc, char* longdesc,
               obj_t* attr, stats_t* stat)
{
    if (class == NULL)
    {
        error("Class to initialize in class_init is NULL.\n");
        return EXIT_FAILURE;
    }

    class->name = name;
    class->shortdesc = shortdesc;
    class->longdesc = longdesc;
    class->attributes = attr;
    class->stats = stat;

    return EXIT_SUCCESS;
}

/* See class.h */
int class_free(class_t* class)
{    
    if (class == NULL)
    {
        return EXIT_SUCCESS;
    }

    free(class);

    return EXIT_SUCCESS;
}