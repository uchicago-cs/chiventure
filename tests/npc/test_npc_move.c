#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "npc/npc_move.h"
#include "game-state/room.h"

/* Tests new() of npc_mov struct */
Test (npc_mov, new)
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room);

    cr_assert_not_null(npc_mov, "npc_mov_new() failed");

    cr_assert_eq(npc_mov->mov_type, NPC_MOV_DEFINITE,
                "npc_mov_new() did not set mov_type");
    cr_assert_str_eq(npc_mov->track, "test_room",
                "npc_mov_new() did not set track");
}


/* Tests initialization of npc_mov struct */
Test (npc_mov, init)
{
    room_t *test_room1 = room_new("test_room1", "test1", "test test1");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room1);

    room_t *test_room2;
    test_room2 = room_new("test_room", "test", "test test");
    int check = npc_mov_init(npc_mov, NPC_MOV_DEFINITE, test_room2);

    cr_assert_eq(check, SUCCESS, "npc_mov_init() failed");

    cr_assert_eq(npc_mov->mov_type, NPC_MOV_DEFINITE,
                "npc_mov_new() did not set mov_type");
    cr_assert_str_eq(npc_mov->track, "test_room",
                "npc_mov_new() did not set track");
}


/* Tests freeing of npcs_in_room struct */
Test (npc_mov, free)
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    int check;

    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room);

    check = npc_mov_free(npc_mov);
    cr_assert_eq(check, SUCCESS, "npc_mov_free() failed");
}


/* Tests register_npc_room_time function */
Test(npc_mov, register_npc_room_time)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room);
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
Test(npc_mov, extend_path_definite)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_definite(npc_mov, room_to_add);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    cr_assert_str_eq(npc_mov->npc_mov_type.npc_mov_definite->npc_path->next->room->room_id,
                     "room_to_add","extend_path_def() failed");
}


/* Tests extend_path_indef function */
Test(npc_mov, extend_path_indefinite)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_indefinite(npc_mov, room_to_add, 10);

    cr_assert_eq(check1, SUCCESS, "extend_path_indef() failed");

    cr_assert_str_eq(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path->next->room->room_id,
                     "room_to_add","extend_path_indef() failed");
}


/* Tests track_room function */
Test(npc_mov, track_room)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room);

    char* room_id_track = track_room(npc_mov);

    cr_assert_str_eq(room_id_track, "test_room", "track_room() failed");
}


/* Tests move_npc_def function */
Test(npc_mov, move_npc_definite)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room);
    room_t *room_to_add1 = room_new("room_to_add1", "add1", "added room1");
    room_t *room_to_add2 = room_new("room_to_add2", "add2", "added room2");

    int check1 = extend_path_definite(npc_mov, room_to_add1);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    check1 = extend_path_definite(npc_mov, room_to_add2);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    int check2 = move_npc_definite(npc_mov);

    cr_assert_eq(check2, 2, "move_npc_def() failed");

    cr_assert_str_eq(npc_mov->track,"room_to_add1",
                    "move_npc_def() failed to move once");

    check2 = move_npc_definite(npc_mov);

    cr_assert_str_eq(npc_mov->track,"room_to_add2",
                    "move_npc_def() failed to move twice");
}

/* Tests reverse_path function */
Test(npc_mov, reverse_path)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room);
    room_t *room_to_add1 = room_new("room_to_add1", "add1", "added room1");
    room_t *room_to_add2 = room_new("room_to_add2", "add2", "added room2");

    int check1 = extend_path_definite(npc_mov, room_to_add1);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    check1 = extend_path_definite(npc_mov, room_to_add2);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    int check2 = move_npc_definite(npc_mov);

    cr_assert_eq(check2, 2, "move_npc_def() failed");

    int check3 = reverse_path(npc_mov);

    cr_assert_eq(check3, SUCCESS, "reverse_path() failed");

    check2 = move_npc_definite(npc_mov);

    cr_assert_str_eq(npc_mov->track,"test_room",
                    "reverse_path() failed to track room");
}
