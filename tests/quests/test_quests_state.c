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

/* Tests init function for passive mission struct */
Test(passive_mission, init)
{
    int xp = 30;
    int levels = 5;
    int health = 10;

    passive_mission_t *p_mission = passive_mission_new(xp, levels, health);

    int check = passive_mission_init(p_mission, xp, levels, health);

    cr_assert_eq(check, SUCCESS,"passive_mission_init() failed");
    cr_assert_eq(p_mission->xp, 30,
                 "mission_init() did not set xp");
    cr_assert_eq(p_mission->levels, 5,
                 "mission_init() did not set levels");
    cr_assert_eq(p_mission->health, 10,
                 "mission_init() did not set health");
}

/* Tests init function for active mission struct */
Test(active_mission, init)
{
    class_t* class = generate_test_class();
    char *npc_meet_id = "meet_npc";
    char *npc_kill_id = "kill_npc";

    item_t *item_to_get = item_new("test_item", "item for testing",
                                   "test item for item_new()");
    npc_t *mission_meet_npc = npc_new(npc_meet_id,"npc1", "npc to meet",
                                      class, NULL, false);

    npc_t *mission_meet_kill = npc_new(npc_kill_id, "npc to kill",
                                       "An npc to kill", class, NULL, false);
    room_t* room_to_visit = room_new("Grand ballroom", "A room", "A test room");

    active_mission_t *a_mission = malloc(sizeof(active_mission_t));

    int check = active_mission_init(a_mission, item_to_get, mission_meet_npc,
                                    mission_meet_kill, room_to_visit);

    cr_assert_eq(check,SUCCESS,"active_mission_init() failed");
}

