#include <stdio.h>
#include <stdlib.h>

enum object_type_t {} /* need to discuss object types with action mgmt */

typedef struct object {
  char *object_id;
  char *short_desc;
  char *long_desc;
  enum object_type_t obj_type; /* object type: clothing, weapon, etc */
  int can_take; /* 0 = cannot take object, 1 = can pick it up,
  2 = condition to pick it up */
  bool condition; /* reserved for future expansion */
} object_t;


object_t *object_new();

// arguments are taken from WDL
int object_init(char *object_id, char *short, char *long);

//
char *get_id(object_t obj);

char *get_short_desc(object_t obj);

char *get_long_desc(object_t obj);

int *get_obj_type(enum object_type_t obj_t);

int take_object(object_t obj);
