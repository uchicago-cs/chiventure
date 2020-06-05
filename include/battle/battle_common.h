#ifndef BATTLE_COMMON_H
#define BATTLE_COMMON_H

#include "battle/battle_structs.h"

/* AI move strategy options */
typedef enum difficulty
{
    BATTLE_AI_NONE = 0,
    BATTLE_AI_GREEDY = 1,
    BATTLE_AI_RANDOM = 2
} difficulty_t;

/* An environment enum that contains the following:
 * ENV_GRASS: grass
 * ENV_DESERT: desert
 * ENV_SNOW: snow
 * ENV_WATER: water
 * (temporary values, to be developed at a later time)
 */
typedef enum environment
{
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
typedef enum turn
{
    PLAYER = 0,
    ENEMY = 1
} turn_t;

/* gives the status of a battle */
typedef enum battle_status
{
    BATTLE_IN_PROGRESS,
    BATTLE_VICTOR_PLAYER,
    BATTLE_VICTOR_ENEMY,
    NO_BATTLE
} battle_status_t;

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
typedef struct combatant
{
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
typedef struct battle
{
    combatant_t *player;
    combatant_t *enemy;
    environment_t environment;
    turn_t turn;
} battle_t;

#endif