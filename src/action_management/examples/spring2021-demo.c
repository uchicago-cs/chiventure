#include <stdio.h>
#include "action_management/action_structs.h"
#include "action_management/actionmanagement.h"
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "game-state/game.h"
#include "../src/custom-actions/include/interface.h"

const char *banner = "This is the 2021 Action-Management team demo";


/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
  chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

  game_t *game = game_new("Welcome to Chiventure!");

  /* Free default game and replace it with ours */
  game_free(ctx->game);
  ctx->game = game;

  return ctx;
}

char *raiseDmg()
{
  return NULL;
}


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();
    attribute_t **args = malloc(sizeof(attribute_t*) *3);
    attribute_t *dmgIncrease = malloc(sizeof(attribute_t));
    char *name = "Dmg";
    attribute_value_t a1, a2;
    a1.int_val = 3;
    a2.int_val = 30;
    dmgIncrease->attribute_key = strdup(name);
    dmgIncrease->attribute_tag = INTEGER;
    dmgIncrease->attribute_value = a2;
    
    attribute_t *wepDmg = malloc(sizeof(attribute_t));
    wepDmg->attribute_key = strdup(name);
    wepDmg->attribute_tag = INTEGER;
    wepDmg->attribute_value = a1;
    
    item_t *sword = item_new(0, "A sword", "A sword");
    args[0] = dmgIncrease;
    args[1] = wepDmg;
    args[2] = wepDmg;
    add_attribute_to_hash(sword, wepDmg);
    add_item_to_player(ctx->game->curr_player, sword);
    AST_block_t *actDmg = AST_action_block_new(ADDITION, 3, args);
    custom_action_t *CA = custom_action_new("damage increase", "item", NULL, "action", actDmg);
    
    add_entry("RAISEDMG", raiseDmg, NULL, NULL);
 
    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
