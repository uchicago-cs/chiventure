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
  game_t *game = game_new("Welcome to Chiventure!");

  /* Create two rooms (room1 and room2). room1 is the initial room */
  room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
  room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
  add_room_to_game(game, room1);
  add_room_to_game(game, room2);
  game->curr_room = room1;
  create_connection(game, "room1", "room2", "NORTH");


  /* Create context */
  chiventure_ctx_t *ctx = chiventure_ctx_new(game);
  game = ctx->game;
  
  return ctx;
}

char *raiseDmg(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
  attribute_t **args = malloc(sizeof(attribute_t*) *3);
  attribute_t *dmgIncrease = malloc(sizeof(attribute_t));
  char *name = "Dmg";
  attribute_value_t a1;
  a1.int_val = 3;
  dmgIncrease->attribute_key = strdup(name);
  dmgIncrease->attribute_tag = INTEGER;
  dmgIncrease->attribute_value = a1;

  attribute_t *wepDmg = get_attribute(get_item_in_hash(ctx->game->curr_player->inventory, "7"), "Dmg");
  args[0] = dmgIncrease;
  args[1] = wepDmg;
  args[2] = wepDmg;
  AST_block_t *actDmg = AST_action_block_new(ADDITION, 3, args);
  custom_action_t *CA = custom_action_new("damage increase", "item", "7", "action", actDmg);
  
  do_custom_action(CA);
  return "Damage Raised";
}

char *seeDmg(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
  int num =  get_attribute(get_item_in_hash(ctx->game->curr_player->inventory, "7"), "Dmg")->attribute_value.int_val;
  char *str;
  sprintf(str, "%d", num);
  return str;
}



int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();
    char *name = "Dmg";
    attribute_value_t a1;
    a1.int_val = 30;
    
    attribute_t *wepDmg = malloc(sizeof(attribute_t));
    wepDmg->attribute_key = strdup(name);
    wepDmg->attribute_tag = INTEGER;
    wepDmg->attribute_value = a1;
    item_t *sword = item_new("7", "A sword", "A sword");
    add_attribute_to_hash(sword, wepDmg);
    add_item_to_player(ctx->game->curr_player, sword);
 
    add_entry("SEEDMG", seeDmg, NULL, ctx->table);
    add_entry("RAISEDMG", raiseDmg, NULL, ctx->table);
    
    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
