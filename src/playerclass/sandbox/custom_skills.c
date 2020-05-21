/*
 * this file is meant to provide some basic abilities to imitate skills using
 * an extremely limited mockup of some custom actions.
 * All skills are hardcoded.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common/utlist.h"

// enum for supported commands
typedef enum {IF, ELSE, ENDIF, ADD, SUB} custom_command;

// enum for which stat should be used in the command
typedef enum {HEALTH, XP, SPEED, PDEF, PATK, RATK, MDEF, MATK, ENERG} stat_param;

// indicates that a parameter is a stat or a constant value
typedef enum {STAT, CONSTANT} param_type;

// a parameter is either a stat or a constant number
typedef union {
    stat_param st;
    int constant;
} custom_parameter_t;

// a single custom action consists of a command and two parameters with their types
typedef struct {
    custom_command comm;

    custom_parameter_t param1;
    param_type p1_type;

    custom_parameter_t param2;
    param_type p2_type;
} custom_action_t;

// a custom action block is a linked list of individual actions
typedef struct _custom_block {
    custom_action_t* action;
    struct _custom_block* next;
} custom_block_t;


int main() {

}