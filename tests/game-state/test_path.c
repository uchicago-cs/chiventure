#include <stdio.h>
#include <criterion/criterion.h>
#include "game-state/room.h"
#include "game-state/game_state_common.h"
#include "game-state/path.h"
#include "action_management/actionmanagement.h"


// BASIC PATH UNIT TESTS ------------------------------------------------------
/* checks creation of new path */
Test(path, new)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "room to test path_new()");
    path_t *new_path = path_new(new_room, "north");

    cr_assert_not_null(new_path, "path_new() test 1 has failed!");
    room_free(new_room);
    path_free(new_path);

}


/* checks path is properly freed */
Test(path, free)
{
    room_t *test_dest = room_new("test_dest", "room for testing",
    "room to test path_free");
    path_t *path_tofree = path_new(test_dest, "west");

    int freed = path_free(path_tofree);

    cr_assert_eq(freed, SUCCESS, "path_free() test 1 has failed!");
    room_free(test_dest);

}


/* checks that conditions are intialized */
Test(path, conditions)
{
    //create path, assert it exists
    room_t *new_room = room_new("new_room", "room for testing",
    "room to test path_new_conditions()");
    path_t *new_path = path_new(new_room, "south");

    cr_assert_not_null(new_path, "path_new() test 2 has failed");

    //create list_action_type_t
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);

    list_action_type_t *first, *second, *last;
    first = malloc(sizeof(list_action_type_t));
    second = malloc(sizeof(list_action_type_t));
    last = malloc(sizeof(list_action_type_t));
    last->act = open;
    last->next = NULL;
    second->act = go;
    second->next = last;
    first->act = eat;
    first->next = second;

    int rc;
    rc = path_new_conditions(new_path,first);

    cr_assert_eq(rc, SUCCESS, "path_new_conditions() test 1 has failed");
    cr_assert_not_null(new_path->conditions, "no conditions have been"
    "implemented");
    path_free(new_path);
    room_free(new_room);
    free(first);
    free(second);
    free(last);
    action_type_free(eat);
    action_type_free(go);
    action_type_free(open);
}

/* checks that condition is removed */
Test(path, remove_condition)
{
    item_t *door = item_new("test_door", "item for testing",
    "test item for remove_condition()");
    door->attributes = NULL;

    room_t *new_room = room_new("new_room", "room for testing",
    "room to test remove_condition()");
    add_item_to_room(new_room, door);

    path_t *new_path = path_new(new_room, "south");
    new_path->through = door;

    //create list_action_type_t
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);

    list_action_type_t *first, *second, *last;
    first = malloc(sizeof(list_action_type_t));
    second = malloc(sizeof(list_action_type_t));
    last = malloc(sizeof(list_action_type_t));
    last->act = open;
    last->next = NULL;
    second->act = go;
    second->next = last;
    first->act = eat;
    first->next = second;

    //add list_action_type_t to path->conditions
    int rc;
    rc = path_new_conditions(new_path,first);

    cr_assert_eq(rc, SUCCESS, "path_new_conditions() failed");
    char *tmp = "OPEN";

    //make hash attribute for item
    attribute_t *OPEN = malloc(sizeof(attribute_t));
    OPEN->attribute_key = strndup(tmp,100);
    OPEN->attribute_tag = BOOLE;
    OPEN->attribute_value.bool_val = false;

    rc = add_attribute_to_hash(new_path->through, OPEN);

    cr_assert_eq(rc, SUCCESS, "add_attribute_to_hash() failed");

    //test function
    rc = remove_condition(new_path, second);

    cr_assert_null(go->room, "condition isn't fully implemented(1)");
    cr_assert_null(go->direction, "condition isn't fully implemented(2)");
    cr_assert_eq(rc, SUCCESS, "remove_condition() failed");
    cr_assert_eq(get_attribute(door, "OPEN")->attribute_value.bool_val, false, 
    "no conditions have been implemented");

    path_free(new_path);
    room_free(new_room);
    free(first);
    free(second);
    free(last);
    action_type_free(eat);
    action_type_free(go);
    action_type_free(open);
}


