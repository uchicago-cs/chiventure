#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "quests/quests_cli.h"

// Functions for displaying quests

/* Converts a completion enum into a string
 *
 * Parameter:
 * - completion: A completion status enum
 * 
 * Returns:
 * - A pointer to a string representing the completion status
*/
char *completion_to_str(completion_status_t completion) {
    char *str = calloc(1, 11);
    switch (completion) {
        case Q_FAILED: 
            strncpy(str, "Failed", 6);
            break;
        case Q_UNACQUIRED:
            strncpy(str, "Unacquired", 10);
            break;
        case Q_STARTED:
            strncpy(str, "Started", 7);
            break;
        case Q_COMPLETED:
            strncpy(str, "Completed", 9);
            break;
    }
    return str;

}

/* See quests_cli.h */
char* show_quests(player_t *player)
{
    assert(player != NULL);
    int cur_len = 1;
    char *prev = malloc(cur_len);
    prev = '\0';
    for (player_quest_t *cur = player->player_quests; cur != NULL; cur = cur->hh.next) {
        char *quest_id = cur->quest_id;
        char *completion = completion_to_str(cur->completion);
        char *buf = malloc(18+strlen(quest_id)+strlen(completion));
        sprintf(buf, "Quest %s: Status: %s\n", quest_id, completion);
        cur_len += strlen(buf);
        prev = realloc(prev, cur_len);
        strcat(prev, buf);
        free(completion);
        free(buf);
    }

    return prev;
}

// Functions for displaying all info about a specific task

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
    char buf[50];
    snprintf(buf, 50, "%s ", id_list_start->id);
    char *rest = store_list(id_list_start->next);
    char *result = strcat(buf, rest);
    return result;
}

/* See quests_cli.h */
char* show_task(char* task_id, player_t *player, quest_hash_t *all_quests)
{
    char buf[1000];
    
    player_task_t *ptask = get_player_task_from_hash(task_id, player->player_tasks);

    task_t *task = get_task_from_quest_hash(task_id, all_quests);
    char *mission_name;
    if (task->mission != NULL) {
        mission_name = task->mission->target_name;
    } else {
        mission_name = "None";
    }

    char rewards[200];
    if (task->reward != NULL) {
        int reward_xp = task->reward->xp;
        char *reward_item;
        if (task->reward->item != NULL) {
            reward_item = task->reward->item->item_id;
        } else {
            reward_item = "no items";
        }
        sprintf(rewards, "%d xp and %s", reward_xp, reward_item);
    } else {
        sprintf(rewards, "None");
    }
    
    char prereqs[200];
    if (task->prereq != NULL) {
        int prereq_hp = task->prereq->hp;
        int prereq_level = task->prereq->level;
        char *prereq_tasks = store_list(task->prereq->task_list->head);
        char *prereq_quests = store_list(task->prereq->quest_list->head);
        sprintf(prereqs, "%d hp and %d level\nPrerequisite Tasks: %sPrerequisite Quests: %s",
                prereq_hp, prereq_level, prereq_tasks, prereq_quests);
    } else {
        sprintf(prereqs, "None\n");
    }

    sprintf(buf, "TASK: %s\nStatus: %s\nMission: %s\nRewards: %s\nPrerequisites: %s",
            task_id, ptask != NULL ? (ptask->completed ? "Completed!" : "Incomplete") : "Inactive  ",
            mission_name, rewards, prereqs);
    return strdup(buf);
}

// Functions for displaying a task tree

/* Creates an empty task printing block
 * - A task printing block is an array of 3 25 length strings
 *   where the first and second strings are the task's id
 *   and the third is the task's completion status
 * - An empty block is a block with each string containing
 *   only spaces
 * 
 * Returns:
 * - A pointer to an empty block created on the heap
*/
char **get_empty_block() {
    char **block = malloc(3 * sizeof(block));
    assert(block != NULL);
    for(int i = 0; i < 3; i++) {
        block[i] = malloc(26);
        assert(block[i] != NULL);
        strncpy(block[i], "                         ", 25);
        block[i][25] = '\0';
    }
    return block;
}

/* Creates a task printing block for a given task
 *  - see get_empty_block() for more info on task printing blocks
 *
 * Parameters:
 * - task: A not NULL task
 * - player: A player
 * 
 * Returns:
 * 
 * - A pointer to an initialized task printing block created on the heap
*/
char **get_task_block(task_t *task, player_t *player) {
    assert(task != NULL);
    assert(player != NULL);
    player_task_t *ptask = get_player_task_from_hash(task->id, player->player_tasks);
    char **block = get_empty_block();
    int len = strlen(task->id);
    strncpy(block[0], task->id, MIN(len, 22));
    int i = 1;
    if(strlen(task->id) > 25) {
        strncpy(block[1], task->id + 22, len - 22);
        i = 2;
    }
    strncpy(block[i], ptask != NULL ? (ptask->completed ? "Status: Completed!" : "Status: Incomplete") : "Status: Inactive  ", 18);
    return block;
}

