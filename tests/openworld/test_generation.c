#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "sample_generation.h"

/* Tests the functions in sample_generation.h */

Test(sample_generation, enter_new_room1) {
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    room_t *sampleRoom2 = room_new("another string1", "another string2", "another string3");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    cr_assert_eq(enter_new_room(sampleRoom1, sampleRoom2), true, 
    "enter_new_room() interpreted two different rooms as the same");
}

Test(sample_generation, enter_new_room1) {
    room_t *sampleRoom = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    cr_assert_eq(enter_new_room(sampleRoom, sampleRoom), false, 
    "enter_new_room() interpreted two same rooms as different");
}