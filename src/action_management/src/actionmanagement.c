#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "actionmanagement.h"

/* See actionmanagement.h */
action_t *action_new(enum actions act, char *c_name,
		     list_t *synonyms, enum kind)
{
  action_t *a = malloc(sizeof(action_t));
  
  if(!a)
    {
      error("Could not allocate memory");
      return NULL;
    }
  
  int new_a = action_init(a, act, c_name, synonyms, parameters);
  if (new_a != SUCCESS)
    {
      error("Could not initialize this action");
      return NULL;
    }
  
  return a;
}


/* See actionmanagement.h */
int action_init(action_t *a, enum actions act, char *c_name,
		list_t *synonyms, enum kind)
{
  assert(a);
  
  a->actions = act;
  a->c_name = cname;
  a->synonyms = synonyms;
  a->kind = kind;
  
  return SUCCESS;
}

/* See actionmanagement.h */
int action_free(action_t *a)
{
  assert(a);
  assert(a->c_name);
  assert(a->synonyms);
  free(a->c_name);
  free(a->synonyms);
  free(a);
  return SUCCESS;
}
