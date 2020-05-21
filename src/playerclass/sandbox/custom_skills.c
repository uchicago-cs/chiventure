/*
 * this file is meant to provide some basic abilities to imitate skills using
 * an extremely limited mockup of some custom actions.
 * All skills are hardcoded.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
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
    int matk; // magic attack
    int energy;
} stats_stub;


/* 
 * creates and initializes a new custom action
 */
custom_action_t* action_new(custom_command comm, custom_param_t p1,
    custom_param_t p2, param_type p1_type, param_type p2_type) {

    custom_action_t *act = malloc(sizeof(custom_action_t));
    assert(act != NULL);
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
    assert(act != NULL);
    custom_block_t *b = malloc(sizeof(custom_block_t));
    assert(b != NULL);
    b->action = act;
    b->next = next;
    return b;
}


/* 
 * compares a stat with an integer constant
 * the only comparison supported is equality (==)
 */
bool compare_stat(stats_stub* stats, stat_param sp, int to_compare) {
    assert(sp != NO_PARAM);
    assert(stats != NULL);

    int stat_value = 0;
    switch (sp) {
        case HEALTH:
            stat_value = stats->health;
            break;
        case XP:
            stat_value = stats->xp;
            break;
        case SPEED:
            stat_value = stats->speed;
            break;
        case PDEF:
            stat_value = stats->pdef;
            break;
        case PATK:
            stat_value = stats->patk;
            break;
        case RATK:
            stat_value = stats->ratk;
            break;
        case MDEF:
            stat_value = stats->mdef;
            break;
        case MATK:
            stat_value = stats->matk;
            break;
        case ENERG:
            stat_value = stats->energy;
            break;
        default:
            return false;
    }
    return to_compare == stat_value;
}


/*
 * adds an integer to a specified stat in the stats struct
 *
 * returns 0 on success, 1 on failure
 */
int add_to_stat(stats_stub* stats, stat_param sp, int to_add) {
    assert(stats != NULL);
    assert(sp != NO_PARAM);

    switch (sp) {
        case HEALTH:
            stats->health += to_add;
            break;
        case XP:
            stats->xp += to_add;
            break;
        case SPEED:
            stats->speed += to_add;
            break;
        case PDEF:
            stats->pdef += to_add;
            break;
        case PATK:
            stats->patk += to_add;
            break;
        case RATK:
            stats->ratk += to_add;
            break;
        case MDEF:
            stats->mdef += to_add;
            break;
        case MATK:
            stats->matk += to_add;
            break;
        case ENERG:
            stats->energy += to_add;
            break;
        default:
            return 1;
    }
    return 0;
}


/* 
 * executes a custom action block. Logic is very simple.
 * assumes the block is well-formed and valid
 * assumes that all actions in the block with parameters have a stat
 *      followed by an integer constant
 */
int execute(stats_stub* stats, custom_block_t* block) {
    assert(stats != NULL);
    assert(block != NULL);

    custom_block_t* curr;
    custom_action_t* curr_act;
    bool if_result = false;
    int rc, status = 0;

    for (curr = block; curr != NULL; curr = curr->next) {
        curr_act = curr->action;

        if (curr_act->comm == ADD) {
            /* handles ADD actions */
            rc = add_to_stat(stats, curr_act->param1.st,
                curr_act->param2.constant);
            if (rc)
                status = 1;

        } else if (curr_act->comm == SUB) {
            /* handles SUB actions - just adds a negative number */
            rc = add_to_stat(stats, curr_act->param1.st,
                - curr_act->param2.constant);
            if (rc)
                status = 1;

        } else if (curr_act->comm == IF) {
            /* evaluates an if action and, if false, skips to ELSE or ENDIF */
            if_result = compare_stat(stats, curr_act->param1.st,
                curr_act->param2.constant);

            if (!if_result) {
                // skip over the rest of the if section
                while (curr_act != NULL && curr_act->comm != ELSE && 
                    curr_act->comm != ENDIF) {
                    curr = curr->next;
                    curr_act = curr->action;
                }
            }
        }
    }
    return status;
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

    // end the if block
    p1.st = NO_PARAM;
    p2.st = NO_PARAM;
    atomic_action = action_new(ENDIF, p1, p2, NONE, NONE);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    return head;
}

/*
 * creates the custom action block for a fireball spell
 * 
 * returns a hardcoded list
 */
custom_block_t* create_fireball_spell() {
    custom_block_t *head = NULL, *block;
    custom_action_t *atomic_action;
    custom_param_t p1;
    custom_param_t p2;

    // skill requires 10 Magic Energy
    p1.st = ENERG;
    p2.constant = 10;
    atomic_action = action_new(IF, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    // do 9 damage
    p1.st = HEALTH;
    p2.constant = 9;
    atomic_action = action_new(SUB, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    // else
    p1.st = NO_PARAM;
    p2.st = NO_PARAM;
    atomic_action = action_new(ELSE, p1, p2, NONE, NONE);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    // recover 2 energy
    p1.st = ENERG;
    p2.constant = 2;
    atomic_action = action_new(ADD, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    // end the if block
    p1.st = NO_PARAM;
    p2.st = NO_PARAM;
    atomic_action = action_new(ENDIF, p1, p2, NONE, NONE);
    block = block_new(atomic_action, NULL);
    LL_APPEND(head, block);

    return head;
}


int main() {

}