/*
 * Lindsey Hsi, Patrick Koopmans, Jessica Xia
 * A player structure
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "game_state_common.h"
#include "stats.h"
#include "item.h"
#include "playerclass/class.h"
#include "skilltrees/skilltrees_enums.h"
#include "skilltrees/inventory.h"
#include "battle/battle_structs.h"

#define QUEST_NAME_MAX_LEN 44

/* An enum representing the possible quest completion statuses currently supportd */
typedef enum completion_status {
    Q_FAILED = -1,
    Q_UNACQUIRED,
    Q_STARTED,
    Q_COMPLETED,
} completion_status_t;

/* A reference to a given quest from game_state that the player has unlocked */
typedef struct player_quest {
    char *quest_id;
    completion_status_t completion;
    UT_hash_handle hh;
} player_quest_t;
typedef struct player_quest player_quest_hash_t;

/* A reference to a given task (for quests) from game_state that the player has unlocked */
typedef struct player_task {
    char *task_id;
    bool completed;
    UT_hash_handle hh;
} player_task_t;
typedef struct player_task player_task_hash_t;

/* A player in game */
typedef struct player {
    /* hh is used for hashtable, as provided in uthash.h*/
    UT_hash_handle hh;

    /* Unique id identifying the player */
    char *player_id;

    /* The player's current level */
    int level;

    /* The cumulative total of experience points acquired by the player */
    int xp;

    /* A string containing the player's race */
    char *player_race;
    
    /* A string containing the name of current room of the player. Right now, every player 
       must be in the same room, which is stored in the game struct, but this may change at 
       some point to allow players to explore at different paces. For now, this is necessary
       to allow certain modules to access the current room without causing circular dependencies. */
    char *crnt_room;

    /* The player's current class. class_t contains the base stats, and skills for that class at
    the beginning of a game. These may change throughout the game, so their current states are stored 
    in the health, player_stats, player_skills fields in this player struct */
    class_t *player_class;

    /* All of the stats, with their values, the player has. This should include
    both the maximum and current health if health is a feature of the current game */
    stats_hash_t *player_stats;

    /* The current skills known to the player */
    skill_inventory_t *player_skills;

    /* All of the effects the player is currently experiencing */
    effects_hash_t *player_effects;

    /* The current items held by the player*/
    item_hash_t *inventory;

    /* The current quests associated with the player */
    player_quest_hash_t* player_quests;

    /* The current tasks associated with the player */
    player_task_hash_t* player_tasks;

    /* The current moves available to the player */
    move_t *moves;
} player_t;

/* This typedef is to distinguish between player_t pointers which are 
* used to point to the player_t structs themselves, and those which are used
* to hash player_t structs with the UTHASH macros as specified
* in src/common/include */
typedef struct player player_hash_t;

/* 
 * Creates and initializes a new player_quest
 *
 * Parameters:
 * - quest_id: The quest id this player_quest is referencing
 * - completion: The current completion status of the quest
 * 
 * Returns:
 * - A pointer to the new player_quest or NULL if there was an error
*/
player_quest_t *player_quest_new(char *quest_id, int completion);

/* 
 * Creates and initializes a new player_task
 *
 * Parameters:
 * - task_id: The task id this player_task is referencing
 * - completed: Whether this task is already completed
 * 
 * Returns:
 * - A pointer to the new player_task or NULL if there was an error
*/
player_task_t *player_task_new(char *task_id, bool completed);

/*
 * Initializes a player quest
 * 
 * Parameters:
 * - pquest: The player_quest getting initialized
 * - quest_id: The quest_id this quest is referencing
 * - completion: The current completion status of the quest
 * 
 * Returns:
 * - SUCCESS if initialized successfully, FAILURE if an error occured
*/
int player_quest_init(player_quest_t *pquest, char *quest_id, int completion);

