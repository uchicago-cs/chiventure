#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Tests init function for achievement struct */
Test(achievement, init)
{
	achievement_t *achievement;
    
    item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");

	int check = achievement_init(achievement, item_to_get);

    cr_assert_srt_eq(achievement->mission->item_id, "test_item", 
                     "achievement_init did not set mission name");
	cr_assert_eq(check, SUCCESS, "achievement_init() test has failed!");
}


/* Tests init function for quest struct */
Test(quest, init)
{
	quest_t *q = malloc(sizeof(quest_t));
    item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");

	int check = quest_init(q, 1, NULL, reward, 0);

    cr_assert_srt_eq(q->reward->short_desc, "item for testing", 
                     "quest_init did not set mission name");
	cr_assert_eq(check, SUCCESS, "quest_init() test has failed!");
}

/* Tests new achievement malloc (new uses init) */
Test(achievement, new)
{
    item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
	achievement_t* achievement = achievement_new(item_to_get);


    cr_assert_srt_eq(achievement->mission->long_desc, "test item for item_new()", 
                     "achievement_new did not set mission name");
	cr_assert_not_null(achivement, "achievement_new() test has failed!");
    cr_assert_eq(achievement->mission, item_to_get, "achievement_new()"
                "did not initialize the item");
    cr_assert_eq(achievement->completed, 0, "achievement_new()"
                "did not initialize the completed status");
}

/* Tests new quest malloc (new uses init) */
Test(quest, new)
{
    item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");
	quest_t* q = quest_new(1, NULL, reward);

	cr_assert_not_null(q, "quest_new() test has failed!");

    cr_assert_eq(quest->quest_id, 1, "achievement_new()"
                "did not initialize the quest_id");
    cr_assert_eq(quest->achievement_list, NULL, "achievement_new()"
                "did not initialize the achievement list");
    cr_assert_eq(quest->reward, reward, "achievement_new()"
                "did not initialize the reward item");)
    cr_assert_eq(quest->status, 0, "achievement_new()"
                "did not initialize the status");)
}


/* Tests achievement_free function */
Test(achievement, free)
{
    item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
	achievement_t* achievement_to_free = achievement_new(item_to_get);

	cr_assert_not_null(achievement_to_free, "achievement_free(): room is null");

	int freed = achievement_free(achievement_to_free);

	cr_assert_eq(freed, SUCCESS, "achievement_free() test has failed!");
}

/* Tests qust_free function */
Test(quest, free)
{
	item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");
	quest_t* q_to_free = quest_new(1, NULL, reward);


	cr_assert_not_null(q_to_free, "quest_free(): room is null");

	int freed = quest_free(quest_to_free);

	cr_assert_eq(freed, SUCCESS, "quest_free() test has failed!");
}