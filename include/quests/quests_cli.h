#ifndef QUESTS_CLI_H
#define QUESTS_CLI_H

#include "quests_state.h"

/* Function for cli that will put all quests the player has in a string
 *
 * Parameters:
 * - player: the player of the game
 *
 * Returns:
 * - a string of all the quests a player has
 */
char* show_quests(player_t *player);

/* Function for cli that will display the task tree associated with a quest
 *
 * Parameters:
 * - quest_id: the quest holding the task tree
 * - player: the player of the game
 * - all_quests: all of the quests in the game
 *
 * Returns:
 * - a string of the task tree
 */
char* show_task_tree(char* quest_id, player_t *player, quest_hash_t *all_quests);

/* Function for cli that will display the info of a task
 *
 * Parameters:
 * - task_id: the task that will be displayed
 * - player: the player of the game
 * - all_quests: all of the quests in the game
 *
 * Returns:
 * - a string of the task elements
 */
char* show_task(char* task_id, player_t *player, quest_hash_t *all_quests);

#endif /* QUESTS_CLI_H */