/*
 * Initializes a player task
 * 
 * Parameters:
 * - ptask: The player_task getting initialized
 * - task_id: The task_id this task is referencing
 * - completed: Whether this task is already completed
 * 
 * Returns:
 * - SUCCESS if initialized successfully, FAILURE if an error occured
*/
int player_task_init(player_task_t *ptask, char *task_id, bool completed);

/*
 * Frees a player_quest
 * 
 * Parameters:
 * - pquest: The player_quest to be freed
 * 
 * Returns:
 * - SUCCESS if freed successfully, FAILURE if an error occured
*/
int player_quest_free(player_quest_t *pquest);

/*
 * Frees a player_quest hash table
 * 
 * Parameters:
 * - player_quests: The player_quest table to be freed
 * 
 * Returns:
 * - SUCCESS if freed successfully, FAILURE if an error occured
*/
int player_quest_hash_free(player_quest_hash_t *player_quests);

/*
 * Frees a player_task
 * 
 * Parameters:
 * - ptask: The player_task to be freed
 * 
 * Returns:
 * - SUCCESS if freed successfully, FAILURE if an error occured
*/
int player_task_free(player_task_t *ptask);

/*
 * Frees a player_task hash table
 * 
 * Parameters:
 * - player_tasks: The player_task table to be freed
 * 
 * Returns:
 * - SUCCESS if freed successfully, FAILURE if an error occured
*/
int player_task_hash_free(player_task_hash_t *player_tasks);

/*
 * Allocates and creates a new player with given ID, starting at level
 *  1 with 0 xp. 
 *
 * Parameters:
 *  player_id: the unique string ID of the player
 *
 * Returns:
 *  Pointer to allocated player
 */
player_t *player_new(char *player_id);

/*
 * Frees resources associated with a player
 *
 * Parameters:
 *  player: the player to be freed
 *
 * Returns:
 *  SUCCESS if successful
 */
int player_free(player_t *player);

/* Deletes a hashtable of players
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of players that need to be deleted
 *
 * Returns:
 *  SUCCESS if successful
 */
int delete_all_players(player_hash_t* players);

/*
 * Sets an allocated player_t object's player_class field to given class_t class
 *          Makes deep copies of the given class's "starting_skills",
 *          "base_stats", and "effects fields" and updates the corresponding
 *          fields in the player struct
 *
 * Parameters:
 *  player: A player. Must point to already allocated memory.
 *  player_class: The player's class. Contains starting fields for
 *                skills and stats
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int player_set_class(player_t *player, class_t *player_class);

/*
 * Sets an allocated player_t's race field to the given string
 *
 * Parameters:
 *  player: A player. Must point to already allocated memory.
 *  player_race: A string containing the player's race
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int player_set_race(player_t *player, char *player_race);

/*
 * Returns the level of the player
 *
 * Parameters:
 *  player: the player
 *
 * Returns:
 *  int, the player's level
 */
int get_level(player_t *player);

/*
 * Increments the level of the player by given amt
 *
 * Parameters:
 *  player: the player
 *  change: the desired amount to increment in player level
 *
 * Returns:
 *  int, the new level
 */
int change_level(player_t *player, int change);

/*
 * Returns the experience points of the player
 *
 * Parameters:
 *  player: the player
 *
 * Returns:
 *  int, the player's experience
 */
int get_xp(player_t *player);

/*
 * Changes the experience (xp) points of the player
 *
 * Parameters:
 *  player: the player
 *  points: how much to change xp (positive or negative)
 *
 * Returns:
 *  int, the player's new xp
 */
int change_xp(player_t *player, int points);

/*
 * Returns the inventory list
 *
 * Parameters:
 *  player: the player
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t* get_inventory(player_t *player);

/* Removes an item from the given player
 * Note that the memory associated with this item is not freed
 * 
 * Parameters:
 *  player struct
 *  item struct
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int remove_item_from_player(player_t *player, item_t *item);

/*
 * Function to get a linked list (utlist) of all the items in the player's inventory
 *
 * Parameters:
 *  player
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_inventory(player_t *player);

/*
 * Returns if the item is in the player's inventory
 *
 * Parameters:
 *  player struct
 *  item struct
 *
 * Returns:
 *  true if item is inventory, false otherwise
 */
