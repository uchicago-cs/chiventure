#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"
#include "playerclass/class.h"
#include "game-state/item.h"
#include "game-state/room.h"
#include "game-state/player.h"
#include "game-state/game.h"

/* Creates a sample class. Taken from test_class.c */
class_t* generate_test_class()
{
    class_t* c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
                " relying on physical strength and years of training to "
                "deal with any obstacle. Mechanically, the warrior focuses "
                "on up-close physical damage with weapons and survives enemy "
                "attacks using heavy armor.\n";

    c = class_new(name, shortdesc, longdesc, NULL, NULL, NULL);

}

/* Tests the function that adds a reward to the player class */
Test(quest, accept_reward) {
    item_t *item = item_new("test item", "item for testing", "This item is made for testing purposes only and is not intended to give the player any sense of enjoyment.");
    reward_t *reward = reward_new(40, item);
    player_t *player = player_new("Steve");

    cr_assert_eq(player->xp, 0, "player xp not initialized to 0!");

    accept_reward(reward, player);

    cr_assert_eq(player->xp, 40, "accept_reward() didn't properly give xp!");
    item_t *search_item = get_item_in_hash(player->inventory, item->item_id);
    cr_assert_not_null(search_item, "item not added to player's inventory");
    
}

/* Tests if a player meets prereqs */
Test(quest, meets_prereqs)
{
    double health = 70;
    int pLevel = 7;

    player_t* player1 = player_new("player1");
    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player1, health_stat);

    player1->level = pLevel;

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);


    bool rc = meets_prereqs(player1, prereq);

    cr_assert_eq(rc, true, "meets_prereqs() returned false, expected true");
}

/* Tests if a player does not make prereqs because of their level*/
Test(quest, cannot_start_level)
{
    int health = 60;
    int pLevel = 1;

    player_t* player1 = player_new("player1");
    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player1, health_stat);

    player1->level = pLevel;

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);


    bool rc = meets_prereqs(player1, prereq);

    cr_assert_eq(rc, false, "meets_prereqs() returned true, expected false");
}

/* Tests if a player does not meet prereqs because of their health */
Test(quest, cannot_start_health)
{
    int health = 20;
    int pLevel = 7;

    player_t* player1 = player_new("player1");
    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player1, health_stat);

    player1->level = pLevel;

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);


    bool rc = meets_prereqs(player1, prereq);

    cr_assert_eq(rc, false, "meets_prereqs() returned true, expected false");
}

/*Tests adding task to a quest */
Test(quest, add_task_to_quest)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;

	quest_t* quest = quest_new("test", NULL, rewards, NULL);
	item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
    char *id = "test mission";

	task_t* task_to_add = task_new(NULL, id, rewards, NULL);

    int res = add_task_to_quest(quest, task_to_add, "NULL");

    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");
}

/* Tests the function that starts a quest */
Test(quest, start_quest)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t *quest = quest_new("test", NULL, rewards, prereq);

    quest_hash_t *hash = NULL;
    add_quest_to_hash(quest, &hash);

    player_t *player = player_new("test player");
    int check = start_quest(quest, player, hash);

    cr_assert_eq(check, SUCCESS, "start_quest() failed");
    int status = get_player_quest_status(quest, player);
    cr_assert_eq(status, 1, "start_quest() failed to set status (incorrectly returned %d)", status);
    player_free(player);
}

/* Tests the function  that fails a quest */
Test(quest, fail_quest)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t* quest = quest_new("test", NULL, rewards, prereq);
    player_t *player = player_new("test player");

    quest_hash_t *hash = NULL;
    add_quest_to_hash(quest, &hash);
    
    start_quest(quest, player, hash);

    int check = fail_quest(quest, player);

    cr_assert_eq(check, SUCCESS, "fail_quest() failed");

    cr_assert_eq(get_player_quest_status(quest, player), -1, "fail_quest() failed to set status");
    player_free(player);
}

/* Function that tests if a quest is completed */
Test(quest,is_quest_completed)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t* quest = quest_new("test", NULL, rewards, prereq);

    class_t* class = generate_test_class();
    char *npc_meet_id = "meet_npc";
    char *npc_kill_id = "kill_npc";

    room_t* room_to_visit = room_new("Grand ballroom", "A room", "A test room");

    mission_t *mission = mission_new("Grand ballroom", VISIT_ROOM); 

    char *id = "test mission";

    task_t *task = task_new(mission, "mission", rewards, NULL);

    int res = add_task_to_quest(quest, task, NULL);

    player_t *player = player_new("test player");
    player->crnt_room = "Grand ballroom";

    quest_hash_t *hash = NULL;
    add_quest_to_hash(quest, &hash);

    start_quest(quest, player, hash);
    reward_t *the_reward = complete_task(task->id, player, quest);
    if (the_reward == NULL) {
        res = FAILURE;
    }
    bool completed = is_task_completed(task, player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    completed = is_quest_completed(quest, player);
    cr_assert_eq(completed, true, "is_quest_completed() failed!");
    
    cr_assert_eq(get_player_quest_status(quest, player), 2,"is_quest_completed() failed!");
    player_free(player);
}

