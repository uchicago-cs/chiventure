#include <criterion/criterion.h>
#include "battle_ai.h"
#include "battle_flow.h"
#include "battle_flow_structs.h"
#include "battle_structs.h"
#include "../include/npc/npc.h"
#include "../include/npc/npc_battle.h"
#include "battle_moves.h"
#include "battle_default_objects.h"
#include "battle_logic.h"
#include "battle_state.h"
#include "battle_move_maker.h"
#include "../include/playerclass/class.h"
#include "battle_print.h"
#include "../include/common/utlist.h"
#include "game-state/item.h"
#include "game-state/player.h"
#include "game-state/mode.h"
#include "game-state/game.h"
#include "battle/battle_common.h"
#include "game-state/room.h"
#include "npc/rooms_npc.h"

/* Test class creation functions -----------------------------------------------------*/

/* This function creates a sample warrior class. It's taken from test_class.c */
class_t *make_new_warrior_class();

/* This function creates a sample bard class. */
class_t *make_new_bard_class();

/* This function creates a sample wizard class. */
class_t *make_new_wizard_class();


/* Battle item creation functions ----------------------------------------------------*/

/* This function creates and initializes a battle item. */
battle_item_t *create_battle_item(int id, int quantity, char* description, 
                                        char *name, bool attack, stat_changes_t *changes);

/* This function creates example hardcoded battle_items for the player. */
battle_item_t* create_player_battle_items();

/* This function creates example hardcoded battle_items for the enemy. */
battle_item_t* create_enemy_battle_items();


/* Stats creation functions ---------------------------------------------------------*/

/* This function creates example hardcoded normal stats for the enemy. */
stat_t* create_enemy_stats_norm();

/* This function creates example hardcoded stats for the enemy but with 100% critical. */
stat_t* create_enemy_stats_crit();

/* This function creates example hardcoded stats for the battle_player. */
stat_t* create_battle_player_stats();

/* This function creates example hardcoded stats for the enemy (first version for battle between NPCs). */
stat_t *create_enemy_stats_v1();

/* This function creates example hardcoded stats for the enemy (second version for battle between NPCs). */
stat_t *create_enemy_stats_v2();


/* Moves creation functions ---------------------------------------------------------*/

/* This function creates hardcoded moves for the battle_player. */
move_t* create_battle_player_moves();

/* This function creates the expected return value for when the AI should return the greediest move. */
move_t* expected_move_greedy();

/* This function creates the expected return value for when the AI should return a random move. */
move_t* expected_move_random();

/* This function is called by test functions to check if give_move returns properly*/
void check_give_move(combatant_t* player, combatant_t* enemy, difficulty_t difficulty, move_t* expected);

/* This function creates a sample npc_mov struct. */
npc_mov_t *generate_test_npc_mov();

/* This function creates hardcoded moves for the battle_player (first version for battle between NPCs). */
move_t *create_enemy_moves_v1();

/* This function creates hardcoded moves for the battle_player (second version for battle between NPCs). */
move_t *create_enemy_moves_v2();


/* Sandbox entity creation functions -------------------------------------------------*/

/* This function creates a sandbox enemy. */
combatant_t* new_enemy();

/* This function creates a sandbox enemy with 100% critical. */
combatant_t* new_enemy_crit();

/* This function creates a sandbox battle_player. */
combatant_t* new_battle_player();