bool item_in_inventory(player_t *player, item_t *item);

/*
 * Assigns a table of stats to a player
 *
 * Parameters:
 *  player: the players
 *  sh: the stats hashtable
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int assign_stats_player(player_t *player, stats_hash_t *sh);

/*
 * Adds a skill to a player's respective skill inventory
 *
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  skill: pointer to an already existing skill that is being added to the
 *         player's skill inventory
 * 
 * Returns:
 *  SUCCESS on successful addition of skill, FAILURE if an error occurs
 * 
 * Note: Same return value as inventory_skill_add()
 */
int player_add_skill(player_t *player, skill_t *skill);

/*
 * Remove a skill from a player's respective skill inventory
 *
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  skill: pointer to an already existing skill that is being removed from the
 *         player's skill inventory
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs
 * 
 * Note: Same return value as inventory_skill_remove()
 */
int player_remove_skill(player_t *player, skill_t *skill);

/*
 * Searches for a skill in a player's respective skill inventory.
 *
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  sid: The skill ID that uniquely identifies the skill
 *  type: The skill type, either active or passive
 * 
 * Returns:
 *  The position of the skill in the skill inventory, -1 if the 
 *  skill is not in the skill inventory.
 *  
 *  Note: Same return value as inventory_has_skill()
 */
int player_has_skill(player_t *player, sid_t sid, skill_type_t type);

/*
 * Changes the base value of a given player's stat by the specified amount
 * 
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  quest_id: the id of the quest
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 * 
 */
int player_add_quest(player_t *player, char *quest_id);

/*
 * Changes the base value of a given player's stat by the specified amount
 * 
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  stat: the name/key of the stat
 *  change: the value to add to the stat. 
 *  If the value is greater than the local max, the value is set to the local max
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 * 
 * Note: Same return value as change_stat()
 */
int player_change_stat(player_t *player, char *stat, double change);

/*
 * Changes the max value of a given player's stat by the specified amount
 *
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  stat: the name/key of the stat
 *  change: the value to add to the stats max
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 *  
 * Note: Same return value as change_stat_max()
 */
int player_change_stat_max(player_t *player, char *stat, double change);

/* 
 * Gets the specified player stat from a player's stats hash table
 * 
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  stat: the name/key of the stat
 * 
 * Returns:
 *  double value of the player's stat. It the value is greater than the global
 *  max, the value is the global max
 * 
 * Note: Same return value as get_stat_current()
 */
double player_get_stat_current(player_t *player, char *stat);

/*
 * Adds a specified stat to a player's stat hash table
 *
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  s: Pointer to the stat to be added
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 * 
 * Note: Same return value as add_stat()
 */
int player_add_stat(player_t *player, stats_t *s);

/*
 * Adds a specified effect to the player's effects hash table
 *
 * Parameters:
 *  player: A player. Must be allocated with player_new()
 *  effect: Pointer to the effect to be added
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 * 
 * Note: Same return value as add_stat_effect()
 */
int player_add_stat_effect(player_t *player, stat_effect_t *effect);

/*
 * Adds a move to the player's list of moves 
 *
 * Parameters:
 *  - player: A player. Must be allocated with player_new()
 *  - move: pointer to the move to be added
 *
 * Returns:
 *  - Success or failure and modifies the status
 *
 */
int add_move(player_t *player, move_t *move);

/* 
 * Adds an item to the player's inventory without checking quests
 * 
 * Parameters:
 * - player: A player. Must be allocated with player_new()
 * - item: The item to add to the player's inventory
 * 
 * Returns:
 * - SuCCESS on success, FAILURE if an error occurs
*/
int add_item_to_player_without_checks(player_t *player, item_t *item);
#endif
