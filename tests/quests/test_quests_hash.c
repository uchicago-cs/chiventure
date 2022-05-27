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
#include "quests/samples.h"
#include "quests/quests_cli.h"

/*see if get_quest_from_hash works with no quests in the hash and with quests in the hash */ 
Test(quest,get_quest)
{ 
    quest_t *quest1 = create_sample_quest("quest one", false, 0, 0, false, 0, 0);
    quest_t *quest2 = create_sample_quest("quest 2", false, 0, 0, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;

    quest_t *answer = get_quest_from_hash("quest one", test_hash_table); 
    cr_assert_eq(answer, NULL, "get_quest() returned quest one was in the table before it was added!");

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table);

    quest_t *answer1 = get_quest_from_hash("quest one", test_hash_table); 
    cr_assert_eq(answer1, quest1, "get_quest() did not return the right quest");

    quest_t *answer2 = get_quest_from_hash("beeppop",test_hash_table); 
    cr_assert_eq(answer2, NULL, "There is an quest with ID of beeppop ");

}

/*test for add quest with 2 unique quest_ID and with adding the same quest */ 
Test(test, add_quest_test)
{
    quest_t *quest1 = create_sample_quest("quest one", false, 0, NULL, false, 0, 0);
    quest_t *quest2 = create_sample_quest("quest two", false, 0, NULL, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;

    int add_quest1 = add_quest_to_hash(quest1, &test_hash_table);
    int add_quest2 = add_quest_to_hash(quest2, &test_hash_table); 
    int add_quest_fail = add_quest_to_hash(quest1, &test_hash_table);

    cr_assert_eq(add_quest1, SUCCESS, "Could not sucessfully add quest1"); 
    cr_assert_eq(add_quest2, SUCCESS, "Could not sucessfully add quest2"); 
    cr_assert_eq(add_quest_fail, FAILURE, "Added quest one to the hash twice!"); 
}

/*test for add task when 2 unique task_ID */ 
Test(test, add_task_test1)
{
    quest_hash_t *hash = NULL;
    quest_t *quest = create_sample_quest("quest one", false, 0, NULL, false, 0, 0);
    add_quest_to_hash(quest, &hash);

    task_t *task1 = create_sample_task("task one", false, NULL, KILL_NPC, false, 0, 0, false, 0, 0);
    task_t *task2 = create_sample_task("task two", false, NULL, KILL_NPC, false, 0, 0, false, 0, 0);

    quest_ctx_t *qctx = create_sample_ctx();

    int add_task1 = add_task_to_player_hash(task1, qctx);
    int add_task2 = add_task_to_player_hash(task2, qctx); 
    int add_task1_again = add_task_to_player_hash(task1, qctx);

    cr_assert_eq(add_task1, SUCCESS, "Could not sucessfully add task1"); 
    cr_assert_eq(add_task2, SUCCESS, "Could not sucessfully add task2"); 
    cr_assert_eq(add_task1_again, FAILURE, "Added task one to the player hash twice!");
}

/* Tests the function that removes one quest from hash table */
Test(quest, remove_quest_one)
{
    quest_t *quest1 = create_sample_quest("remove quest", false, 0, NULL, false, 0, 0);
    quest_t *quest2 = create_sample_quest("keep quest", false, 0, NULL, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;
    add_quest_to_hash(quest1, &test_hash_table);
    add_quest_to_hash(quest2, &test_hash_table);

    // only removing one quest
    int res = remove_quest_in_hash(test_hash_table, quest1->quest_id);
    cr_assert_eq(res, SUCCESS, "failed to remove");
    cr_assert_null(get_quest_from_hash("remove quest", test_hash_table), "Quest 1 not removed properly!");
    cr_assert_not_null(get_quest_from_hash("keep quest", test_hash_table), "Quest 2 removed even though it's not supposed to be!");
}

/* Tests the function that removes all quests from hash table */
Test(quest, remove_quest_all)
{
    quest_t *quest1 = create_sample_quest("remove quest 1", false, 0, NULL, false, 0, 0);
    quest_t *quest2 = create_sample_quest("remove quest 2", false, 0, NULL, false, 0, 0);

    quest_hash_t *test_hash_table = NULL;
    add_quest_to_hash(quest1, &test_hash_table);
    add_quest_to_hash(quest2, &test_hash_table);

    int res = remove_quest_all(&test_hash_table);
    cr_assert_eq(res, SUCCESS, "remove_quest_all() failed to 2nd test");
    
    quest_t *result1 = get_quest_from_hash("remove quest 1", test_hash_table);
    quest_t *result2 = get_quest_from_hash("remove quest 2", test_hash_table);

    cr_assert_null(result1, "Quest 1 not removed properly!");
    cr_assert_null(result2, "Quest 2 not removed properly!");
}
