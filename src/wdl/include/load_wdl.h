#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "game.h"
#include "item.h"
#include "room.h"
#include "load_item.h"
#include "load_room.h"
#include "load_game.h"

//file path that specifies which yaml file to use
#define PATH_TO_YAML "../examples/sample_yaml/simplified_wdl.yaml"

/*
 * load_wdl, loads a wdl specified internally into all game-state structs
 *
 * input: nothing
 * 
 * output: a pointer to an game_t struct
 * that has been filled with the contents of the yaml file
 */
game_t *load_wdl();