/* Gets a task block if the task exists or an empty block if the task doesn't exist
 *
 * Parameters:
 * - task: A task (possibly NULL)
 * - player: A player
 * 
 * Returns:
 * - The a block initialized for the task or an empty block if the task is NULL
*/
char **get_block(task_t *task, player_t *player) {
    if(task != NULL) {
        return get_task_block(task, player);
    }
    return get_empty_block();
}

/* Merges corresponding strings from 2 blocks into the first block
 * - Also frees the second block
 *
 * Parameters:
 * - block1: The task printing block that will contain the merged contents
 * - block2: The task printing block getting merged and freed
 * - cur_size: The current length of each string in block1
*/
int merge_two_blocks(char **block1, char **block2, int cur_size) {
    for(int i = 0; i < 3; i++) {
        block1[i] = realloc(block1[i], cur_size + 26);
        strncpy(&block1[i][cur_size], block2[i], 25);
        block1[i][cur_size + 25] = '\0';
        free(block2[i]);
    }
    free(block2);
    return cur_size + 25;
}

/* A recursive helper for get_task_tree_height()
 *
 * Parameters:
 * - task_tree: The current task tree
 * - max_so_far: The maximum height seen so far
 * 
 * Returns:
 * - The maximum height between the max height of its child and its sibling
 *   OR max_so_far if the current task_tree is NULL
*/
int get_task_tree_height_rec(task_tree_t *task_tree, int max_so_far) {
    if(task_tree == NULL) {
        return max_so_far;
    }
    int child = get_task_tree_height_rec(task_tree->lmostchild, max_so_far + 1);
    int sibling = get_task_tree_height_rec(task_tree->rsibling, max_so_far);
    return MAX(child, sibling);
}

/* Calculates the height of a task tree
 *
 * Parameters:
 * - task_tree: A task tree
 * 
 * Returns:
 * - The height of the inputted task tree
 *
*/
int get_task_tree_height(task_tree_t *task_tree) {
    get_task_tree_height_rec(task_tree, 0);
} 

/* A recursive helper for get_task_tree_line_width()
 *
 * Parameters:
 * - task_tree: A task tree
 * - max_so_far: The max line width so far
 * 
 * Returns:
 * - The maximum line width between its child and its sibling
 *   OR max_so_far if the current task_tree is NULL
*/
int get_task_tree_line_width_rec(task_tree_t *task_tree, int max_so_far) {
    if(task_tree == NULL) {
        return max_so_far;
    }
    int child = get_task_tree_line_width_rec(task_tree->lmostchild, 0);
    int sibling = get_task_tree_line_width_rec(task_tree->rsibling, max_so_far + 1);
    return MAX(child, sibling);
}

/* Finds the tree's line width
 * - A tree's line width is the maximum number of siblings any node can have
 *
 * Parameters:
 * - task_tree: A task Tree
 *
 * Returns:
 * - The line width of the inputted task tree
*/
int get_task_tree_line_width(task_tree_t *task_tree) {
    return get_task_tree_line_width_rec(task_tree, 0);
}

/* A recursive helper for init_matricies()
 * 
 * Parameters:
 * - matrix: A pointer to a task tree matrix
 * - tree_line_matrix: A pointer to a tree line matrix
 * - cur_tree: The current task tree
 * - y: The corresponding y matrix index of the current tree
 * - x: The corresponding x matrix index of the current tree
 * - cur_line_width: The distance between matrix indicies for siblings
 *                   at this y level
 * - line_width: The tree's line width
 * 
*/
void init_matricies_rec(task_t ****matrix, int ***tree_line_matrix, task_tree_t *cur_tree, int y, int x, int cur_line_width, int line_width) {
    (*matrix)[y][x] = cur_tree->task;
    if(cur_tree->rsibling != NULL) {
        for(int i = 0; i < cur_line_width; i++) {
            (*tree_line_matrix)[y][x + i] = 1;
        }
        init_matricies_rec(matrix, tree_line_matrix, cur_tree->rsibling, y, x + cur_line_width, cur_line_width, line_width);
    }
    if(cur_tree->lmostchild != NULL) {
        init_matricies_rec(matrix, tree_line_matrix, cur_tree->lmostchild, y + 1, x, cur_line_width / line_width, line_width);
    }
}

/* Initializes a task matrix and a tree line matrix based on a given task tree
 * - A task matrix is a 2D array of task pointers. 
 *    - The tasks in the matrix should be spaced as the tree should be formatted
 * - A tree_line_matrix is a 2D array of 0s and 1s where each 1 represents a connected
 *   node in the tree
 * 
 * Ex: A tree with 2 tasks that each have 2 children
 * Task Matrix:
 *   t1p, NULL,  t2p, NULL
 *  t1c1, t1c2, t2c1, t2c2
 * 
 * Tree Line Matrix:
 * 1,    1,    0,    0
 * 1,    0,    1,    0
 * 
 * Parameters:
 * - matrix: A pointer to a task matrix
 * - tree_line_matrix: A pointer to a tree_line_matrix
 * - task_tree: A pointer to a task tree
 * - width: The width of the matricies
 * - line_width: The line width of the tree
*/
void init_matricies(task_t ****matrix, int ***tree_line_matrix, task_tree_t *task_tree, int width, int line_width) {
    init_matricies_rec(matrix, tree_line_matrix, task_tree, 0, 0, width / line_width, line_width);
}

