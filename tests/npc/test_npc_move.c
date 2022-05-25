#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "npc/npc_move.h"
#include "npc/npc.h"
#include "game-state/room.h"
#include "game-state/game.h"

/* Creates a sample class. Taken from test_class.c */
class_t *generate_test_class2()
{
    class_t* c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
               " relying on physical strength and years of training to "
               "deal with any obstacle. Mechanically, the warrior focuses "
               "on up-close physical damage with weapons and survives enemy "
               "attacks using heavy armor.\n";

    stats_global_t *global_speed = stats_global_new("speed", 200);
    stats_hash_t *stats = NULL;
    stats_t *speed_stat = malloc(sizeof(stats_t));
    char *the_key = malloc(sizeof(char) * 8);
    strcpy(the_key, "speed");
    speed_stat->key = the_key;
    speed_stat->global = global_speed;
    speed_stat->val = 150;
    speed_stat->max = 200;
    speed_stat->modifier = 1;
    HASH_ADD(hh, stats, key, strlen(the_key), speed_stat);

    c = class_new(name, shortdesc, longdesc, NULL, stats, NULL);
    return c;
}

/* Tests new() of npc_mov struct */
Test (npc_mov, new)
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room->room_id, 0);

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
    npc_mov_t *npc_mov;
    npc_mov = malloc(sizeof(npc_mov_t));
    memset(npc_mov, 0, sizeof(npc_mov_t));
    npc_mov->track = malloc(MAX_ID_LEN);

    int check = npc_mov_init(npc_mov, NPC_MOV_DEFINITE, test_room1->room_id, 0);
    cr_assert_eq(check, SUCCESS, "npc_mov_init() failed");

    cr_assert_eq(npc_mov->mov_type, NPC_MOV_DEFINITE,
                 "npc_mov_init() did not set mov_type");
    cr_assert_str_eq(npc_mov->track, "test_room1",
                     "npc_mov_init() did not set track");

    npc_mov_t *npc_mov2 = malloc(sizeof(npc_mov_t));
    memset(npc_mov2, 0, sizeof(npc_mov_t));
    npc_mov2->track = malloc(MAX_ID_LEN);
    int check2 = npc_mov_init(npc_mov2, NPC_MOV_INDEFINITE, test_room1->room_id, 10);
    cr_assert_eq(npc_mov2->path->room_time->assigned_time, 10,
                 "npc_mov_init() failed to set assigned_time");
}


/* Tests freeing of npc_mov struct */
Test (npc_mov, free)
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    int check;

    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room->room_id, 0);

    check = npc_mov_free(npc_mov);
    cr_assert_eq(check, SUCCESS, "npc_mov_free() failed");
}


/* Tests extend_path_def fucntion */
Test(npc_mov, extend_path_definite)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room->room_id, 0);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_definite(npc_mov, room_to_add->room_id);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    cr_assert_str_eq(npc_mov->path->next->room_id,
                     "room_to_add","extend_path_def() failed");
}


/* Tests extend_path_indef function */
Test(npc_mov, extend_path_indefinite)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room->room_id, 10);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check1 = extend_path_indefinite(npc_mov, room_to_add->room_id, 20);

    cr_assert_eq(check1, SUCCESS, "extend_path_indef() failed");
    cr_assert_str_eq(npc_mov->path->next->room_id,
                     "room_to_add","extend_path_indef() failed");
    cr_assert_eq(npc_mov->path->next->room_time->assigned_time,
                 20, "extend_path_indef() failed");
}

/* Tests get_npc_num_rooms function for definite move */
Test(npc_mov, get_npc_num_rooms_def)
{
    room_t *test_room = room_new("test room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room->room_id, 0);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check = extend_path_definite(npc_mov, room_to_add->room_id);

    cr_assert_eq(check, SUCCESS, "extend_path_def() failed");

    int get = get_npc_num_rooms(npc_mov);

    cr_assert_eq(get, 2, "number of rooms in NPC path is %d. "
                 "get_npc_num_rooms() returned %d.",
                 2, get);
}


/* Tests get_npc_num_rooms function for indefinite move */
Test(npc_mov, get_npc_num_rooms_indef)
{
    room_t *test_room = room_new("test room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room->room_id, 5);
    room_t *room_to_add = room_new("room_to_add", "add", "added room");

    int check = extend_path_indefinite(npc_mov, room_to_add->room_id, 10);

    cr_assert_eq(check, SUCCESS, "extend_path_indef() failed");

    int get = get_npc_num_rooms(npc_mov);

    cr_assert_eq(get, 2, "number of rooms in NPC path is %d. "
                 "get_npc_num_rooms() returned %d",
                 2, get);
}


/* Tests get_npc_curr_room_id and get_next_npc_room_id functions */
Test(npc_mov, get_npc_room_id)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room->room_id, 5);
    cr_assert_eq(extend_path_indefinite(npc_mov, "test2", 10), SUCCESS,
                 "extend_path_indef() failed");

    char* room_id_track = get_npc_curr_room_id(npc_mov);
    cr_assert_str_eq(room_id_track, "test_room", "get_npc_curr_room_id() failed");

    room_id_track = get_next_npc_room_id(npc_mov);
    cr_assert_str_eq(room_id_track, "test2", "get_next_npc_room_id() failed");
}

