#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "rooms-npc.h"
#include "room.h"


/* Tests new() of npcs_in_room struct */
Test (npcs_in_room, new) {
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = npcs_in_room_new(1,"test_room");

    cr_assert_not_null(npcs_in_room, "npcs_in_room_new() failed");

    cr_assert_eq(npcs_in_room->room_id, 1,
                "npcs_in_room_new() did not set room_id");

	cr_assert_eq(npcs_in_room->room_name, "test_room",
                "npcs_in_room_new() did not set room_id");

	cr_assert_eq(npcs_in_room->num_of_npcs, 0,
                "npcs_in_room_new() did not set num_of_npcs");		
}


/* Tests new() of npc_mov struct */
Test (npc_mov, new) {
    npc_mov_t *npc_mov;
    room_t *test_room;
    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new("test_npc", MOV_DEF, test_room);

    cr_assert_not_null(npc_mov, "npc_mov_new() failed");

    cr_assert_eq(npc_mov->npc_id, "test_npc",
                "npc_mov_new() did not set npc_id");
    cr_assert_not_null(npc_mov->npc_mov_type->mov_def->npc_path,
                "npc_mov_new() did not set npc_path");
    cr_assert_eq(npc_mov->mov_type, MOV_DEF,
                "npc_mov_new() did not set mov_type");                 
	cr_assert_eq(npc_mov->track, "test_room",
                "npc_mov_new() did not set track");		
}


/* Tests initialization of npcs_in_room struct */
Test (npcs_in_room, init) {
    npcs_in_room_t *npcs_in_room;
    int check = npcs_in_room_init(&npcs_in_room, 1, "test_room");
     
    cr_assert_eq(check, SUCCESS, "npcs_in_room_init() failed"); 

	cr_assert_eq(npcs_in_room.room_id, 1,
                "npcs_in_room_init() did not set room_id");

    cr_assert_eq(npcs_in_room.room_name, "test_room",
                "npcs_in_room_init() did not set room_id");

	cr_assert_eq(npcs_in_room.num_of_npcs, 0,
                "npcs_in_room_init() did not set num_of_npcs");
}


/* Tests initialization of npc_mov struct */
Test (npc_mov, init) {
    npc_mov_t *npc_mov = malloc(sizeof(npc_mov_t));
        room_t *test_room;
    test_room = room_new("test_room", "test", "test test");
    int check = npc_mov_init(npc_mov,"test_npc", MOV_DEF, test_room);

    cr_assert_eq(check, SUCCESS, "npc_mov_init() failed"); 

    cr_assert_eq(npc_mov->npc_id, "test_npc",
                "npc_mov_new() did not set npc_id");
    cr_assert_not_null(npc_mov->npc_mov_type->mov_def->npc_path,
                "npc_mov_new() did not set npc_path");
    cr_assert_eq(npc_mov->mov_type, MOV_DEF,
                "npc_mov_new() did not set mov_type");                 
	cr_assert_eq(npc_mov->track, "test_room",
                "npc_mov_new() did not set track");	    
}


/* Tests freeing of npcs_in_room struct */
Test (npcs_in_room, free) { 
	npcs_in_room_t *npcs_in_room; 
	int check; 
	npcs_in_room =  npcs_in_room_new("test_room");
	
	check = npcs_in_room_free(npcs_in_room); 
	cr_assert_eq(check, SUCCESS, "npcs_in_room_free() failed"); 
}


/* Tests freeing of npcs_in_room struct */
Test (npc_mov, free) { 
	npc_mov_t *npc_mov; 
	int check; 
	npc_mov =  npc_new("test_room");
	
	check = npc_mov_free(npc_mov); 
	cr_assert_eq(check, SUCCESS, "npc_mov_free() failed"); 
}

/* Tests add_npc_to_room function */
Test (npcs_in_room, add_npc_to_room) {
    npc_t *npc = npc_new("npc_test", 20, NULL); 
    npcs_in_room_t *npcs_in_room = npcs_in_room_new(1, "test_room");
	int num_of_npcs_initial = npcs_in_room->num_of_npcs;

    int check1 = add_npc_to_room(npcs_in_room, npc);
	int num_of_npcs_final = npcs_int_room->num_of_npcs;

    cr_assert_eq(check1, SUCCESS, "add_npc_to_room() failed");

    npc_t *check2;
    HASH_FIND(hh, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check2);

    cr_assert_not_null(check2, "add_npc_to_room() failed,"
								" could not find newly added npcs");

	cr_assert_eq(num_of_npcs_initial+1,num_of_npcs_final,
				 "add_npc_to_room() failed, incorrect number of npcs in room");
}

/* tests the npcs_in_room_get_number function */
Test (npcs_in_room, npcs_in_room_get_number)
{
	npcs_in_room_t *npcs_in_room;
	npcs_in_room = npcs_in_room_new(1, "test_room");
	npc_t *test_npc1 = npc_new("test_npc1", 20, NULL);
	int added_npc1 = add_npc_to_room(npcs_in_room,test_npc1);

	cr_assert_eq(added_npc1, SUCCESS, "add_npc_to_room() failed");

	npc_t *test_npc2 = npc_new("test_npc2", 40, NULL);
	int added_npc2 = add_npc_to_room(npcs_in_room,test_npc2);

	cr_assert_eq(added_npc2, SUCCESS, "add_npc_to_room() failed");

	cr_asser_eq(npcs_in_room->2,2,"npcs_in_room_get_number() failed.");
}


/* Tests register_time_in_room function */
Test(npc_mov, register_time_in_room) {
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", INDEF_PATH, "test_room");
    int time = 60;

    int check1 = register_time_in_room(npc_mov, test_room, time);

    cr_assert_eq(check1, SUCCESS, "register_time_in_room() failed");

    time_in_room_hash_t  *indef_hash = 
                            npc_mov->npc_mov_type->mov_indef->room_time;

    time_in_room_t *check2;
    
    HASH_FIND(hh, indef_hash, "test_room", strlen("test_room"), check2);

    cr_assert_eq(check2->room_id, "test_room",
                "register_time_in_room() did not set room_id");
    cr_assert_eq(check2->room_id, time,
                "register_time_in_room() did not set time");
}


/* Tests extend_path_def fucntion */
Test(npc_mov, extend_path_def) {
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", INDEF_PATH, "test_room");
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_def(npc_mov, room_to_add);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");
}


/* Tests extend_path_indef function */
Test(npc_mov, extend_path_indef) {
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", INDEF_PATH, "test_room");
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_indef(npc_mov, room_to_add);

    cr_assert_eq(check1, SUCCESS, "extend_path_indef() failed");
}


/* Tests track_room function */
Test(npc_mov, track_room) {
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", INDEF_PATH, "test_room");

    char* room_id_track = track_room(npc_mov);

    cr_assert_eq(room_id_track, "test_roo ", "track_room() failed");
}


/* Tests reverse_path function */
Test(npc_mov, reverse_path) {
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new("test_npc", INDEF_PATH, "test_room");
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_def(npc_mov, room_to_add);

    cr_assert_eq(check1, SUCCESS, "extend_path_indef() failed");

    int check2 = reverse_path(npc_mov);

    cr_assert_eq(check2, SUCCESS, "reverse_path() failed");
}