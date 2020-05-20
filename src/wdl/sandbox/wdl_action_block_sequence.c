#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "wdl_action_block_sequence.h"

/* See wdl_action_block_sequence.h for documentation */
wdl_action_block_t *wdl_action_block_get_next(wdl_action_block_t *curr)
{
    assert(curr != NULL);
    return curr->next;
}


/* See wdl_action_block_sequence.h for documentation */
char *wdl_action_block_get_name(wdl_action_block_t *action_block)
{
    assert(action_block != NULL);
    return action_block->block_name;
}


/* See wdl_action_block_sequence.h for documentation */
char *wdl_action_block_get_params(wdl_action_block_t *action_block)
{
    assert(action_block != NULL);
    return action_block->block_parameters;
}


/* See wdl_action_block_sequence.h for documentation */
wdl_action_sequence_t *wdl_action_sequence_new(json_dict_obj *raw_json_object)
{
    assert(raw_json_object != NULL);
    return NULL; 
    // need to wait for the implementation of the json object representation
}


/* See wdl_action_block_sequence.h for documentation */
wdl_action_block_t *wdl_action_block_new(char *block_name, char *block_parameters)
{
    assert((block_name != NULL) && (block_parameters != NULL));
    assert(block_name[0] != '\0');
    
    wdl_action_block_t *new_block = malloc(sizeof(*new_block));
    assert(new_block != NULL);
    
    strncpy(new_block->block_name, block_name, ACTION_BLOCK_NAME_MAXLEN);
    strncpy(new_block->block_parameters, block_parameters, ACTION_BLOCK_PARAMS_MAXLEN);

    new_block->next = NULL;

    return new_block;
}


int wdl_action_sequence_free(wdl_action_sequence_t *action_seq)
{
    if (action_seq == NULL)
    {
        fprintf(stderr, "Can't free a NULL action sequence!\n");
        return FAILURE;
    }

    assert(action_seq->args != NULL);
    free(action_seq->args);

    assert(action_seq->head != NULL);
    wdl_action_block_t *curr, *temp;
    LL_FOREACH_SAFE(action_seq->head, curr, temp) 
    {
        LL_DELETE(action_seq->head, curr);
        free(curr);
    }

    free(action_seq);
    return SUCCESS;
}
