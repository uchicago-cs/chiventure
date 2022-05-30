#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "test_wdl.h"
#include "wdl/load_quests.h"
#include "wdl/load_game.h"
#include "quests/quests_state.h"

#define QUESTS_PATH "../../../tests/wdl/examples/wdl/quests_sample.wdl"
/*
 * helper function for parsing a YAML file into an object
 * shamelessly stolen from test_game.c
 */
static obj_t *__get_doc_obj()
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_default.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_TRUNCATE, &error);
    cr_assert_eq(error, ZIP_ET_NONE, 
        "Could not create zip file; code: %d", error);

    // Add DEFAULT.json to the zip
    char *data_name = "DEFAULT.json";
    char *data_path = QUESTS_PATH;

    zip_error_t err = {0};
    zip_source_t *zip_src = zip_source_file_create(data_path, 0, 0, &err);
    cr_assert_not_null(zip_src, "Could not create zip source; code: %d", zip_error_system_type(&err));

    zip_int64_t idx = zip_file_add(zip, data_name, zip_src, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add file to zip file; check archive code");

    // Write and save to disk
    int rc = zip_close(zip);
    zip_error_t *close = zip_get_error(zip);
    cr_assert_neq(rc, -1, 
        "Could not close zip file; check archive code: %s", zip_error_strerror(close));

    int open_status;
    zip = zip_open(zip_name, 0, &open_status);

    // Read the zip into an obj
    obj_t *obj = obj_new("doc");
    rc = load_obj_store_from_zip(obj, zip);

    return obj;
}

