#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "openworld/autogenerate.h"
#include "openworld/default_rooms.h"
#include "openworld/default_items.h"

/* Tests the functions in auto_generation.h */

/* Checks that room with no paths returns false for path_exists_in_dir() */
Test(autogenerate, path_exists_in_dir_none)
{
    room_t *room = room_new("string1", "string2", "string3");
    cr_assert_eq(false, path_exists_in_dir(room, "NORTH"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "EAST"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "SOUTH"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "WEST"), "Expected false but got true");
}

/* Checks that room with a path in a given direction is determined as such */
Test(autogenerate, path_exists_in_dir_one_true)
{
    room_t *room = room_new("string1", "string2", "string3");
    room_t *dest_room = room_new("string1", "string2", "string3");

    // Path to dest_room
    path_t* path1 = path_new(dest_room, "NORTH");

    cr_assert_eq(SUCCESS, add_path_to_room(room, path1), "Could not add path to room");

    cr_assert_eq(true, path_exists_in_dir(room, "NORTH"), "Expected true but got false");
    cr_assert_eq(false, path_exists_in_dir(room, "EAST"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "SOUTH"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "WEST"), "Expected false but got true");
}

/* Checks that room with a path in a different direction is determined as such, i.e.
* if the existing direction is different from all valid directions (NORTH, EAST, SOUTH, WEST) */
Test(autogenerate, path_exists_in_dir_false)
{
    room_t *room = room_new("string1", "string2", "string3");
    room_t *dest_room = room_new("string1", "string2", "string3");

    // Path to dest_room
    path_t* path1 = path_new(dest_room, "DIFFERENT");

    cr_assert_eq(SUCCESS, add_path_to_room(room, path1), "Could not add path to room");

    cr_assert_eq(false, path_exists_in_dir(room, "NORTH"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "EAST"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "SOUTH"), "Expected false but got true");
    cr_assert_eq(false, path_exists_in_dir(room, "WEST"), "Expected false but got true");
}

/* Checks that room with paths in every direction returns true, so long as
* the given direction is valid */
Test(autogenerate, path_exists_in_dir_one_all_true)
{
    room_t *room = room_new("string1", "string2", "string3");
    room_t *dest_room1 = room_new("string1", "string2", "string3");
    room_t *dest_room2 = room_new("string1", "string2", "string3");
    room_t *dest_room3 = room_new("string1", "string2", "string3");
    room_t *dest_room4 = room_new("string1", "string2", "string3");

    // Paths to destination rooms (dest_roomX, where X is a number 1 <= X <= 4)
    path_t* path1 = path_new(dest_room1, "NORTH");
    path_t* path2 = path_new(dest_room2, "EAST");
    path_t* path3 = path_new(dest_room3, "SOUTH");
    path_t* path4 = path_new(dest_room4, "WEST");

    // Add all the paths to the test room
    cr_assert_eq(SUCCESS, add_path_to_room(room, path1), "Could not add path to room");
    cr_assert_eq(SUCCESS, add_path_to_room(room, path2), "Could not add path to room");
    cr_assert_eq(SUCCESS, add_path_to_room(room, path3), "Could not add path to room");
    cr_assert_eq(SUCCESS, add_path_to_room(room, path4), "Could not add path to room");

    // Valid directions tests
    cr_assert_eq(true, path_exists_in_dir(room, "NORTH"), "Expected true but got false");
    cr_assert_eq(true, path_exists_in_dir(room, "EAST"), "Expected true but got false");
    cr_assert_eq(true, path_exists_in_dir(room, "SOUTH"), "Expected true but got false");
    cr_assert_eq(true, path_exists_in_dir(room, "WEST"), "Expected true but got false");

    // Invalid direction test
    cr_assert_eq(false, path_exists_in_dir(room, "NOT A DIRECTION"), "Expected false but got true");
}

