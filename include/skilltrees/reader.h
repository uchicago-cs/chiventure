
#ifndef INCLUDE_READER_H_
#define INCLUDE_READER_H_

#include "skilltrees/skilltrees_common.h"
#include "skilltrees/skilltrees_enums.h"
#include "battle/battle_structs.h"
#include "skilltrees/effect.h"

/*
 * Allocates a reader in the heap.
 *
 * Parameters:
 *  - type: The reader type, ATTRIBUTE or STATISTIC
 *  - att_reader: Reader of type ATTRIBUTE
 *  - stat_reader: Reader of type STATISTIC
 *
 * Returns:
 *  - A pointer to the reader, or NULL if reader cannot be allocated
 */
reader_effect_t* reader_effect_new(reader_type_t type, attr_reader_effect_t* attr_reader,
                  stat_reader_effect_t* stat_reader);

/*
 * Initalizes a reader
 *
 * Parameters:
 *  - reader: Pointer to the reader being initalized
 *  - type: The reader type, ATTRIBUTE or STATISTIC
 *  - att_reader: Reader of type ATTRIBUTE
 *  - stat_reader: Reader of type STATISTIC
 *
 * Returns:
 *  - 1 if initalized succesfully, 0 if failure
 */
int reader_effect_init(reader_effect_t* reader, reader_type_t type, attr_reader_effect_t* attr_reader,
                  stat_reader_effect_t* stat_reader);

/*
 * Frees a reader in the heap.
 *
 * Parameters:
 *  - reader: Pointer to the reader being freed
 *
 * Returns:
 *  - 1 if freed succesfully, 0 if failure
 */
int reader_effect_free(reader_effect_t* reader);

/*
 * Allocates a stat reader in the heap.
 *
 * Parameters:
 *  - value: Value being compared
 *  - comp: The type of comparison being made
 *  - location: Location of value being compared
 *
 * Returns:
 *  - A pointer to the stat reader, or NULL if reader cannot be allocated
 */
stat_reader_effect_t* stat_reader_effect_new(int value, stats_type_t stat_type,
                      comparison_t comp, reader_location_t location);

/*
 * Initalizes a statistic reader
 *
 * Parameters:
 *  - reader: Pointer to the stat reader being initalized
 *  - value: Value being compared
 *  - comp: The type of comparison being made
 *  - location: Location of value being compared
 *
 * Returns:
 *  - 1 if initalized succesfully, 0 if failure
 */
int stat_reader_effect_init(stat_reader_effect_t* reader, int value, stats_type_t stat_type,
                            comparison_t comp, reader_location_t location);

/*
 * Frees a stat reader in the heap.
 *
 * Parameters:
 *  - reader: Pointer to the stat reader being freed
 *
 * Returns:
 *  - 1 if freed succesfully, 0 if failure
 */
int stat_reader_effect_free(stat_reader_effect_t* reader);

/*
 * Allocates an attribute reader in the heap.
 *
 * Parameters:
 *  - value: string being compared
 *  - str_len: the length of the value string
 *  - location: Location of value being compared
 *
 * Returns:
 *  - A pointer to the attribute reader, or NULL if reader cannot be allocated
 */
attr_reader_effect_t* attr_reader_effect_new(char *value, int str_len, reader_location_t location);

/*
 * Initalizes an attribute reader
 *
 * Parameters:
 *  - reader: Pointer to the attribute reader being initalized
 *  - value: string being compared
 *  - str_len: length of string
 *  - location: Location of value being compared
 *
 * Returns:
 *  - 1 if initalized succesfully, 0 if failure
 */
int attr_reader_effect_init(attr_reader_effect_t* reader,char *value,
                            int str_len, reader_location_t location);

/*
 * Frees an attribute reader in the heap.
 *
 * Parameters:
 *  - reader: Pointer to the attribute reader being freed
 *
 * Returns:
 *  - 1 if freed succesfully, 0 if failure
 */
int attr_reader_effect_free(attr_reader_effect_t* reader);

/*
 * Reads a reader effect
 *
 * Parameters:
 *  - reader: Pointer to the reader being read
 *  - ctx - A context object to pull data from to execute the reader
 *
 * Returns:
 *  - 0 if reader is false, 1 if reader is true
 */
int execute_reader_effect(reader_effect_t* reader, chiventure_ctx_t* ctx );

/*
 * Reads an attribute reader effect
 *
 * Parameters:
 *  - reader: Pointer to the attribute reader being read
 *  - ctx - A context object to pull data from to execute the reader
 *
 * Returns:
 *  - 0 if reader is false, 1 if reader is true
 */
int execute_attr_reader_effect(attr_reader_effect_t* reader, chiventure_ctx_t* ctx);

/*
 * Reads a statistic reader effect
 *
 * Parameters:
 *  - reader: Pointer to the statistic reader being read
 *  - ctx - A context object to pull data from to execute the reader
 *
 * Returns:
 *  - 0 if reader is false, 1 if reader is true
 */
int execute_stat_reader_effect(stat_reader_effect_t* reader, chiventure_ctx_t* ctx);

#endif /*INCLUDE_READER_/home/nkbilaver/CS220/chiventure/src/skilltrees/CMakeLists.txt*/