/* Tests init function for task struct */
Test(task, init)
{
    item_t *item_to_get = item_new("test_item", "item for testing",
                                   "test item for item_new()");
    char *id = "test mission";

    active_mission_t *a_mission = active_mission_new(item_to_get, NULL, NULL, NULL);

    mission_t *mission = malloc(sizeof(mission_t));
    mission->a_mission = a_mission;
    mission->p_mission = NULL;

    item_t *item = item_new("reward_item", "item for rewarding",
                            "test item for item_new()");
    int xp = 40;
    reward_t *rewards = reward_new(xp, item);

    task_t *task = malloc(sizeof(task_t));

    int check = task_init(task, mission, id, rewards);

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

Test(stat_req, new)
{
    int hp = 40;
    int level = 5;

    stat_req_t *stat_req = stat_req_new(hp, level);


    cr_assert_eq(stat_req->hp, 40, "reward_new did not set xp");
    cr_assert_eq(stat_req->level, 5, "reward_new did not set level");

}

reward_t *create_sample_rewards(int xp, item_t *item)
{
    reward_t *rewards = malloc(sizeof(reward_t));

    rewards->xp = xp;
    rewards->item = item;

    return rewards;
}

stat_req_t *create_sample_stat_req(int hp, int level)
{
    stat_req_t *stat_req = malloc(sizeof(stat_req));

    stat_req->hp = hp;
    stat_req->level = level;

    return stat_req;
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

    int check = quest_init(q, "test", NULL, rewards, stat_req);

    cr_assert_eq(check, SUCCESS, "quest_init() test has failed!");
}

/* Tests new task malloc (new uses init) */
Test(task, new)
{
    item_t *item_to_get = item_new("test_item", "item for testing",
                                   "test item for item_new()");
    char *id = "test mission";

    active_mission_t *a_mission = active_mission_new(item_to_get, NULL, NULL, NULL);

    mission_t *mission = malloc(sizeof(mission_t));
    mission->a_mission = a_mission;
    mission->p_mission = NULL;

    item_t *item = item_new("reward_item", "item for rewarding",
                            "test item for item_new()");
    int xp = 40;
    reward_t *rewards = reward_new(xp, item);

    task_t* task = task_new(mission, id, rewards);

    cr_assert_not_null(task, "task_new() test has failed!");
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
}

/* Tests if a player meets prereqs */
Test(quest, meets_prereqs)
{
    item_t *item_to_get = item_new("test_item", "item for testing",
                                   "test item for item_new()");
    char *id = "test mission";

    active_mission_t *a_mission = active_mission_new(item_to_get, NULL, NULL, NULL);
    mission_t *mission = malloc(sizeof(mission_t));
    mission->a_mission = a_mission;
    mission->p_mission = NULL;

    item_t *item = item_new("reward_item", "item for rewarding",
                            "test item for item_new()");
    int xp = 30;
    reward_t *rewards = reward_new(xp, item);

    task_t* task_to_free = task_new(mission, id, rewards);


    cr_assert_not_null(task_to_free, "task_free(): room is null");

    int freed = task_free(task_to_free);

    cr_assert_eq(freed, SUCCESS, "task_free() test has failed!");
}

/* Tests if a player does not make prereqs because of their level*/
Test(quest, cannot_start_level)
{
    class_t* class = generate_test_class();
    char *npc_meet_id = "meet_npc";
    char *npc_kill_id = "kill_npc";

    item_t *item_to_get = item_new("test_item", "item for testing",
                                   "test item for item_new()");
    npc_t *mission_meet_npc = npc_new(npc_meet_id,"npc1", "npc to meet",
                                      class, NULL, false);

    npc_t *mission_meet_kill = npc_new(npc_kill_id,"npc2", "npc to kill",
                                       class, NULL, false);
    room_t* room_to_visit = room_new("Grand ballroom", "A room", "A test room");

    active_mission_t *a_mission = active_mission_new(item_to_get, mission_meet_npc,
                                  mission_meet_kill, room_to_visit);

    cr_assert_not_null(a_mission, "active_mission_free(): room is null");

    int freed = active_mission_free(a_mission);

    cr_assert_eq(freed, SUCCESS, "active_mission_free() test has failed!");
}

/* Tests passive_mission_free function by making xp node */
Test(passive_mission_xp, free)
{
    int xp = 5;
    int level = 1;
    int health = 10;

    passive_mission_t *p_mission = passive_mission_new(xp, level, health);

    cr_assert_not_null(p_mission, "passive_mission_free(): room is null");

    int freed = passive_mission_free(p_mission);

    cr_assert_eq(freed, SUCCESS, "passive_mission_free() test has failed!");
}

/* Tests passive_mission_free function by making xp node */
Test(passive_mission_levels, free)
{
    int xp = 5;
    int level = 1;
    int health = 10;

    passive_mission_t *p_mission = passive_mission_new(xp, level, health);

    cr_assert_not_null(p_mission, "passive_mission_free(): room is null");

    int freed = passive_mission_free(p_mission);

    cr_assert_eq(freed, SUCCESS, "passive_mission_free() test has failed!");
}

/* Tests passive_mission_free function by making xp node */
Test(passive_mission_health, free)
{
    int xp = 5;
    int level = 1;
    int health = 10;

    passive_mission_t *p_mission = passive_mission_new(xp, level, health);

    cr_assert_not_null(p_mission, "passive_mission_free(): room is null");

    int freed = passive_mission_free(p_mission);

    cr_assert_eq(freed, SUCCESS, "passive_mission_free() test has failed!");
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

/*Tests adding task to a quest */
Test(quest, add_task_to_quest)
{
    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);
    item_t *item_to_get = item_new("test_item", "item for testing",
                                   "test item for item_new()");
    char *id = "test mission";

    active_mission_t *a_mission = active_mission_new(item_to_get, NULL, NULL, NULL);
    mission_t *mission = malloc(sizeof(mission_t));
    mission->a_mission = a_mission;
    mission->p_mission = NULL;

    task_t* task_to_add = task_new(mission, id, rewards);

    int res = add_task_to_quest(quest, task_to_add, "NULL");

    cr_assert_eq(res, SUCCESS, "add_task_to_quest() failed!");

/* Tests if a player can start the quest */
Test(quest, can_start)
{
    double health = 70;
    int pLevel = 7;

    player_t* player1 = player_new("player1");
    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player1, health_stat);

    player1->level = pLevel;

    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    int xp = 50;
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);

    bool rc = can_start_quest(quest, player1);

    cr_assert_eq(rc, true, "can_start_quest() returned false, expected true");
}