/* Tests get_npc_num_rooms function */
Test(npc_mov, get_npc_num_rooms)
{
    room_t *room1 = room_new("r1", "room1", "room one");
    room_t *room2 = room_new("r2", "room2", "room two");
    room_t *room3 = room_new("r3", "room3", "room three");

    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, room1->room_id, 0);
    cr_assert_eq(extend_path_definite(npc_mov, room2->room_id), SUCCESS,
                 "extend_path_def() failed");
    cr_assert_eq(extend_path_definite(npc_mov, room3->room_id), SUCCESS,
                 "extend_path_def()2 failed");
    cr_assert_eq(extend_path_definite(npc_mov, room1->room_id), SUCCESS,
                 "extend_path_def()3 failed");

    cr_assert_eq(get_npc_num_rooms(npc_mov), 4, "get_npc_num_rooms() failed");
}
/* Tests move_npc_mov function for definite NPCs */
Test(npc_mov, move_npc_mov_def)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room->room_id, 0);
    room_t *room_to_add1 = room_new("room_to_add1", "add1", "added room1");
    room_t *room_to_add2 = room_new("room_to_add2", "add2", "added room2");

    int check1 = extend_path_definite(npc_mov, room_to_add1->room_id);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    check1 = extend_path_definite(npc_mov, room_to_add2->room_id);

    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    int check2 = move_npc_mov(npc_mov);

    cr_assert_eq(check2, SUCCESS, "move_npc_mov() failed");

    cr_assert_str_eq(npc_mov->track,"room_to_add1",
                     "move_npc_mov() failed to move once");

    check2 = move_npc_mov(npc_mov);

    cr_assert_str_eq(npc_mov->track,"room_to_add2",
                     "move_npc_mov() failed to move twice");

    int check3 = move_npc_mov(npc_mov);

    cr_assert_str_eq(npc_mov->track, "room_to_add2",
                     "move_npc_mov() failed to stay in place");
    cr_assert_eq(check3, FAILURE, "move_npc_mov didn't keep NPC in place");
}


/* Tests move_npc_mov function for indefinite NPCs */
Test(npc_mov, move_npc_mov_indef)
{
    int time = 10;
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room->room_id, 5);
    room_t *room_to_add1 = room_new("room_to_add1", "add1", "added room1");
    room_t *room_to_add2 = room_new("room_to_add2", "add2", "added room2");

    int check1 = extend_path_indefinite(npc_mov, room_to_add1->room_id, time);
    cr_assert_eq(check1, SUCCESS, "extend_path_indefinite() failed");

    check1 = extend_path_indefinite(npc_mov, room_to_add2->room_id, time);

    cr_assert_eq(check1, SUCCESS, "extend_path_indefinite() failed");

    int check2 = move_npc_mov(npc_mov);

    cr_assert_eq(check2, SUCCESS, "move_npc_mov() failed");

    cr_assert_str_eq(npc_mov->track,"room_to_add1",
                     "move_npc_mov() failed to move once");

    check2 = move_npc_mov(npc_mov);

    cr_assert_str_eq(npc_mov->track,"room_to_add2",
                     "move_npc_mov() failed to move twice");

    int check3 = move_npc_mov(npc_mov);

    cr_assert_str_eq(npc_mov->track, "room_to_add2",
                     "move_npc_mov() failed to stay in place");
    cr_assert_eq(check3, SUCCESS, "move_npc_mov failed to reverse path");

    int check4 = move_npc_mov(npc_mov);

    cr_assert_str_eq(npc_mov->track,"room_to_add1",
                     "move_npc_mov() failed to move after path reversal");
    cr_assert_eq(check4, SUCCESS, "move_npc_mov() failed to move");
}


/* Tests flip_npc_path_direction function */
Test(npc_mov, flip_npc_path_direction)
{
    room_t *test_room = room_new("test_room", "test", "test test");
    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room->room_id, 0);
    room_t *room_to_add1 = room_new("room_to_add1", "add1", "added room1");
    room_t *room_to_add2 = room_new("room_to_add2", "add2", "added room2");

    int check1 = extend_path_definite(npc_mov, room_to_add1->room_id);
    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    check1 = extend_path_definite(npc_mov, room_to_add2->room_id);
    cr_assert_eq(check1, SUCCESS, "extend_path_def() failed");

    int check2 = move_npc_mov(npc_mov);
    cr_assert_eq(check2, SUCCESS, "move_npc_mov() failed");

    int check3 = flip_npc_path_direction(npc_mov);
    cr_assert_eq(check3, SUCCESS, "flip_npc_path_direction() failed");
    cr_assert_eq(npc_mov->npc_path_direction, NPC_MOV_REVERSED, "flip_npc_path_direction() failed to reverse path");

    check2 = move_npc_mov(npc_mov);

    cr_assert_str_eq(npc_mov->track,"test_room",
                     "flip_npc_path_direction() failed to track room");
}

