#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Tests init function for achievement struct */
Test(achievement, init)
{
	item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
    mission_t *mission = mission_new(item_to_get, NULL);

    achievement_t *achievement = achievement_new(mission);

	int check = achievement_init(achievement, mission);

    cr_assert_str_eq(achievement->mission->item_to_collect->item_id, "test_item",
                     "achievement_init did not set mission name");
    cr_assert_eq(achievement->completed, 0,
                     "achievement_init did not initialize completed bool");
	cr_assert_eq(check, SUCCESS, "achievement_init() test has failed!");
}

/* Tests init function for quest struct */
Test(quest, init)
{
	quest_t *q = malloc(sizeof(quest_t));
    item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");

	int check = quest_init(q, 1, NULL, reward, 0);

    cr_assert_str_eq(q->reward->item_id, "test_item",
                     "quest_init did not set item_id");
    cr_assert_null(q->achievement_list,
                     "quest_init did not set achievement_list");
    cr_assert_eq(q->quest_id, 1,  "quest_init did not set quest_id");
    cr_assert_eq(q->status, 0,  "quest_init did not set status");
	cr_assert_eq(check, SUCCESS, "quest_init() test has failed!");
}

/* Tests new achievement malloc (new uses init) */
Test(achievement, new)
{
    item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
    mission_t *mission = mission_new(item_to_get, NULL);
	achievement_t* achievement = achievement_new(mission);

	cr_assert_not_null(achievement, "achievement_new() test has failed!");
    cr_assert_str_eq(achievement->mission->item_to_collect->item_id, "test_item", 
                     "achievement_init did not set mission name");
    cr_assert_eq(achievement->completed, 0, 
                     "achievement_init did not initialize completed bool");
}

/* Tests new quest malloc (new uses init) */
Test(quest, new)
{
    item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");
	quest_t* q = quest_new(1, NULL, reward);

	cr_assert_not_null(q, "quest_new() test has failed!");

    cr_assert_eq(q->quest_id, 1, "achievement_new()"
                "did not initialize the quest_id");
    cr_assert_eq(q->achievement_list, NULL, "achievement_new()"
                "did not initialize the achievement list");
    cr_assert_str_eq(q->reward->item_id, "test_item", "achievement_new()"
                "did not initialize the reward item");
    cr_assert_eq(q->status, 0, "achievement_new()"
                "did not initialize the status");
}

/* Tests achievement_free function */
Test(achievement, free)
{
    item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
    mission_t *mission = mission_new(item_to_get, NULL);

	achievement_t* achievement_to_free = achievement_new(mission);

	cr_assert_not_null(achievement_to_free, "achievement_free(): room is null");

	int freed = achievement_free(achievement_to_free);

	cr_assert_eq(freed, SUCCESS, "achievement_free() test has failed!");
}

/* Tests quest_free function */
Test(quest, free)
{
	item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");
	quest_t* q_to_free = quest_new(1, NULL, reward);

	cr_assert_not_null(q_to_free, "quest_free(): room is null");

	int freed = quest_free(q_to_free);

	cr_assert_eq(freed, SUCCESS, "quest_free() test has failed!");
}
