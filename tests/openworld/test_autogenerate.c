#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "openworld/autogenerate.h"

/* Tests the functions in sample_generation.h */

/* Checks that a given room correctly interpreted as having no paths 
Test(autogenerate, any_paths1)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    cr_assert_eq(any_paths(sample_room1), false, 
        "anypaths(): Should not have any paths");
}
*/
/* Checks that a room with one path is correctly interpreted as having 
 * one or more paths (any_paths() -> true) 
Test(autogenerate, any_paths2)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (0 == add_path_to_room(sample_room2, path_to_room));

    cr_assert_eq(any_paths(sample_room2), true, 
        "anypaths(): Should have a path");
}*/

/* Checks that a room with two paths is correctly interpreted as having 
 * one or more paths (any_paths() -> true) 
Test(autogenerate, any_paths3)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString", "anotherString", "anotherString");

    room_t *sample_room3 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (0 == add_path_to_room(sample_room2, path_to_room));

    // Path to sample_room3
    path_t* path_to_room2 = path_new(sample_room3, "to sample_room3");
    assert (0 == add_path_to_room(sample_room2, path_to_room2));

    cr_assert_eq(any_paths(sample_room2), true, 
        "anypaths(): Should have paths");
}*/

/* Checks that a room with multiple (3) paths is correctly interpreted as 
 * having one or more paths (any_paths() -> true) 
Test(autogenerate, any_paths4)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString", "anotherString", "anotherString");

    room_t *sample_room3 = room_new("anotherString1", "anotherString2", "anotherString3");

    room_t *sample_room4 = room_new("s1", "s2", "s3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (0 == add_path_to_room(sample_room2, path_to_room));

    // Path to sample_room3
    path_t* path_to_room2 = path_new(sample_room3, "to sample_room3");
    assert (0 == add_path_to_room(sample_room2, path_to_room2));

    // Path to sample_room4
    path_t* path_to_room3 = path_new(sample_room3, "to sample_room4");
    assert (0 == add_path_to_room(sample_room2, path_to_room3));

    cr_assert_eq(any_paths(sample_room2), true, 
        "anypaths(): Should have paths");
}*/

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with NULL paths and items fields 
Test(autogenerate, roomspec_to_room1)
{
    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r);

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample room name"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}*/

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with paths field not NULL 
Test(autogenerate, roomspec_to_room2)
{   
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r);

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample room name"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}
*/
/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with items field not NULL 
Test(autogenerate, roomspec_to_room3)
{   
    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", sample_item);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r);

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample room name"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == sample_item);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}
*/
/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with paths and items fields not NULL 
Test(autogenerate, roomspec_to_room4)
{   
    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", sample_item);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r);

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample room name"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == sample_item);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}*/

/* Checks that room_generate returns FAILURE when the current room of the 
 * game has a single outward path (i.e. not a dead end) 
Test(autogenerate, room_generate_failure_one)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Test Case 1: Game with 1 outward path in its current room
    path_t *outward_path = path_new(sample_room1, "outward path to sample_room1");
    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, outward_path), 
        "Could not add outward_path, which leads to sample_room1");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 1, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Test 1 for a game with 1 outward path in its curr_room field
    cr_assert_eq(FAILURE, room_generate(g, sample_gencontext), 
        "room_generate() returned SUCCESS when it should have returned FAILURE");
}
*/
/* Checks that room_generate returns FAILURE when the current room of the 
 * game has two or more outward paths (i.e. not a dead end) 
Test(autogenerate, room_generate_failure_multiple)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, path_to_room), 
        "Could not add path_to_room (path), which leads to sample_room1");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    // Test Case 1: Game with 2 outward paths in its current room
    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, path_to_room2), 
        "Could not add path_to_room2, which leads to sample_room2");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Test 1 for a game with 2 outward paths in its curr_room field
    cr_assert_eq(FAILURE, room_generate(g, sample_gencontext), 
        "room_generate(): game has 2 outward paths in curr_room, should have returned FAILURE");

    path_t *outward_path3 = path_new(sample_room1, "outward path to sample_room1");

    // Test Case 2: Game with 3 outward paths in its current room
    cr_assert_eq(SUCCESS, add_path_to_room(g->curr_room, outward_path3), 
        "Could not add path_to_room2, which leads to sample_room2");

    // Test 2 for a game with 3 outward paths in its curr_room field
    cr_assert_eq(FAILURE, room_generate(g, sample_gencontext), 
        "room_generate(): game has 3 outward paths in curr_room, should have returned FAILURE");
}
*/
/* One roomspec case: Checks that, given a game, context (gencontext_t), and room_id, 
 * room_generate correctly creates a room from the head of the context 
 * and adds it to the game via a path (only if game->curr_room is a dead end) 
Test(autogenerate, room_generate_success_one)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 1 roomspec case
    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext), 
        "room_generate() returned FAILURE when it should have returned SUCCESS");
}
*/
/* 2 roomspec case: Checks that, given a game, context (gencontext_t), and room_id, 
 * room_generate correctly creates a room from the head of the context 
 * and adds it to the game via a path (only if game->curr_room is a dead end) 
Test(autogenerate, room_generate_success_two)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // 2 roomspec case
    speclist_t *tail = speclist_new(sample_roomspec2);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, tail);

    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext), 
        "room_generate() returned FAILURE when it should have returned SUCCESS");
}
*/
/* 3 roomspec case: Checks that, given a game, context (gencontext_t), and room_id, 
 * room_generate correctly creates a room from the head of the context 
 * and adds it to the game via a path (only if game->curr_room is a dead end) 
Test(autogenerate, room_generate_success_three)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec3 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
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

    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext), 
        "room_generate() returned FAILURE when it should have returned SUCCESS");
}
*/
/* Checks that multi_room_generate returns FAILURE if the current room of the 
 * given game is not a dead end, i.e. there are outward paths 
Test(autogenerate, invalid_multi_room)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

    cr_assert_eq(any_paths(sample_room2), true, 
        "sample_room2 should have a path");

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Ensure game->curr_room has paths
    g->curr_room = sample_room2;

    cr_assert_eq(FAILURE, multi_room_generate(g, sample_gencontext));
}
*/
/* Checks that multi_room_generate successfully generates/adds rooms from a 
 * context (gencontext_t) struct's speclist field when one room is requested 
Test(autogenerate, valid_multi_room1)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

    cr_assert_eq(any_paths(sample_room2), true, 
        "sample_room2 should have a path");

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 1 roomspec case
    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;

    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext));
}
*/
/* Checks that multi_room_generate successfully generates/adds rooms from a 
 * context (gencontext_t) struct's speclist field when two rooms are requested 
Test(autogenerate, valid_multi_room2)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

    cr_assert_eq(any_paths(sample_room2), true, 
        "sample_room2 should have a path");

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 2 roomspec case
    speclist_t *tail = speclist_new(sample_roomspec2);
    cr_assert_not_null(tail, "Could not create new speclist");
    
    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, tail);

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;

    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext));
}
*/
/* Checks that multi_room_generate successfully generates/adds rooms from a 
 * context (gencontext_t) struct's speclist field when multiple (3) rooms are requested 
Test(autogenerate, valid_multi_room3)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

    cr_assert_eq(any_paths(sample_room2), true, 
        "sample_room2 should have a path");

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec3 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
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

    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext));
}*/
