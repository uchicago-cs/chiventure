#ifndef _GAME_STATE_COMMON_H
#define _GAME_STATE_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

#include "common/uthash.h"
#include "common/utlist.h"
#include "common/common.h"

#define MAX_ID_LEN 20
#define MAX_SDESC_LEN 50
#define MAX_LDESC_LEN 300
#define MAX_MSG_LEN 300
#define MAX_START_DESC_LEN 500 // for string in game struct
#define HASH_SIZE 500 // temporary hash table size for testing item fxns

//Macros for move_room()
#define GAME_NULL 2
#define ROOM_NULL 3
#define FINAL_ROOM 4

//Macros for game_action_t functions
#define ITEM_SRC_NULL 2
#define ITEM_MODIFY_NULL 3
#define ACTION_NULL 4
#define ATTRIBUTE_NULL 5
#define PLAYER_NULL 6
#define CONDITION_NULL 7

//Macros for create_connection()
#define ROOM_SRC_NULL 2
#define ROOM_DEST_NULL 3

//Macros for quests
#define QUEST_NAME_MAX_LEN 44

#endif
