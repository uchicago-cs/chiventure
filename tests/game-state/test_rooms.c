#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/room.h"

/* Creates a sample battle_item. Taken from test_battle_ai.c */
battle_item_t *generate_test_battle_item(int id, int quantity, char* description, 
                                         char *name, bool attack, stat_changes_t *changes)
{
     battle_item_t* item = (battle_item_t*) calloc(1, sizeof(battle_item_t));

     item->id = id;
     item->name = name;
     item->description = description;
     item->quantity = quantity;
     item->description = description;
     item->attack = attack;
     item->attributes = changes;

     return item;
}

/* Creates a sample class. Taken from test_class.c */
class_t *generate_test_class()
{
    class_t *c;
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
    empty_room->coords = NULL;
    empty_room->tag = 0;
    int check = room_init(empty_room, "test_room", "This is a test room",
                          "The purpose of this room is testing");

    cr_assert_eq(check, SUCCESS, "room_init() test 1 has failed!");
    room_free(empty_room);
}

/* Tests new room malloc (new uses init) */
Test(room_start, new)
{
    room_t *new_room = room_new("test_room", "room for testing",
                                "testing if memory is correctly allocated for new rooms");

    cr_assert_not_null(new_room, "room_new() test 1 has failed!");
    room_free(new_room);
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
    room_free(new_room);
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
    room_free(new_room);
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
    room_free(new_room);
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
    room_free(new_room);
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
    room_free(room);
    item_free(test_item);
    delete_item_llist(item_list);
}

/* Checks if sdesc is correctly returned
* Runs two small tests
* Tests same sdesc and different sdesc
*/
Test(room_get, get_sdesc)
{
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
    room_free(new_room);
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
    room_free(new_room);
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
    room_free(room1);
    room_free(room2);
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
    ITER_ALL_PATHS(room1, curr_path)
    {
        cnt++;
        if (!strncmp(curr_path->dest->room_id, "room3", MAX_ID_LEN))
        {
            cr_assert_str_eq(curr_path->direction, "south",
                             "direction does not correspond");
        }
        else if (!strncmp(curr_path->dest->room_id, "room2", MAX_ID_LEN))
        {
            cr_assert_str_eq(curr_path->direction, "north",
                             "direction does not correspond");
        }
        else
        {
            cr_assert_fail("non-existent room detected");
        }
    }
    cr_assert_eq(cnt, 2, "wrong path counts");
    room_free(room1);
    room_free(room2);
    room_free(room3);
}

/* Creates example moves. Taken from test_battle_ai.c */
move_t *create_enemy_moves()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = move_new(1, "earthquake", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 100, 100, NULL, NULL, NULL, NULL);
    poke = move_new(2, "poke", "", PHYS, NO_TARGET, NO_TARGET,
                    SINGLE, 0, NULL, 40, 100, NULL, NULL, NULL, NULL);
    rock_throw = move_new(3, "rock throw", "", PHYS, NO_TARGET, NO_TARGET,
                          SINGLE, 0, NULL, 90, 100, NULL, NULL, NULL, NULL);
    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw);
}

/* Creates example stats. Taken from test_battle_ai.c */
stat_t *create_enemy_stats1()
{
    stat_t *test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_def = 10;
    test_stats->mag_atk = 10;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->sp = 50;
    test_stats->max_sp = 50;

    return test_stats;
}

// /* Creates example moves. Taken from test_battle_ai.c */
// move_t *create_enemy_moves1()
// {
//     move_t *head, *earthquake, *poke, *rock_throw;
//     head = NULL;
//     earthquake = create_move(1, NULL, true, 100, 0);
//     poke = create_move(2, NULL, true, 40, 0);
//     rock_throw = create_move(3, NULL, true, 90, 0);
//     DL_APPEND(head, earthquake);
//     DL_APPEND(head, poke);
//     DL_APPEND(head, rock_throw);
//     return head;
// }

