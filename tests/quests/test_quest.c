#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quest.h"
#include "quests/samples.h"

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

