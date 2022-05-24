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

    rc = reader_effect_init(reader, type, attr_reader, stat_reader);
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
    reader->attr_reader = attr_reader;
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
stat_reader_effect_t* stat_reader_effect_new(int value, stats_type_t stat_type, 
                                comparison_t comp, reader_location_t location){
    stat_reader_effect_t* reader;
    int rc;

    reader = (stat_reader_effect_t*)malloc(sizeof(stat_reader_effect_t));
    if (reader == NULL) {
        fprintf(stderr, "stat_reader_effect_new: memory allocation failed\n");
        return NULL;
    }

    rc = stat_reader_effect_init(reader,value, stat_type, comp, location);

    if (rc) {
        fprintf(stderr, "stat_reader_effect_init: initialization failed\n");
        return NULL;
    }

    return reader;
}

/*See reader.h*/
int stat_reader_effect_init(stat_reader_effect_t* reader,int value, stats_type_t stat_type,
                            comparison_t comp, reader_location_t location){
    assert(reader != NULL);

    reader->value = value;
    reader->stat_type = stat_type;
    reader->comparison = comp;
    reader->location = location;

    return SUCCESS;
}

/*See reader.h*/
int stat_reader_effect_free(stat_reader_effect_t* reader){
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

    rc = attr_reader_effect_init(reader, value, str_len, location);

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

    reader->value = malloc((str_len + 1)*sizeof(char));
    strcpy(reader->value, value);

    reader->str_len = str_len;
    reader->location = location;

    return SUCCESS;
}

/*See reader.h*/
int attr_reader_effect_free(attr_reader_effect_t* reader){
    assert(reader != NULL);

    free(reader->value);
    free(reader);

    return SUCCESS;
}

/*See reader.h*/
int execute_reader_effect(reader_effect_t* reader, chiventure_ctx_t* ctx){
    if(reader->type == READER_ATTRIBUTE){
        assert(reader->attr_reader != NULL);
        return execute_attr_reader_effect(reader->attr_reader, ctx);
    }
    if(reader->type == READER_STATISTIC){
        assert(reader->stat_reader != NULL);
        return execute_stat_reader_effect(reader->stat_reader, ctx);
    }

    return 0;
}

//Helper function for execute_attr_reader_effect to check if structs are allocated
//Yes, we know that this is abhorrent. Blame C for not letting us search through structs. 
int check_attribute_null(chiventure_ctx_t* ctx, reader_location_t location){
    if (location == READ_PLAYER) {
        if (ctx != NULL){
            if (ctx->game != NULL){
                if (ctx->game->battle_ctx != NULL){
                    if (ctx->game->battle_ctx->game != NULL){
                        if (ctx->game->battle_ctx->game->battle != NULL){
                            if (ctx->game->battle_ctx->game->battle->player != NULL){
                                if (ctx->game->battle_ctx->game->battle->player->class_type != NULL){
                                    if (ctx->game->battle_ctx->game->battle->player->class_type->name != NULL){         
                                        return 0;
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
        return 1;
    }

    if (location = READ_SINGLE_TARGET) {
        if (ctx != NULL){
            if (ctx->game != NULL){
                if (ctx->game->battle_ctx != NULL){
                    if (ctx->game->battle_ctx->game != NULL){
                        if (ctx->game->battle_ctx->game->battle != NULL){
                            if (ctx->game->battle_ctx->game->battle->enemy != NULL){
                                if (ctx->game->battle_ctx->game->battle->enemy->class_type != NULL){
                                    if (ctx->game->battle_ctx->game->battle->enemy->class_type->name != NULL){
                                        return 0;  
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
        return 1;
    }

    if (location = READ_WORLD) {
        if (ctx != NULL){
            if (ctx->game != NULL){
                if (ctx->game->curr_room != NULL){
                    if (ctx->game->curr_room->room_id != NULL){
                        if (ctx->game->curr_room->room_id){
                            return 0;
                        }
                    }
                }
            }
        }
        return 1;
    }
}

/*See reader.h*/
int execute_attr_reader_effect(attr_reader_effect_t* reader, chiventure_ctx_t* ctx){
    reader_location_t loc;

    switch(reader->location){
        case READ_PLAYER:
            //Check for presence of struct
            loc = READ_PLAYER;
            if (check_attribute_null(ctx, loc) == 1){
                return -1;
            }
            if (NULL != reader->value){
                if (0 == strcmp(reader->value, ctx->game->curr_player->player_class->name)){
                    return true;
                } else {
                    return false;
                }
            }
        case READ_SINGLE_TARGET:
            //Check for presence of struct
            loc = READ_SINGLE_TARGET;
            if (check_attribute_null(ctx, loc) == 1){
                return -1;
            }
            if (NULL != reader->value){
                if (0 == strcmp(reader->value, ctx->game->battle_ctx->game->battle->enemy->class_type->name)){
                    return true;
                } else {
                    return false;
                }
            }

        case READ_WORLD:
            //Check for presence of struct
            loc = READ_WORLD;
            if (check_attribute_null(ctx, loc) == 1){
                return -1;
            }
            if (NULL != reader->value){
                if (0 == strcmp(reader->value, ctx->game->curr_room->room_id)){
                    return true;
                } else {
                    return false;
                }
            }
    }

    return -1;
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
    return -1;
}

//Helper function for execute_stat_reader
int check_stats(int value, stats_type_t type, comparison_t comp, stat_t* stats){
    switch(type){
            case SPEED:
                return compare_values(value, stats->speed, comp);

            case DEFENSE:
                return compare_values(value, stats->phys_def, comp);

            case STRENGTH:
                return compare_values(value, stats->phys_atk, comp);

            case HP:
                return compare_values(value, stats->hp, comp);

            case MAX_HP:
                return compare_values(value, stats->max_hp, comp);
    }
    return -1;
}

//Helper function for execute_stat_reader_effect to check if structs are allocated
//Yes, we know that this is awful. Blame C for not letting us search through structs. 
int check_battle_null(chiventure_ctx_t* ctx){
    if (ctx != NULL){
        if (ctx->game != NULL){
            if (ctx->game->battle_ctx != NULL){
                if (ctx->game->battle_ctx->game != NULL){
                    if (ctx->game->battle_ctx->game->battle != NULL){
                        if (ctx->game->battle_ctx->game->battle){
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

/*See reader.h*/
int execute_stat_reader_effect(stat_reader_effect_t* reader, chiventure_ctx_t* ctx){

    //Check for presence of battle struct
    if (check_battle_null(ctx) == 1){
        return -1;
    }

    battle_t* battle = ctx->game->battle_ctx->game->battle;

    switch(reader->location){
        case READ_PLAYER:

            if (battle->player != NULL){
                if (battle->player->stats != NULL){
                    return check_stats(reader->value, reader->stat_type, reader->comparison, 
                            ctx->game->battle_ctx->game->battle->player->stats);
                }
            }     
            break;


        case READ_SINGLE_TARGET:
            if (battle->enemy != NULL){
                if (battle->enemy->stats != NULL){
                    return check_stats(reader->value, reader->stat_type, reader->comparison, 
                            ctx->game->battle_ctx->game->battle->enemy->stats); 
                } 
            } 
            break;
        
        //Not aware of any stats for READ_WORLD at this time
        // case READ_WORLD:

        default :
            return -1;

    }
    return -1;
}