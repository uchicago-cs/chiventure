#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game.h"


/*need to figure out how to feed in test struct into criterion
//assuming that is completed
Test(game, init) 
{
    game_t *game = //test struct

}

Test(game, save) 
{
    game_t *game = //test struct
    int rc = 0;
    rc = save_game(game, f);
    cr_assert_eq(rc, 1, "file not saved");
}

Test(game, move room) 
{
    game_t *game = //teststruct
    game->curr_room = curr;
    room_t *new_room = //add new room?
    move_room(game, new_room);
    int strcheck = strcmp(curr->room_id, game->curr_room->room_id);
    int chk = 0;
    if(strcheck != 1)
        chk = 1;
    
    cr_assert_eq(chk, 1, "failed to move to new room");

}

Test(game, free)
{
//tbd? 
}
*/

Test(iter, get_all_rooms) {
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new(strdup("room1"), strdup("room1 short"), strdup("room1 long long long"));
    room_t *room2 = room_new(strdup("room2"), strdup("room2 short"), strdup("room2 long long long"));
    room_t *room3 = room_new(strdup("room3"), strdup("room3 short"), strdup("room3 long long long"));
    HASH_ADD_KEYPTR(hh, game->all_rooms, room1->room_id, strlen(room1->room_id), room1);
    HASH_ADD_KEYPTR(hh, game->all_rooms, room2->room_id, strlen(room2->room_id), room2);
    HASH_ADD_KEYPTR(hh, game->all_rooms, room3->room_id, strlen(room3->room_id), room3);
    int cnt = 0;
    room_t *curr_room;
    room_list_t *list = get_all_rooms(game);
    room_list_t *elt;
    LL_FOREACH(list, elt) {
        cnt++;
        curr_room = elt->room;
        if (!strncmp(curr_room->room_id, "room1", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room1 long long long",
            "ldesc does not correspond");
        } else if (!strncmp(curr_room->room_id, "room2", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room2 long long long",
            "ldesc does not correspond");
        } else if (!strncmp(curr_room->room_id, "room3", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room3 long long long",
            "ldesc does not correspond");
        } else {
            cr_assert_fail("non-existent room detected");
        }
    }
    cr_assert_eq(cnt, 3, "wrong room counts");
    cr_assert_eq(delete_room_llist(list), SUCCESS, "delete llist failed");
    game_free(game);
}
