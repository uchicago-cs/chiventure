#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "npc/rooms-npc.h"
#include "game-state/room.h"

/* Tests new() of npcs_in_room struct */
Test (npcs_in_room, new)
{
    npcs_in_room_t *npcs_in_room;

    npcs_in_room = npcs_in_room_new("test_room");

    cr_assert_not_null(npcs_in_room, "npcs_in_room_new() failed");

    cr_assert_str_eq(npcs_in_room->room_id, "test_room",
                "npcs_in_room_new() did not set room_id");

    cr_assert_null(npcs_in_room->npc_list,
                    "npcs_in_room_new() did not set npc_list");

    cr_assert_eq(npcs_in_room->num_of_npcs, 0,
                "npcs_in_room_new() did not set num_of_npcs");
}


/* Tests initialization of npcs_in_room struct */
Test (npcs_in_room, init)
{
    npcs_in_room_t *npcs_in_room = npcs_in_room_new("test room");

    int check = npcs_in_room_init(npcs_in_room, "test_room2");

    cr_assert_eq(check, SUCCESS, "npcs_in_room_init() failed");

    cr_assert_str_eq(npcs_in_room->room_id, "test_room2",
                "npcs_in_room_init() did not set room_id");

    cr_assert_eq(npcs_in_room->num_of_npcs, 0,
                "npcs_in_room_init() did not set num_of_npcs");
}


/* Tests freeing of npcs_in_room struct */
Test (npcs_in_room, free)
{
    npcs_in_room_t *npcs_in_room;
    int check;
    npcs_in_room =  npcs_in_room_new("test_room");

    check = npcs_in_room_free(npcs_in_room);
    cr_assert_eq(check, SUCCESS, "npcs_in_room_free() failed");
}


/* Tests add_npc_to_room function */
Test (npcs_in_room, add_npc_to_room)
{
    char *npc_id = "npc_test";
    npc_t *npc = npc_new(npc_id, "test npc", "test npc", NULL, NULL, false);
    npcs_in_room_t *npcs_in_room = npcs_in_room_new("test_room");
    int num_of_npcs_initial = npcs_in_room->num_of_npcs;

    int check1 = add_npc_to_room(npcs_in_room, npc);
    int num_of_npcs_final = npcs_in_room->num_of_npcs;

    cr_assert_eq(check1, SUCCESS, "add_npc_to_room() failed");

    npc_t *check2;
    HASH_FIND(hh_room, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check2);

    cr_assert_not_null(check2, "add_npc_to_room() failed,"
                                " could not find newly added npcs");

    cr_assert_str_eq(check2->npc_id,"npc_test", "add_npc_to_room()"
                            "did not set npc_id");

    cr_assert_eq(num_of_npcs_initial+1, num_of_npcs_final,
                 "add_npc_to_room() failed, incorrect number of npcs in room");
}


/* Tests delete_npc_from_room function */
Test (npcs_in_room, delete_npc_from_room)
{
    char *npc_id = "npc_test";
    npc_t *npc = npc_new(npc_id, "test npc", "test npc", NULL, NULL, false);
    npcs_in_room_t *npcs_in_room = npcs_in_room_new("test_room");
    int num_of_npcs_pre_add = npcs_in_room->num_of_npcs;

    int check1 = add_npc_to_room(npcs_in_room, npc);
    int num_of_npcs_post_add = npcs_in_room->num_of_npcs;

    cr_assert_eq(check1, SUCCESS, "add_npc_to_room() failed");
    cr_assert_eq(num_of_npcs_pre_add+1, num_of_npcs_post_add,
                 "add_npc_to_room() failed, incorrect number of npcs in room");

    int check2 = delete_npc_from_room(npcs_in_room, npc);
    int num_of_npcs_post_delete = npcs_in_room->num_of_npcs;

    cr_assert_eq(check2, SUCCESS, "delete_npc_from_room() failed");

    npc_t *check3;
    HASH_FIND(hh_room, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check3);

    cr_assert_null(check3, "delete_npc_from_room() failed,"
                           " found deleted npc in room");
    
    cr_assert_eq(num_of_npcs_post_add, num_of_npcs_post_delete + 1,
                 "delete_npc_from_room() failed, incorrect number of npcs in room");
}


/* tests the npcs_in_room_get_number function */
Test (npcs_in_room, npcs_in_room_get_number)
{
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = npcs_in_room_new("test_room");
    char *npc_id1 = "test_npc1";
    npc_t *test_npc1 = npc_new(npc_id1, "test npc", "test npc", NULL, NULL, false);
    int added_npc1 = add_npc_to_room(npcs_in_room,test_npc1);

    cr_assert_eq(added_npc1, SUCCESS, "add_npc_to_room() failed");

    char *npc_id2 = "test_npc2";
    npc_t *test_npc2 = npc_new(npc_id2, "test npc", "test npc", NULL, NULL, false);
    int added_npc2 = add_npc_to_room(npcs_in_room,test_npc2);

    cr_assert_eq(added_npc2, SUCCESS, "add_npc_to_room() failed");

    cr_assert_eq(npcs_in_room->num_of_npcs,2,"npcs_in_room_get_number() failed.");
}
