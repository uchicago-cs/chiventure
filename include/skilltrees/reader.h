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
reader_effect_new(reader_type_t type, attr_reader_effect_t att_reader,
                  stat_reader_effect_t stat_reader);