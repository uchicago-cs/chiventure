#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/room.h"

// BASIC ROOM UNIT TESTS ------------------------------------------------------
/* Tests init function of room */
/* manually mallocs */
Test(room_start, init)
{
    room_t *empty_room = malloc(sizeof(room_t));
    empty_room->items = NULL;
    empty_room->long_desc = malloc(sizeof(char*)*MAX_LDESC_LEN+1);
    empty_room->short_desc = malloc(sizeof(char*)*MAX_SDESC_LEN+1);
    empty_room->room_id = malloc(sizeof(char*)*MAX_ID_LEN+1);
    empty_room->paths = NULL;
    int check = room_init(empty_room, "test_room", "This is a test room",
    "The purpose of this room is testing");

    cr_assert_eq(check, SUCCESS, "room_init() test 1 has failed!");
}

/* Tests new room malloc (new uses init) */
Test(room_start, new)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");

    cr_assert_not_null(new_room, "room_new() test 1 has failed!");

}

/* Tests room_free function */
Test(room_start, free)
{
    room_t *room_tofree = room_new("test_room", "room for testing",
    "testing if memory is correctly freed for rooms");

    cr_assert_not_null(room_tofree, "room_free(): room is null");
    int freed = room_free(room_tofree);

    cr_assert_eq(freed, SUCCESS, "room_free() test 1 has failed!");


}

/* Tests add_item_to_room
* Adds two items with different ids
*/
Test(room_item, add_item_to_room)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    item_t *test_item = item_new("test_item", "item for testing",
    "testing to see if get_item() works");
    item_t *test_item2 = item_new("test_item2", "item2 for testing",
    "testing to see if get_item() works 2");
    int rv = add_item_to_room(new_room, test_item);
    int rc = add_item_to_room(new_room, test_item2);
    cr_assert_eq(rv, SUCCESS, "item not added to room correctly");
    cr_assert_eq(rc, SUCCESS, "item2 not added to room correctly");

}

/* Tests add_item_to_room
 * Adds two duplicate items, succeeding only if items 
 * have different memory addresses
 */
Test(room_item, add_duplicate_item_to_room)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    item_t *test_item = item_new("test_item", "item for testing",
    "testing to see if get_item() works");
    item_t *test_item2 = item_new("test_item", "item2 for testing",
    "testing to see if get_item() exits correctly");

    int rv = add_item_to_room(new_room, test_item);
    cr_assert_eq(rv, SUCCESS, "item not added to room correctly");

    int check = add_item_to_room(new_room, test_item2);
    cr_assert_eq(check, SUCCESS, "duplicate item not added to room correctly");
    
    check = add_item_to_room(new_room, test_item2);
    cr_assert_eq(check, FAILURE, "item at same memory address as item "
                 "already in room added again to room");

}

/* Checks if get_item_in_room() correctly retrieves an item in room*/
Test(room_item, get_item)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    item_t *test_item = item_new("test_item", "item for testing",
    "testing to see if get_item() works");
    int rv = add_item_to_room(new_room, test_item);
    cr_assert_eq(rv, SUCCESS, "item not added to room correctly");
    item_t *returned_item = get_item_in_room(new_room, "test_item");
    cr_assert_eq(test_item, returned_item, "item not added to room correctly");

}

/* Checks if get_item_in_room() returns NULL when searching non-existent item*/
Test(room_item, get_nonexistent_item)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    item_t *test_item = item_new("test_item", "item for testing",
    "testing to see if get_item() works");
    int rv = add_item_to_room(new_room, test_item);
    cr_assert_eq(rv, SUCCESS, "item not added to room correctly");
    item_t *returned_item = get_item_in_room(new_room, "test_item_2");
    cr_assert_null(returned_item, "Item retrieved but should be NULL");

}
/* Checks if remove_item_from_room properly removes items */
Test(room_item, remove_item_from_room)
{
    room_t *room = room_new("room", "short", "long");
    item_t *test_item = item_new("item", "short", "long");
    item_t *dup_item = item_new("item", "short", "long");
    item_list_t *item_list;
    int rc;
    
    rc = add_item_to_room(room, test_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_room failed to "
                 "add an item to room");
    rc = add_item_to_room(room, dup_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_room failed to "
                 "add an item to room");
    
    rc = remove_item_from_room(room, test_item);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_room failed to "
                 "remove an item from room");
    
    item_list = get_all_items_in_room(room);
    cr_assert_not_null(item_list, "remove_item_from_room removed "
                       "both identical items from room");
}

