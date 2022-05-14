/*
 * Skill implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/reader.h"

/*See reader.h*/
reader_effect_t* reader_effect_new(reader_type_t type, attr_reader_effect_t* attr_reader,
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

/*See reader.h*/
int reader_effect_init(reader_effect_t* reader, reader_type_t type, attr_reader_effect_t* attr_reader,
                  stat_reader_effect_t* stat_reader){
    assert(reader != NULL);

    reader->type = type;
    reader->attr_reader = att_reader;
    reader->stat_reader = stat_reader;

    return SUCCESS;
}

/*See reader.h*/
int reader_effect_free(reader_effect_t* reader){
    assert(reader != NULL);

    free(reader->attr_reader);
    free(reader->stat_reader);
    free(reader);

    return SUCCESS;
}

/*See reader.h*/
stat_reader_effect_t* stat_reader_effect_new(int value, int stat_type, comparison_t comp, reader_location_t location){
    stat_reader_effect_t* reader;
    int rc;

    reader = (stat_reader_effect_t*)malloc(sizeof(stat_reader_effect_t));
    if (skill == NULL) {
        fprintf(stderr, "stat_reader_effect_new: memory allocation failed\n");
        return NULL;
    }

    rc = int reader_effect_init(reader,stat_type, value, comp, location);

    if (rc) {
        fprintf(stderr, "stat_reader_effect_init: initialization failed\n");
        return NULL;
    }

    return reader;
}

/*See reader.h*/
int stat_reader_effect_init(stat_reader_effect_t* reader,int value, int stat_type,
                            comparison_t comp, reader_location_t location){
    assert(reader != NULL);

    reader->value = value;
    reader->stat_type = stat_type;
    reader->comp = comp;
    reader->location = location;

    return SUCCESS;
}

/*See reader.h*/
int stat_reader_effect_free(stat_reader_effect* reader){
    assert(reader != NULL);

    free(reader);

    return SUCCESS;
}

/*See reader.h*/
int execute_reader_effect(reader_effect_t* reader, chiventure_ctx_t* ctx){
    if(reader->type == READ_ATTRIBUTE){
        assert(reader->attr_reader_effect != NULL);
        return execute_attr_reader_effect(reader->attr_reader_effect);
    }
    if(reader->type == READ_STATISTIC){
        assert(reader->stat_reader_effect != NULL);
        return execute_stat_reader_effect(reader->stat_reader_effect);
    }

    return 0;
}

/*See reader.h*/
int execute_attr_reader_effect(attr_reader_effect_t* reader, chiventure_ctx_t* ctx){

    switch(reader->location){
        case READ_PLAYER:
            if(0 == strcmp(reader->value, ctx->game->curr_player->player_class->name)){
                return true;
            } else {
                return false;
            }

        case READ_SINGLE_TARGET:
            if(0 == strcmp(reader->value, ctx->game->battle_ctx->enemy->player_class->name)){
                return true;
            } else {
                return false;
            }

        case READ_WORLD:
            if(0 == strcmp(reader->value, ctx->game->curr_room->room_id)){
                return true;
            } else {
                return false;
            }
    }

    return false;
}

