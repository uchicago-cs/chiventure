#include "npc/npc_action.h"

/* See npc_action.h */
npc_action_t *npc_action_new(char *c_name, enum npc_action_kind kind)
{
    npc_action_t *a;
    int rc;
    a = malloc(sizeof(npc_action_t));
    if(a == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }
    rc = npc_action_init(a, c_name, kind);
    if(rc != SUCCESS)
    {
        error("Could not initialize action");
        return NULL;
    }
    return a;
}

/* See npc_action.h */
int npc_action_init(npc_action_t *a, char *c_name, enum npc_action_kind kind)
{
    assert(a != NULL);
    a->c_name = strdup(c_name);
    a->kind = kind;
    if (a->c_name == NULL)
    {
        error("Could not initialize action name");
        return FAILURE;
    }
    return SUCCESS;
}

/* See npc_action.h */
int npc_action_free(npc_action_t *a)
{
    assert(a != NULL);
    free(a->c_name);
    free(a);
    return SUCCESS;
}
