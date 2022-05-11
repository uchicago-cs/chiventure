#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow_structs.h"

/* Stub for the player_new function in player.h game-state module */

battle_player_t *new_ctx_player(char* p_id, class_t *c_type, stat_t *stats, move_t *moves, battle_item_t* items)
{
      battle_player_t *ctx_player = calloc(1, sizeof(battle_player_t));
      assert(ctx_player != NULL);

      ctx_player->player_id = p_id;
      ctx_player->class_type = c_type;
      ctx_player->stats = stats;
      ctx_player->moves = moves;
      ctx_player->items = items;

      return ctx_player;
}

/* Stub for the game_new function in game.h game-state module */
battle_game_t *new_battle_game()
{
      battle_game_t *g = calloc(1, sizeof(battle_game_t));
      assert(g != NULL);
      g->player = NULL;
      g->battle = NULL;

      return g;
}

/* see battle_flow_structs.h */
turn_component_t *init_turn_component(turn_component_t tc, int m, int i, int p){
      tc.move = m;
      tc.item = i;
      tc.pass = p;
      return SUCCESS;
}

/* see battle_flow_structs.h */
turn_component_list_t *new_turn_component_list(turn_component_t t, turn_component_list_t *r){
      turn_component_list_t *new_tcl = (turn_component_list_t *) malloc (sizeof(turn_component_list_t));
      if (new_tcl == NULL){
            perror("Could not allocate memory");
            return NULL;
      }
      new_tcl->current = t;
      assert(r!=NULL);
      new_tcl->rest = r;
      return new_tcl;
}

/* see battle_flow_structs.h */
turn_component_list_t *init_turn(turn_component_list_t *tcl, turn_component_list_t *r, turn_component_t c){
      assert(tcl != NULL);
      assert(r != NULL);
      tcl->current = c;
      tcl->rest = r;
      return SUCCESS;
}

/* see battle_flow_structs.h */
int turn_free(turn_component_list_t *tcl){
      free(tcl->rest);
      free(tcl);
}