/* Verifies that the example file, which covers every parsing possibility, is parsed correctly */
Test(quests_wdl, all_encompassing_example) {
    game_t *game = game_new("Quest Test!");
    obj_t *doc = __get_doc_obj();

    // Add items to game
    item_t *search_warrant = item_new("Search Warrant", "A warrant for searching", "A warrant that permits the searching of certain locations");
    add_item_to_game(game, search_warrant);
    item_t *sailing_handbook = item_new("Sailing Handbook", "A handbook for sailing", "A handbook that teaches the mystical art of sailing");
    add_item_to_game(game, sailing_handbook);
    item_t *interrogation_handbook = item_new("Interrogation Handbook", "A handbook for interrogation", "A handbook that teaches the mystical art of interrogation");
    add_item_to_game(game, interrogation_handbook);
    item_t *sword = item_new("Legendary Sword of Steve", "Steve's legendary sword of legends", "Legend says that this sword of legends can slice through the most legendary opponents");
    add_item_to_game(game, sword);

    get_item_from_game(game, "Legendary Sword of Steve");
    // Add quests to game
    load_quests(doc, game);
    cr_assert_not_null(game->all_quests, "No quest added to game!");
    /* First quest */
    // Check first quest's parameters
    quest_t *find_steve = get_quest_from_hash("Find Steve", game->all_quests);
    cr_assert_not_null(find_steve, "Find Steve quest not added to game's quest hash!");
    cr_assert_not_null(find_steve->reward, "Find Steve quest does not have a reward!");
    cr_assert_eq(find_steve->reward->xp, 500, "Find Steve quest's reward has incorrect xp!");
    cr_assert_null(find_steve->reward->item, "Find Steve quest's reward has a not-NULL item!");

    // Check first task's parameters
    task_tree_t *land_scout_tree = find_steve->task_tree;
    cr_assert_not_null(land_scout_tree, "Find Steve quest has NULL task tree!");
    task_t *land_scout = land_scout_tree->task;
    cr_assert_not_null(land_scout, "Land Scout task is NULL!");
    cr_assert_str_eq(land_scout->id, "Talk to Land Scout", "Land Scout task has incorrect id!");
    cr_assert_not_null(land_scout->mission, "Land Scout task has no mission!");
    cr_assert_str_eq(land_scout->mission->target_name, "Land Scout", "Land Scout task's mission has the wrong target!");
    cr_assert_eq(land_scout->mission->type, MEET_NPC, "Land Scout task's mission has the wrong type!");
    cr_assert_not_null(land_scout->prereq, "Land Scout task has no prereq!");
    cr_assert_eq(land_scout->prereq->hp, 10, "Land Scout task's prereq has incorrect hp!");
    cr_assert_eq(land_scout->prereq->level, 2, "Land Scout task's prereq has incorrect level!");
    cr_assert_not_null(land_scout->reward, "Land Scout task has no reward!");
    cr_assert_eq(land_scout->reward->xp, 100, "Land Scout task's reward has incorrect xp!");
    cr_assert_not_null(land_scout->reward->item, "Land Scout task's reward has no item!");
    cr_assert_str_eq(land_scout->reward->item->item_id, "search warrant", "Land Scout task's reward has incorrect item!");

    // Check first task's immediate child's parameters
    task_tree_t *enter_lair_tree = land_scout_tree->lmostchild;
    cr_assert_not_null(enter_lair_tree, "Land Scout task tree has no left child!");
    task_t *enter_lair = enter_lair_tree->task;
    cr_assert_not_null(enter_lair, "Enter Lair task is NULL!");
    cr_assert_str_eq(enter_lair->id, "Enter Steve's Lair", "Enter Lair task has incorrect id!");
    cr_assert_not_null(enter_lair->mission, "Enter Lair task has no mission!");
    cr_assert_str_eq(enter_lair->mission->target_name, "Steve's Lair", "Enter Lair task's mission has the wrong target!");
    cr_assert_eq(enter_lair->mission->type, VISIT_ROOM, "Enter Lair task's mission has the wrong type!");
    cr_assert_not_null(enter_lair->prereq, "Enter Lair task has no prereq!");
    cr_assert_eq(enter_lair->prereq->hp, 12, "Enter Lair task's prereq has incorrect hp!");
    cr_assert_eq(enter_lair->prereq->level, 3, "Enter Lair task's prereq has incorrect level!");
    cr_assert_not_null(enter_lair->prereq->task_list, "Enter Lair task's prereq has no task list!");
    cr_assert_str_eq(enter_lair->prereq->task_list->head->id, "Talk to Land Scout", "Enter Lair task's prereq has an incorrect task in its task list");
    cr_assert_not_null(enter_lair->reward, "Enter Lair task has no reward!");
    cr_assert_eq(enter_lair->reward->xp, 100, "Enter Lair task's reward has incorrect xp!");

    // Check first task's child's sibling
    task_tree_t *steves_mom_tree = enter_lair_tree->rsibling;
    cr_assert_not_null(steves_mom_tree, "Enter Lair task tree has no right sibling!");
    task_t *steves_mom = steves_mom_tree->task;
    cr_assert_not_null(steves_mom, "Steve's Mom task is NULL!");
    cr_assert_str_eq(steves_mom->id, "Talk to Steve's Mom", "Steve's Mom task has incorrect id!");
    cr_assert_not_null(steves_mom->mission, "Steve's Mom task has no mission!");
    cr_assert_str_eq(steves_mom->mission->target_name, "Steve's Mom", "Steve's Mom task's mission has the wrong target!");
    cr_assert_eq(steves_mom->mission->type, MEET_NPC, "Steve's Mom task's mission has the wrong type!");
    cr_assert_not_null(steves_mom->prereq, "Steve's Mom task has no prereq!");
    cr_assert_eq(steves_mom->prereq->hp, 10, "Steve's Mom task's prereq has incorrect hp!");
    cr_assert_eq(steves_mom->prereq->level, 2, "Steve's Mom task's prereq has incorrect level!");
    cr_assert_not_null(steves_mom->prereq->task_list, "Steve's Mom task's prereq has no task list!");
    cr_assert_str_eq(steves_mom->prereq->task_list->head->id, "Talk to Land Scout", "Steve's Mom task's prereq has an incorrect task in its task list");
    cr_assert_not_null(steves_mom->reward, "Steve's Mom task has no reward!");
    cr_assert_eq(steves_mom->reward->xp, 50, "Steve's Mom task's reward has incorrect xp!");

    // Check first task's child's sibling
    task_tree_t *sea_scout_tree = land_scout_tree->rsibling;
    cr_assert_not_null(sea_scout_tree, "Land Scout task tree has no right sibling!");
    task_t *sea_scout = sea_scout_tree->task;
    cr_assert_not_null(sea_scout, "Sea Scout task is NULL!");
    cr_assert_str_eq(sea_scout->id, "Talk to Sea Scout", "Sea Scout task has incorrect id!");
    cr_assert_not_null(sea_scout->mission, "Sea Scout task has no mission!");
    cr_assert_str_eq(sea_scout->mission->target_name, "Sea Scout", "Sea Scout task's mission has the wrong target!");
    cr_assert_eq(sea_scout->mission->type, MEET_NPC, "Sea Scout task's mission has the wrong type!");
    cr_assert_not_null(sea_scout->prereq, "Sea Scout task has no prereq!");
    cr_assert_eq(sea_scout->prereq->hp, 15, "Sea Scout task's prereq has incorrect hp!");
    cr_assert_eq(sea_scout->prereq->level, 4, "Sea Scout task's prereq has incorrect level!");
    cr_assert_not_null(sea_scout->reward, "Sea Scout task has no reward!");
    cr_assert_eq(sea_scout->reward->xp, 100, "Sea Scout task's reward has incorrect xp!");
    cr_assert_not_null(sea_scout->reward->item, "Sea Scout task's reward has no item!");
    cr_assert_str_eq(sea_scout->reward->item->item_id, "search warrant", "Sea Scout task's reward has incorrect item!");

    // Check 3 layers deep
    task_tree_t *pirate_cove_tree = sea_scout_tree->lmostchild;
    cr_assert_not_null(pirate_cove_tree, "Sea Scout task tree has no leftmost child!");
    task_t *pirate_cove = pirate_cove_tree->task;
    cr_assert_not_null(pirate_cove, "Pirate Cove task is NULL!");
    cr_assert_str_eq(pirate_cove->id, "Find the Pirate Cove", "Pirate Cove task has incorrect id!");
    cr_assert_not_null(pirate_cove->mission, "Pirate Cove task has no mission!");
    cr_assert_str_eq(pirate_cove->mission->target_name, "Pirate Cove", "Pirate Cove task's mission has the wrong target!");
    cr_assert_eq(pirate_cove->mission->type, VISIT_ROOM, "Pirate Cove task's mission has the wrong type!");
    cr_assert_not_null(pirate_cove->prereq, "Pirate Cove task has no prereq!");
    cr_assert_eq(pirate_cove->prereq->hp, 15, "Pirate Cove task's prereq has incorrect hp!");
    cr_assert_eq(pirate_cove->prereq->level, 4, "Pirate Cove task's prereq has incorrect level!");
    cr_assert_not_null(pirate_cove->prereq->task_list, "Pirate Cove task's prereq has no task list!");
    cr_assert_str_eq(pirate_cove->prereq->task_list->head->id, "Talk to Sea Scout", "Pirate Cove task's prereq has an incorrect task in its task list");
    cr_assert_not_null(pirate_cove->reward, "Pirate Cove task has no reward!");
    cr_assert_eq(pirate_cove->reward->xp, 100, "Pirate Cove task's reward has incorrect xp!");

    // Check 4 layers deep left most child
    task_tree_t *pirate_map_tree = pirate_cove_tree->lmostchild;
    cr_assert_not_null(pirate_map_tree, "Pirate Cove task tree has no leftmost child!");
    task_t *pirate_map = pirate_map_tree->task;
    cr_assert_not_null(pirate_map, "Pirate Map task is NULL!");
    cr_assert_str_eq(pirate_map->id, "Obtain the Pirates' Map", "Pirate Map task has incorrect id!");
    cr_assert_not_null(pirate_map->mission, "Pirate Map task has no mission!");
    cr_assert_str_eq(pirate_map->mission->target_name, "Pirate Map", "Pirate Map task's mission has the wrong target!");
    cr_assert_eq(pirate_map->mission->type, COLLECT_ITEM, "Pirate Map task's mission has the wrong type!");
    cr_assert_not_null(pirate_map->prereq, "Pirate Map task has no prereq!");
    cr_assert_eq(pirate_map->prereq->hp, 15, "Pirate Map task's prereq has incorrect hp!");
    cr_assert_eq(pirate_map->prereq->level, 4, "Pirate Map task's prereq has incorrect level!");
    cr_assert_not_null(pirate_map->prereq->task_list, "Pirate Map task's prereq has no task list!");
    cr_assert_str_eq(pirate_map->prereq->task_list->head->id, "Talk to Sea Scout", "Pirate Map task's prereq has an incorrect task in its task list");
    cr_assert_str_eq(pirate_map->prereq->task_list->head->next->id, "Find the Pirate Cove", "Pirate Map task's prereq has an incorrect task in its task list");
    cr_assert_not_null(pirate_map->reward, "Pirate Map task has no reward!");
    cr_assert_eq(pirate_map->reward->xp, 200, "Pirate Map task's reward has incorrect xp!");
    cr_assert_not_null(pirate_map->reward->item, "Pirate Map task's rewrad has no item!");
    cr_assert_str_eq(pirate_map->reward->item->item_id, sailing_handbook->item_id, "Pirate Map task's reward has incorrect item!");

    // Check 4 layers deep sibling
    task_tree_t *pirate_captain_tree = pirate_map_tree->rsibling;
    cr_assert_not_null(pirate_captain_tree, "Pirate Map task tree has no right sibling!");
    task_t *pirate_captain = pirate_captain_tree->task;
    cr_assert_not_null(pirate_captain, "Pirate Captain task is NULL!");
    cr_assert_str_eq(pirate_captain->id, "Interrogate the Pirate Captain", "Pirate Captain task has incorrect id!");
    cr_assert_not_null(pirate_captain->mission, "Pirate Captain task has no mission!");
    cr_assert_str_eq(pirate_captain->mission->target_name, "Pirate Captain", "Pirate Captain task's mission has the wrong target!");
    cr_assert_eq(pirate_captain->mission->type, MEET_NPC, "Pirate Captain task's mission has the wrong type!");
    cr_assert_not_null(pirate_captain->prereq, "Pirate Captain task has no prereq!");
    cr_assert_eq(pirate_captain->prereq->hp, 20, "Pirate Captain task's prereq has incorrect hp!");
    cr_assert_eq(pirate_captain->prereq->level, 5, "Pirate Captain task's prereq has incorrect level!");
    cr_assert_not_null(pirate_captain->prereq->task_list, "Pirate Captain task's prereq has no task list!");
    cr_assert_str_eq(pirate_captain->prereq->task_list->head->id, "Talk to Sea Scout", "Pirate Captain task's prereq has an incorrect task in its task list");
    cr_assert_str_eq(pirate_captain->prereq->task_list->head->next->id, "Find the Pirate Cove", "Pirate Captain task's prereq has an incorrect task in its task list");
    cr_assert_not_null(pirate_captain->reward, "Pirate Captain task has no reward!");
    cr_assert_eq(pirate_captain->reward->xp, 250, "Pirate Captain task's reward has incorrect xp!");
    cr_assert_not_null(pirate_captain->reward->item, "Pirate Captain task's rewrad has no item!");
    cr_assert_str_eq(pirate_captain->reward->item->item_id, interrogation_handbook->item_id, "Pirate Captain task's reward has incorrect item!");

    /* Second Quest */
    quest_t *vanquish_steve = get_quest_from_hash("Vanquish Steve", game->all_quests);
    cr_assert_not_null(vanquish_steve, "Vanquish Steve quest not added to game's quest hash!");
    cr_assert_not_null(vanquish_steve->reward, "Vanquish Steve quest does not have a reward!");
    cr_assert_eq(vanquish_steve->reward->xp, 1000, "Vanquish Steve quest's reward has incorrect xp!");
    cr_assert_not_null(vanquish_steve->reward->item, "Vanquish Steve quest's reward has no item!");
    cr_assert_str_eq(vanquish_steve->reward->item->item_id, sword->item_id, "Vanquish Steve quest's reward has incorrect item!");
    cr_assert_not_null(vanquish_steve->prereq, "Vanquish Steve quest does not have a prereq!");
    cr_assert_eq(vanquish_steve->prereq->hp, 20, "Vanquish Steve quest's prereq has incorrect hp!");
    cr_assert_eq(vanquish_steve->prereq->level, 7, "Vanquish Steve quest's prereq has incorrect level!");
    cr_assert_not_null(vanquish_steve->prereq->quest_list, "Vanquish Steve quest's prereq has an empty quest list!");
    cr_assert_str_eq(vanquish_steve->prereq->quest_list->head->id, "Find Steve", "Vanquish Steve quest's prereq has incorrect quest in quest list");

    // Check first task
    task_tree_t *kill_steve_tree = vanquish_steve->task_tree;
    cr_assert_not_null(kill_steve_tree, "Vanquish Steve quest has NULL task tree!");
    task_t *kill_steve = kill_steve_tree->task;
    cr_assert_not_null(kill_steve, "Kill Steve task is NULL!");
    cr_assert_str_eq(kill_steve->id, "Kill Steve", "Kill Steve task has incorrect id!");
    cr_assert_not_null(kill_steve->mission, "Kill Steve task has no mission!");
    cr_assert_str_eq(kill_steve->mission->target_name, "Steve", "Kill Steve task's mission has the wrong target!");
    cr_assert_eq(kill_steve->mission->type, KILL_NPC, "Kill Steve task's mission has the wrong type!");
    cr_assert_not_null(kill_steve->prereq, "Kill Steve task has no prereq!");
    cr_assert_eq(kill_steve->prereq->hp, 30, "Kill Steve task's prereq has incorrect hp!");
    cr_assert_eq(kill_steve->prereq->level, 12, "Kill Steve task's prereq has incorrect level!");
    cr_assert_not_null(kill_steve->prereq->quest_list, "Kill Steve task's prereq has no quest list!");
    cr_assert_str_eq(kill_steve->prereq->quest_list->head->id, "Find Steve", "Kill Steve task's prereq has an incorrect quest in its quest list");
    cr_assert_not_null(kill_steve->prereq->task_list, "Kill Steve task's prereq has no task list!");
    cr_assert_str_eq(kill_steve->prereq->task_list->head->id, "Obtain Knife", "Kill Steve task's prereq has an incorrect task in its task list");
    cr_assert_not_null(kill_steve->reward, "Kill Steve task has no reward!");
    cr_assert_eq(kill_steve->reward->xp, 500, "Kill Steve task's reward has incorrect xp!");

    // Check second task
    task_tree_t *baby_photo_tree = kill_steve_tree->rsibling;
    cr_assert_not_null(baby_photo_tree, "Kill Steve task tree has no right sibling!");
    task_t *baby_photo = baby_photo_tree->task;
    cr_assert_not_null(baby_photo, "Baby Photo task is NULL!");
    cr_assert_str_eq(baby_photo->id, "Steal Steve's Embarassing Baby Photos", "Baby Photo task has incorrect id!");
    cr_assert_not_null(baby_photo->mission, "Baby Photo task has no mission!");
    cr_assert_str_eq(baby_photo->mission->target_name, "Steve's Embarassing Baby Photos", "Baby Photo task's mission has the wrong target!");
    cr_assert_eq(baby_photo->mission->type, COLLECT_ITEM, "Baby Photo task's mission has the wrong type!");
    cr_assert_not_null(baby_photo->prereq, "Baby Photo task has no prereq!");
    cr_assert_not_null(baby_photo->prereq->quest_list, "Baby Photo task's prereq has no quest list!");
    cr_assert_str_eq(baby_photo->prereq->quest_list->head->id, "Find Steve", "Baby Photo task's prereq has an incorrect quest in its quest list");
    cr_assert_not_null(baby_photo->prereq->task_list, "Baby Photo task's prereq has no task list!");
    cr_assert_str_eq(baby_photo->prereq->task_list->head->id, "Interrogate the Pirate Captain", "Baby Photo task's prereq has an incorrect task in its task list");
    cr_assert_not_null(baby_photo->reward, "Baby Photo task has no reward!");
    cr_assert_eq(baby_photo->reward->xp, 100, "Baby Photo task's reward has incorrect xp!");

    // Check quest created by prereq task worked correctly
    quest_t *knife_quest = get_quest_from_hash("Obtain Knife", game->all_quests);
    cr_assert_not_null(knife_quest, "Knife Quest does not exist!");
    cr_assert_str_eq(knife_quest->quest_id, "Obtain Knife", "Knife Quest has incorrect id!");
    task_tree_t *knife_task_tree = knife_quest->task_tree;
    cr_assert_not_null(knife_task_tree, "Knife Quest has no task tree!");
    task_t *knife = knife_task_tree->task;
    cr_assert_not_null(knife, "Knife Task does not exist!");
    cr_assert_str_eq(knife->id, "Obtain Knife", "Knife Task has incorrect id!");
    cr_assert_not_null(knife->mission, "Knife Task has no mission!");
    cr_assert_str_eq(knife->mission->target_name, "Knife", "Knife Task's mission has incorrect target name");
    cr_assert_eq(knife->mission->type, COLLECT_ITEM, "Knife Task's mission has incorrect type!");

}