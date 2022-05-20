#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"
#include "quests/quests_structs.h"
#include "playerclass/class.h"
#include "game-state/item.h"
#include "game-state/room.h"
#include "game-state/player.h"
#include "game-state/game.h"

/* A helper function that creates a task and all parameters associated with it for testing 
 *
 * Parameters: 
 * - task_id: The id of the task getting created
 * - create_mission: Whether to create a mission for the task
 * - mission_target_name: The target name of the new mission (ignored if not creating a mission)
 * - mission_type: The type of the new mission (ignored if not creating a mission)
 * - create_reward: Whether to create a reward for the task
 * - reward_xp: The xp for the reward (ignored if not creating a reward)
 * - reward_item: A pointer to a preexisting item for the reward (ignored if not creating a reward)
 * - create_prereq: Whether to create a prereq for the task
 * - prereq_hp: The hp for the prereq (ignored if not creating a prereq)
 * - prereq_level: The level for the prereq (ignored if not creating a prereq)
 * 
 * Returns: 
 * - A pointer to the new task struct or NULL if there was an error
*/
task_t *create_sample_task(char *task_id, 
    bool create_mission, char *mission_target_name, mission_types_t mission_type,
    bool create_reward, int reward_xp, item_t *reward_item, 
    bool create_prereq, int prereq_hp, int prereq_level) {

    assert(task_id != NULL);

    mission_t *mission = NULL;
    if(create_mission) {
        mission = mission_new(mission_target_name, mission_type);
    }  

    reward_t *reward = NULL;
    if(create_reward) {
        reward = reward_new(reward_xp, reward_item);
    }

    prereq_t *prereq = NULL;
    if(create_prereq) {
        prereq = prereq_new(prereq_hp, prereq_level);
    }

    return task_new(task_id, mission, reward, prereq);
}

/* A helper function that creates a quest and all parameters associated with it for testing 
 *
 * Parameters: 
 * - quest_id: The id of the quest getting created
 * - create_reward: Whether to create a reward for the quest
 * - reward_xp: The xp for the reward (ignored if not creating a reward)
 * - reward_item: A pointer to a preexisting item for the reward (ignored if not creating a reward)
 * - create_prereq: Whether to create a prereq for the quest
 * - prereq_hp: The hp for the prereq (ignored if not creating a prereq)
 * - prereq_level: The level for the prereq (ignored if not creating a prereq)
 * 
 * Returns: 
 * - A pointer to the new quest struct or NULL if there was an error
*/
quest_t *create_sample_quest(char *quest_id,
    bool create_reward, int reward_xp, item_t *reward_item,
    bool create_prereq, int prereq_hp, int prereq_level) {
    
    assert(quest_id != NULL);

    reward_t *reward = NULL;
    if(create_reward) {
        reward = reward_new(reward_xp, reward_item);
    }

    prereq_t *prereq = NULL;
    if(create_prereq) {
        prereq = prereq_new(prereq_hp, prereq_level);
    }
    return quest_new(quest_id, reward, prereq);
}

/* A helper function that creates a player and all parameters associated with it for testing 
 *
 * Parameters: 
 * - player_id: The id of the player getting created
 * - health: The health of the player
 * - level: The level of the player
 * 
 * Returns: 
 * - A pointer to the new player struct or NULL if there was an error
*/
player_t *create_sample_player(char *player_id, int health, int level) {
    player_t* player = player_new(player_id);

    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player, health_stat);

    player->level = level;
    return player;
}

/* A helper function that creates a quest ctx with a default player (hp: 50, level: 5) and an 
 * empty quest hash table
 * 
 * Returns: 
 * - A pointer to the new quest_ctx struct or NULL if there was an error
*/
quest_ctx_t *create_sample_ctx() {
    player_t *player = create_sample_player("player", 50, 5);
    return quest_ctx_new(player, NULL);
}

