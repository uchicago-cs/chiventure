#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "playerclass/class.h"
#include "game-state/item.h"
#include "game-state/room.h"
#include "game-state/player.h"
#include "quests/quest_hash.h"


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

/*Tests adding task to a quest */
Test(quest, add_task_to_quest)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

	quest_t* quest = quest_new("beeobop", NULL, rewards, stat_req);
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

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    char *quest1_id = "quest one";
    char *quest2_id = "quest two";

    quest_t *quest1 = quest_new(quest1_id, NULL, rewards, stat_req);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest1, &test_hash_table); 

    cr_assert_eq(add_quest2, FAILURE, "quest1 wasn't added properly"); 
}


* Tests the function that removes one quest from hash table */
Test(quest, remove_quest_one)
{
    int xp = 50;
    item_t *item = item_new("test_item", "item for testing",
    "test item");
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    char *quest1_id = "remove quest";
    char *quest2_id = "keep quest";

    quest_t *quest1 = quest_new("remove quest", NULL, rewards, stat_req);
    quest_t *quest2 = quest_new("keep quest", NULL, rewards, stat_req);

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
    reward_t *rewards = create_sample_rewards(xp, item);

    int hp = 50;
    int level = 5;
    stat_req_t *stat_req = create_sample_stat_req(hp, level);

    quest_t *quest1 = quest_new("remove quest one", NULL, rewards, stat_req);
    quest_t *quest2 = quest_new("remove quest two", NULL, rewards, stat_req);

    quest_hash_t *test_hash_table = NULL;

    int quest_1 = add_quest_to_hash(quest1, &test_hash_table);
    int quest_2 = add_quest_to_hash(quest2, &test_hash_table);

    // only removing all quests
    int res = remove_quest_all(test_hash_table);
    cr_assert_eq(res,SUCCESS, "remove_quest_all() failed to 2nd test");
}

