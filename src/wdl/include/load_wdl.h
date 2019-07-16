#ifndef INCLUDE_LOAD_WDL_H
#define INCLUDE_LOAD_WDL_H

#include "load_item.h"
#include "load_room.h"
#include "load_game.h"
#include "wdl_common.h"
#include "parser.h"

 /*
 * load_wdl, loads a wdl specified internally into all game-state structs
 *
 * input: nothing
 * 
 * output: a pointer to an game_t struct
 * that has been filled with the contents of the yaml file
 */
game_t *load_wdl(char *path_to_file);

 #endif /* end if for LOAD_WDL_H */