/* Tests if a player cannot start the quest because of their level*/
Test(quest, cannot_start_level)
{
    int health = 60;
    int pLevel = 1;

    player_t* player1 = player_new("player1");
    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player1, health_stat);

    player1->level = pLevel;

    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    int xp = 50;
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);

    bool rc = can_start_quest(quest, player1);

    cr_assert_eq(rc, false, "can_start_quest() returned false, expected true");
}

/* Tests if a player cannot start the quest because of their health */
Test(quest, cannot_start_health)
{
    int health = 20;
    int pLevel = 7;

    player_t* player1 = player_new("player1");
    stats_global_t *global = stats_global_new("health", health);
    stats_t *health_stat = stats_new(global, health);
    player_add_stat(player1, health_stat);

    player1->level = pLevel;

    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    int xp = 50;
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);

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
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t *quest = quest_new("test", NULL, rewards, stat_req);
    player_t *player = player_new("test player");
    int check = start_quest(quest, player);

    int check = start_quest(quest, qctx);
    cr_assert_eq(check, SUCCESS, "start_quest() failed");
    
    int status = get_player_quest_status(quest, qctx->player);
    cr_assert_eq(status, Q_STARTED, "start_quest() failed to set status (incorrectly returned %d)", status);
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

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);
    player_t *player = player_new("test player");

    start_quest(quest, player);

    int check = fail_quest(quest, player);

    int check = fail_quest(quest, qctx->player);
    cr_assert_eq(check, SUCCESS, "fail_quest() failed");

    cr_assert_eq(get_player_quest_status(quest, player), -1, "fail_quest() failed to set status");
    player_free(player);
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
    npc_t *mission_meet_npc = npc_new(npc_meet_id,"npc1", "npc to meet",
                                      class, NULL, false);

    npc_t *mission_meet_kill = npc_new(npc_kill_id,"npc2", "npc to kill",
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

    player_t *player = player_new("test player");
    start_quest(quest, player);

    bool completed = is_task_completed(task_to_complete, player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    reward_t *new_reward = complete_task(task_to_complete, player);
    if (new_reward == NULL)
        res = FAILURE;

    cr_assert_eq(res, SUCCESS, "complete_task() failed!");
    player_free(player);
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

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);

    class_t* class = generate_test_class();
    char *npc_meet_id = "meet_npc";
    char *npc_kill_id = "kill_npc";

    item_t *item_to_get = item_new("test_item", "item for testing",
                                   "test item for item_new()");
    npc_t *mission_meet_npc = npc_new(npc_meet_id,"npc1", "npc to meet",
                                      class, NULL, false);

    npc_t *mission_meet_kill = npc_new(npc_kill_id,"npc2", "npc to kill",
                                       class, NULL, false);
    room_t* room_to_visit = room_new("Grand ballroom", "A room", "A test room");

    active_mission_t *a_mission = active_mission_new(item_to_get, mission_meet_npc,
                                  mission_meet_kill, room_to_visit);

    start_quest(quest, qctx);
    update_task(task->id, qctx);

    mission_t *mission = malloc(sizeof(mission_t));
    mission->a_mission = a_mission;
    mission->p_mission = NULL;

    task_t *task = task_new(mission, "mission", rewards);

    int res = add_task_to_quest(quest, task, NULL);

    player_t *player = player_new("test player");
    start_quest(quest, player);
    reward_t *the_reward = complete_task(task, player);
    if (the_reward == NULL)
    {
        res = FAILURE;
    }
    bool completed = is_task_completed(task, player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    completed = is_quest_completed(quest, qctx->player);
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
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t *quest = quest_new("test", NULL, rewards, stat_req);
    player_t *player = player_new("test player");
    int check = get_player_quest_status(quest, player);

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
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t *quest = quest_new("test", NULL, rewards, stat_req);
    player_t *player = player_new("test player");
    int check = get_player_quest_status(quest, player);

    add_task_to_quest(quest, task_to_complete, "NULL");

    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);
    add_quest_to_game(ctx->game, quest); 
    
    quest_ctx_t *qctx = create_sample_ctx();
    qctx->quest_hash = ctx->game->all_quests;
    assert(qctx->player->player_quests == NULL);
    start_quest(quest, qctx);

    bool completed = is_task_completed(task_to_complete, qctx->player);
    cr_assert_eq(completed, false, "is_task_completed() returned true when it shouldn't have!");

    cr_assert_eq(get_player_quest_status(quest, player), 2, "complete_quest failed to complete the quest");
    cr_assert_str_eq(res->item->item_id, "test_item",
                     "complete_quest failed to reward the item");
}

