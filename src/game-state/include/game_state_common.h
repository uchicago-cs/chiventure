#ifndef _GAME_STATE_COMMON_H
#define _GAME_STATE_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "uthash.h"
#include "utlist.h"
#include "common.h"

#define MAX_ID_LEN 20
#define MAX_SDESC_LEN 50
#define MAX_LDESC_LEN 300
#define MAX_START_DESC_LEN 500 // for string in game struct
#define HASH_SIZE 500 // temporary hash table size for testing item fxns

//Macros for for move_room()
#define GAME_NULL 2
#define ROOM_NULL 3
#define FINAL_ROOM 4 


#endif
