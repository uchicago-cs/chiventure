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
    int matck; // magic attack
    int energ; // energy
} stats_stub;


/* 
 * creates and initializes a new custom action
 */
custom_action_t* action_new(custom_command comm, custom_param_t p1,
    custom_param_t p2, param_type p1_type, param_type p2_type) {

    custom_action_t *act = malloc(sizeof(custom_action_t));
    act->comm = comm;
    act->param1 = p1;
    act->p1_type = p1_type;
    act->param2 = p2;
    act->p2_type = p2_type;

    return act;
}


/*
 * creates and initializes a new custom action block
 */
custom_block_t* block_new(custom_action_t* act, custom_block_t* next) {
    
    custom_block_t *b = malloc(sizeof(custom_block_t));
    b->action = act;
    b->next = next;
    return b;
}

/*
 * creates the custom action block for a sword swing skill
 * 
 * returns a hardcoded list
 */
custom_block_t* create_swing_sword() {
    custom_block_t *head = NULL, *block;
    custom_action_t *atomic_action;
    custom_param_t p1;
    custom_param_t p2;
    
    // skill will check if physical attack is 5
    p1.st = PATK;
    p2.constant = 5;
    atomic_action = action_new(IF, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    // if it is, reduce health by 3
    // (the player's health because this doesn't support multiple sets of stats)
    p1.st = HEALTH;
    p2.constant = 3;
    atomic_action = action_new(SUB, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    // end the if
    p1.st = NO_PARAM;
    p2.st = NO_PARAM;
    atomic_action = action_new(ENDIF, p1, p2, NONE, NONE);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    return head;
}

int main() {

}