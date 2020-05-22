#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "openworld/autogenerate.h"

/* Tests the functions in sample_generation.h */

/* Checks that a given room correctly interpreted as having no paths */
Test(autogenerate, any_paths1)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    cr_assert_eq(any_paths(sample_room1), false, 
        "anypaths(): Should not have any paths");
}

/* Checks that a room with one path is correctly interpreted as having 
 * one or more paths (any_paths() -> true) */
Test(autogenerate, any_paths2)
{
    room_t *sample_room1 = room_new("string1", "string2", "string3");

    room_t *sample_room2 = room_new("anotherString1", "anotherString2", "anotherString3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");
    assert (0 == add_path_to_room(sample_room2, path_to_room));

    cr_assert_eq(any_paths(sample_room2), true, 
        "anypaths(): Should have a path");
}

/* Checks that a room with two paths is correctly interpreted as having 
 * one or more paths (any_paths() -> true) */
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
}

/* Checks that a room with multiple (3) paths is correctly interpreted as 
 * having one or more paths (any_paths() -> true) */
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
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with NULL paths and items fields */
Test(autogenerate, roomspec_to_room1)
{
    roomspec_t *r = roomspec_new("short desc", "long desc", NULL, NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r, "room_id");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "room_id"), 0, "roomspec_new(): room_id not set");

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
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *r = roomspec_new("short desc", "long desc", NULL, path_to_room);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r, "room_id");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "room_id"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == NULL);
    t2 = (room->paths == path_to_room);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* Checks that, given a roomspec pointer, roomspec_to_room correctly returns a 
 * room pointer with items field not NULL */
Test(autogenerate, roomspec_to_room3)
{   
    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    roomspec_t *r = roomspec_new("short desc", "long desc", sample_item, NULL);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r, "room_id");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "room_id"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == sample_item);
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

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *r = roomspec_new("short desc", "long desc", sample_item, path_to_room);
    game_t *g = game_new("start desc");
    room_t *room = roomspec_to_room(g, r, "one more");

    cr_assert_not_null(room, "roomspec_new(): The returned room is NULL");
    cr_assert_not_null(room->room_id, "roomspec_new(): room_id field is NULL");

    // Hash handle and room_id fields will be unique
    cr_assert_eq(strcmp(room->short_desc, "short desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->long_desc, "long desc"), 0, 
        "roomspec_to_room(): short desc not set");

    cr_assert_eq(strcmp(room->room_id, "one more"), 0, "roomspec_new(): room_id not set");

    bool t1, t2;
    t1 = (room->items == sample_item);
    t2 = (room->paths == path_to_room);

    cr_assert_eq(t1, true, "room->items not set by roomspec_to_room()");
    cr_assert_eq(t2, true, "room->paths not set by roomspec_to_room()");
}

/* One roomspec case: Checks that, given a game, context (gencontext_t), and room_id, 
 * room_generate correctly creates a room from the head of the context 
 * and adds it to the game via a path (only if game->curr_room is a dead end) */
Test(autogenerate, room_generate_success1)
{
    game_t *g = game_new("start desc");
    g->curr_room = room_new("room with no outward paths", "short desc", "long desc");

    item_t *sample_item = item_new("item_id", "short_desc", "long_desc");

    room_t *sample_room1 = room_new("string1", "string2", "string3");

    // Path to sample_room1
    path_t* path_to_room = path_new(sample_room1, "to sample_room1");

    roomspec_t *sample_roomspec = roomspec_new("short_desc", "long_desc", sample_item, path_to_room);
    cr_assert_not_null(sample_roomspec, "sample_roomspec should not be NULL");

    speclist_t *sample_speclist = speclist_new(sample_roomspec);
    cr_assert_not_null(sample_speclist, "sample_speclist should not be NULL");

    room_t *sample_room2 = room_new("string_1", "string_2", "string_3");

    // Path to sample_room2
    path_t* path_to_room2 = path_new(sample_room2, "to sample_room2");

    gencontext_t *sample_gencontext = gencontext_new(path_to_room2, 5, 0, 0, sample_speclist);
    cr_assert_not_null(sample_gencontext, "sample_gencontext should not be NULL");

    cr_assert_eq(SUCCESS, room_generate(g, sample_gencontext, "room_id"), 
        "room_generate() failed when it should have succeeded");
}

// FAILURE CASE with 1, another one with 2, TWO ROOM CASE, THREE ROOM CASE