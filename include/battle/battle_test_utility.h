#include "battle/battle_ai.h"
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_structs.h"
#include "npc/npc.h"
#include "npc/npc_battle.h"
#include "battle/battle_moves.h"
#include "battle/battle_default_objects.h"
#include "battle/battle_logic.h"
#include "battle/battle_state.h"
#include "../include/battle/battle_move_maker.h"
#include "playerclass/class.h"
#include "battle/battle_print.h"
#include "common/utlist.h"

class_t *create_test_class();

class_t *make_wizard();

/* Creates + initializes a battle_item */
 battle_item_t *create_battle_item(int id, int quantity, char* description, 
                                        char *name, bool attack, stat_changes_t *changes);

/* Creates + initializes a battle_item */
 battle_item_t *create_npc_battle_item(int id, int quantity, char* description, 
                                        char *name, bool attack, stat_changes_t *changes);

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_norm();

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_crit();

/* Creates example hardcoded stats for the battle_player*/
stat_t* create_battle_player_stats();

/* Creates example hardcoded battle_items for the player*/
battle_item_t* create_player_battle_items();

/* Creates example hardcoded items for the enemy*/
battle_item_t* create_enemy_battle_items();

/* Creates example hardcoded moves for the enemy*/
move_t* create_enemy_moves();

/* Creates example hardcoded stats for the battle_player*/
move_t* create_battle_player_moves();

/* Creates the expected return value for when the AI should return the greediest move*/
move_t* expected_move_greedy();

/* Creates the expected return value for when the AI should return a random move*/
move_t* expected_move_random();

/* Creates sandbox enemy*/
combatant_t* new_enemy();

/* Creates sandbox enemy with crit value 100% */
combatant_t* new_enemy_crit();

/* Creates sandbox battle_player*/
combatant_t* new_battle_player();

/* Called by test functions to check give_move returns properly*/
void check_give_move(combatant_t* player, combatant_t* enemy, difficulty_t difficulty, move_t* expected);

 /* Creates + initializes a battle_item */
 battle_item_t *npc_create_battle_item(int id, int quantity, char* description, 
                                        char *name, bool attack, stat_changes_t *changes);