/* checks that last condition is removed and attribute changed */
Test(path, remove_final_condtion)
{
    item_t *door = item_new("test_door", "item for testing",
    "test item for remove_condition()");
    door->attributes = NULL;
    
    room_t *new_room = room_new("new_room", "room for testing",
    "room to test remove_condition()");
    add_item_to_room(new_room, door);

    path_t *new_path = path_new(new_room, "south");
    new_path->through = door;

    //create list_action_type_t
    action_type_t *open;
    open = action_type_new("open", ITEM);

    list_action_type_t *first;
    first = malloc(sizeof(list_action_type_t));
    first->act = open;
    first->next = NULL;

    //add list_action_type_t to path->conditions
    int rc;
    rc = path_new_conditions(new_path,first);

    cr_assert_eq(rc, SUCCESS, "path_new_conditions() failed");
    
    //make hash attribute for item
    attribute_t *OPEN = malloc(sizeof(attribute_t));
    char *tmp = "OPEN";
    OPEN->attribute_key = strndup(tmp, 100);
    OPEN->attribute_tag = BOOLE;
    OPEN->attribute_value.bool_val = false;
    rc = add_attribute_to_hash(new_path->through, OPEN);

    cr_assert_eq(rc, SUCCESS, "add_attribute_to_hash() failed");

    //test function
    rc = remove_condition(new_path, first);

    cr_assert_null(open->room, "condition isn't fully implemented(1)");
    cr_assert_null(open->direction, "condition isn't fully implemented(2)");    
    cr_assert_eq(rc, SUCCESS, "remove_condition() failed");
    cr_assert_eq(get_attribute(door, "OPEN")->attribute_value.bool_val, true, 
    "no conditions have been implemented");
    path_free(new_path);
    room_free(new_room);
    free(first);
    action_type_free(open);
}


// TESTS FOR ADDING FUNCTIONS -------------------------------------------------

Test(path, add_to_room)
{
    room_t *test_room = room_new("test_room", "room for testing",
    "testing add_path_to_room()");
    path_t *test_path = path_new(test_room, "east");

    cr_assert_not_null(test_path,
        "add_path_to_room() test: path initialization failed!");

    int added = add_path_to_room(test_room, test_path);
    cr_assert_eq(added, SUCCESS,
        "add_path_to_room() test: path was not successfully added to room!");
    room_free(test_room);
}

Test(path, add_to_null_room)
{
    room_t *test_room = NULL;
    path_t *test_path = path_new(test_room, "east");

    cr_assert_not_null(test_path,
        "add_path_to_room() test: path initialization failed!");

    int added = add_path_to_room(test_room, test_path);
    cr_assert_eq(added, FAILURE,
        "add_path_to_room() test: path was wrongfully added to NULL room!");
    path_free(test_path);
}

Test(path, add_null_path_to_room)
{
    room_t *test_room = room_new("test_room", "room for testing",
    "testing add_path_to_room()");
    path_t *test_path = NULL;

    int added = add_path_to_room(test_room, test_path);
    cr_assert_eq(added, FAILURE,
        "add_path_to_room() test: NULL path was wrongfully added to room!");
    room_free(test_room);
}


/* will write tests for adding conditions to path when WDL and action management
finalize  */

// TESTS FOR FIND/SEARCH FUNCTIONS --------------------------------------------
Test(path, search)
{
    room_t *test_room = room_new("test_room", "room for testing",
    "testing path_search()");
    path_t *test_path = path_new(test_room, "south");

    int added = add_path_to_room(test_room, test_path);
    cr_assert_eq(added, SUCCESS,
        "path_search() test: path was not successfully added to room!");

    path_t *path_found = path_search(test_room, "south");

    cr_assert_str_eq(path_found->direction, "south",
    "path_search() test: path found has incorrect direction!");
    cr_assert_str_eq(path_found->dest->room_id, "test_room",
    "path_search() test: path found has incorrect destination room!");
    room_free(test_room);
}

Test(path, search_null_room)
{
    room_t *test_room = NULL;

    path_t *path_found = path_search(test_room, "south");

    cr_assert_null(path_found,
        "path_search() test: path somehow found in NULL room");
}

Test(path, find_room)
{
    room_t *test_room = room_new("test_room", "room for testing",
    "room for testing find_room_from_path()");
    path_t *test_path = path_new(test_room, "north");

    room_t *found_room = find_room_from_path(test_path);

    cr_assert_str_eq(found_room->room_id, "test_room",
    "find_room_from_path() test: room found from path has incorrect room_id!");

    cr_assert_str_eq(found_room->short_desc, "room for testing",
    "find_room_from_path() test: room found has incorrect short desc!");

    cr_assert_str_eq(found_room->long_desc,
        "room for testing find_room_from_path()",
        "find_room_from_path() test: room found has incorrect long desc!");
    path_free(test_path);
    room_free(test_room);
}

Test(path, find_room_null_path)
{
    path_t *test_path = NULL;

    room_t *found_room = find_room_from_path(test_path);

    cr_assert_null(found_room,
        "find_room_from_path() test: room wrongfully found from NULL path");
}

Test(path, del_all)
{
    room_t *test_room = room_new("test_room", "room for testing",
    "item for testing del_all_paths function");
    path_t *test_path1 = path_new(test_room, "north");
    path_t *test_path2 = path_new(test_room, "east");
    path_t *test_path3 = path_new(test_room, "south");

    add_path_to_room(test_room, test_path1);
    add_path_to_room(test_room, test_path2);
    add_path_to_room(test_room, test_path3);

    int test = delete_all_paths(test_room->paths);
    cr_assert_eq(test, SUCCESS, "delete_all_paths() test failed!");
    test_room->paths = NULL;
    room_free(test_room);
}
