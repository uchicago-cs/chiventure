/*
 * Skill implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/reader.h"

/*See reader.h*/
reader_effect_t* reader_effect_new(reader_type_t type, attr_reader_effect_t* att_reader,
                stat_reader_effect_t* stat_reader){
    reader_effect_t* reader;
    int rc;

    reader = (reader_effect_t*)malloc(sizeof(reader_effect_t));
    if (reader == NULL) {
        fprintf(stderr, "reader_effect_new: memory allocation failed\n");
        return NULL;
    }

    rc = reader_effect_init(reader, type, att_reader, stat_reader);
    if (rc) {
        fprintf(stderr, "reader_effect_new: initialization failed\n");
        return NULL;
    }

    return reader;
}

int reader_effect_init(reader_effect_t* reader, reader_type_t type, attr_reader_effect_t att_reader,
                  stat_reader_effect_t stat_reader){
    assert(reader != NULL);

    reader->type = type;

}