/* Tests init function for mission struct */
Test(mission, init)
{   
    mission_t mission;

    int check = mission_init(&mission, "Poseidon", KILL_NPC);

    cr_assert_eq(check,SUCCESS,"mission_init() failed");
    cr_assert_eq(mission.target_name, "Poseidon", "mission_init() failed to set target name!");
    cr_assert_eq(mission.type, KILL_NPC, "mission_init() failed to set type!");
}

/* Tests init function for task struct */
Test(task, init)
{
    char *id = "test mission";
    mission_t *mission = mission_new("Trident", COLLECT_ITEM);

    item_t *item = item_new("reward_item", "item for rewarding",
    "test item for item_new()");
    int xp = 40;
    reward_t *rewards = reward_new(xp, item);;

    task_t *task = malloc(sizeof(task_t));

	int check = task_init(task, id, mission, rewards, NULL);

	cr_assert_eq(check, SUCCESS, "task_init() test has failed!");
}

/* Tests new function for reward struct */
Test(reward, new)
{
    int xp = 40;
	item_t *item = item_new("test_item", "item for testing",
    "test item for item_new()");

    reward_t *rewards = reward_new(xp, item);

    cr_assert_str_eq(rewards->item->item_id, "test_item",
                     "reward_new did not set item_id reward");
    cr_assert_eq(rewards->xp, 40,  "reward_new did not set xp");                 
}

/* tests init function for prereq struct */
Test(prereq, init)
{
    int hp = 40;
    int level = 5;

    prereq_t prereq;

    int rc = prereq_init(&prereq, hp, level);

    cr_assert_eq(rc, SUCCESS, "prereq_init failed!");
    cr_assert_eq(prereq.hp, 40, "prereq_init did not set hp");
    cr_assert_eq(prereq.level, 5, "prereq_init did not set level");  
}

/* Tests new function for prereq struct */
Test(prereq, new)
{
    int hp = 20;
    int level = 17;

    prereq_t *prereq = prereq_new(hp, level);

    cr_assert_not_null(prereq, "prereq_new failed to create a prereq");
    cr_assert_eq(prereq->hp, 20, "prereq did not set hp");
    cr_assert_eq(prereq->level, 17, "prereq did not set level");  
}

/* Tests init function for quest struct */
Test(quest, init)
{   
    quest_t q;

    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	int check = quest_init(&q, "test", rewards, prereq);

	cr_assert_eq(check, SUCCESS, "quest_init() test has failed!");
    cr_assert_eq(q.prereq, prereq, "quest_init() failed to set prereq!");
    cr_assert_eq(q.reward, rewards, "quest_init() failed to set reward!");

}

/* Tests new task malloc (new uses init) */
Test(task, new)
{
    char *id = "test mission";

    mission_t *mission = mission_new("Steve", MEET_NPC);

    item_t *item = item_new("reward_item", "item for rewarding",
    "test item for item_new()");
    int xp = 40;
    reward_t *rewards = reward_new(xp, item);

    prereq_t *prereq = prereq_new(3, 2);

	task_t* task = task_new(id, mission, rewards, prereq);

	cr_assert_not_null(task, "task_new() test has failed!");
    cr_assert_str_eq(task->id, id, "task_new() didn't set id!");
    cr_assert_eq(task->mission, mission, "task_new() didn't set mission!");
    cr_assert_eq(task->reward, rewards, "task_new() didn't set rewards!");
    cr_assert_eq(task->prereq, prereq, "task_new() didn't set prereq!");
}

/* Tests new quest malloc (new uses init) */
Test(quest, new)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t* q = quest_new("test", rewards, prereq);

	cr_assert_not_null(q, "quest_new() test has failed!");


    cr_assert(strcmp(q->quest_id, "test") == 0, "quest_new()"
                "did not initialize the task tree");
    cr_assert_str_eq(q->reward->item->item_id, "test_item", "quest_new()"
                "did not initialize the reward item");
    cr_assert_eq(q->reward->xp, 50, "quest_new()"
                "did not initialize the xp reward");
    cr_assert_eq(q->prereq->hp, 50,
                     "quest_init did not set prereq hp");
    cr_assert_eq(q->prereq->level, 5,
                     "quest_init did not set prereq level");
}

