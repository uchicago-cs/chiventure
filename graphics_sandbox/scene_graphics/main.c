#include "scene_graphics.h"

int main(void) {

    scene_graphics_t* scene_graphics;

    scene_graphics = new_scene_graphics("NSWF","nsfw.png",(Vector2){100,100},(Vector2){440,440},(Vector2){400,400},(Vector2){400,400});


    runSceneGraphics(scene_graphics);

    free(scene_graphics);

    return 0;
}