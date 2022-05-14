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
stat_reader_effect_t* stat_reader_effect_new(int value, stat_type_t stat_type, 
                                comparison_t comp, reader_location_t location){
    stat_reader_effect_t* reader;
    int rc;

    reader = (stat_reader_effect_t*)malloc(sizeof(stat_reader_effect_t));
    if (reader == NULL) {
        fprintf(stderr, "stat_reader_effect_new: memory allocation failed\n");
        return NULL;
    }

    rc = int stat_reader_effect_init(reader,stat_type, value, comp, location);

    if (rc) {
        fprintf(stderr, "stat_reader_effect_init: initialization failed\n");
        return NULL;
    }

    return reader;
}

/*See reader.h*/
int stat_reader_effect_init(stat_reader_effect_t* reader,int value, stat_type_t stat_type,
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
attr_reader_effect_t* attr_reader_effect_new(char *value, int str_len, reader_location_t location){
    attr_reader_effect_t* reader;
    int rc;

    reader = (attr_reader_effect_t*)malloc(sizeof(attr_reader_effect_t));
    if (reader == NULL) {
        fprintf(stderr, "attr_reader_effect_new: memory allocation failed\n");
        return NULL;
    }

    rc = int attr_reader_effect_init(reader, value, str_len, location);

    if (rc) {
        fprintf(stderr, "attr_reader_effect_init: initialization failed\n");
        return NULL;
    }

    return reader;
}

/*See reader.h*/
int attr_reader_effect_init(attr_reader_effect_t* reader,char *value,
                            int str_len, reader_location_t location){
    assert(reader != NULL);

    reader->value = value;
    reader->str_len = str_len;
    reader->location = location;

    return SUCCESS;
}

/*See reader.h*/
int attr_reader_effect_free(attr_reader_effect* reader){
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
            if(0 == strcmp(reader->attr_reader->value, ctx->game->curr_player->player_class->name)){
                return true;
            } else {
                return false;
            }

        case READ_SINGLE_TARGET:
            if(0 == strcmp(reader->attr_reader->value, ctx->game->battle_ctx->enemy->player_class->name)){
                return true;
            } else {
                return false;
            }

        case READ_WORLD:
            if(0 == strcmp(reader->attr_reader->value, ctx->game->curr_room->room_id)){
                return true;
            } else {
                return false;
            }
    }

    return NULL;
}

//Helper function for execute_stat_reader
int compare_values(int val1, int val2, comparison_t comp){
    switch(comp){
        case EQUALS:
            return (val1 == val2);
        
        case NOT:
            return(val1 != val2);

        case GREATER:
            return(val1 > val2);

        case LESSER:
            return (val1 < val2);

        case GREATER_EQUAL:
            return(val1 >= val2);

        case LESSER_EQUAL:
            return (val1 <= val2);
    }
    return NULL;
}

//Helper function for execute_stat_reader
int check_stats(int value, stat_type_t type, comparison_t comp, stats_t* stats){
    switch(type){
            case SPEED:
                return compare_values(value, stats_t->speed, comp);

            case DEFENSE:
                return compare_values(value, stats_t->phys_def, comp);

            case STRENGTH:
                return compare_values(value, stats_t->phys_atk, comp);

            case HP:
                return compare_values(value, stats_t->hp, comp);

            case MAX_HP:
                return compare_values(value, stats_t->max_hp, comp);
    }
    return NULL;
}


/*See reader.h*/
int execute_stat_reader_effect(stat_reader_effect_t* reader, chiventure_ctx_t* ctx){
    switch(reader->location){
        case READ_PLAYER:
            return check_stats(reader->value, reader->stat_type, reader->comp, 
                        ctx->game->battle_ctx->player->stats);


        case READ_SINGLE_TARGET:
            return check_stats(reader->value, reader->stat_type, reader->comp, 
                        ctx->game->battle_ctx->enemy->stats);

        //Not aware of any stats for READ_WORLD at this time
        // case READ_WORLD:

    }

    return NULL;
}