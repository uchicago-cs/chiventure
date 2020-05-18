#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_generation.h"

/* Tests the functions in sample_generation.h */

Test(autogenerate, any_paths1)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    cr_assert_eq(any_paths(sampleRoom1), false, 
    "anypaths(): Should not have any paths");
}

Test(autogenerate, any_paths2)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    room_t *sampleRoom2 = room_new("anotherString1", "anotherString2", "anotherString3");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room));

    cr_assert_eq(any_paths(sampleRoom2), true, 
    "anypaths(): Should have a path");
}

Test(autogenerate, any_paths2)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    room_t *sampleRoom2 = room_new("anotherString", "anotherString", "anotherString");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    room_t *sampleRoom3 = room_new("anotherString1", "anotherString2", "anotherString3");
    cr_assert_not_null(sampleRoom3, "sampleRoom3 is NULL");

    // Path to sampleRoom1
    path_t* path_to_room = path_new(sampleRoom1, "to sampleRoom1");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room));

    // Path to sampleRoom3
    path_t* path_to_room2 = path_new(sampleRoom3, "to sampleRoom3");
    assert (0 == add_path_to_room(sampleRoom2, path_to_room2));

    cr_assert_eq(any_paths(sampleRoom2), true, 
    "anypaths(): Should have paths");
}