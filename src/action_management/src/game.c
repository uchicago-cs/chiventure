#include "game.h"
#include "common.h"


/* In the absence of Game State's code,
   here are empty/skeleton implementations of the functions in game.h,
   so our code will compile. We acknowledge there will be warnings
   about unused parameters, since these are skeleton functions.
   ========================================================================== */


/* See game.h */
int toggle_condition(game_t *g, action_t *a, item_t *i) {
  return SUCCESS;
}


/* See game.h */
int get_long_desc(item_t *i) {
  return SUCCESS;
}


/* See game.h */
int remove_inventory_item(player_t *p, item_t *i) {
  return SUCCESS;
}


/* See game.h */
int take_object(item_t *i) {
  return SUCCESS;
}


/* See game.h */
int add_inventory_item(player_t *p, item_t *i) {
  return SUCCESS;
}


/* See game.h */
int change_health(player_t *p, int change, int max_health) {
  return SUCCESS;
}


/* See game.h */
int player_move(game_t *g, direction_t *d) {
  return SUCCESS;
}


/* See game.h */
int found_in_room(game_t *g, npc_t *n) {
  return SUCCESS;
}


/* See game.h */
int npc_talk(player_t *p, npc_t *n) {
  return SUCCESS;
}
