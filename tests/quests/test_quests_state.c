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

	int check = task_init(task, mission, id, rewards, NULL);

	cr_assert_eq(check, SUCCESS, "task_init() test has failed!");
}

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

Test(prereq, new)
{
    int hp = 20;
    int level = 17;

    prereq_t *prereq = prereq_new(hp, level);

    cr_assert_not_null(prereq, "prereq_new failed to create a prereq");
    cr_assert_eq(prereq->hp, 20, "prereq did not set hp");
    cr_assert_eq(prereq->level, 17, "prereq did not set level");  
}


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

	int check = quest_init(&q, "test", NULL, rewards, prereq);

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

	task_t* task = task_new(mission, id, rewards, NULL);

	cr_assert_not_null(task, "task_new() test has failed!");
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

	quest_t* q = quest_new("test", NULL, rewards, prereq);

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
    char *id = "test task";

    int xp = 30;
    reward_t *rewards = reward_new(xp, NULL);

	task_t* task_to_free = task_new(NULL, id, rewards, NULL);


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
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

	quest_t* q_to_free = quest_new("test", NULL, rewards, prereq);

	cr_assert_not_null(q_to_free, "quest_free(): room is null");
    cr_assert(strcmp(q_to_free->quest_id, "test") == 0, "quest_id incorrect");

	int freed = quest_free(q_to_free);

	cr_assert_eq(freed, SUCCESS, "quest_free() test has failed!");
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
    quest_ctx_t *qctx = quest_ctx_new(player, hash);
    int check = start_quest(quest, qctx);

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

    quest_ctx_t *qctx = quest_ctx_new(player, hash);
    
    start_quest(quest, qctx);

    int check = fail_quest(quest, player);

    cr_assert_eq(check, SUCCESS, "fail_quest() failed");

    cr_assert_eq(get_player_quest_status(quest, player), -1, "fail_quest() failed to set status");
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
    quest_ctx_t *qctx = quest_ctx_new(player, ctx->game->all_quests);

    start_quest(quest, qctx);

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
    quest_ctx_t *qctx = quest_ctx_new(player, hash);

    start_quest(quest, qctx);
    
    bool completed = is_task_completed(task_to_complete, player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    cr_assert_eq(get_player_task_from_hash(task_to_complete->id, player->player_tasks)->completed, true, "start_quest didn't call complete_task() properly failed!");
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
    quest_ctx_t *qctx = quest_ctx_new(player, hash);

    start_quest(quest, qctx);
    reward_t *the_reward = complete_task(task->id, qctx);
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
    quest_ctx_t *qctx = quest_ctx_new(player, hash);

    start_quest(quest, qctx);
    check = get_player_quest_status(quest, player);

    cr_assert_eq(check,1,"get_player_quest_status() failed with started status");
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
    quest_ctx_t *qctx = quest_ctx_new(player, hash);

    start_quest(quest, qctx);
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
    quest_ctx_t *qctx = quest_ctx_new(player, hash);

    start_quest(quest, qctx);

    reward_t *res = complete_quest(quest, player);

    cr_assert_eq(res, NULL,"quest_completed failed to reward the item");
}



/*see if get_quest_from_hash works when there is quest in Hash */ 
Test(quest,get_quest1)
{ 
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    char *quest1_id = "quest one";
    char *quest2_id = "quest two";

    quest_t *quest1 = quest_new(quest1_id, NULL, rewards, prereq);
    quest_t *quest2 = quest_new(quest2_id, NULL, rewards, prereq);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table);

    quest_t *answer = get_quest_from_hash(quest1_id,test_hash_table); 
    cr_assert_eq(answer, quest1, "get_queset() did not return the right quest");

}

/*see if get_quest_from_hash work when there is no quest in the hash */ 
Test(quest,get_quest2)
{ 
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    char *quest1_id = "quest one";
    char *quest2_id = "quest two";

    quest_t *quest1 = quest_new(quest1_id, NULL, rewards, prereq);
    quest_t *quest2 = quest_new(quest2_id, NULL, rewards, prereq);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table);

    quest_t *answer = get_quest_from_hash("beeppop",test_hash_table); 
    cr_assert_eq(answer, NULL, "There is an quest with ID of beeppop ");
}


