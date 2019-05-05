#include "object.h"

// need function to initialize and allocate object

/* allocates a new object on the heap */
object_t *object_new();

int object_init(char *object_id, char *short, char *long);

char *get_id(object_t obj);

char *get_short_desc(object_t obj);

char *get_long_desc(object_t obj);

int *get_obj_type(enum object_type_t obj_t);

int take_object(object_t obj);