/* Merges a row of a task matrix into a single string
 * 
 * Parameters:
 * - matrix_row: A pointer to a row from a task matrix
 * - tree_line_matrix_row: A pointer to a row from a tree line matrix
 * - player: A pointer to a player
 * - width: The width of the matricies
 * - last_line: Whether or not this is the last line in the matrix (1 or 0)
 *   - This is necessary so additional lines aren't printed under the tree
 * 
 * Returns:
 * - A string containing a properly formatted display of the tasks in the 
 *   row of that task matrix
*/
char *merge_line(task_t ***matrix_row, int **tree_line_matrix_row, player_t *player, int width, int last_line) {
    task_t *start = (*matrix_row)[0];
    char **start_block = get_block(start, player);
    char **next_block;
    int cur_size = 25;

    // Get blocks for each task in the line and merge them into one block
    for(int i = 1; i < width; i++) {
        next_block = get_block((*matrix_row)[i], player);
        cur_size = merge_two_blocks(start_block, next_block, cur_size);
    }

    // Allocates memory for the line's string
    char *str = malloc((cur_size + 1) * 6 + 1);

    // Adds '-'s and '|'s to the string to denote branch connections
    for(int i = 0; i < cur_size; i++) {
        str[i] = ((*tree_line_matrix_row)[i / 25] == 1) ? '-' : ' ';
        char vert = (i % 25 == 0 && (*matrix_row)[i / 25] != NULL) ? '|' : ' ';
        str[i + cur_size + 1] = vert;
        str[i + 5 * (cur_size + 1)] = vert;
    }
    str[cur_size] = '\n';
    str[2 * (cur_size + 1) - 1] = '\n';
    str[6 * (cur_size + 1) - 1] = '\n';
    
    // Puts each line from the merged block into the string
    for(int i = 2; i < 5; i++) {
        strncpy(str + i * (cur_size + 1), start_block[i - 2], cur_size);
        str[(i + 1) * (cur_size + 1) - 1] = '\n';
        free(start_block[i - 2]);
    }
    free(start_block);
    str[(cur_size + 1) * 6] = '\0';

    // If it is the last line of the matrix, the last row of lines should
    // not display
    if(last_line) {
        str[(cur_size + 1) * 5] = '\0';
    }
    return str;
}

/* Merges all of the rows of the task matrix into a single properly formatted string
 *
 * Parameters:
 * - matrix: A pointer to a task matrix
 * - tree_line_matrix: A pointer to a tree line matrix
 * - player: A pointer to a player
 * - width: The width of the matricies
 * - height: The height of the matricies
*/
char *merge_matrix(task_t ****matrix, int ***tree_line_matrix, player_t *player, int width, int height) {
    char *start_line = merge_line(&(*matrix)[0], &(*tree_line_matrix)[0], player, width, 0);
    int cur_len = strlen(start_line) + 1;
    char *line = malloc(cur_len);
    strncpy(line, start_line, cur_len - 1);
    line[cur_len - 1] = '\0';
    free(start_line);
    for(int i = 1; i < height; i++) {
        char *cur_line = merge_line(&(*matrix)[i], &(*tree_line_matrix)[i], player, width, i == height - 1);
        cur_len += strlen(cur_line);
        line = realloc(line, cur_len);
        strcat(line, cur_line);
        free(cur_line);
    }

    return line;
}

/* See quests_cli.h */
char *show_task_tree(char* quest_id, player_t *player, quest_hash_t *all_quests)
{
    // Find quest and player quest from quest_id
    quest_t *quest = get_quest_from_hash(quest_id, all_quests);
    player_quest_t *pquest = get_player_quest_from_hash(quest_id, player->player_quests);
    if(quest == NULL || pquest == NULL) {
        char *error = malloc(18);
        strncpy(error, "Quest not found!", 16);
        error[16] = '\n';
        error[17] = '\0';
        return error;
    }

    // Initializes task and tree line matricies
    int height = get_task_tree_height(quest->task_tree);
    int line_width = get_task_tree_line_width(quest->task_tree);
    int width = (int) pow(line_width, height);
    task_t ***task_matrix = malloc(height * sizeof(task_t***));
    int **tree_line_matrix = malloc(height * sizeof(int *));
    for(int i = 0; i < height; i++) {
        task_matrix[i] = malloc(width * sizeof(task_t**));
        tree_line_matrix[i] = malloc(width * sizeof(int));
        for(int j = 0; j < width; j++) {
            task_matrix[i][j] = NULL;
            tree_line_matrix[i][j] = 0;
        }
    }
    init_matricies(&task_matrix, &tree_line_matrix, quest->task_tree, width, line_width);
    
    // Merge the matricies to get the string output
    char *string = merge_matrix(&task_matrix, &tree_line_matrix, player, width, height);

    // Free the matricies
    for(int i = 0; i < height; i++) {
        free(task_matrix[i]);
        free(tree_line_matrix[i]);
    }
    free(task_matrix);
    free(tree_line_matrix);
    return string;
}