/* Tests auto_gen_movement for definite movement function */
Test(npc_mov, auto_gen_movement_definite)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "room1 short", "room1 long long long");
    room_t *room2 = room_new("room2", "room2 short", "room2 long long long");
    room_t *room3 = room_new("room3", "room3 short", "room3 long long long");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    int cnt = 0;
    int rc, num_rooms_in_npc;
    room_t *curr_room;
    room_list_t *all_rooms = get_all_rooms(game);
    char *curr_room_id;
    class_t *c = generate_test_class2();

    room_t *test_room = room_new("test_room", "test", "test test");
    add_room_to_game(game, test_room);

    npc_mov_t* npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room->room_id, 0);
    npc_t *npc = npc_new("test", "testnpc", "test npc", c, npc_mov, FRIENDLY);

    rc = auto_gen_movement(npc, all_rooms);
    npc_path_dll_t *elt;

    DL_FOREACH(npc_mov->path, elt)
    {
        cnt++;
        curr_room_id = elt->room_id;
        HASH_FIND(hh, game->all_rooms, curr_room_id,
                  strnlen(curr_room_id, MAX_ID_LEN), curr_room);
        if (!strncmp(curr_room_id, "room1", MAX_ID_LEN))
        {
            cr_assert_str_eq(get_ldesc(curr_room), "room1 long long long",
                             "ldesc does not correspond");
        }
        else if (!strncmp(curr_room_id, "room2", MAX_ID_LEN))
        {
            cr_assert_str_eq(get_ldesc(curr_room), "room2 long long long",
                             "ldesc does not correspond");
        }
        else if (!strncmp(curr_room_id, "room3", MAX_ID_LEN))
        {
            cr_assert_str_eq(get_ldesc(curr_room), "room3 long long long",
                             "ldesc does not correspond");
        }
    }

    num_rooms_in_npc = get_npc_num_rooms(npc_mov);

    cr_assert_eq(cnt, num_rooms_in_npc, "room_count returns %d, "
                 "but there should be %d rooms in npc_mov",
                 cnt, num_rooms_in_npc);

    cr_assert_eq(npc_mov_free(npc_mov),
                 SUCCESS, "npc_mov_free() failed");

    game_free(game);
}

Test(npc_mov, auto_gen_movement_indefinite)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "room1 short", "room1 long long long");
    room_t *room2 = room_new("room2", "room2 short", "room2 long long long");
    room_t *room3 = room_new("room3", "room3 short", "room3 long long long");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    int cnt = 0;
    int rc, num_rooms_in_npc;
    room_t *curr_room;
    char *curr_room_id;
    class_t *c = generate_test_class2();

    room_t *test_room = room_new("test_room", "test", "test test");
    add_room_to_game(game, test_room);

    npc_mov_t *npc_mov = npc_mov_new(NPC_MOV_INDEFINITE, test_room->room_id, 60);
    npc_t *npc = npc_new("test", "testnpc", "test npc", c, npc_mov, FRIENDLY);

    rc = auto_gen_movement(npc, get_all_rooms(game));
    npc_path_dll_t *elt;

    DL_FOREACH(npc_mov->path, elt)
    {
        cnt++;
        curr_room_id = elt->room_id;
        HASH_FIND(hh, game->all_rooms, curr_room_id, strlen(curr_room_id), curr_room);
        if (strncmp(curr_room->room_id, "room1", MAX_ID_LEN) == 0)
        {
            cr_assert_str_eq(get_ldesc(curr_room), "room1 long long long",
                             "ldesc does not correspond");
        }
        else if (!strncmp(curr_room->room_id, "room2", MAX_ID_LEN))
        {
            cr_assert_str_eq(get_ldesc(curr_room), "room2 long long long",
                             "ldesc does not correspond");
        }
        else if (!strncmp(curr_room->room_id, "room3", MAX_ID_LEN))
        {
            cr_assert_str_eq(get_ldesc(curr_room), "room3 long long long",
                             "ldesc does not correspond");
        }
    }

    num_rooms_in_npc = get_npc_num_rooms(npc->movement);
    cr_assert_eq(cnt, num_rooms_in_npc,
                 "room_count returns %d, but there should be %d rooms in npc_mov",
                 cnt, num_rooms_in_npc);

    cr_assert_eq(npc_mov_free(npc_mov), SUCCESS, "npc_mov_free() failed");

    game_free(game);
}
