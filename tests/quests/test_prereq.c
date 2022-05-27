#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/prereq.h"
#include "quests/samples.h"

/* tests init function for prereq struct */
Test(prereq, init)
{
    int hp = 40;
    int level = 5;

    prereq_t prereq;

    int rc = prereq_init(&prereq, hp, level);

    cr_assert_eq(rc, SUCCESS, "prereq_init failed!");
    cr_assert_eq(prereq.hp, 40, "prereq_init did not set hp");
    cr_assert_eq(prereq.level, 5, "prereq_init did not set level");  
}

/* Tests new function for prereq struct */
Test(prereq, new)
{
    int hp = 20;
    int level = 17;

    prereq_t *prereq = prereq_new(hp, level);

    cr_assert_not_null(prereq, "prereq_new failed to create a prereq");
    cr_assert_eq(prereq->hp, 20, "prereq did not set hp");
    cr_assert_eq(prereq->level, 17, "prereq did not set level");  
}

