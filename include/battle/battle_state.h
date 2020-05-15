#ifndef BATTLE_STATE_H
#define BATTLE_STATE_H

#include "battle_structs.h"
#include "common/utlist.h"
#include "common/common.h"

/* An environment enum that contains the following:
 * ENV_GRASS: grass
 * ENV_DESERT: desert
 * ENV_SNOW: snow
 * ENV_WATER: water
 * (temporary values, to be developed at a later time)
 */
typedef enum _environment_t {
     ENV_GRASS = 0,
     ENV_DESERT = 1,
     ENV_SNOW = 2,
     ENV_WATER = 3
} environment_t;

/* A character type enum that contains the following:
 * PLAYER: player
 * ENEMY: enemy/enemies
 * (temporary values, to be developed at a later time)
 */
typedef enum char_t {
    PLAYER = 0,
    ENEMY = 1
} char_t;

/* A character struct that contains the following:
 * name: character name
 * char_type: character type, player or enemy
 * class: class type
 * stats: pointer to stats module (stub)
 * moves: pointer to moves module (stub)
 * items: pointer to items module (stub)
 * next: allows for character lists using utlist.h
 */
typedef struct _character_t {
    char *name;
    char_t type;
    class_t class;
    stat_t *stats;
    move_t *moves;
    item_t *items;
    character_t *next;
} character_t;

/* A battle struct that contains the following:
 * - player: a character pointer, storing the player
 * - enemies: a character pointer, storing the enemy/enemies
 * - environment: stores battle environment
 * - turn: a char_t enum storing the current turn
 */
typedef struct _battle_t {
    character_t *player;
    character_t *enemies;
    environment_t environment;
    char_t turn;
} battle_t;

/* Creates a new battle  struct
 * Parameters:
 * - player: a pointer to player character
 * - enemy: a pointer to enemy character/s
 * - environment: an environment enum
 * - turn: a char_t enum indicating the current turn
 * Return: a pointer to the new battle
 */
battle_t *battle_new(character_t *player, character_t *enemy,
    environment_t environment, char_t turn);

/* Initialize a battle  struct
 * Parameters:
 * - battle: a pointer to a battle struct in memory
 * - player: a pointer to player character
 * - enemy: a pointer to enemy character/s
 * - environment: an environment enum
 * - turn: a char_t enum indicating the current turn
 * returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int battle_init(battle_t battle, character_t *player, character_t *enemy,
    environment_t environment, char_t turn);

/* Frees a battle struct from memory */
void free_battle(battle_t *battle);

/* Initialize a character  struct
 * Parameters:
 * - name: name string
 * - char_type: char_t indicating character type
 * - stat_t: pointer to stats module (stub)
 * - move_t: pointer to moves module (stub)
 * - item_t: pointer to items module (stub)
 * - next: a pointer to a potential next character in a list
 * Return: a pointer to the new character
 */
character_t *character_new(char *name, char_t type, stat_t *stats,
    move_t *moves, item_t *items, character_t *next);

/* Creates a new character  struct
 * Parameters:
 * - character: a pointer to character in memory
 * - name: name string
 * - char_type: char_t indicating character type
 * - stat_t: a pointer to stats module (stub)
 * - move_t: a pointer to moves module (stub)
 * - item_t: a pointer to items module (stub)
 * - next: a pointer to a potential next character in a list
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int *character_init(character_t *character, char *name, char_t type,
     stat_t *stats, move_t *moves, item_t *items, character_t *next);

/* Frees a character struct from memory */
void free_character(character_t *character);
#endif
