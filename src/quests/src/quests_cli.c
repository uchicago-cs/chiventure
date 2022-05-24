#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_cli.h"

/* See quests_cli.h */
char* show_quests(player_t *player)
{
    return NULL;
}

/* See quests_cli.h */
char* show_task_tree(char* quest_id, player_t *player, quest_hash_t *all_quests)
{
    return NULL;
}

/* helper function to print all the elements of a list
 *
 * Parameters
 * - id_list_start: the first node of an id list
 *
 * Returns:
 * - a string holding the list of ids
 *
 */
char *store_list(id_list_node_t *id_list_start)
{
    if(id_list_start == NULL) {
        return strdup("\n");
    }
    char buf[40];
    snprintf(buf, 40, "%s ", id_list_start->id);
    char *rest = store_list(id_list_start->next);
    char *result = strcat(buf, rest);
    return result;
}

/* See quests_cli.h */
char* show_task(char* task_id, player_t *player, quest_hash_t *all_quests)
{
    char buf[1000];
    
    task_t *task = get_task_from_quest_hash(task_id, all_quests);
    char *mission_name = task->mission->target_name;
    int reward_xp = task->reward->xp;
    char *reward_item = task->reward->item->item_id;
    int prereq_hp = task->prereq->hp;
    int prereq_level = task->prereq->level;
    char *prereq_tasks = store_list(task->prereq->task_list->head);
    char *prereq_quests = store_list(task->prereq->quest_list->head);

    sprintf(buf, "TASK: %s\nMission: %s\nRewards: %d xp and %s\nPrerequisites: "
            "%d hp and %d level\nPrerequisite Tasks: %sPrerequisite Quests: %s",
            task_id, mission_name, reward_xp, reward_item, prereq_hp, prereq_level,
            prereq_tasks, prereq_quests);
    return strdup(buf);
}

