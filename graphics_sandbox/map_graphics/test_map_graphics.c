#include "map_graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>


Test(map_graphics, new)
{

    map_graphics_t* m = new_map_graphics("I am the map name","I am the map path");
    cr_assert_not_null(m,"new_map_graphics has failed");
    cr_assert_str_eq(m->title,"I am the map name","new_map_graphics failed to set title");
    cr_assert_str_eq(m->image_path,"I am the map path","new_map_graphics failed to set image path");

}

Test(map_graphics, free)
{
    map_graphics_t* m = new_map_graphics("I am the map name","I am the map path");
    cr_assert_not_null(m,"new_map_graphics has failed");
    cr_assert_str_eq(m->title,"I am the map name","new_map_graphics failed to set title");
    cr_assert_str_eq(m->image_path,"I am the map path","new_map_graphics failed to set image path");
    int rc;
    rc = free_map_graphics(m);
    cr_assert_eq(SUCCESS,rc,"free_map_graphics has failed");

}