/* Tests the function that completes the task when the task has a prereq*/
Test(quest, complete_task_prereq)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t* quest = quest_new("test", NULL, rewards, stat_req);
    player_t *player = player_new("test player");

    start_quest(quest, player);

    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);
    start_quest(quest, qctx);
    
    bool completed = is_task_completed(task_to_complete, qctx->player);
    cr_assert_eq(completed, true, "is_task_completed() failed!");

    cr_assert_eq(get_player_task_from_hash(task_to_complete->id, qctx->player->player_tasks)->completed, true, "start_quest didn't call complete_task() properly failed!");
}



/*see if get_quest_from_hash works when there is quest in Hash */
Test(quest,get_quest1)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    char *quest1_id = "quest one";
    char *quest2_id = "quest two";

    quest_t *quest1 = quest_new(quest1_id, NULL, rewards, stat_req);
    quest_t *quest2 = quest_new(quest2_id, NULL, rewards, stat_req);

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
    reward_t *rewards = create_sample_rewards(xp, item);

    player_t *player = create_sample_player("player", 60, 6);
    qctx->player = player;

    int check = can_player_start_quest(qctx, "test");

    cr_assert_eq(check, true, "can_player_start_quest() failed");
}

/* Tests the function for checking if the player can complete a task*/
Test(quest, can_player_complete_task)
{
    item_t *item = item_new("test_item", "item for testing", "test item");
	quest_t *quest = create_sample_quest("test", true, 50, item, true, 40, 4);
    task_t *task = create_sample_task("test", true, "Steve", KILL_NPC, false, 0, NULL, true, 40, 4);
    add_task_to_quest(quest, task, NULL);
    quest_ctx_t *qctx = create_sample_ctx();
    add_quest_to_hash(quest, &qctx->quest_hash);
    start_quest(quest, qctx);

    int check = can_player_complete_task(qctx, "test");

    quest_t *answer = get_quest_from_hash("beeppop",test_hash_table);
    cr_assert_eq(answer, NULL, "There is an quest with ID of beeppop ");
}

/*test for add quest when 2 unique quest_ID */
Test(test, add_quest_test1)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    item_t *item1 = item_new("reward_item", "item for rewarding",
    "test item for item_new()");
    int xp1 = 40;
    reward_t *rewards1 = reward_new(xp1, item1);

    prereq_t *prereq1 = prereq_new(3, 2);

	task_t* task1 = task_new(id1, mission1, rewards1, prereq1);

    char *id2 = "test mission22";

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table);

    cr_assert_eq(add_quest1, SUCCESS, "Could not sucessfully add quest1");
    cr_assert_eq(add_quest2, SUCCESS, "Could not sucessfully add quest2");
}
/*test for add quest when a quest with same ID aredy exist in hash*/
Test(test, add_quest_test2)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
                            "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    prereq_t *prereq2 = prereq_new(3, 2);

	task_t* task2 = task_new(id2, mission2, rewards2, prereq2);

    item_t *item = item_new("test item", "item for testing", "item");
    reward_t *rewards = reward_new(20, item);
    prereq_t *prereq = prereq_new(50, 50);
    task_tree_t *task_tree = NULL;

    quest_t* q = quest_new("test", rewards, prereq);
    q->task_tree = task_tree;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest1, &test_hash_table);

    cr_assert_eq(add_quest2, FAILURE, "quest1 wasn't added properly");
}