/* The tests above are checked, but for 2 or 3 valid paths */
Test(autogenerate, path_exists_in_dir_mid)
{
    room_t *room = room_new("string1", "string2", "string3");
    room_t *dest_room1 = room_new("string1", "string2", "string3");
    room_t *dest_room2 = room_new("string1", "string2", "string3");
    room_t *dest_room3 = room_new("string1", "string2", "string3");

    // 2 paths
    path_t* path1 = path_new(dest_room1, "NORTH");
    path_t* path2 = path_new(dest_room2, "EAST");
    cr_assert_eq(SUCCESS, add_path_to_room(room, path1), "Could not add path to room");
    cr_assert_eq(SUCCESS, add_path_to_room(room, path2), "Could not add path to room");

    // Valid directions tests
    cr_assert_eq(true, path_exists_in_dir(room, "NORTH"), "Expected true but got false");
    cr_assert_eq(true, path_exists_in_dir(room, "EAST"), "Expected true but got false");
    cr_assert_eq(false, path_exists_in_dir(room, "SOUTH"), "Expected true but got false");
    cr_assert_eq(false, path_exists_in_dir(room, "WEST"), "Expected false but got true");

    // Add a third path
    path_t* path3 = path_new(dest_room3, "SOUTH");
    cr_assert_eq(SUCCESS, add_path_to_room(room, path3), "Could not add path to room");
    cr_assert_eq(true, path_exists_in_dir(room, "SOUTH"), "Expected true but got false");

    // The first two paths should remain (should still get true)
    cr_assert_eq(true, path_exists_in_dir(room, "NORTH"), "Expected true but got false");
    cr_assert_eq(true, path_exists_in_dir(room, "EAST"), "Expected true but got false");

    // Invalid direction test
    cr_assert_eq(false, path_exists_in_dir(room, "NOT A DIRECTION"), "Expected false but got true");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a
* room pointer with NULL paths and items fields */
Test(autogenerate, roomspec_to_room1)
{
    roomspec_t *r = make_default_room("school", NULL, NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(r);

    // no need to check short/long desc because we know these are set by default_room
    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, false, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a
* room pointer with paths field not NULL */
Test(autogenerate, roomspec_to_room2)
{
    roomspec_t *r = make_default_room("castle", NULL, NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(r);

    // no need to check short/long desc because we know these are set by default_room
    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, false, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a
* room pointer with items field not NULL */
Test(autogenerate, roomspec_to_room3)
{
    roomspec_t *r = make_default_room("farmhouse", NULL, NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(r);

    // no need to check short/long desc because we know these are set by default_room
    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, false, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");

}

/* Checks that room_generate returns FAILURE when the current room of the
* game has outward paths in all directions */
Test(autogenerate, room_generate_failure)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");
    item_t *sample_item2 = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 1 roomspec case
    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item2);
    cr_assert_not_null(sample_roomspec2, "sample_roomspec2 should not be NULL");

    // 2 roomspec case
    speclist_t *tail = speclist_new(sample_roomspec2);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, tail);

    room_t *dest_room1 = room_new("string1", "string2", "string3");
    room_t *dest_room2 = room_new("string1", "string2", "string3");
    room_t *dest_room3 = room_new("string1", "string2", "string3");
    room_t *dest_room4 = room_new("string1", "string2", "string3");

    path_t* path_north = path_new(dest_room1, "NORTH");
    path_t* path_east = path_new(dest_room2, "EAST");
    path_t* path_south = path_new(dest_room3, "SOUTH");
    path_t* path_west = path_new(dest_room4, "WEST");

    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, path_north),
                 "Could not add path to room");
    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, path_east),
                 "Could not add path to room");
    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, path_south),
                 "Could not add path to room");
    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, path_west),
                 "Could not add path to room");

    cr_assert_eq(FAILURE, room_generate(g, sample_gencontext, sample_roomspec),
                 "room_generate() returned SUCCESS when it should have returned FAILURE");
}

