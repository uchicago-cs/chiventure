#include "object.h"

/* allocates a new object on the heap */
object_t *object_new();

/* creates new object */
int object_init(char *object_id, char *short_desc, char *long_desc)
{

  /* TO DO */

  return 0;
}

/* the following functions retrieve specific information from desired object
in anticipation of supporting player demands */
/* will add function basics to ensure compilation */

/* get_id function
Functions: retrieves unique object id
Parameters: object struct
Returns: object id string
*/
char *get_id(object_t obj)
{

  /* TO DO */

  return NULL;
}

/* get_short_desc function
Functions: retrieves short description of object
Parameters: object struct
Returns: description string
*/
char *get_short_desc(object_t obj)
{

  /* TO DO */

  return NULL;
}

/* get_long_desc function
Functions: retrieves long description of object
Parameters: object struct
Returns: description string
*/
char *get_long_desc(object_t obj)
{

  /* TO DO */

  return NULL;
}

/* get_obj_type function
Functions: retrieves type of object
Parameters: object struct
Returns: 0 for failure, 1 for success (tentative: will print object type?)
*/
int *get_obj_type(object_t obj)
{

  /* TO DO */

  return NULL;
}

/* take_object function
Functions: checks whether object in question can be taken
Parameters: object struct
Returns: 0 for yes, 1 for no
*/
int take_object(object_t obj)
{

  /* TO DO */

  return 0;
}
