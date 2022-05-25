/*
 * main file for trying out the custom_skills sandbox code
 */
#include <stdio.h>
#include <stdlib.h>
#include "custom_skills.h"

/*
 * creates the custom action block for a sword swing skill
 * 
 * Parameters
 *  - none
 *
 * Returns
 *  - a hardcoded custom block sequence
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
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    // if it is, reduce health by 3
    // (the player's health because this doesn't support multiple sets of stats)
    p1.st = HEALTH;
    p2.constant = 3;
    atomic_action = action_new(SUB, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    // end the if block
    p1.st = NO_PARAM;
    p2.st = NO_PARAM;
    atomic_action = action_new(ENDIF, p1, p2, NONE, NONE);
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    return head;
}

/*
 * creates the custom action block for a fireball spell
 *
 * Parameters
 *  - none
 * 
 * Returns
 *  - a hardcoded custom block sequence
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
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    // do 9 damage
    p1.st = HEALTH;
    p2.constant = 9;
    atomic_action = action_new(SUB, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    // remove 10 Magic Energy
    p1.st = ENERG;
    p2.constant = 10;
    atomic_action = action_new(SUB, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    // else
    p1.st = NO_PARAM;
    p2.st = NO_PARAM;
    atomic_action = action_new(ELSE, p1, p2, NONE, NONE);
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    // recover 2 energy
    p1.st = ENERG;
    p2.constant = 2;
    atomic_action = action_new(ADD, p1, p2, STAT, CONSTANT);
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    // end the if block
    p1.st = NO_PARAM;
    p2.st = NO_PARAM;
    atomic_action = action_new(ENDIF, p1, p2, NONE, NONE);
    block = block_new(atomic_action);
    DL_APPEND(head, block);

    return head;
}


/*
 * prints the contents of a stats struct
 *
 * Parameters
 *  - stats. the stats struct to print
 *
 * Returns
 *  - none. prints out the contents of the struct
 */
void print_stats(stats_t* stats) {
    assert(stats != NULL);
    printf("health: %d\n", stats->health);
    printf("xp: %d\n", stats->xp);
    printf("speed: %d\n", stats->speed);
    printf("phys. def.: %d\n", stats->pdef);
    printf("phys. atk.: %d\n", stats->patk);
    printf("ranged atk.: %d\n", stats->ratk);
    printf("magic def.: %d\n", stats->mdef);
    printf("magic atk.: %d\n", stats->matk);
    printf("energy: %d\n\n", stats->energy);
}


int main() {
    int rc;
    // irrelevant stats are set to 1
    stats_t *stats1 = stats_new(25, 1, 1, 1, 5, 1, 1, 1, 8);
    stats_t *stats2 = stats_new(25, 1, 1, 1, 1, 1, 1, 1, 10);

    custom_block_t *sword = create_swing_sword();
    custom_block_t *fireball = create_fireball_spell();

    printf("Initial stats1\n");
    print_stats(stats1);

    rc = execute(stats1, sword);
    printf("Sword swing status: %d\n", rc);
    printf("Stats1 after swinging a sword\n");
    print_stats(stats1);

    rc = execute(stats1, fireball);
    printf("Fireball status: %d\n", rc);
    printf("Stats1 ater fireball attempt\n");
    print_stats(stats1);

    printf("\nInitial stats2\n");
    print_stats(stats2);

    rc = execute(stats2, fireball);
    printf("Fireball status: %d\n", rc);
    printf("Stats2 ater fireball\n");
    print_stats(stats2);
}