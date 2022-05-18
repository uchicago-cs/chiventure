#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "playerclass/class.h"
#include "game-state/item.h"
#include "game-state/room.h"
#include "game-state/player.h"
#include "quests/quest.h"



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

/* Tests init function for quest struct */
Test(quest, init)
{   
    quest_t *q = malloc(sizeof(quest_t));

    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	int check = quest_init(q, "test", NULL, rewards, stat_req, 0);

	cr_assert_eq(check, SUCCESS, "quest_init() test has failed!");
}
/* Tests new quest malloc (new uses init) */
Test(quest, new)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* q = quest_new("test", NULL, rewards, stat_req);

	cr_assert_not_null(q, "quest_new() test has failed!");


    cr_assert(strcmp(q->quest_id, "test") == 0, "quest_new()"
                "did not initialize the task tree");
    cr_assert_str_eq(q->reward->item->item_id, "test_item", "quest_new()"
                "did not initialize the reward item");
    cr_assert_eq(q->reward->xp, 50, "quest_new()"
                "did not initialize the xp reward");
    cr_assert_eq(q->stat_req->hp, 50,
                     "quest_init did not set stat req hp");
    cr_assert_eq(q->stat_req->level, 5,
                     "quest_init did not set stat req level");
    cr_assert_eq(q->status, 0, "quest_new()"
                "did not initialize the status");
}


/* Tests quest_free function */
Test(quest, free)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* q_to_free = quest_new("test", NULL, rewards, stat_req);

	cr_assert_not_null(q_to_free, "quest_free(): room is null");
    cr_assert(strcmp(q_to_free->quest_id, "test") == 0, "quest_id incorrect");

	int freed = quest_free(q_to_free);

	cr_assert_eq(freed, SUCCESS, "quest_free() test has failed!");
}

/* Tests if a player can start the quest */
Test(quest, can_start)
{
    int health = 20;

    player_t* player1 = player_new("player1");

    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* quest = quest_new("test4", NULL, rewards, stat_req);

    int rc = can_start_quest(quest, player1);

    cr_assert_eq(rc, 0, "can_start_quest() returned false, expected true");
}

/* Tests the function  that fails a quest */
Test(quest, fail_quest)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* quest = quest_new("test2", NULL, rewards, stat_req);

    int check = fail_quest(quest);

    cr_assert_eq(check, SUCCESS, "fail_quest() failed");

    cr_assert_eq(quest->status, -1, "fail_quest() failed to set status");
}


/* Tests the function that completes the task */
Test(quest, complete_task)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);

    class_t* class = generate_test_class();
    char *npc_meet_id = "meet_npc";
    char *npc_kill_id = "kill_npc";

    item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
    npc_t *mission_meet_npc = npc_new(npc_meet_id ,"npc1", "npc to meet",
                                class, NULL, false);

    npc_t *mission_meet_kill = npc_new(npc_kill_id ,"npc2", "npc to kill", 
                                       class, NULL, false);
    room_t* room_to_visit = room_new("Grand ballroom", "A room", "A test room");

    active_mission_t *a_mission = active_mission_new(item_to_get, mission_meet_npc,
                                                     mission_meet_kill, room_to_visit); 


    char *id = "test mission";

    mission_t *mission = malloc(sizeof(mission_t));
    mission->a_mission = a_mission;
    mission->p_mission = NULL;

	task_t* task_to_complete = task_new(mission, id, rewards);

    int res = add_task_to_quest(quest, task_to_complete, "NULL");

    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");

    reward_t *new_reward = complete_task(quest, "test mission");
    if (new_reward == NULL)
        res = FAILURE;

    cr_assert_eq(res, SUCCESS, "complete_task() failed!");
}

/* Function that tests if a quest is completed */
Test(quest,is_quest_completed)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* quest = quest_new("test 1", NULL, rewards, stat_req);

    class_t* class = generate_test_class();
    char *npc_meet_id = "meet_npc";
    char *npc_kill_id = "kill_npc";

    item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
    npc_t *mission_meet_npc = npc_new(npc_meet_id ,"npc1", "npc to meet",
                                class, NULL, false);

    npc_t *mission_meet_kill = npc_new(npc_kill_id ,"npc2", "npc to kill", 
                                       class, NULL, false);
    room_t* room_to_visit = room_new("Grand ballroom", "A room", "A test room");

    active_mission_t *a_mission = active_mission_new(item_to_get, mission_meet_npc,
                                                     mission_meet_kill, room_to_visit); 

    char *id = "test mission";

    mission_t *mission = malloc(sizeof(mission_t));
    mission->a_mission = a_mission;
    mission->p_mission = NULL;

    task_t *task = task_new(mission, "mission", rewards);

    int res = add_task_to_quest(quest, task, NULL);

    reward_t *the_reward = complete_task(quest, "mission");
    if (the_reward == NULL)
        res = FAILURE;

    res = is_quest_completed(quest);

    cr_assert_eq(quest->status,2,"is_quest_completed() failed!");
    
    cr_assert_eq(res,1,"is_quest_completed() failed!");
    
}

/* Tests the function that checks the status of the quest */
Test(quest,get_quest_status)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* quest = quest_new("beepbop", NULL, rewards, stat_req);

    int check = get_quest_status(quest);

    cr_assert_eq(check,0,"get_quest_status() failed with not statred status");

    check = start_quest(quest);

    check = get_quest_status(quest);

    cr_assert_eq(check,1,"get_quest_status() failed with started status");
}

/* Tests the function that reward the item after a quest*/
Test(quest,complete_quest)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* quest = quest_new("test", NULL, rewards, stat_req);
    quest->status = 2;

    reward_t *res = complete_quest(quest);

    cr_assert_str_eq(res->item->item_id, "test_item",
                    "quest_completed failed to reward the item");
}


/* Tests the function that is incomplete*/
Test(quest,complete_quest2)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* quest = quest_new("test", NULL, rewards, stat_req);
    quest->status = 0;

    reward_t *res = complete_quest(quest);

    cr_assert_eq(res, NULL,"quest_completed failed to reward the item");
}

