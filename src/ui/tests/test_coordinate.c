#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coordinate.h"

// Checks that a given x and y-coordinate are allocated in memory within a
// coordinate struct
Test(coordinate, new)
{
    //coord_t *c;
    //c = malloc(sizeof(coord_t));

    coord_t *rc;
    rc = malloc(sizeof(coord_t));
    rc = coord_new(5, 3, 7);

    cr_assert_not_null(rc, "coord_init() failed");
    cr_assert_eq(rc->x, 5, "coord_init() didn't set the coordinates's x-coordinate");
    cr_assert_eq(rc->y, 3, "coord_init() didn't set the coordinates's y-coordinate");
    cr_assert_eq(rc->z, 7, "coord_init() didn't set the coordinates's z-coordinate");

}


//Checks whether two rooms are equal
int check_equal(coord_record_t *one, coord_record_t *two)
{
	if (one->r->room_id == NULL && two->r->room_id == NULL) {
		return 1;
	}

	int one_x = one->key.x;
	int one_y = one->key.y;
	int two_x = two->key.x;
    int two_y = two->key.y;
    char *one_id = one->r->room_id;
    char *two_id = two->r->room_id;

    if (one_x == two_x && one_y == two_y && one_id == two_id)
    {
        return 1;
    } else {
        return 0;
    }

}

//Returns a room when a coordinate has already been assigned to it
void check_find_coord(coord_record_t *coordmap, int x, int y, int z, coord_record_t *rd_expected,
						int expected)
{
	coord_record_t *rd;
	rd = malloc(sizeof(coord_record_t));

    rd = find_coord(coordmap, x, y, z);

    int equal = check_equal(rd, rd_expected);

    cr_assert_eq(equal, expected,
                 " Coordinate record %d is %s but"
                 " find_room returned %s",
                 rd_expected->r->room_id,
                 expected? "not present":"present",
                 equal? "false":"true");
}

/* Checks that a room not present in the hash table returns NULL */
Test(coordinate, not_found)
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = malloc(sizeof(room_t));
    initial->room_id = "123";
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    check_find_coord(coordmap, 1, 2, 1, NULL, 0);
}

/* Checks that a room present in the hash table returns the correct
coord_record */
Test(coordinate, found)
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = malloc(sizeof(room_t));
    initial->room_id = "125";
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    check_find_coord(coordmap, 0, 0, 0, coordmap, 1);
}

//Returns SUCCESS if a coordinate is not present and adds it
void check_add_coord(coord_record_t *coordmap, int x, int y, int z, room_t *r,
						int expected)
{
	int rc;

    rc = try_add_coord(coordmap, x, y, z, r);

    cr_assert_eq(rc, expected,
                 " Room %.02f has %s but "
                 "try_add_room returned %s",
                 r->room_id,
                 expected? "not been added":"been added",
                 rc? "false":"true");
}

/* Checks that a room not present in the hash table is added */
Test(coordinate, added_successfully)
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = malloc(sizeof(room_t));
    initial->room_id = "125";
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    room_t *r = malloc(sizeof(room_t));
    r->room_id = "24";

    check_add_coord(coordmap, 3, 4, 1, r, SUCCESS);
}

/* Checks that a room present in the hash table is not added */
Test(coordinate, add_failure )
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = malloc(sizeof(room_t));
    initial->room_id = "125";
    cr->r = initial;

    room_t *room_2 = malloc(sizeof(room_t));
    room_2->room_id = "126";

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    check_add_coord(coordmap, 0, 0, 0, room_2, FAILURE);
}

//Returns SUCCESS if all rooms are assigned coordinates
/*void check_assign_dfs(coord_record_t *coordmap, int vertical_hops,
           game_t *game, int horizontal_hops, room_t* room, int expected)
{
    int rc;

    rc = assign(coordmap, vertical_hops, horizontal_hops, room, game);

    cr_assert_eq(rc, expected,
                 "The map is %s but "
                 "create_valid_map returned %s",
                 expected? "is not a valid map":"is a valid map",
                 rc? "failure":"success");
}*/

//Returns SUCCESS if all rooms are assigned coordinates
void check_create_valid_map(game_t *game,
					int expected)
{
    coord_record_t *end_map;
    end_map = malloc(sizeof(coord_record_t));

    end_map = create_valid_map(game);

    cr_assert_eq(end_map, expected,
                 "The map is %s but "
                 "create_valid_map returned %s",
                 expected? "is not a valid map":"is a valid map",
                 end_map? "failure":"success");
}
