/*
 * this file is meant to provide some basic abilities to imitate skills using
 * an extremely limited mockup of some custom actions.
 * All skills are hardcoded.
 */

#include "custom_skills.h"


/* see custom_skills.h */
custom_action_t* action_new(custom_command comm, custom_param_t p1,
    custom_param_t p2, param_type p1_type, param_type p2_type) {

    custom_action_t *act = calloc(1, sizeof(custom_action_t));
    assert(act != NULL);

    act->comm = comm;
    act->param1 = p1;
    act->p1_type = p1_type;
    act->param2 = p2;
    act->p2_type = p2_type;

    return act;
}


/* see custom_skills.h */
custom_block_t* block_new(custom_action_t* act) {
    assert(act != NULL);

    custom_block_t *b = calloc(1, sizeof(custom_block_t));
    assert(b != NULL);

    b->action = act;
    b->next = NULL;
    return b;
}


/* see custom_skills.h */
stats_t *stats_new(int hp, int xp, int sp, int pdef, int patk, int ratk,
    int mdef, int matk, int energy) {

    stats_t *st = calloc(1, sizeof(stats_t));
    assert(st != NULL);

    st->health = hp;
    st->xp = xp;
    st->speed = sp;
    st->pdef = pdef;
    st->patk = patk;
    st->ratk = ratk;
    st->mdef = mdef;
    st->matk = matk;
    st->energy = energy;
    return st;
}


/* 
 * compares a stat with an integer constant
 * the only comparison supported is equality (==)
 *
 * Parameters
 *  - stats. the stats struct to draw from for the comparison
 *  - sp. specifies the stat that should be compared to
 *  - to_compare. the value to comapre the stat with
 *
 * Returns
 *  - true if the specified stat equals the given integer
 *  - false if it does not or if the sp has value NO_PARAM
 */
bool compare_stat(stats_t* stats, stat_param sp, int to_compare) {
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
 * adds an amount to a specified stat in the stats struct
 *
 * Parameters
 *  - stats. the stat set we want to add to
 *  - sp. specifies the stat we want to add to
 *  - to_add. integer value to be added to a stat.
 *
 * Returns
 *  - SUCCESS on success, FAILURE if sp has value NO_PARAM
 */
int add_to_stat(stats_t* stats, stat_param sp, int to_add) {
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
            return FAILURE;
    }
    return SUCCESS;
}


/* see custom_skills.h */
int execute(stats_t* stats, custom_block_t* block) {
    assert(stats != NULL);
    assert(block != NULL);

    custom_block_t* curr;
    custom_action_t* curr_act;
    bool if_result = false;
    bool in_ignored_if = false;
    int rc, status = SUCCESS;

    DL_FOREACH(block, curr) {
        curr_act = curr->action;

        /* controls skipping over statements in false if blocks
         * and statements in else blocks where the if statement was true */
        if (curr_act->comm == ENDIF || curr_act->comm == ELSE) {
            in_ignored_if = false;
        } else if (in_ignored_if) {
            continue;
        }

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
            if (rc) {
                status = FAILURE;
            }

        } else if (curr_act->comm == IF) {
            /* evaluates an if action and, if false, skips to ELSE or ENDIF */
            if_result = compare_stat(stats, curr_act->param1.st,
                curr_act->param2.constant);

            if (!if_result) {
                /* skip over any commands contingent on the if statement
                 * when the condition is false */
                in_ignored_if = true;
            }

        } else if (curr_act->comm == ELSE && if_result) {
            /* skips to ENDIF when it reaches an else branch 
             * after doing the if branch */
            in_ignored_if = true;
        }
    }
    return status;
}