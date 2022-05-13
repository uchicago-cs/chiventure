#ifndef INCLUDE_READER_H_
#define INCLUDE_READER_H_

#include "skilltrees/skilltrees_common.h"
#include "skilltrees/skilltrees_enums.h"
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
stat_reader_effect_t* stat_reader_effect_new(int value, comparison_t comp, reader_location_t location);

/*
 * Initalizes a reader
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
int stat_reader_effect_init(stat_reader_effect_t* reader,int value,
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
int stat_reader_effect_free(stat_reader_effect* reader);

/*
 * Reads a reader effect
 *
 * Parameters:
 *  - reader: Pointer to the reader being read
 *
 * Returns:
 *  - 0 if reader is true, 1 if reader is false
 */
int execute_reader_effect(reader_effect_t* reader);

/*
 * Reads an attribute reader effect
 *
 * Parameters:
 *  - reader: Pointer to the attribute reader being read
 *
 * Returns:
 *  - 0 if reader is true, 1 if reader is false
 */
int execute_attr_reader_effect(attr_reader_effect_t* reader);

/*
 * Reads a statistic reader effect
 *
 * Parameters:
 *  - reader: Pointer to the statistic reader being read
 *
 * Returns:
 *  - 0 if reader is true, 1 if reader is false
 */
int execute_stat_reader_effect(stat_reader_effect_t* reader);