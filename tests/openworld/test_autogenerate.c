#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "openworld/autogenerate.h"

/* Tests the functions in sample_generation.h */

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with NULL paths and items fields */
Test(autogenerate, roomspec_to_room1)
{
    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(r, "sample_room_id");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample_room_id"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with paths field not NULL */
Test(autogenerate, roomspec_to_room2)
{   
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");

    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(r, "sample_room_id");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample_room_id"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with items field not NULL */
Test(autogenerate, roomspec_to_room3)
{   
    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");
    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", sample_room1->items);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(r, "sample_room_id");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample_room_id"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items != sample_room1->items); // Deep copy
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with paths and items fields not NULL */
Test(autogenerate, roomspec_to_room4)
{   
    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");
    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");

    roomspec_t *r = roomspec_new("sample room name", "short desc", "long desc", sample_room1->items);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(r, "sample_room_id");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "sample_room_id"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items != sample_item); // Deep copy
    t2 = (room->paths == NULL);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
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

    cr_assert_eq(FAILURE, room_generate(g, sample_gencontext, "sample_room_id"), 
        "room_generate() returned SUCCESS when it should have returned FAILURE");
}

/* One roomspec case: Checks that, given a game, context (gencontext_t), and room_id, 
 * room_generate correctly creates a room from the head of the context 
 * and adds it to the game via a path (if game->curr_room has available path directions) */
Test(autogenerate, room_generate_success_one)
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

    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext, "sample_room_id"), 
        "room_generate() returned FAILURE when it should have returned SUCCESS");
}

/* 2 roomspec case: Checks that, given a game, context (gencontext_t), and room_id, 
 * room_generate correctly creates a room from the head of the context 
 * and adds it to the game via a path (only if game->curr_room is a dead end) */
Test(autogenerate, room_generate_success_two)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec2, "sample_roomspec2 should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // 2 roomspec case
    speclist_t *tail = speclist_new(sample_roomspec2);
    cr_assert_not_null(tail, "Could not create new speclist");

    // Doubly linked
    speclist_t *head = NULL;
    DL_APPEND(head, sample_gencontext->speclist);
    DL_APPEND(sample_gencontext->speclist, tail);

    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext, "sample_room_id"), 
        "room_generate() returned FAILURE when it should have returned SUCCESS");
}

/* 3 roomspec case: Checks that, given a game, context (gencontext_t), and room_id, 
 * room_generate correctly creates a room from the head of the context 
 * and adds it to the game via a path (only if game->curr_room is a dead end) */
Test(autogenerate, room_generate_success_three)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec2, "sample_roomspec2 should not be NULL");

    roomspec_t *sample_roomspec3 = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec3, "sample_roomspec3 should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

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

    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext, "sample_room_id"), 
        "room_generate() returned FAILURE when it should have returned SUCCESS");
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
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

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

    cr_assert_eq(FAILURE, multi_room_generate(g, sample_gencontext, "sample_room_id"), 
        "multi_room_generate() returned SUCCESS instead of FAILURE");
}

/* Checks that multi_room_generate successfully generates/adds rooms from a 
 * context (gencontext_t) struct's speclist field when one room is requested */
Test(autogenerate, valid_multi_room1)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 1 roomspec case
    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;

    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext, "sample_room_id"), 
        "multi_room_generate() returned FAILURE instead of SUCCESS");
}

/* Checks that multi_room_generate successfully generates/adds rooms from a 
 * context (gencontext_t) struct's speclist field when two rooms are requested */
Test(autogenerate, valid_multi_room2)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");
    item_t *sample_item2 = item_new("item_id2", "short_desc", "long_desc");
    item_t *sample_item3 = item_new("item_id3", "short_desc", "long_desc");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

    roomspec_t *sample_roomspec = roomspec_new("sample name", "short_desc", "long_desc", sample_item);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    // 1 roomspec case
    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 1, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    // Ensure game->curr_room does not have paths
    g->curr_room = sample_room1;

    roomspec_t *sample_roomspec2 = roomspec_new("sample name", "short_desc", "long_desc", sample_item2);
    cr_assert_not_null(sample_roomspec2, "sample_roomspec2 should not be NULL");

    roomspec_t *sample_roomspec3 = roomspec_new("sample name", "short_desc", "long_desc", sample_item3);
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

    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext, "sample_room_id"), 
        "multi_room_generate() returned FAILURE instead of SUCCESS");
}

/* Checks that multi_room_generate successfully generates/adds rooms from a 
 * context (gencontext_t) struct's speclist field when multiple (3) rooms are requested */
Test(autogenerate, valid_multi_room3)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "NORTH");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "NORTH");
    assert (SUCCESS == add_path_to_room(sample_room2, path_to_room));

    game_t *g = game_new("start desc");

    cr_assert_eq(SUCCESS, add_room_to_game(g, sample_room2), "Could not add room sample_room2 to game g");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    cr_assert_eq(SUCCESS, add_item_to_room(sample_room1, sample_item), "Could not add item to room");

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

    cr_assert_eq(SUCCESS, multi_room_generate(g, sample_gencontext, "sample_room_id"));
}