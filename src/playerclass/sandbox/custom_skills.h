/*
 * defines data structures and functions for a simple mock custom actions system
 * used for creating skills out of custom actions
 */

#ifndef CUSTOM_SKILLS_H
#define CUSTOM_SKILLS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "common/utlist.h"
#include "common/common.h"

// enum for supported commands
typedef enum {IF, ELSE, ENDIF, ADD, SUB} custom_command;

// enum for which stat should be used in the command
typedef enum {HEALTH, XP, SPEED, PDEF, PATK, RATK, MDEF, MATK, ENERG, NO_PARAM} stat_param;

// indicates that a parameter is a stat or a constant value
typedef enum {STAT, CONSTANT, NONE} param_type;

// a parameter is either a stat or a constant number
typedef union {
    stat_param st;
    int constant;
} custom_param_t;

// a single custom action consists of a command and two parameters with their types
typedef struct {
    custom_command comm;

    custom_param_t param1;
    param_type p1_type;

    custom_param_t param2;
    param_type p2_type;
} custom_action_t;

// a custom action block is a linked list of individual actions
typedef struct _custom_block {
    custom_action_t* action;
    struct _custom_block* next;
    struct _custom_block* prev;
} custom_block_t;

// this is a stub struct to represent stats
typedef struct {
    int health;
    int xp;
    int speed;
    int pdef; // physical defense
    int patk; // physical attack
    int ratk; // ranged attack
    int mdef; // magic defense
    int matk; // magic attack
    int energy;
} stats_t;


/* 
 * creates and initializes a new custom action
 * 
 * Parameters
 *  - comm. the action command
 *  - p1, p2. the parameters of the command (use NO_PARAM if there are none)
 *  - p1_type, p2_type. the types of the parameters, either stats or integers
 *
 * Returns
 *  - a pointer to a custom action struct
 */
custom_action_t* action_new(custom_command comm, custom_param_t p1,
    custom_param_t p2, param_type p1_type, param_type p2_type);


/*
 * creates and initializes a new custom action block
 * 
 * Parameters
 *  - act. the custom action to be added
 *  - next. a pointer to the next action block in the sequence
 *
 * Returns
 *  - a pointer to a custom block struct
 */
custom_block_t* block_new(custom_action_t* act);


/*
 * creates and initializes a stats struct
 *
 * Parameters
 *  - hp, xp, sp, pdef, patk, ratk, mdef, matk, energy. The values of each stat
 *
 * Returns
 *  - a pointer to a stats struct
 */
stats_t *stats_new(int hp, int xp, int sp, int pdef, int patk, int ratk,
    int mdef, int matk, int energy);


/* 
 * executes a custom action block. Logic is very simple.
 * assumes the block is well-formed and valid
 * assumes that all actions in the block with parameters have a stat
 *      followed by an integer constant
 *
 * Parameters
 *  - stats. the stat set of the character doing the skill
 *  - block. the list of actions that make up the skill
 *
 * Returns 
 *  - SUCCESS if all ADD and SUB actions in the block control flow were executed successfully
 *  - FAILURE if at least one such action failed
 */
int execute(stats_t* stats, custom_block_t* block);


#endif