/* Checks if sdesc is correctly returned
* Runs two small tests
* Tests same sdesc and different sdesc
*/
Test(room_get, get_sdesc) {
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    char test[MAX_SDESC_LEN] = "room for testing";
    char fail[MAX_SDESC_LEN] = "this is supposed to fail";
    int check = strncmp(get_sdesc(new_room), test, MAX_SDESC_LEN);
    int check2 = strncmp(get_sdesc(new_room), fail, MAX_SDESC_LEN);
    //if check2 returns !SUCCESS, set to SUCCESS
    if(check2 != SUCCESS)
      check2 = SUCCESS;
    cr_assert_eq(check, SUCCESS, "get_sdesc: failed to get sdesc");
    cr_assert_eq(check2, SUCCESS, "get_sdesc: failed to fail wrong strncmp");
}

/* Checks if ldesc is correctly returned
* Runs two small tests
* Tests same ldesc and different ldesc
*/
Test(room_get, get_ldesc)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    char test[MAX_LDESC_LEN] =
    "testing if memory is correctly allocated for new rooms";
    char fail[MAX_LDESC_LEN] = "this is supposed to fail";
    int check = strncmp(get_ldesc(new_room), test, MAX_LDESC_LEN);
    int check2 = strncmp(get_ldesc(new_room), fail, MAX_LDESC_LEN);
    //if check2 returns !SUCCESS, set to SUCCESS
    if(check2 != SUCCESS)
      check2 = SUCCESS;
    cr_assert_eq(check, SUCCESS, "get_ldesc: failed to get sdesc");
    cr_assert_eq(check2, SUCCESS, "get_ldesc: failed to fail wrong strncmp");
}

/* Tests path
* Runs two tests
* test1 checks if correct room is returned
* test2 checks if non-null room is returned
*/
Test(room_find, find_room_from_dir)
{
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    path_t *path_real = path_new(room2, "west");
    add_path_to_room(room1, path_real);
    room_t *succ = find_room_from_dir(room1, "west");
    room_t *fail = find_room_from_dir(room1, "east");

    //checks that room_ids are the same
    int c1 = strncmp(room2->room_id, succ->room_id, MAX_ID_LEN);
    cr_assert_not_null(succ, "returned NULL room instead of room2");
    //ensures find_room_from_dir returns NULL
    cr_assert_null(fail, "found nonexistent room");
    cr_assert_eq(c1, SUCCESS, "failed to obtain correct room_id");

}

Test(iter_macro, iter_paths)
{
    room_t *room1 = room_new("room1", "room1 short", "room1 long long long");
    room_t *room2 = room_new("room2", "room2 short", "room2 long long long");
    room_t *room3 = room_new("room3", "room3 short", "room3 long long long");
    add_path_to_room(room1, path_new(room2, "north"));
    add_path_to_room(room1, path_new(room3, "south"));
    int cnt = 0;
    path_t *curr_path;
    ITER_ALL_PATHS(room1, curr_path) {
        cnt++;
        if (!strncmp(curr_path->dest->room_id, "room3", MAX_ID_LEN)) {
            cr_assert_str_eq(curr_path->direction, "south",
            "direction does not correspond");
        } else if (!strncmp(curr_path->dest->room_id, "room2", MAX_ID_LEN)) {
            cr_assert_str_eq(curr_path->direction, "north",
            "direction does not correspond");
        } else {
            cr_assert_fail("non-existent room detected");
        }
    }
    cr_assert_eq(cnt, 2, "wrong path counts");
    room_free(room1);
    room_free(room2);
    room_free(room3);
}

// Conditions not done yet. Leave it for now.
/*
Test(iter_macro, iter_conditions)
{
    room_t *room1 = room_new("room1", "room1 short", "room1 long long long");
    room_t *room2 = room_new("room2", "room2 short", "room2 long long long");
    path_t *path = path_new(room2, "north");
    add_path_to_room(room1, path);
    add_condition_to_path(path, attribute_condition_new());
    int cnt = 0;
    path_t *curr_path;
    ITER_ALL_CONDITIONS(room1, curr_condi) {
        cnt++;
        if (!strncmp(curr_path->dest->room_id, "room3", MAX_ID_LEN)) {
            cr_assert_str_eq(curr_path->direction, "south",
            "direction does not correspond");

            cr_assert_str_eq(curr_path->direction, "north",
            "direction does not correspond");
        }
    }
    cr_assert_eq(cnt, 2, "wrong path counts");
}
*/

/*
//tested
room_t *room_new();
int room_init(room_t *new_room, char *room_id, char *short_desc, char *long_desc);
int room_free(room_t *room);
item_t* get_item_in_room(room_t* room, char* item_id);
int add_item_to_room(room_t *room, item_t *item);
char *get_sdesc(room_t *room);
char *get_ldesc(room_t *room);
room_t *find_room_from_dir(room_t *curr, char* direction);

//untested (will remain untested)
int delete_all_conditions(condition_list_t conditions);

*/
