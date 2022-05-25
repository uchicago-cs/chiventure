#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "read_gdl.h"

/* Checks that new_camera() properly mallocs and inits a new camera struct*/
Test(camera, new)
{
    unsigned int width = 300;
    unsigned int height = 300;
    
    camera_t *camera;
    camera = new_camera(width,height);
    
    cr_assert_not_null(camera, "make_camera() failed");
   
    cr_assert_eq(camera->width, 300, "make_camera() didn't set width");
    cr_assert_eq(camera->height, 300, "make_camera() didn't set height");
}

/* Checks that init_camera() properly inits values for camera struct */
Test(camera, init)
{
    unsigned int width = 300;
    unsigned int height = 300;

    camera_t *camera;
    int rc;
    
    rc = init_camera(camera,width,height);

    cr_assert_eq(rc, SUCCESS, "init_camera() failed");

    cr_assert_eq(camera->width,300,"init_camera() didn't set width");
    cr_assert_eq(camera->height,300,"init_camera() didn't set height");
}

/* Tests taht free_camera properly frees a heap allocated camera struct */
Test(camera, free)
{
    unsigned int width = 300;
    unsigned int height = 300;
    int rc;

    camera_t *camera;
    camera = new_camera(width,height);
   
    cr_assert_not_null(camera, "make_camera() failed");

    rc = free_camera(camera);

    cr_assert_eq(rc, SUCCESS, "free_camera() failed");
}