/* One roomspec case: Checks that, given a game, context (gencontext_t), and room_id,
* room_generate correctly creates a room from the head of the context
* and adds it to the game via a path (if game->curr_room has available path directions) */
Test(autogenerate, room_generate_success_one)
{
    game_t *g = game_new("start desc");
    roomspec_t *hash = make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    g->curr_room = roomspec_to_room(random_room_lookup(spec));

    // Path to sample_room1
    path_t* path_to_room = path_new(g->curr_room, "NORTH");

    roomspec_t *room2 = random_room_lookup(spec);
    cr_assert_not_null(room2, "sample_roomspec should not be NULL");

    // 1 roomspec case
    cr_assert_not_null(spec, "sample_speclist should not be NULL");

    room_t *sample_room2 = roomspec_to_room(room2);

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, spec);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    roomspec_t *room3 = random_room_lookup(spec);
    cr_assert_not_null(room3, "room3 should not be NULL");

    // 2 roomspec case
    speclist_t *tail = speclist_new(room2);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, tail);


    //create roomspec
    roomspec_t *rspec = random_room_lookup(spec);
    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext, rspec),
                 "room_generate() returned FAILURE when it should have returned SUCCESS");

    path_hash_t *current, *tmp;
    room_t *new_room;
    HASH_ITER(hh, g->curr_room->paths, current, tmp) {
        // current is an outward path from curr_room
        new_room = current->dest;
        break;
    }

    current = NULL;
    tmp = NULL;
    unsigned int count = 0;
    HASH_ITER(hh, new_room->paths, current, tmp) {
        count++;
    }

    cr_assert_eq(1, count, "There should be one (backwards) path into the current room");
}

/* 2 roomspec case: Checks that, given a game, context (gencontext_t), and room_id,
* room_generate correctly creates a room from the head of the context
* and adds it to the game via a path (only if game->curr_room is a dead end) */
Test(autogenerate, room_generate_success_two)
{
    game_t *g = game_new("start desc");
    roomspec_t *hash = make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    g->curr_room = roomspec_to_room(random_room_lookup(spec));

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *room2 = random_room_lookup(spec);
    room_t *sample_room1 = roomspec_to_room(room2);

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");

    roomspec_t *sample_roomspec = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec2 = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec2, "sample_roomspec2 should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, spec);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // 2 roomspec case
    speclist_t *tail = speclist_new(sample_roomspec2);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, tail);

    //create roomspec
    roomspec_t *rspec = random_room_lookup(spec);
    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext, rspec),
                 "room_generate() returned FAILURE when it should have returned SUCCESS");

    path_hash_t *current, *tmp;
    room_t *new_room;
    HASH_ITER(hh, g->curr_room->paths, current, tmp) {
        // current is an outward path from curr_room
        new_room = current->dest;
        break;
    }

    current = NULL;
    tmp = NULL;
    unsigned int count = 0;
    HASH_ITER(hh, new_room->paths, current, tmp) {
        count++;
    }

    cr_assert_eq(1, count, "There should be one (backwards) path into the current room");
}

/* 3 roomspec case: Checks that, given a game, context (gencontext_t), and room_id,
* room_generate correctly creates a room from the head of the context
* and adds it to the game via a path (only if game->curr_room is a dead end) */
Test(autogenerate, room_generate_success_three)
{
    game_t *g = game_new("start desc");
    roomspec_t *hash = make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    g->curr_room = roomspec_to_room(random_room_lookup(spec));

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t * sample1 = random_room_lookup(spec);;
    room_t *sample_room1 = roomspec_to_room(sample1);

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");

    roomspec_t *sample_roomspec = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec2 = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec2, "sample_roomspec2 should not be NULL");

    roomspec_t *sample_roomspec3 = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec3, "sample_roomspec3 should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, spec);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // 3 roomspec case
    speclist_t *mid = speclist_new(sample_roomspec2);
    cr_assert_not_null(mid, "Could not create new speclist");
    speclist_t *tail = speclist_new(sample_roomspec3);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, mid);
    DL_APPEND(sample_gencontext->speclist, tail);

    //create roomspec
    roomspec_t *rspec = random_room_lookup(spec);
    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext, rspec),
                 "room_generate() returned FAILURE when it should have returned SUCCESS");

    path_hash_t *current, *tmp;
    room_t *new_room;
    HASH_ITER(hh, g->curr_room->paths, current, tmp) {
        // current is an outward path from curr_room
        new_room = current->dest;
        break;
    }

    current = NULL;
    tmp = NULL;
    unsigned int count = 0;
    HASH_ITER(hh, new_room->paths, current, tmp) {
        count++;
    }

    cr_assert_eq(1, count, "There should be one (backwards) path into the current room");
}