/*test for add task when 2 unique task_ID */ 
Test(test, add_task_test1)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    char *task1_id = "task one";
    char *task2_id = "task two";

    quest_hash_t *hash = NULL;
    quest_t *quest = quest_new("test", NULL, rewards, prereq);
    add_quest_to_hash(quest, &hash);

    task_t *task1 = task_new(NULL, task1_id, rewards, prereq);
    task_t *task2 = task_new(NULL, task2_id, rewards, prereq);

    player_t *player = player_new("test player");
    quest_ctx_t *qctx = quest_ctx_new(player, hash);

    int add_task1 = add_task_to_player_hash(task1, qctx);
    int add_task2 = add_task_to_player_hash(task2, qctx); 

    cr_assert_eq(add_task1, SUCCESS, "Could not sucessfully add task1"); 
    cr_assert_eq(add_task2, SUCCESS, "Could not sucessfully add task2"); 
}
/*test for add task when a task with same ID already exists in hash*/
Test(test, add_task_test2)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    char *task1_id = "task one";
    char *task2_id = "task one";

    quest_hash_t *hash = NULL;
    quest_t *quest = quest_new("test", NULL, rewards, prereq);
    add_quest_to_hash(quest, &hash);
    
    task_t *task1 = task_new(NULL, task1_id, rewards, prereq);
    task_t *task2 = task_new(NULL, task2_id, rewards, prereq);

    player_t *player = player_new("test player");
    quest_ctx_t *qctx = quest_ctx_new(player, hash);

    int add_task1 = add_task_to_player_hash(task1, qctx);
    int add_task2 = add_task_to_player_hash(task2, qctx); 

    cr_assert_eq(add_task1, SUCCESS, "Could not sucessfully add task1"); 
    cr_assert_eq(add_task2, FAILURE, "task2 added even though task_id already present in hash table"); 
}

/*test for add quest when 2 unique quest_ID */ 
Test(test, add_quest_test1)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    char *quest1_id = "quest one";
    char *quest2_id = "quest two";

    quest_t *quest1 = quest_new(quest1_id, NULL, rewards, prereq);
    quest_t *quest2 = quest_new(quest2_id, NULL, rewards, prereq);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table); 

    cr_assert_eq(add_quest1, SUCCESS, "Could not sucessfully add quest1"); 
    cr_assert_eq(add_quest2, SUCCESS, "Could not sucessfully add quest2"); 
}
/*test for add quest when a quest with same ID already exists in hash*/
Test(test, add_quest_test2)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;
    prereq_t *prereq = prereq_new(hp, level);

    char *quest1_id = "quest one";
    char *quest2_id = "quest two";

    quest_t *quest1 = quest_new(quest1_id, NULL, rewards, prereq);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest1, &test_hash_table); 

    cr_assert_eq(add_quest2, FAILURE, "quest1 wasn't added properly"); 
}

/* Tests the function that removes one quest from hash table */
Test(quest, remove_quest_one)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;

    char *quest1_id = "remove quest";
    char *quest2_id = "keep quest";

    quest_t *quest1 = quest_new("remove quest", NULL, rewards, NULL);
    quest_t *quest2 = quest_new("keep quest", NULL, rewards, NULL);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table);

    // only removing one quest
    int res = remove_quest_in_hash(test_hash_table, quest1_id);
    cr_assert_eq(res,SUCCESS, "failed to remove");
}

/* Tests the function that removes all quests from hash table */
Test(quest, remove_quest_all)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = reward_new(xp, item);

    int hp = 50;
    int level = 5;

    quest_t *quest1 = quest_new("remove quest one", NULL, rewards, NULL);
    quest_t *quest2 = quest_new("remove quest two", NULL, rewards, NULL);

    quest_hash_t *test_hash_table = NULL;

    int quest_1 = add_quest_to_hash(quest1, &test_hash_table);
    int quest_2 = add_quest_to_hash(quest2, &test_hash_table);

    // only removing all quests
    int res = remove_quest_all(test_hash_table);
    cr_assert_eq(res,SUCCESS, "remove_quest_all() failed to 2nd test");
}

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
