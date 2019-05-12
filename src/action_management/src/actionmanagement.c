#include <stdlib.h>
#include <stdio.h>
#include "actionmanagement.h"


action_t *action_new(enum actions act, char *c_name,
  list_t *synonyms, enum kind)
  {
    action_t *a = malloc(sizeof(action_t));

    if(a == NULL)
    {
      error("Could not allocate memory");
      return NULL;
    }

    new_a = action_init(a, act, c_name, synonyms, parameters);
    if (new_a != SUCCESS)
    {
      error("Could not initialize this action");
      return NULL;
    }

    return a;
  }


int action_init(action_t *a, enum actions act, char *c_name,
  list_t *synonyms, enum kind)
  {
    assert(a != NULL);

    a->actions = act;
    a->c_name = cname;
    a->synonyms = synonyms;
    a->kind = kind;

    return SUCCESS;
  }


int action_free(action_t *a)
{
  assert(a != NULL);
  free(a->c_name);
  free(a->synonyms);
  free(a->parameters);
  free(a)
  return SUCCESS;
}
