#ifndef _MODE_H
#define _MODE_H

#include "game_state_common.h"

/* Forward declaration */
typedef struct chiventure_ctx chiventure_ctx_t;

/* Mode operation function type */
typedef char *mode_operation(char* str, chiventure_ctx_t* ctx);

/* An enumeration of game mode types */
typedef enum mode_type {
	NORMAL,        //run chiventure as normal
	CONVERSATION   //for conversations with NPCs
} mode_type_t;

typedef struct mode {
	mode_type_t curr_mode;
	mode_operation run_mode;
	char* mode_ctx;
} mode_t;
