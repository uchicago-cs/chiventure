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

/* Creates a sample class. Taken from test_class.c  and same as generate NPCtest class*/
class_t *generate_test_class();

class_t *create_test_class();

class_t *make_wizard();


/* Battle item creation functions ----------------------------------------------------*/

/* Creates + initializes a battle_item  SAME AS CREATE_NPC_BATTLE_ITEM and npc_create_battle_item and generate_test_battle_item*/
 battle_item_t *create_battle_item(int id, int quantity, char* description, 
                                        char *name, bool attack, stat_changes_t *changes);

/* Creates example hardcoded battle_items for the player*/
battle_item_t* create_player_battle_items();

/* Creates example hardcoded items for the enemy*/
battle_item_t* create_enemy_battle_items();


/* Stats creation functions ---------------------------------------------------------*/

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_norm();

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_crit();

/* Creates example hardcoded stats for the battle_player*/
stat_t* create_battle_player_stats();

/* Creates example stats. Taken from test_battle_ai.c Same as create_enemy_stats()*/
stat_t *create_enemy_stats1();

/* Creates example stats. Taken from test_battle_ai.c */
stat_t *create_enemy_stats2();


/* Moves creation functions ---------------------------------------------------------*/

/* Creates example hardcoded stats for the battle_player*/
move_t* create_battle_player_moves();

/* Creates the expected return value for when the AI should return the greediest move*/
move_t* expected_move_greedy();

/* Creates the expected return value for when the AI should return a random move*/
move_t* expected_move_random();

/* Called by test functions to check give_move returns properly*/
void check_give_move(combatant_t* player, combatant_t* enemy, difficulty_t difficulty, move_t* expected);

/* Creates a sample npc_mov struct. Taken from test_npc_move.c */
npc_mov_t *generate_test_npc_mov();

/*Same as create_enemy_moves()*/
move_t *create_enemy_moves1();

/* Creates example moves. Taken from test_battle_ai.c */
move_t *create_enemy_moves2();


/* Sandbox entity creation functions -------------------------------------------------*/

/* Creates sandbox enemy*/
combatant_t* new_enemy();

/* Creates sandbox enemy with crit value 100% */
combatant_t* new_enemy_crit();

/* Creates sandbox battle_player*/
combatant_t* new_battle_player();


/* Dialogue Building Functions ------------------------------------------------------*/

void check_add_node(int num_nodes);

void check_add_edge(int num_edges);


