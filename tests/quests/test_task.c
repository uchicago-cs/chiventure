#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "game-state/item.h"
#include "quests/task.h"
#include "quests/samples.h"

/* Tests init function for mission struct */
Test(mission, init)
{   
    mission_t mission;

    int check = mission_init(&mission, "Poseidon", KILL_NPC);

    cr_assert_eq(check,SUCCESS,"mission_init() failed");
    cr_assert_eq(mission.target_name, "Poseidon", "mission_init() failed to set target name!");
    cr_assert_eq(mission.type, KILL_NPC, "mission_init() failed to set type!");
}

/* Tests new function for mission struct */
Test(mission, new)
{   
    mission_t *mission = mission_new("Poseidon", KILL_NPC);

    cr_assert_not_null(mission, "mission_new() failed");
    cr_assert_eq(mission->target_name, "Poseidon", "mission_init() failed to set target name!");
    cr_assert_eq(mission->type, KILL_NPC, "mission_init() failed to set type!");
}

/* Tests mission_free function */
Test(mission, free)
{
    mission_t *mission = mission_new("Atlantis", VISIT_ROOM);

    cr_assert_not_null(mission, "mission_free(): room is null");
    
    int freed = mission_free(mission);

    cr_assert_eq(freed, SUCCESS, "mission_free() test has failed!");
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