/* Tests task_free function */
Test(task, free)
{
	task_t* task_to_free = create_sample_task("test", 
                                                false, NULL, MEET_NPC, 
                                                false, 0, NULL, 
                                                false, 0, 0);

	cr_assert_not_null(task_to_free, "task_free(): room is null");

	int freed = task_free(task_to_free);

	cr_assert_eq(freed, SUCCESS, "task_free() test has failed!");
}

/* Tests mission_free function */
Test(mission, free)
{
    mission_t *mission = mission_new("Atlantis", VISIT_ROOM);

    cr_assert_not_null(mission, "mission_free(): room is null");
    
    int freed = mission_free(mission);

    cr_assert_eq(freed, SUCCESS, "mission_free() test has failed!");
}

/* Tests quest_free function */
Test(quest, free)
{
    quest_t *q_to_free = create_sample_quest("test",
                                                false, 50, NULL,
                                                false, 0, 0);

	cr_assert_not_null(q_to_free, "quest_free(): quest not created properly");
    cr_assert(strcmp(q_to_free->quest_id, "test") == 0, "quest_id incorrect");

	int freed = quest_free(q_to_free);

	cr_assert_eq(freed, SUCCESS, "quest_free() test has failed!");
}

/*Tests adding task to a quest */
Test(quest, add_task_to_quest)
{
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    quest_t *quest = create_sample_quest("test",
                                            true, 50, item,
                                            false, 0, 0);

	task_t *task_to_add = create_sample_task("test task",
                                                false, NULL, KILL_NPC,
                                                true, 50, NULL,
                                                false, 0, 0);
    task_t *task_sibling = create_sample_task("test sibling",
                                              false, NULL, KILL_NPC,
                                              true, 60, NULL,
                                              false, 0, 0);
    task_t *task_child = create_sample_task("test child",
                                             false, NULL, KILL_NPC,
                                             true, 70, NULL,
                                             false, 0, 0);
    task_t *task_sibling_child = create_sample_task("test sibling child",
                                                    false, NULL, KILL_NPC,
                                                    true, 80, NULL,
                                                    false, 0, 0);
    task_t *task_child_sibling = create_sample_task("test child sibling",
                                                    false, NULL, KILL_NPC,
                                                    true, 90, NULL,
                                                    false, 0, 0);
                                             

    int res = add_task_to_quest(quest, task_to_add, NULL);
    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");

    res = add_task_to_quest(quest, task_sibling, NULL);
    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");

    res = add_task_to_quest(quest, task_child, "test task");
    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");

    res = add_task_to_quest(quest, task_sibling_child, "test sibling");
    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");

    res = add_task_to_quest(quest, task_child_sibling, "test task");
    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");
    
    cr_assert_eq(quest->task_tree->task, task_to_add, "add_task_to_quest() didn't set first task");
    cr_assert_eq(quest->task_tree->rsibling->task, task_sibling, "add_task_to_quest() didn't set first sibling");
    cr_assert_eq(quest->task_tree->lmostchild->task, task_child, "add_task_to_quest() didn't set child");
    cr_assert_eq(quest->task_tree->rsibling->lmostchild->task, task_sibling_child, "add_task_to_quest() didn't set sibling's child");
    cr_assert_eq(quest->task_tree->lmostchild->rsibling->task, task_child_sibling, "add_task_to_quest() didn't set child's sibling");
}