/* Tests the function that checks the status of the quest */
Test(quest,get_player_quest_status)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t *quest = quest_new("test", NULL, rewards, prereq);
    player_t *player = player_new("test player");
    int check = get_player_quest_status(quest, player);

    cr_assert_eq(check, 0, "get_player_quest_status() failed with not statred status");

    quest_hash_t *hash = NULL;
    add_quest_to_hash(quest, &hash);

    start_quest(quest, player, hash);
    check = get_player_quest_status(quest, player);

    cr_assert_eq(check,1,"get_player_quest_status() failed with started status");
    player_free(player);
}

/* Tests the function that completes the task when the task has a mission */
Test(quest, complete_task_mission)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, NULL);

    item_t *trident= item_new("trident", "Poseidon's sacred trident", "The epic trident that Poseidon weilds to protect the World's Oldest Bubble from harm");
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    mission_t *mission = mission_new("trident", COLLECT_ITEM); 

    char *id = "test mission";

	task_t* task_to_complete = task_new(mission, id, rewards, NULL);

    int res = add_task_to_quest(quest, task_to_complete, "NULL");
    
    add_quest_to_game(ctx->game, quest); 

    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");
    player_t *player = player_new("test player");
    start_quest(quest, player, ctx->game->all_quests);

    bool completed = is_task_completed(task_to_complete, player);
    cr_assert_eq(completed, false, "is_task_completed() returned true when it shouldn't have!");

    add_item_to_player(player, trident, ctx->game);

    res = get_player_quest_status(quest, player);
    cr_assert_eq(res, 2, "complete_task() failed!");
    player_free(player);
}

/* Tests the function that completes the task when the task has a prereq*/
Test(quest, complete_task_prereq)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, prereq);

    quest_hash_t *hash = NULL;
    add_quest_to_hash(quest, &hash);

    class_t* class = generate_test_class();

    char *id = "test mission";

	task_t* task_to_complete = task_new(NULL, id, rewards, prereq);

    int res = add_task_to_quest(quest, task_to_complete, "NULL");

    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");

    player_t *player = player_new("test player");
    stats_global_t *global = stats_global_new("health", hp);
    stats_t *health_stat = stats_new(global, hp);
    player_add_stat(player, health_stat);
    player->level = level;
    start_quest(quest, player, hash);
    
    bool completed = is_task_completed(task_to_complete, player);
    cr_assert_eq(completed, true, "is_task_completed() returned false!");

    cr_assert_eq(get_player_task_from_hash(task_to_complete->id, player->player_tasks)->completed, true, "start_quest didn't call complete_task() properly failed!");
    player_free(player);
}

/* Tests the function that reward the item after a quest*/
Test(quest,complete_quest)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t *quest = quest_new("test", NULL, rewards, prereq);
    player_t *player = player_new("test player");
    int check = get_player_quest_status(quest, player);

    cr_assert_eq(check, 0, "get_quest_status() failed with not statred status");

    quest_hash_t *hash = NULL;
    add_quest_to_hash(quest, &hash);

    start_quest(quest, player, hash);
    check = get_player_quest_status(quest, player);

    cr_assert_eq(check,1,"get_quest_status() failed with started status");
    cr_assert_eq(is_quest_completed(quest, player), true, "quest created in complete_quest is not complete");
    reward_t *res = complete_quest(quest, player);

    cr_assert_eq(get_player_quest_status(quest, player), 2, "complete_quest failed to complete the quest");
    cr_assert_str_eq(res->item->item_id, "test_item",
                    "complete_quest failed to reward the item");
}

/* Tests the function that is incomplete*/
Test(quest,complete_quest2)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t* quest = quest_new("test", NULL, rewards, prereq);
    player_t *player = player_new("test player");

    quest_hash_t *hash = NULL;
    add_quest_to_hash(quest, &hash);

    start_quest(quest, player, hash);

    reward_t *res = complete_quest(quest, player);

    cr_assert_eq(res, NULL,"quest_completed failed to reward the item");
}

