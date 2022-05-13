#ifndef QUEST_HASH_H
#define QUEST_HASH_H

#include "quest.h"

/*
 * This typedef distinguishes between quest_t pointers
 * which are used to point to quest_t structs in the 
 * traditional sense and those which are used to hash
 * quest_t structs with the UTHASH macros as specified
 * in include/common
 */
typedef struct quest quest_hash_t;

/* Gets a quest from the given hash table
 *
 * Parameters:
 *  quest id string
 *  pointer to quest hash table
 *
 * Returns:
 *  quest struct if successful, NULL if quest is not found
 */
quest_t *get_quest_from_hash(char *quest_id, quest_hash_t *hash_table);

/* Adds a quest to the given hash table
 *
 * Parameters:
 *  pointer to quest struct
 *  pointer to a pointer quest hash table
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_hash(quest_t *quest, quest_hash_t **hash_table);

#endif /* QUEST_HASH_H */