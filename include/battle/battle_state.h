#ifndef BATTLE_STATE_H
#define BATTLE_STATE_H

#include "battle_moves.h"
#include "battle_structs.h"
#include "common/utlist.h"
#include "common/common.h"
#include <stdbool.h>
#include <string.h>

/* An environment enum that contains the following:
 * ENV_GRASS: grass
 * ENV_DESERT: desert
 * ENV_SNOW: snow
 * ENV_WATER: water
 * (temporary values, to be developed at a later time)
 */
typedef enum environment {
    ENV_NONE = -1,
    ENV_GRASS = 0,
    ENV_DESERT = 1,
    ENV_SNOW = 2,
    ENV_WATER = 3
} environment_t;

/* A turn  enum that contains the following:
 * PLAYER: player turn
 * ENEMY: enemy/enemies turn
 */
typedef enum turn {
    PLAYER = 0,
    ENEMY = 1
} turn_t;

/* A combatant struct that contains the following:
 * name: combatant name
 * is_friendly: whether combatant is the player or enemy
 * class: class type
 * stats: pointer to stats module (stub)
 * moves: pointer to moves module (stub)
 * items: pointer to items module (stub)
 * ai: combatant's ai move strategy
 * next: allows for combatant lists using utlist.h
 * prev: allows for combatant lists using utlist.h
 */
typedef struct combatant {
    char *name;
    bool is_friendly;
    class_t *class;
    stat_t *stats;
    move_t *moves;
    item_t *items;
    difficulty_t ai;
    struct combatant *next;
    struct combatant *prev;
} combatant_t;

/* A battle struct that contains the following:
 * - player: a combatant pointer, storing the player
 * - enemy: a combatant pointer, storing the enemy/enemies
 * - environment: stores battle environment
 * - turn: a turn_t enum storing the current turn
 */
typedef struct battle {
    combatant_t *player;
    combatant_t *enemy;
    environment_t environment;
    turn_t turn;
} battle_t;

/* Creates a new battle  struct
 * Parameters:
 * - player: a pointer to player combatant
 * - enemy: a pointer to enemy combatant/s
 * - env: an environment enum
 * - turn: a turn_t enum indicating the current turn
 * returns: a pointer to the new battle
 */
battle_t *battle_new(combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn);

/* Initialize a battle  struct
 * Parameters:
 * - b: a pointer to a battle struct in memory
 * - player: a pointer to player combatant
 * - enemy: a pointer to enemy combatant/s
 * - env: an environment enum
 * - turn: a turn_t enum indicating the current turn
 * returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int battle_init(battle_t *b, combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn);

/* Frees a battle struct from memory */
int battle_free(battle_t *b);

/* Initialize a combatant struct
 * Parameters:
 * - name: name string
 * - is_friendly: bool indicating character type
 * - class: pointer to the player class struct 
 * - stats: pointer to the stats of the combatant(stub)
 * - moves: pointer to the linked list of moves for the combatant (stub)
 * - items: pointer to the linked list of items for the combatant (stub)
 * - ai: combatant's ai move strategy
 * returns: a pointer to the new character
 */
combatant_t *combatant_new(char *name, bool is_friendly, class_t *class,
             stat_t *stats, move_t *moves, item_t *items, difficulty_t ai);

/* Creates a new combatant struct
 * Parameters:
 * - c: a pointer to combatant in memory
 * - name: name string
 * - is_friendly: bool indicating character type
 * - class: pointer to the player class struct 
 * - stats: a pointer to the stats of the combatant (stub)
 * - moves: a pointer to the linked list of moves for the combatant (stub)
 * - items: a pointer to the linked list of items for the combatant (stub)
 * - ai: combatant's ai move strategy
 * returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int combatant_init(combatant_t *c, char *name, bool is_friendly, class_t *class,
     stat_t *stats, move_t *moves, item_t *items, difficulty_t ai);

/* Frees a combatant struct from memory
 * Parameters:
 * - c: a pointer to combatant in memory
 * returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int combatant_free(combatant_t *c);

/* Frees a list of combatant structs from memory
 * Parameters:
 * - c: a pointer to combatant in memory
 * returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int combatant_free_all(combatant_t *c);
#endif
