#include "scene_graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>

/* Testing new_scene_graphics*/
Test(scene_graphics, new)
{

    scene_graphics_t* s;

    s = new_scene_graphics("test scene","../nsfw.png", (Vector2){100,150},
                            (Vector2){500,550}, (Vector2){400,450}, (Vector2){300,320});

    cr_assert_not_null(s,"new_scene_graphics() failed");

    cr_assert_str_eq(s->SceneName, "test scene", "new_scene_graphics() didn't set title");

    cr_assert_str_eq(s->ImagePath,"../nsfw.png","new_scene_graphics() didn't set image path");

    cr_assert_eq(s->WindowPos.x,100,"new_scene_graphics() didn't set WindowPos.x");

    cr_assert_eq(s->WindowPos.y,150,"new_scene_graphics() didn't set WindowPos.y");

    cr_assert_eq(s->WindowSize.x,500,"new_scene_graphics() didn't set WindowSize.x");

    cr_assert_eq(s->WindowSize.y,550,"new_scene_graphics() didn't set WindowSize.y");

    cr_assert_eq(s->SceneSize.x,400,"new_scene_graphics() didn't set SceneSize.x");

    cr_assert_eq(s->SceneSize.y,450,"new_scene_graphics() didn't set SceneSize.y");

    cr_assert_eq(s->PlayerPosition.x,300,"new_scene_graphics() didn't set PlayerPosition.x");

    cr_assert_eq(s->PlayerPosition.y,320,"new_scene_graphics() didn't set PlayerPosition.y");
}

/* Testing free_scene_graphics*/
Test(scene_graphics, free)
{
    scene_graphics_t *s;
    int rc;
    
    s = new_scene_graphics("test scene","../nsfw.png", (Vector2){100,100},
                            (Vector2){500,500}, (Vector2){400,400}, (Vector2){300,300});

    cr_assert_not_null(s,"new_scene_graphics() failed");

    rc = free_scene_graphics(s);

    cr_assert_eq(rc,SUCCESS,"free_scene_graphics() failed");

}