/* Checks that multi_room_generate returns FAILURE if the current room of the
* given game is not a dead end, i.e. there are outward paths */
Test(autogenerate, invalid_multi_room)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");
    assert(SUCCESS == add_path_to_room(sample_room2, path_to_room));

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, NULL);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;

    cr_assert_eq(FAILURE, multi_room_generate(g, sample_gencontext, "school", 1),
                 "multi_room_generate() returned SUCCESS instead of FAILURE");
}

/* Checks that multi_room_generate successfully generates/adds rooms from a
* context (gencontext_t) struct's speclist field when one room is requested */
Test(autogenerate, valid_multi_room1)
{
    roomspec_t *hash = make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);

    roomspec_t *sample1 = random_room_lookup(spec);
    room_t *sample_room1 = roomspec_to_room(sample1);
    roomspec_t *sample2 = random_room_lookup(spec);
    room_t *sample_room2 = roomspec_to_room(sample2);

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");
    assert(SUCCESS == add_path_to_room(sample_room2, path_to_room));

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    roomspec_t *sample_roomspec = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 1 roomspec case
    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;
    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext, "school",  1),
                 "multi_room_generate() returned FAILURE instead of SUCCESS");
}

/* Checks that multi_room_generate successfully generates/adds rooms from a
* context (gencontext_t) struct's speclist field when two rooms are requested */
Test(autogenerate, valid_multi_room2)
{
    roomspec_t *hash =make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);

    roomspec_t *sample1 = random_room_lookup(spec);
    room_t *sample_room1 = roomspec_to_room(sample1);
    roomspec_t *sample2 = random_room_lookup(spec);
    room_t *sample_room2 = roomspec_to_room(sample2);

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");
    assert(SUCCESS == add_path_to_room(sample_room2, path_to_room));

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");
    item_t *sample_item2 = item_new("item_id2", "short_desc", "long_desc");
    item_t *sample_item3 = item_new("item_id3", "short_desc", "long_desc");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    roomspec_t *sample_roomspec = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 1 roomspec case
    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;

    roomspec_t *sample_roomspec2 = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec2, "sample_roomspec2 should not be NULL");

    roomspec_t *sample_roomspec3 = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec3, "sample_roomspec3 should not be NULL");

    speclist_t *mid = speclist_new(sample_roomspec2);
    cr_assert_not_null(mid, "Could not create new speclist");
    speclist_t *tail = speclist_new(sample_roomspec3);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, mid);
    DL_APPEND(sample_gencontext->speclist, tail);

    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext, "school", 2),
                 "multi_room_generate() returned FAILURE instead of SUCCESS");
}

/* Checks that multi_room_generate successfully generates/adds rooms from a
* context (gencontext_t) struct's speclist field when multiple (3) rooms are requested */
Test(autogenerate, valid_multi_room3)
{
    roomspec_t *hash = make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);

    roomspec_t *sample1 = random_room_lookup(spec);
    room_t *sample_room1 = roomspec_to_room(sample1);
    roomspec_t *sample2 = random_room_lookup(spec);
    room_t *sample_room2 = roomspec_to_room(sample2);

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");
    assert(SUCCESS == add_path_to_room(sample_room2, path_to_room));

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    roomspec_t *sample_roomspec = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    roomspec_t *sample_roomspec2 = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec3 = random_room_lookup(spec);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 3 roomspec case
    speclist_t *mid = speclist_new(sample_roomspec2);
    cr_assert_not_null(mid, "Could not create new speclist");
    speclist_t *tail = speclist_new(sample_roomspec3);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, mid);
    DL_APPEND(sample_gencontext->speclist, tail);

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;
    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext, "school", 3));
}

