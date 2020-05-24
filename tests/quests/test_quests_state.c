#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

Test(achievement, init)
{
	achievement_t *achievement = malloc(sizeof(achievement_t));
    

	int check = achievement_init(achievement, "test_room", "This is a test room",
	"The purpose of this room is testing");

	cr_assert_eq(check, SUCCESS, "room_init() test 1 has failed!");
}

/* Tests quest_new */
/* Test(quests_state, quest_new)
{
    quest_t *q;

}
*/