/* Tests if a player created with specified stats meets prereqs of different specifie stats
 *
 * Parameters:
 * - player_hp: The health of the player getting created
 * - player_level: The level of the player getting created
 * - prereq_hp: The health for the prereq getting created
 * - prereq_level: The level for the prereq getting created
 * - expected_result: Whether or not the player is supposed to meet the prereqs
 *   
*/
void meets_prereqs_test(int player_hp, int player_level, int prereq_hp, int prereq_level, bool expected_result) {
    player_t *player = create_sample_player("player1", player_hp, player_level);
    prereq_t *prereq = prereq_new(prereq_hp, prereq_level);

    bool rc = meets_prereqs(player, prereq);

    cr_assert_eq(rc, expected_result, "meets_prereqs() returned the incorrect result!");
}

/* Tests if a player meets prereqs */
Test(quest, meets_prereqs)
{
    meets_prereqs_test(50, 5, 30, 2, true);
}

/* Tests if a player does not make prereqs because of their level*/
Test(quest, cannot_start_level)
{
    meets_prereqs_test(50, 5, 30, 70, false);
}

/* Tests if a player does not meet prereqs because of their health */
Test(quest, cannot_start_health)
{
    meets_prereqs_test(50, 5, 7000, 3, false);
}

/* Tests the function that starts a quest */
Test(quest, start_quest)
{
	quest_t *quest = create_sample_quest("test", false, 0, NULL, false, 0, 0);

    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);

    int check = start_quest(quest, qctx);
    cr_assert_eq(check, SUCCESS, "start_quest() failed");
    
    int status = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(status, 1, "start_quest() failed to set status (incorrectly returned %d)", status);
}

/* Tests the function  that fails a quest */
Test(quest, fail_quest)
{
    quest_t *quest = create_sample_quest("test", false, 0, NULL, false, 0, 0);
    task_t *task = create_sample_task("test", false, NULL, KILL_NPC, false, 0, NULL, true, 700, 700);
    add_task_to_quest(quest, task, NULL);
    
    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);
    
    start_quest(quest, qctx);

    int check = fail_quest(quest, qctx->player);
    cr_assert_eq(check, SUCCESS, "fail_quest() failed");

    cr_assert_eq(get_player_quest_status(quest, qctx->player), -1, "fail_quest() failed to set status");
}


/* Tests the function that completes the task when the task has a mission */
Test(quest, complete_task_mission)
{
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    item_t *trident = item_new("trident", "Poseidon's sacred trident", "The epic trident that Poseidon weilds to protect the World's Oldest Bubble from harm");

    quest_t* quest = create_sample_quest("test", true, 50, item, false, 0, 0);
    task_t *task_to_complete = create_sample_task("acquire trident", true, "trident", COLLECT_ITEM, true, 50, NULL, false, 0, 0);

    add_task_to_quest(quest, task_to_complete, "NULL");

    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);
    add_quest_to_game(ctx->game, quest); 
    
    quest_ctx_t *qctx = create_sample_ctx();
    qctx->quest_hash = ctx->game->all_quests;
    assert(qctx->player->player_quests == NULL);
    start_quest(quest, qctx);

    bool completed = is_task_completed(task_to_complete, qctx->player);
    cr_assert_eq(completed, false, "is_task_completed() returned true when it shouldn't have!");

    add_item_to_player(qctx->player, trident, ctx->game);
    int res = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(res, 2, "complete_task() failed!");
}

/* Tests the function that completes the task when the task has a prereq*/
Test(quest, complete_task_prereq)
{
    quest_t *quest = create_sample_quest("test", true, 50, NULL, true, 50, 5);
	task_t* task_to_complete = create_sample_task("test", false, NULL, KILL_NPC, false, 0, NULL, true, 50, 5);
    add_task_to_quest(quest, task_to_complete, NULL);

    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);
    start_quest(quest, qctx);
    
    bool completed = is_task_completed(task_to_complete, qctx->player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    cr_assert_eq(get_player_task_from_hash(task_to_complete->id, qctx->player->player_tasks)->completed, true, "start_quest didn't call complete_task() properly failed!");
}

