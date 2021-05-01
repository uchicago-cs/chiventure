#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"
#include "playerclass/class.h"
#include "game-state/item.h"

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
   	item_t *item_to_get = item_new("test_item", "item for testing",
    "test item for item_new()");
    class_t* class = generate_test_class();
    npc_mov_t* movement;
    char *npc_id1 = "test_npc";
    npc_t *mission_npc1 = npc_new(npc_id1 ,"npc","npc for testing",
                                100, class, movement);
    mission_t *mission = mission_new(item_to_get, mission_npc1);

    item_t *item_to_get2 = item_new("test_item2", "item for testing",
    "test item for item_new()");
    char *npc_id2 = "test_npc2";
    npc_t *mission_npc2 = npc_new(npc_id2,"npc","npc for testing",
                                100, class, movement);
    int check = mission_init(mission, item_to_get2, mission_npc2);

    cr_assert_eq(check,SUCCESS,"mission_init() failed");
    cr_assert_str_eq(mission->item_to_collect->item_id,"test_item2",
                    "mission_init() did not set item");
    cr_assert_str_eq(mission->npc_to_meet->npc_id, "test_npc2",
                    "mission_init() did not set npc");   
}

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

/*Tests adding achievement to a quest */
Test(quest, add_achievement_to_quest)
{
    item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");
    quest_t *quest = quest_new(1, NULL, reward);

    item_t *mission_item = item_new("mission_item", "item for testing",
    "test item for item_new()");
    class_t* class = generate_test_class();
    char *npc_id = "test_npc";
    npc_mov_t* movement;
    npc_t *mission_npc = npc_new(npc_id,"npc","npc for testing",
                                100, class, movement);
    mission_t *mission = mission_new(mission_item,mission_npc);

    achievement_t *achievement = achievement_new(mission);

    int res = add_achievement_to_quest(quest, achievement);

    cr_assert_eq(res, SUCCESS, "add_achievement_to_quest() failed!");

    achievement_t *achievement_test = quest->achievement_list->achievement;
    mission_t *mission_test = achievement->mission;
    cr_assert_eq(achievement_test->completed,0,"add_achievement_to_quest() did"
                                        "not set the completed boolean.");

    cr_assert_str_eq(mission_test->item_to_collect->item_id,"mission_item",
                    "add_achievement_to_quest() did not set item");
    cr_assert_str_eq(mission_test->npc_to_meet->npc_id,"test_npc",
                    "add_achievement_to_quest() did not set npc"); 
}

/* Tests the function  that starts a quest */
Test(quest, start_quest)
{
    item_t *reward = item_new("test_item", "item for testing",
                            "test item for item_new()");
    quest_t *quest = quest_new(1, NULL, reward);

    int check = start_quest(quest);

    cr_assert_eq(check, SUCCESS, "start_quest() failed");

    cr_assert_eq(quest->status, 1, "start_quest() failed to set status");
}

/* Tests the function  that fails a quest */
Test(quest, fail_quest)
{
    item_t *reward = item_new("test_item", "item for testing",
                            "test item for item_new()");
    quest_t *quest = quest_new(1, NULL, reward);

    int check = fail_quest(quest);

    cr_assert_eq(check, SUCCESS, "fail_quest() failed");

    cr_assert_eq(quest->status, -1, "fail_quest() failed to set status");
}


/* Tests the function that completes the achievement */
Test(quest, complete_achievement)
{
    item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");
    quest_t *quest = quest_new(1, NULL, reward);

    item_t *mission_item = item_new("mission_item", "item for testing",
    "test item for item_new()");
    class_t* class = generate_test_class();
    npc_mov_t* movement;
    char *npc_id = "mission_npc";
    npc_t *mission_npc = npc_new(npc_id,"npc","npc for testing",
                                100, class, movement);
    mission_t *mission = mission_new(mission_item,mission_npc);

    achievement_t *achievement = achievement_new(mission);

    int res = add_achievement_to_quest(quest, achievement);

    cr_assert_eq(res, SUCCESS, "add_achievement_to_quest() failed!");

    res = complete_achievement(quest, mission_item, mission_npc);

    cr_assert_eq(res, SUCCESS, "complete_achievement() failed!");

    mission_t *mission_check = quest->achievement_list->achievement->mission;

    cr_assert_str_eq(mission_check->item_to_collect->item_id, "mission_item",
                    "complete_achievement() did not check the correct item");
    
    cr_assert_str_eq(mission_check->npc_to_meet->npc_id, "mission_npc",
                    "complete_achievement() did not check the correct npc");

    cr_assert_eq(quest->achievement_list->achievement->completed, 1,
                "complete_achivement() did not complete the achievement");
}

/* Function that tests if a quest is completed */
Test(quest,is_quest_completed)
{
    item_t *reward = item_new("test_item", "item for testing",
    "test item for item_new()");
    quest_t *quest = quest_new(1, NULL, reward);

    item_t *mission_item = item_new("mission_item", "item for testing",
    "test item for item_new()");
    class_t* class = generate_test_class();
    char *npc_id = "mission_npc";
    npc_mov_t* movement;
    npc_t *mission_npc = npc_new(npc_id,"npc","npc for testing",
                                100, class, movement);
    mission_t *mission = mission_new(mission_item,mission_npc);

    achievement_t *achievement = achievement_new(mission);

    int res = add_achievement_to_quest(quest, achievement);

    res = complete_achievement(quest, mission_item, mission_npc);

    res = is_quest_completed(quest);

    cr_assert_eq(quest->status,2,"is_quest_completed() failed!");
    
    cr_assert_eq(res,1,"is_quest_completed() failed!");
    
}

/* Tests the function that checks the status of the quest */
Test(quest,get_quest_status)
{
    item_t *reward = item_new("test_item", "item for testing",
                            "test item for item_new()");
    quest_t *quest = quest_new(1, NULL, reward);

    int check = get_quest_status(quest);

    cr_assert_eq(check,0,"get_quest_status() failed with not statred status");

    check = start_quest(quest);

    check = get_quest_status(quest);

    cr_assert_eq(check,1,"get_quest_status() failed with started status");
}

/* Tests the function that reward the item after a quest*/
Test(quest,complete_quest)
{
    item_t *reward = item_new("test_item", "item for testing",
                            "test item for item_new()");
    quest_t *quest = quest_new(1, NULL, reward);
    quest->status = 2;

    item_t *res = complete_quest(quest);

    cr_assert_str_eq(res->item_id, "test_item",
                    "quest_completed failed to reward the item");
}