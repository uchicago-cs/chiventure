#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quest_hash.h"

/* Refer to quest_hash.h */
quest_t *get_quest_from_hash(char *quest_id, quest_hash_t *hash_table)
{
    quest_t *q;
    HASH_FIND_STR(hash_table, quest_id, q);
    return q;
}

/* Refer to quest_hash.h */
int add_quest_to_hash(quest_t *quest, quest_hash_t **hash_table)
{
    quest_t *check;
    
    check = get_quest_from_hash(quest->quest_id, *hash_table);

    if (check != NULL) 
    {
        return FAILURE; //quest id is already in the hash table
    }

    HASH_ADD_STR(*hash_table, quest_id,quest);
    return SUCCESS;
}

/* refer to quests_state.h */
int remove_quest_in_hash(quest_hash_t *hash_table, char *quest_id) 
{
    quest_t *check; 
    check = get_quest_from_hash(quest_id, hash_table);

    if (check == NULL){ 
        return FAILURE; /* quest is not in hash_table) */
    } 

    HASH_DEL(hash_table,check); 
    quest_free(check); 
    if (get_quest_from_hash(quest_id, hash_table) != NULL){
        return FAILURE;
    }
    return SUCCESS;

}

/* refer to quests_state.h */
int remove_quest_all(quest_hash_t *hash_table)
{ 
    quest_t *current_quest, *temp; 
    HASH_ITER(hh, hash_table, current_quest, temp) 
    { 
        HASH_DEL(hash_table, current_quest);
        free(current_quest);
    }
    return SUCCESS; 
}