/* Function that tests if a quest is completed */
Test(quest,is_quest_completed)
{
    item_t *item = item_new("test_item", "item for testing", "test item");
	quest_t* quest = create_sample_quest("Cinderella", true, 50, item, false, 0, 0);

    room_t* room_to_visit = room_new("Grand ballroom", "A room", "A test room");

    task_t *task = create_sample_task("Visit ballroom", true, "Grand ballroom", VISIT_ROOM, true, 50, item, false, 0, 0);
    add_task_to_quest(quest, task, NULL);

    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);
    qctx->player->crnt_room = "Grand ballroom";

    start_quest(quest, qctx);
    accept_reward(complete_task(task->id, qctx), qctx);

    bool in_inventory = item_in_inventory(qctx->player, item);
    cr_assert_eq(in_inventory, true, "complete task didn't properly give the reward");
    
    bool completed = is_task_completed(task, qctx->player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    completed = is_quest_completed(quest, qctx->player);
    cr_assert_eq(completed, true, "is_quest_completed() failed!");
    
    cr_assert_eq(get_player_quest_status(quest, qctx->player), 2,"is_quest_completed() failed!");
    player_free(qctx->player);
}

/* Tests the function that checks the status of the quest */
Test(quest,get_player_quest_status)
{
	quest_t *quest = create_sample_quest("test", false, 0, 0, false, 0, 0);
    quest_ctx_t *qctx = create_sample_ctx();

    int check = get_player_quest_status(quest, qctx->player);

    cr_assert_eq(check, 0, "get_player_quest_status() failed with not statred status");

    add_quest_to_hash(quest, &qctx->quest_hash);
    start_quest(quest, qctx);

    check = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(check, 1, "get_player_quest_status() failed with started status");
}

/* Tests the function that reward the item after a quest*/
Test(quest,complete_quest)
{
    item_t *item = item_new("test_item", "item for testing", "test item");
	quest_t *quest = create_sample_quest("test", true, 50, item, true, 50, 5);
    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);

    int check = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(check, 0, "get_quest_status() returned something interesting even though the quest hasn't started yet!");

    start_quest(quest, qctx);
    check = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(check, 1, "get_quest_status() failed to set starting status!");

    cr_assert_eq(is_quest_completed(quest, qctx->player), true, "quest created in complete_quest is not complete");
    reward_t *res = complete_quest(quest, qctx->player);
    cr_assert_eq(get_player_quest_status(quest, qctx->player), 2, "complete_quest failed to complete the quest");
    cr_assert_str_eq(res->item->item_id, "test_item", "complete_quest failed to reward the item");
}

/*see if get_quest_from_hash works with no quests in the hash and with quests in the hash */ 
Test(quest,get_quest)
{ 
    quest_t *quest1 = create_sample_quest("quest one", false, 0, 0, false, 0, 0);
    quest_t *quest2 = create_sample_quest("quest 2", false, 0, 0, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;

    quest_t *answer = get_quest_from_hash("quest one", test_hash_table); 
    cr_assert_eq(answer, NULL, "get_quest() returned quest one was in the table before it was added!");

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table);

    quest_t *answer1 = get_quest_from_hash("quest one", test_hash_table); 
    cr_assert_eq(answer1, quest1, "get_quest() did not return the right quest");

    quest_t *answer2 = get_quest_from_hash("beeppop",test_hash_table); 
    cr_assert_eq(answer2, NULL, "There is an quest with ID of beeppop ");

}

