#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_rooms.h"

obj_t *get_doc_obj()
{
    obj_t *obj = obj_new("doc");
    parse_game(PATH, obj);
    return obj;
}

/* check to see if rooms are added to game struct correctly */
Test(rooms, add_rooms)
{
    obj_t *doc = get_doc_obj();
    game_t *g = game_new();

    // check adding rooms to game
    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    // find a room and check sdesc and ldesc
    room_t *r = find_room_from_game(g, "room A");
    char *s = get_sdesc(r);
    char *scmp = "This is room A";
    rc = strncmp(s, scmp, strlen(scmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse room sdesc");

    char *l = get_ldesc(r);
    char *lcmp = "This is room A long";
    rc = strncmp(l, lcmp, strlen(lcmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse room ldesc");

    //TODO: make sure we can check all attribute fields
}

/* check to see if connections are added to game struct correctly */
Test(rooms, add_connections)
{
    obj_t *doc = get_doc_obj();
    game_t *g = game_new();

    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    // find path given room and direction
    room_t *r = find_room_from_game(g, "room A");
    path_t *p = path_search(r, "north");
    char *to_id = p->dest->room_id;
    char *s = "room B";
    rc = strncmp(to_id, s, strlen(s));
    cr_assert_eq(rc, SUCCESS, "failed to parse connection");

    //TODO: make sure we can check every single connection
}
