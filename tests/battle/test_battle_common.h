#ifndef TEST_BATTLE_COMMON_H
#define TEST_BATTLE_COMMON_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "battle/battle_ai.h"
#include "battle/battle_moves.h"

/* Creates example moveset designed for the enemy*/
move_t* create_moveset1();

/* Creates example moveset designed for the player*/
move_t* create_moveset2();

/* Creates example stat spread for an average non-crit enemy */
stat_t* create_enemy_stats_avg();

/* Creates example stat spread for a crit enemy */
stat_t* create_enemy_stats_crit();

/* Creates example stat spread for a player without crit or accuracy odds */
stat_t* create_player_stats_avg();

/* Creates example stat spread for a player with crit and accuracy odds */
stat_t* create_player_stats_critacc();

/* Creates basic combatant for testing purposes */
combatant_t* create_combatant(char* name, bool friendly, stat_t* stats,
                              move_t* moves, difficulty_t ai);

#endif
