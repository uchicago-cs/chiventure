#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"
#include "quests/samples.h"
#include "playerclass/class.h"
#include "game-state/item.h"
#include "game-state/room.h"
#include "game-state/player.h"
#include "game-state/game.h"
#include "quests/quests_cli.h"

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

/* Tests the function that starts a quest */
Test(quest, start_quest)
{
	quest_t *quest = create_sample_quest("test", false, 0, NULL, false, 0, 0);

    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);

    int check = start_quest(quest, qctx);
    cr_assert_eq(check, SUCCESS, "start_quest() failed");
    
    int status = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(status, Q_STARTED, "start_quest() failed to set status (incorrectly returned %d)", status);
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

    cr_assert_eq(get_player_quest_status(quest, qctx->player), Q_FAILED, "fail_quest() failed to set status");
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
    update_task(task->id, qctx);

    bool in_inventory = item_in_inventory(qctx->player, item);
    cr_assert_eq(in_inventory, true, "complete task didn't properly give the reward");
    
    bool completed = is_task_completed(task, qctx->player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    completed = is_quest_completed(quest, qctx->player);
    cr_assert_eq(completed, true, "is_quest_completed() failed!");
    
    cr_assert_eq(get_player_quest_status(quest, qctx->player), Q_COMPLETED,"is_quest_completed() failed!");
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
    cr_assert_eq(check, Q_STARTED, "get_player_quest_status() failed with started status");
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
    cr_assert_eq(res, Q_COMPLETED, "complete_task() failed!");
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

/* Tests the function that reward the item after a quest*/
Test(quest,complete_quest)
{
    item_t *item = item_new("test_item", "item for testing", "test item");
	quest_t *quest = create_sample_quest("test", true, 50, item, true, 50, 5);
    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);

    int check = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(check, Q_UNACQUIRED, "get_quest_status() returned something interesting even though the quest hasn't started yet!");

    start_quest(quest, qctx);
    check = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(check, Q_STARTED, "get_quest_status() failed to set starting status!");

    cr_assert_eq(is_quest_completed(quest, qctx->player), true, "quest created in complete_quest is not complete");
    reward_t *res = complete_quest(quest, qctx->player);
    cr_assert_eq(get_player_quest_status(quest, qctx->player), Q_COMPLETED, "complete_quest failed to complete the quest");
    cr_assert_str_eq(res->item->item_id, "test_item", "complete_quest failed to reward the item");
}

/* Tests the function for if an npc gives quest */
Test(quest, npc_can_give_quest)
{
    item_t *item = item_new("test_item", "item for testing", "test item");
	quest_t *quest = create_sample_quest("test", true, 50, item, true, 50, 5);
    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);

    player_t *player = create_sample_player("player", 60, 6);
    qctx->player = player;

    int check = npc_can_give_quest(qctx, "test");

    cr_assert_eq(check, true, "npc_can_give_quest() failed");
}

/* Tests the function if an npc gives tasks */
Test(quest, npc_can_give_task)
{
    item_t *item = item_new("test_item", "item for testing", "test item");
	quest_t *quest = create_sample_quest("test", true, 50, item, true, 50, 5);
    task_t *task = create_sample_task("test", false, NULL, KILL_NPC, false, 0, NULL, true, 50, 5);
    add_task_to_quest(quest, task, NULL);
    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);

    player_t *player = create_sample_player("player", 60, 6);
    qctx->player = player;

    int check = npc_can_give_task(qctx, "test");

    cr_assert_eq(check, true, "npc_can_give_task() failed");
}

Test(task_tree, free)
{
    char *id1 = "test mission";

    mission_t *mission1 = mission_new("Steve", MEET_NPC);

    item_t *item1 = item_new("reward_item", "item for rewarding",
    "test item for item_new()");
    int xp1 = 40;
    reward_t *rewards1 = reward_new(xp1, item1);

    prereq_t *prereq1 = prereq_new(3, 2);

	task_t* task1 = task_new(id1, mission1, rewards1, prereq1);

    char *id2 = "test mission22";

    mission_t *mission2 = mission_new("JOe", MEET_NPC);

    item_t *item2 = item_new("reward_item", "item for rewarding",
    "test item for item_new()");
    int xp2 = 40;
    reward_t *rewards2 = reward_new(xp2, item2);

    prereq_t *prereq2 = prereq_new(3, 2);

	task_t* task2 = task_new(id2, mission2, rewards2, prereq2);

    item_t *item = item_new("test item", "item for testing", "item");
    reward_t *rewards = reward_new(20, item);
    prereq_t *prereq = prereq_new(50, 50);
    task_tree_t *task_tree = NULL;

    quest_t* q = quest_new("test", rewards, prereq);
    q->task_tree = task_tree;

    int add_parent = add_task_to_quest(q, task2, "test mission22");
    int add_child = add_task_to_quest(q, task1, "test mission");

    int freed = task_tree_free(q->task_tree);

    cr_assert_eq(freed, SUCCESS, "task_tree_free() failed");
}
