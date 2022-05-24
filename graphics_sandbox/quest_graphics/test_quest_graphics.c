#include "quest_graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>

/* Testing new_quest_graphics*/
Test(quest_graphics, new)
{

    quest_graphics_t* q;

    q = new_quest_graphics((Vector2){200,210}, (Vector2){400,420},
    (Vector2){50,60}, (Vector2){70,80}, NULL, "test", false, 10.1);

    cr_assert_not_null(q, "new_quest_graphics failed");
    cr_assert_str_eq(q->CurrentTaskName,"test","new_quest_graphis failed to set currentTaskName");
    cr_assert_eq(q->WindowPos.x,200,"new_quest_graphics failed to set WindowPos.x");
    cr_assert_eq(q->WindowPos.y,210,"new_quest_graphics failed to set WindowPos.y");
    cr_assert_eq(q->WindowSize.x,400,"new_quest_graphics failed to set WindowSize.x");
    cr_assert_eq(q->WindowSize.y,420,"new_quest_graphics failed to set WindowSize.y");
    cr_assert_eq(q->SegmentDimension.x,50,"new_quest_graphics failed to set SegmentDimension.x");
    cr_assert_eq(q->SegmentDimension.y,60,"new_quest_graphics failed to set SegmentDimension.y");
    cr_assert_eq(q->DrawStartPosition.x,70,"new_quest_graphics failed to set DrawStartPosition.x");
    cr_assert_eq(q->DrawStartPosition.y,80,"new_quest_graphics failed to set DrawStartPosition.y");
    //Not testing task_tree struct right now as it is a mockup, will incorporate later
    cr_assert_eq(q->ShowRemainingHorizontal,false,"new_quest_graphics failed to set DrawRemainingHorizontal");
    cr_assert_float_eq(q->SquareSide,10.1, 0.01,"new_quest_graphics failed to set SquareSide");

}

/* Testing init_quest_graphics*/
Test(quest_graphics, init)
{
    quest_graphics_t q;

    int rc = init_quest_graphics(&q, (Vector2){200,210}, (Vector2){400,420},
    (Vector2){50,60}, (Vector2){70,80}, NULL, "test", false, 10.1);

    cr_assert_eq(rc,SUCCESS,"init_quest_graphics has failed");

    cr_assert_str_eq(q.CurrentTaskName,"test","new_quest_graphics failed to set currentTaskName");
    cr_assert_eq(q.WindowPos.x,200,"new_quest_graphics failed to set WindowPos.x");
    cr_assert_eq(q.WindowPos.y,210,"new_quest_graphics failed to set WindowPos.y");
    cr_assert_eq(q.WindowSize.x,400,"new_quest_graphics failed to set WindowSize.x");
    cr_assert_eq(q.WindowSize.y,420,"new_quest_graphics failed to set WindowSize.y");
    cr_assert_eq(q.SegmentDimension.x,50,"new_quest_graphics failed to set SegmentDimension.x");
    cr_assert_eq(q.SegmentDimension.y,60,"new_quest_graphics failed to set SegmentDimension.y");
    cr_assert_eq(q.DrawStartPosition.x,70,"new_quest_graphics failed to set DrawStartPosition.x");
    cr_assert_eq(q.DrawStartPosition.y,80,"new_quest_graphics failed to set DrawStartPosition.y");
    //Not testing task_tree struct right now as it is a mockup, will incorporate later
    cr_assert_eq(q.ShowRemainingHorizontal,false,"new_quest_graphics failed to set DrawRemainingHorizontal");
    cr_assert_float_eq(q.SquareSide,10.1, 0.01,"new_quest_graphics failed to set SquareSide");

}


/* Testing free_quest_graphics*/
Test(quest_graphics, free)
{
    quest_graphics_t* q;
    int rc;

    q = new_quest_graphics((Vector2){200,210}, (Vector2){400,420},
    (Vector2){50,60}, (Vector2){70,80}, NULL, "test", false, 10.1);

    cr_assert_not_null(q, "new_quest_graphics failed");

    rc = free_quest_graphics(q);

    cr_assert_eq(rc,SUCCESS,"free_quest_graphics failed");

}
