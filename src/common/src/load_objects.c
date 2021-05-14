#include "common/load_objects.h"
#include "wdl/load_game.h"

/* See load_objects.h for documentation */
game_t *load_objects(wdl_ctx_t *ctx)
{
    game_t *game;

    if(ctx->obj != NULL)
    {
        game = load_game(ctx->obj);
        return game;
    }

    // /* this section must be filled out more properly to allow for WDL
    //    objects to be loaded */

    // objstore_t** ht = ctx->ht; //hashtable where all objects are stored

    // object_t *player_obj = get_object(ht, 0,"player");
    // char *intro_text = (char*) get_attr_data(get_obj_attribute(
    //                                          player_obj,"intro_text"));

    // game = game_new(intro_text);

    // return game;
}