/*test for add task when 2 unique task_ID */ 
Test(test, add_task_test1)
{
    quest_hash_t *hash = NULL;
    quest_t *quest = create_sample_quest("quest one", false, 0, NULL, false, 0, 0);
    add_quest_to_hash(quest, &hash);

    task_t *task1 = create_sample_task("task one", false, NULL, KILL_NPC, false, 0, 0, false, 0, 0);
    task_t *task2 = create_sample_task("task two", false, NULL, KILL_NPC, false, 0, 0, false, 0, 0);

    quest_ctx_t *qctx = create_sample_ctx();

    int add_task1 = add_task_to_player_hash(task1, qctx);
    int add_task2 = add_task_to_player_hash(task2, qctx); 
    int add_task1_again = add_task_to_player_hash(task1, qctx);

    cr_assert_eq(add_task1, SUCCESS, "Could not sucessfully add task1"); 
    cr_assert_eq(add_task2, SUCCESS, "Could not sucessfully add task2"); 
    cr_assert_eq(add_task1_again, FAILURE, "Added task one to the player hash twice!");
}

/*test for add quest with 2 unique quest_ID and with adding the same quest */ 
Test(test, add_quest_test)
{
    quest_t *quest1 = create_sample_quest("quest one", false, 0, NULL, false, 0, 0);
    quest_t *quest2 = create_sample_quest("quest two", false, 0, NULL, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table); 
    int add_quest_fail = add_quest_to_hash(quest1, &test_hash_table);

    cr_assert_eq(add_quest1, SUCCESS, "Could not sucessfully add quest1"); 
    cr_assert_eq(add_quest2, SUCCESS, "Could not sucessfully add quest2"); 
    cr_assert_eq(add_quest_fail, FAILURE, "Added quest one to the hash twice!"); 
}

/* Tests the function that removes one quest from hash table */
Test(quest, remove_quest_one)
{
    quest_t *quest1 = create_sample_quest("remove quest", false, 0, NULL, false, 0, 0);
    quest_t *quest2 = create_sample_quest("keep quest", false, 0, NULL, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;
    add_quest_to_hash(quest1, &test_hash_table);
    add_quest_to_hash(quest2, &test_hash_table);

    // only removing one quest
    int res = remove_quest_in_hash(test_hash_table, quest1->quest_id);
    cr_assert_eq(res, SUCCESS, "failed to remove");
    cr_assert_null(get_quest_from_hash("remove quest", test_hash_table), "Quest 1 not removed properly!");
    cr_assert_not_null(get_quest_from_hash("keep quest", test_hash_table), "Quest 2 removed even though it's not supposed to be!");
}

/* Tests the function that removes all quests from hash table */
Test(quest, remove_quest_all)
{
    quest_t *quest1 = create_sample_quest("remove quest 1", false, 0, NULL, false, 0, 0);
    quest_t *quest2 = create_sample_quest("remove quest 2", false, 0, NULL, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;
    add_quest_to_hash(quest1, &test_hash_table);
    add_quest_to_hash(quest2, &test_hash_table);

    int res = remove_quest_all(&test_hash_table);
    cr_assert_eq(res, SUCCESS, "remove_quest_all() failed to 2nd test");
    
    quest_t *result1 = get_quest_from_hash("remove quest 1", test_hash_table);
    quest_t *result2 = get_quest_from_hash("remove quest 2", test_hash_table);

    cr_assert_null(result1, "Quest 1 not removed properly!");
    cr_assert_null(result2, "Quest 2 not removed properly!");
}

/* Tests the function that adds the contents of a reward struct into a player struct */
Test(quest, accept_reward) {
    item_t *item = item_new("test item!", "item for testing", "This item is made for testing purposes only and is not intended to give the player any sense of enjoyment.");
    reward_t *reward = reward_new(40, item);
    player_t *player = player_new("Steve");
    quest_hash_t *quest_hash = NULL;
    quest_ctx_t *qctx = quest_ctx_new(player, quest_hash);

    accept_reward(reward, qctx);
    cr_assert_eq(player->xp, 40, "accept_reward() didn't properly give xp!");

    item_t *search_item = get_item_in_hash(player->inventory, item->item_id);
    cr_assert_not_null(search_item, "item not added to player's inventory");
}
