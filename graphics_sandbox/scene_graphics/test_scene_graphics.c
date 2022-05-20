#include "scene_graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>


Test(scene_graphics, new)
{

    scene_graphics_t* s;

    s = new_scene_graphics("test scene","../nsfw.png",NULL);

    cr_assert_not_null(s,"new_scene_graphics() failed");

    cr_assert_eq(s->title, "test scene", "new_scene_graphics() didn't set title");

    cr_assert_eq(s->image_path,"../nsfw.png","new_scene_graphics() didn't set image path");

}

Test(scene_graphics, free)
{
    scene_graphics_t *s;
    int rc;
    
    s = new_scene_graphics("test scene","../nsfw.png",NULL);

    cr_assert_not_null(s,"new_scene_graphics() failed");

    rc = free_scene_graphics(s);

    cr_assert_eq(rc,1,"free_scene_graphics() failed");

}