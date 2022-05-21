#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "playerclass/class.h"
#include "game-state/item.h"
#include "game-state/room.h"
#include "game-state/player.h"
#include "quests/quests_hash.h"

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

    quest_hash_t *qhash = NULL;

    task_t *task1 = task_new(NULL, task1_id, rewards, prereq);
    task_t *task2 = task_new(NULL, task2_id, rewards, prereq);

    player_task_hash_t *test_hash_table = NULL;

    int add_task1 = add_task_to_player_hash(task1, &test_hash_table, qhash);
    int add_task2 = add_task_to_player_hash(task2, &test_hash_table, qhash); 

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

    quest_hash_t *qhash = NULL;

    task_t *task1 = task_new(NULL, task1_id, rewards, prereq);
    task_t *task2 = task_new(NULL, task2_id, rewards, prereq);

    player_task_hash_t *test_hash_table = NULL;

    int add_task1 = add_task_to_player_hash(task1, &test_hash_table, qhash);
    int add_task2 = add_task_to_player_hash(task2, &test_hash_table, qhash); 

    cr_assert_eq(add_task1, SUCCESS, "Could not sucessfully add task1"); 
    cr_assert_eq(add_task2, FAILURE, "task2 added even though task_id already present in hash table"); 
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

