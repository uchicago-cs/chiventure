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


/* Tests auto_gen_movement function */
Test(npc_mov, auto_gen_movement)
{
	/* 
	 * This test is based heavily off of the Test(path_actions, validate_path)
	 * contained in tests/action_management/test_path_actions.c
	 */
	
	/* DECLARE VARIABLES */
	chiventure_ctx_t *ctx_test;
	game_t *game_test;
	player_t *player_test;
	room_t *room_north, *room_south, *room_east, *room_west, *room_origin;
	npc_mov_t *mov_indef, *mov_def;
	int rc_indef, num_rooms_indef, rc_def, num_rooms_def, total_num_rooms;

	/* CREATE VARIABLE CONTENTS */
	ctx_test = chiventure_ctx_new(NULL);
	game_test = game_new("This is a test game!");
	player_test = player_new("player");
	room_origin = room_new("room_o", "origin room", "This is the room the player starts in.");
	room_north = room_new("room_n", "room north of origin", "This is the room north of the spawn.");
	room_south = room_new("room_s", "room south of origin", "This is the room south of the spawn.");
        room_east = room_new("room_e", "room east of origin", "This is the room east of the spawn.");
        room_west = room_new("room_w", "room west of origin", "This is the room west of the spawn.");
	mov_indef = npc_mov_new(NPC_MOV_INDEFINITE, room_origin);
	mov_def = npc_mov_new(NPC_MOV_DEFINITE, room_origin);


	/* FILL VARIABLE CONTENTS */
	add_player_to_game(game_test, player_test);
	set_curr_player(game_test, player_test);
	add_room_to_game(game_test, room_origin);
	add_room_to_game(game_test, room_north);
	add_room_to_game(game_test, room_south);
	add_room_to_game(game_test, room_east);
	add_room_to_game(game_test, room_west);
	/*create_connection(game_test, room_origin->room_id, room_north->room_id, "north");
	create_connection(game_test, room_north->room_id, room_origin->room_id, "origin");
	create_connection(game_test, room_origin->room_id, room_south->room_id, "south");
        create_connection(game_test, room_south->room_id, room_origin->room_id, "origin");
	create_connection(game_test, room_origin->room_id, room_east->room_id, "east");
        create_connection(game_test, room_east->room_id, room_origin->room_id, "origin");
	create_connection(game_test, room_origin->room_id, room_west->room_id, "west");
        create_connection(game_test, room_west->room_id, room_origin->room_id, "origin");*/
	
	/* TEST HELPER */

	total_num_rooms = get_num_rooms(game_test); // expected = 5
	cr_assert_eq(5, total_num_rooms,
			"The number of rooms is %d but get_num_rooms() says %d",
			5, total_num_rooms);
	
	/* TEST AUTO_GEN_MOVEMENT FOR INDEF */

	for(int i = 0; i < 10; i++)
	{
		rc_indef = auto_gen_movement(mov_indef, game_test);
		
		num_rooms_indef = get_npc_num_rooms(mov_indef);

		cr_assert_eq(SUCCESS, rc_indef, 
				"auto_gen_movement() failed for indefinite movement");
		cr_assert_geq(num_rooms_indef, 1,
				"The number of rooms in the npc mov struct is %d which is less than"
				"the actual amount, %d",
				num_rooms_indef, 1);
		cr_assert_leq(num_rooms_indef, 5,
				"The number of rooms in the npc mov struct is %d which is more than"
				"the actual amount, %d",);
		
	}

	/* TEST AUTO_GEN_MOVEMENT FOR DEF */

	for(int i = 0; i < 10; i++)
	{
		rc_def = auto_gen_movement(mov_def, game_test);
	
		cr_assert_eq(SUCCESS, rc_def,
                	        "auto_gen_movement() failed for definite movement");

	}

}