/* testing speclist_from_hash for school bucket*/
Test(speclist, school_hash)
{
    roomspec_t *hash = make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    cr_assert_not_null(spec);

    speclist_t *tmp = spec;

    while (tmp != NULL) {
        if (!strcmp(spec->spec->room_name, "classroom") &&
                !strcmp(spec->spec->room_name, "closet") &&
                !strcmp(spec->spec->room_name, "cafeteria") &&
                !strcmp(spec->spec->room_name, "hallway")&&
                !strcmp(spec->spec->room_name, "library")) {
            cr_assert_str_neq(spec->spec->room_name, "classroom");
        }
        tmp = tmp->next;
    }
}

/* testing speclist_from_hash for farmhouse bucket*/
Test(speclist, farm_hash)
{
    roomspec_t *hash = make_default_room("farmhouse", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    cr_assert_not_null(spec);

    speclist_t *tmp = spec;

    while (tmp != NULL) {
        if (!strcmp(spec->spec->room_name, "barn") &&
                !strcmp(spec->spec->room_name, "closet") &&
                !strcmp(spec->spec->room_name, "kitchen") &&
                !strcmp(spec->spec->room_name, "living room") &&
                !strcmp(spec->spec->room_name, "open field")) {
            cr_assert_str_neq(spec->spec->room_name, "barn");
        }
        tmp = tmp->next;
    }
}

/* testing speclist_from_hash for castle bucket*/
Test(speclist, castle_hash)
{
    roomspec_t *hash = make_default_room("castle", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    cr_assert_not_null(spec);

    speclist_t *tmp = spec;

    while (tmp != NULL) {
        if (!strcmp(spec->spec->room_name, "throne room") &&
                !strcmp(spec->spec->room_name, "closet") &&
                !strcmp(spec->spec->room_name, "dungeon") &&
                !strcmp(spec->spec->room_name, "hallway") &&
                !strcmp(spec->spec->room_name, "library")) {
            cr_assert_str_neq(spec->spec->room_name, "throne room");
        }
        tmp = tmp->next;
    }
}

/* testing random room lookup for school speclist*/
Test(speclist, school_lookup)
{
    roomspec_t *hash = make_default_room("school", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    cr_assert_not_null(spec);

    roomspec_t *r = random_room_lookup(spec);
    cr_assert_not_null(r);
    cr_assert_not_null(r->room_name);
    cr_assert_not_null(r->short_desc);
    cr_assert_not_null(r->long_desc);

    if (!strcmp(r->room_name, "classroom") &&
            !strcmp(r->room_name, "closet") &&
            !strcmp(r->room_name, "cafeteria") &&
            !strcmp(r->room_name, "hallway") &&
            !strcmp(r->room_name, "library")) {
        //bogus error code if doesn't match any of the 5 room types
        cr_assert_str_neq(r->room_name, "classroom");
    }


}

/* testing random room lookup for farmhouse speclist*/
Test(speclist, farm_lookup)
{
    roomspec_t *hash = make_default_room("farmhouse", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    cr_assert_not_null(spec);

    roomspec_t *r = random_room_lookup(spec);
    cr_assert_not_null(r);
    cr_assert_not_null(r->room_name);
    cr_assert_not_null(r->short_desc);
    cr_assert_not_null(r->long_desc);

    if (!strcmp(r->room_name, "barn") &&
            !strcmp(r->room_name, "closet") &&
            !strcmp(r->room_name, "kitchen") &&
            !strcmp(r->room_name, "living room") &&
            !strcmp(r->room_name, "open field")) {
        cr_assert_str_neq(r->room_name, "barn");
    }
}

/* testing random room lookup for castle speclist*/
Test(speclist, castle_lookup)
{
    roomspec_t *hash = make_default_room("castle", NULL, NULL);
    speclist_t *spec = NULL;
    speclist_from_hash(&spec, hash);
    cr_assert_not_null(spec);

    roomspec_t *r = random_room_lookup(spec);
    cr_assert_not_null(r);
    cr_assert_not_null(r->room_name);
    cr_assert_not_null(r->short_desc);
    cr_assert_not_null(r->long_desc);

    if (!strcmp(r->room_name, "throne room") &&
            !strcmp(r->room_name, "closet") &&
            !strcmp(r->room_name, "dungeon") &&
            !strcmp(r->room_name, "hallway") &&
            !strcmp(r->room_name, "library")) {
        cr_assert_str_neq(r->room_name, "throne room");
    }
}

/* testing random_items for barn roomspec*/
Test(roomspec, barn_item)
{
    roomspec_t *hash = make_default_room("farmhouse", NULL, NULL);
    roomspec_t *r = NULL;
    HASH_FIND_STR(hash, "barn", r);

    item_hash_t *items = random_items(r);
    if (items != NULL) {
        cr_assert_not_null(items->item_id);
        if (!strcmp(items->item_id, "apple") &&
                !strcmp(items->item_id, "cow") &&
                !strcmp(items->item_id, "eagle") &&
                !strcmp(items->item_id, "rabbit") &&
                !strcmp(items->item_id, "yam")) {
            cr_assert_str_neq(items->item_id, "rabbit");
        }
    }
}

/* testing random_items for classroom roomspec*/
Test(roomspec, class_item)
{
    roomspec_t *hash = make_default_room("school",NULL, NULL);
    roomspec_t *r = NULL;
    HASH_FIND_STR(hash, "classroom", r);

    item_hash_t *items = random_items(r);
    if (items != NULL) {
        cr_assert_not_null(items->item_id);
        if (!strcmp(items->item_id, "book") &&
                !strcmp(items->item_id, "door") &&
                !strcmp(items->item_id, "pencil") &&
                !strcmp(items->item_id, "watercolors") &&
                !strcmp(items->item_id, "video")) {
            cr_assert_str_neq(items->item_id, "pencil");
        }
    }
}

/* testing random_items for throne room roomspec*/
Test(roomspec, throne_item)
{
    roomspec_t *hash = make_default_room("castle", NULL, NULL);
    roomspec_t *r = NULL;
    HASH_FIND_STR(hash, "throne room", r);

    item_hash_t *items = random_items(r);
    if (items != NULL) {
        cr_assert_not_null(items->item_id);
        if (!strcmp(items->item_id, "nail") &&
                !strcmp(items->item_id, "book") &&
                !strcmp(items->item_id, "ladder") &&
                !strcmp(items->item_id, "gold") &&
                !strcmp(items->item_id, "yam")) {
            cr_assert_str_neq(items->item_id, "yam");
        }
    }
}

/* testing random_item_lookup for 0 iterations*/
Test(item_hash, zero_lookup)
{
    item_hash_t *dst = NULL;
    item_hash_t *src = get_default_items();
    int rc;
    rc = random_item_lookup(&dst, src, 0);
    cr_assert_not_null(dst);
}

/* testing random_item_lookup for 1 iteration*/
Test(item_hash, one_lookup)
{
    item_hash_t *dst = NULL;
    item_hash_t *src = get_default_items();
    int rc;
    rc = random_item_lookup(&dst, src, 1);
    cr_assert_not_null(dst);
}

/* testing random_item_lookup for 3 iterations*/
Test(item_hash, three_lookup)
{
    item_hash_t *dst = NULL;
    item_hash_t *src = get_default_items();
    int rc;
    rc = random_item_lookup(&dst, src, 3);

    cr_assert_not_null(dst);
}