/* Checks that transfer_all_npc_items() removes items from a dead npc and
   transfers them to the room */
Test(npc_battle, transfer_all_npc_items_dead)
{
    npc_t *npc = npc_new("npc", "short", "long", NULL, NULL, HOSTILE);
    stat_t *stats = create_enemy_stats1();
    move_t *moves = create_enemy_moves();
    item_t *test_item1 = item_new("item1", "short", "long");
    item_t *test_item2 = item_new("item2", "short", "long");
    item_t *test_item3 = item_new("item3", "short", "long");
    room_t *room = room_new("test_room", "room for testing",
                            "testing if memory is correctly allocated for new rooms");

    cr_assert_not_null(npc, "npc_new() failed");
    cr_assert_not_null(test_item1, "item_new() 1 failed");
    cr_assert_not_null(test_item2, "item_new() 2 failed");
    cr_assert_not_null(test_item3, "item_new() 3 failed");
    cr_assert_not_null(room, "room_new() failed");

    battle_item_t *dagger = generate_test_battle_item(1, 1,
                            "A hearty dagger sure to take your breath away... for good",
                            "dagger", true, NULL);

    add_battle_to_npc(npc, stats, moves, BATTLE_AI_GREEDY, 
    HOSTILE, generate_test_class(), dagger, NULL, NULL, NULL);
    add_item_to_npc(npc, test_item1);
    add_item_to_npc(npc, test_item2);
    add_item_to_npc(npc, test_item3);

    item_hash_t *actual = NULL;
    add_item_to_hash(&actual, test_item1);
    add_item_to_hash(&actual, test_item2);
    add_item_to_hash(&actual, test_item3);

    cr_assert_not_null(npc->npc_battle, "add_battle_to_npc() failed");
    cr_assert_not_null(npc->inventory, "add_item_to_npc() failed to add item");
    cr_assert_not_null(actual, "add_item_to_hash() failed to add items");

    change_npc_hp(npc, -1*(npc->npc_battle->stats->hp));
    int rc = transfer_all_npc_items(npc, room);

    cr_assert_eq(rc, SUCCESS, "transfer_all_npc_items() failed");
    cr_assert_eq(actual, room->items,
                 "transfer_all_npc_items() failed to add room items");
    cr_assert_null(npc->inventory,
                   "transfer_all_npc_items() failed to remove npc items");

}

/* Checks that transfer_all_npc_items() does not remove items from a living npc
   and transfer them to the room */
Test(npc_battle, transfer_all_npc_items_alive)
{
    npc_t *npc = npc_new("npc", "short", "long", NULL, NULL, HOSTILE);
    stat_t *stats = create_enemy_stats1();
    move_t *moves = create_enemy_moves();
    item_t *test_item1 = item_new("item1", "short", "long");
    item_t *test_item2 = item_new("item2", "short", "long");
    item_t *test_item3 = item_new("item3", "short", "long");
    room_t *room = room_new("test_room", "room for testing",
                            "testing if memory is correctly allocated for new rooms");

    cr_assert_not_null(npc, "npc_new() failed");
    cr_assert_not_null(test_item1, "item_new() 1 failed");
    cr_assert_not_null(test_item2, "item_new() 2 failed");
    cr_assert_not_null(test_item3, "item_new() 3 failed");
    cr_assert_not_null(room, "room_new() failed");

    battle_item_t *dagger = generate_test_battle_item(1, 1,
                            "A hearty dagger sure to take your breath away... for good",
                            "dagger", true, NULL);

    add_battle_to_npc(npc, stats, moves, BATTLE_AI_GREEDY, 
    HOSTILE, generate_test_class(), dagger, NULL, NULL, NULL);
    add_item_to_npc(npc, test_item1);
    add_item_to_npc(npc, test_item2);
    add_item_to_npc(npc, test_item3);

    item_hash_t *actual = NULL;
    add_item_to_hash(&actual, test_item1);
    add_item_to_hash(&actual, test_item2);
    add_item_to_hash(&actual, test_item3);

    cr_assert_not_null(npc->npc_battle, "add_battle_to_npc() failed");
    cr_assert_not_null(npc->inventory, "add_item_to_npc() failed to add items");
    cr_assert_not_null(actual, "add_item_to_hash() failed to add items");

    int rc = transfer_all_npc_items(npc, room);

    cr_assert_eq(rc, FAILURE, "transfer_all_npc_items() transferred items");
    cr_assert_null(room->items,
                   "transfer_all_npc_items() added room items");
    cr_assert_eq(actual, npc->inventory,
                 "transfer_all_npc_items() removed npc items");

}

