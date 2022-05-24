#include <stdio.h>
#include "action_management/action_structs.h"
#include "action_management/actionmanagement.h"
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "game-state/game.h"
#include "../src/custom-actions/include/interface.h"

/* This demo uses monkeypatching to showcase changes to custom-actions
and the player module */


/* Ascii art generated from 
https://patorjk.com/software/taag/#p=display&h=2&v=0&f=Poison&t=Actn-Mgmt%0A */
const char *banner =   
"\n\n @@@@@@    @@@@@@@  @@@@@@@  @@@  @@@             @@@@@@@@@@    @@@@@@@@  @@@@@@@@@@   @@@@@@@  \n"
"@@@@@@@@  @@@@@@@@  @@@@@@@  @@@@ @@@             @@@@@@@@@@@  @@@@@@@@@  @@@@@@@@@@@  @@@@@@@  \n"
"@@!  @@@  !@@         @@!    @@!@!@@@             @@! @@! @@!  !@@        @@! @@! @@!    @@!    \n"
"!@!  @!@  !@!         !@!    !@!!@!@!             !@! !@! !@!  !@!        !@! !@! !@!    !@!    \n"
"@!@!@!@!  !@!         @!!    @!@ !!@!  @!@!@!@!@  @!! !!@ @!@  !@! @!@!@  @!! !!@ @!@    @!!    \n"
"!!!@!!!!  !!!         !!!    !@!  !!!  !!!@!@!!!  !@!   ! !@!  !!! !!@!!  !@!   ! !@!    !!!    \n"
"!!:  !!!  :!!         !!:    !!:  !!!             !!:     !!:  :!!   !!:  !!:     !!:    !!:    \n"
":!:  !:!  :!:         :!:    :!:  !:!             :!:     :!:  :!:   !::  :!:     :!:    :!:    \n"
"::   :::   ::: :::     ::     ::   ::             :::     ::    ::: ::::  :::     ::      ::    \n"
" :   : :   :: :: :     :     ::    :               :      :     :: :: :    :      :       :  \n";


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


  player_t *player = player_new("test");
  add_player_to_game(game, player);
  game->curr_player = player;

  /* Create context */
  chiventure_ctx_t *ctx = chiventure_ctx_new(game);
  game = ctx->game;
  
  return ctx;
}

char *raiseDmg(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
  attribute_t **args = malloc(sizeof(attribute_t*) *3);

  attribute_t *dmgIncrease = int_attr_new("Dmg", 3);
  attribute_t *dmgCap = int_attr_new("Dmg", 15);
  
  attribute_t *wepDmg = get_attribute(get_item_in_hash(ctx->game->curr_player->inventory, "a sword"), "Dmg");

  args[0] = dmgIncrease;
  args[1] = wepDmg;
  args[2] = wepDmg;

  /* Action that addes the value of dmgIncrease (3) to the weapon damage */
  AST_block_t *actDmg = AST_action_block_new(ADDITION, 3, args);

  attribute_t **args2 = malloc(sizeof(attribute_t*) * 3);
  args2[0] = wepDmg;
  args2[1] = wepDmg;
  args2[2] = wepDmg;

  /* Action that doubles weapon damage */
  AST_block_t *actDmg2 = AST_action_block_new(ADDITION, 3, args2);

  AST_block_t **actions = malloc(sizeof(AST_block_t*) * 2);
  actions[0] = actDmg2;
  actions[1] = actDmg;

  /* Checks if the weapon damage is less than the dmgCap attribute (currently 15) */
  conditional_block_t *cond = conditional_block_new(LTB, wepDmg, dmgCap);

  /* Branch block represents an if statement
   * if(damage < dmgCap)
   *    damage = damage + damage (Double the damage)
   * else 
   *  damage = damage + dmgIncrease
   */
  AST_block_t *branch = AST_branch_block_new(1, &cond, IFELSE, 2, actions);

  /* Custom action contains only the branch block in the list
   * The branch block will in turn decide which of the two actions
   *    that it should run based on the conditional.
   */
  custom_action_t *CA = custom_action_new("damage increase", "item", "A sword", "action", branch);

  do_custom_action(CA);
  char *str = malloc(sizeof(char) * 128);
  custom_action_free(CA);
  attribute_free(dmgCap);
  attribute_free(dmgIncrease);
  free(args);
  free(args2);
  free(actions);
  sprintf(str, "Your damage is now %d", wepDmg->attribute_value.int_val);
  return str;
}

char *seeDmg(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
  int num =  get_attribute(get_item_in_hash(ctx->game->curr_player->inventory, "a sword"), "Dmg")->attribute_value.int_val;
  /* Weapon damage will never become 4 digits unless RAISEDMG is run over 300 times. */  
  char *str = malloc(sizeof(char) *4);
  sprintf(str, "%d", num);
  return str;
}

/* Prints the current value of the current player's "strength" stat, if it exists*/
char *print_player_strength(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    player_t *player = ctx->game->curr_player;
    char *str;

    double strength = player_get_stat_current(player, "strength");

    if (strength == -1)
    {
        return "To you, strength is a foreign concept.";
    } else
    {
        sprintf(str, "Your strength is %.2f.", strength);

        return str;
    }
}

/* Adds the strength stat to the player's stats hash. Usually,
stats will be added to the player at the start of a game. */
char *learn_strength(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    player_t *player = ctx->game->curr_player;

    double strength = player_get_stat_current(player, "strength");
    if (strength != -1)
    {
        return "You already have the strength stat.";
    }


    stats_global_t *strength_stat = stats_global_new("strength", 100);
    stats_t *s = stats_new(strength_stat, 100);

    int added = player_add_stat(player, s);

    return "Knowledge is power. You now have the strength stat.";
}

/* Changes the player's strength stat by a given amount. Normally, the player
module's change stat function will be used by other modules in their own
functionalities (such as increasing stats upon equipping items, damaging
stats in battle, etc.) */
char *change_strength(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if (tokens[1] == NULL)
    {
        return "Please give a strength value.";
    }

    char *str = malloc(100);
    player_t *player = ctx->game->curr_player;

    double strength = player_get_stat_current(player, "strength");

    if (strength == -1)
    {
        return "You do not know strength.";
    }

    double change = atoi(tokens[1]) + 0.0;
    player_change_stat(player, "strength", change);

    sprintf(str, "You have gained %.2f strength.", change);

    return str;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    attribute_t *wepDmg = int_attr_new("Dmg", 7);

    item_t *sword = item_new("A sword", "A sword", "A sword");
    add_attribute_to_hash(sword, wepDmg);
    add_item_to_player(ctx->game->curr_player, sword, ctx->game);
 
    add_entry("SEEDMG", seeDmg, NULL, ctx->cli_ctx->table);
    add_entry("RAISEDMG", raiseDmg, NULL, ctx->cli_ctx->table);

    add_entry("MYSTRENGTH", print_player_strength, NULL, ctx->cli_ctx->table);
    add_entry("LEARNSTRENGTH", learn_strength, NULL, ctx->cli_ctx->table);
    add_entry("CHANGESTRENGTH", change_strength, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
