#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "npc/rooms-npc.h"
#include "npc/npc.h"
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


/* Tests new() of npc_mov struct */
Test (npc_mov, new)
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new("test_npc", NPC_MOV_DEFINITE, test_room);

    cr_assert_not_null(npc_mov, "npc_mov_new() failed");

    cr_assert_str_eq(npc_mov->npc_id, "test_npc",
                "npc_mov_new() did not set npc_id");
    cr_assert_eq(npc_mov->mov_type, NPC_MOV_DEFINITE,
                "npc_mov_new() did not set mov_type");
    cr_assert_str_eq(npc_mov->track, "test_room",
                "npc_mov_new() did not set track");
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


/* Tests initialization of npc_mov struct */
Test (npc_mov, init)
{
    room_t *test_room1 = room_new("test_room1", "test1", "test test1");
    npc_mov_t *npc_mov = npc_mov_new("test_npc1", NPC_MOV_DEFINITE, test_room1);

    room_t *test_room2;
    test_room2 = room_new("test_room", "test", "test test");
    int check = npc_mov_init(npc_mov,"test_npc2", NPC_MOV_DEFINITE, test_room2);

    cr_assert_eq(check, SUCCESS, "npc_mov_init() failed");

    cr_assert_str_eq(npc_mov->npc_id, "test_npc2",
                "npc_mov_new() did not set npc_id");
    cr_assert_eq(npc_mov->mov_type, NPC_MOV_DEFINITE,
                "npc_mov_new() did not set mov_type");
    cr_assert_str_eq(npc_mov->track, "test_room",
                "npc_mov_new() did not set track");
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


/* Tests freeing of npcs_in_room struct */
Test (npc_mov, free)
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    int check;

    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new("test_npc", NPC_MOV_DEFINITE, test_room);

    check = npc_mov_free(npc_mov);
    cr_assert_eq(check, SUCCESS, "npc_mov_free() failed");
}


/* Tests add_npc_to_room function */
Test (npcs_in_room, add_npc_to_room)
{
    //stats_t *stats = stats_new("npc_test_stat", 20);
    npc_t *npc = npc_new("npc_test", "test npc", "test npc", 100, NULL);
    npcs_in_room_t *npcs_in_room = npcs_in_room_new("test_room");
    int num_of_npcs_initial = npcs_in_room->num_of_npcs;

    int check1 = add_npc_to_room(npcs_in_room, npc);
    int num_of_npcs_final = npcs_in_room->num_of_npcs;

    cr_assert_eq(check1, SUCCESS, "add_npc_to_room() failed");

    npc_t *check2;
    HASH_FIND(hh, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check2);

    cr_assert_not_null(check2, "add_npc_to_room() failed,"
                                " could not find newly added npcs");

    cr_assert_str_eq(check2->npc_id,"npc_test", "add_npc_to_room()"
                            "did not set npc_id");

    cr_assert_eq(num_of_npcs_initial+1, num_of_npcs_final,
                 "add_npc_to_room() failed, incorrect number of npcs in room");
}


/* tests the npcs_in_room_get_number function */
Test (npcs_in_room, npcs_in_room_get_number)
{
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = npcs_in_room_new("test_room");
    npc_t *test_npc1 = npc_new("test_npc1", "test npc", "test npc", 100, NULL);
    int added_npc1 = add_npc_to_room(npcs_in_room,test_npc1);

    cr_assert_eq(added_npc1, SUCCESS, "add_npc_to_room() failed");

    npc_t *test_npc2 = npc_new("test_npc2", "test npc", "test npc", 100, NULL);
    int added_npc2 = add_npc_to_room(npcs_in_room,test_npc2);

    cr_assert_eq(added_npc2, SUCCESS, "add_npc_to_room() failed");

    cr_assert_eq(npcs_in_room->num_of_npcs,2,"npcs_in_room_get_number() failed.");
}


/* Tests register_npc_room_time function */
Test(npc_mov, register_npc_room_time)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", NPC_MOV_INDEFINITE, test_room);
    int time = 60;

    int check1 = register_npc_room_time(npc_mov, test_room, time);

    cr_assert_eq(check1, SUCCESS, "register_npc_room_time() failed");

    npc_room_time_t *check2;


    HASH_FIND(hh, npc_mov->npc_mov_type.npc_mov_indefinite->room_time,
                 test_room->room_id, strlen(test_room->room_id),
                 check2);

    cr_assert_not_null(check2, "register_npc_room_time() failed");

    cr_assert_str_eq(check2->room_id, "test_room",
                "register_npc_room_time() did not set room_id");
    cr_assert_eq(check2->time, time,
                "register_npc_room_time() did not set time");
}


/* Tests extend_path_def fucntion */
Test(npc_mov, extend_path_def) 
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", NPC_MOV_DEFINITE, test_room);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_def(npc_mov, room_to_add);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    cr_assert_str_eq(npc_mov->npc_mov_type.npc_mov_definite->npc_path->next->room->room_id,
                     "room_to_add","extend_path_def() failed");
}


/* Tests extend_path_indef function */
Test(npc_mov, extend_path_indef)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", NPC_MOV_INDEFINITE, test_room);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_indef(npc_mov, room_to_add, 10);

    cr_assert_eq(check1, SUCCESS, "extend_path_indef() failed");
}


/* Tests track_room function */
Test(npc_mov, track_room)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", NPC_MOV_INDEFINITE, test_room);

    char* room_id_track = track_room(npc_mov);

    cr_assert_str_eq(room_id_track, "test_room", "track_room() failed");
}


/* Tests reverse_path function */
Test(npc_mov, reverse_path)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", NPC_MOV_DEFINITE, test_room);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_def(npc_mov, room_to_add);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    int check2 = reverse_path(npc_mov);

    cr_assert_eq(check2, SUCCESS, "reverse_path() failed");
}

Test(npc_mov, move_npc_def)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", NPC_MOV_DEFINITE, test_room);
    room_t *room_to_add1 = room_new("room_to_add1", "add1", "added room1");
    room_t *room_to_add2 = room_new("room_to_add2", "add2", "added room2");

    int check1 = extend_path_def(npc_mov, room_to_add1);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    check1 = extend_path_def(npc_mov, room_to_add2);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    int check2 = move_npc_def(npc_mov);

    cr_assert_eq(check2, 2, "move_npc_def() failed");
}