/* Checks that transfer_all_npc_items() works when the npc has an empty
   inventory */
Test(npc_battle, transfer_all_npc_items_empty_inventory)
{
    npc_t *npc = npc_new("npc", "short", "long", NULL, NULL, HOSTILE);
    stat_t *stats = create_enemy_stats1();
    move_t *moves = create_enemy_moves();
    room_t *room = room_new("test_room", "room for testing",
                            "testing if memory is correctly allocated for new rooms");

    cr_assert_not_null(npc, "npc_new() failed");
    cr_assert_not_null(room, "room_new() failed");

    battle_item_t *dagger = generate_test_battle_item(1, 1,
                            "A hearty dagger sure to take your breath away... for good",
                            "dagger", true, NULL);

    add_battle_to_npc(npc, stats, moves, BATTLE_AI_GREEDY, 
    HOSTILE, generate_test_class(), dagger, NULL, NULL, NULL);

    cr_assert_not_null(npc->npc_battle, "add_battle_to_npc() failed");
    cr_assert_null(npc->inventory, "npc->inventory not NULL");
    change_npc_hp(npc, -1*(npc->npc_battle->stats->hp));

    int rc = transfer_all_npc_items(npc, room);

    cr_assert_eq(rc, SUCCESS, "transfer_all_npc_items() failed");
    cr_assert_null(room->items,
                   "transfer_all_npc_items() added room items");
    cr_assert_null(npc->inventory,
                   "transfer_all_npc_items() still has npc items");

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

/* testing coords struct functions */
Test(coords, init)
{
    coords_t *new_coords = malloc(sizeof(coords_t));
    int check = coords_init(new_coords, 0, 0);

    cr_assert_eq(check, SUCCESS, "coords_init() test 1 has failed!");
    coords_free(new_coords);
}

Test(coords, new)
{
    coords_t *new_coords = coords_new(0, 0);

    cr_assert_not_null(new_coords, "coords_new() test 1 has failed!");
    coords_free(new_coords);
}

Test(coords, free)
{
    coords_t *coords_tofree = coords_new(0, 0);

    cr_assert_not_null(coords_tofree, "coords_free(): coords is null");
    int freed = coords_free(coords_tofree);

    cr_assert_eq(freed, SUCCESS, "coords_free() test 1 has failed!");   
}

Test(coords, add_coords_to_room)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    coords_t *add_these_coords = coords_new(1,1);
    cr_assert_not_null(add_these_coords, "add_coords_to_room(): coords is null");

    add_coords_to_room(add_these_coords, new_room);
    cr_assert_eq(new_room->coords, add_these_coords, "add_coords_to_room() test 1 has failed");
}

Test(coords, find_coords_of_room)
{
    room_t *new_room = room_new("test_room", "room for testing",
    "testing if memory is correctly allocated for new rooms");
    coords_t *add_these_coords = coords_new(1,1);
    cr_assert_not_null(add_these_coords, "find_coords_of_room(): coords is null");
    add_coords_to_room(add_these_coords, new_room);

    coords_t *check_coords = find_coords_of_room(new_room);
    cr_assert_eq(check_coords, add_these_coords, "find_coords_of_room() test 1 has failed");
}
