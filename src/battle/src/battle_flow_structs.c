#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow_structs.h"

/* see battle_flow_structs.h */
battle_ctx_t *new_battle_ctx(battle_game_t *game, battle_status_t status, 
                            turn_component_list_t *tcl)
{
      battle_ctx_t *new_ctx = (battle_ctx_t *) malloc (sizeof(battle_ctx_t));
      assert(new_ctx != NULL);
      assert(game != NULL);
      assert(tcl != NULL);
      new_ctx->game = game;
      new_ctx->status = status;
      new_ctx->tcl = tcl;
      return new_ctx;
}

/* see battle_flow_structs.h */
battle_ctx_t *init_battle_ctx(battle_ctx_t *ctx, battle_game_t *game, 
                             battle_status_t status, turn_component_list_t *tcl)
{
      assert(ctx != NULL);
      assert(game != NULL);
      assert(tcl != NULL);
      ctx->game = game;
      ctx->status = status;
      ctx->tcl = tcl;
      return SUCCESS;
}

/* see battle_flow_structs.h */
int turn_free(turn_component_list_t *tcl)
{
      while (tcl != NULL)
      {
            turn_component_list_t *buf = tcl;
            tcl = tcl->next;
            free(buf);
      }
      return 0;
}

/* see battle_flow_structs.h */
int battle_ctx_free(battle_ctx_t *ctx)
{
      turn_free(ctx->tcl);
      battle_game_free(ctx->game);
      free(ctx);
      return 0;
}

/* see battle_flow_structs.h */
int battle_game_free(battle_game_t *game)
{
      battle_free(game->battle);
      battle_player_free(game->player);
      free(game);
      return 0;
}

/* see battle_flow_structs.h */
int battle_player_free(battle_player_t *player)
{
      free(player->player_id);
      free(player->stats);
      class_free(player->class_type);
      move_free(player->moves);
      battle_item_free(player->items);
      battle_equipment_free(player->armor);
      battle_equipment_free(player->accessory);
      battle_equipment_free(player->weapon);
      free(player);
      return 0;
}

int battle_equipment_free(battle_equipment_t *equip)
{
      free(equip->name);
      free(equip->description);
      stat_changes_free(equip->attributes);
      free(equip);
      return 0;
}


int battle_item_free(battle_item_t *item)
{
      while (item!=NULL){
            battle_item_t *buf = item;
            item = item->next;
            free(buf->name);
            free(buf->description);
            stat_changes_free(item->attributes);
            free(buf);
      }
      return 0;
}

/* see battle_flow_structs.h */
int stat_changes_free(stat_changes_t *changes)
{
      while (changes != NULL)
      {
            stat_changes_t *buf = changes;
            changes = changes->next;
            free(buf);
      }
      return 0;
}

/* Stub for the player_new function in player.h game-state module */
battle_player_t *new_ctx_player(char* p_id, class_t *c_type, stat_t *stats, move_t *moves, 
                              battle_item_t* items, battle_equipment_t *weapon, 
                              battle_equipment_t *accessory, battle_equipment_t *armor)
{
      battle_player_t *ctx_player = calloc(1, sizeof(battle_player_t));
      assert(ctx_player != NULL);

      ctx_player->player_id = p_id;
      ctx_player->class_type = c_type;
      ctx_player->stats = stats;
      ctx_player->moves = moves;
      ctx_player->items = items;
      ctx_player->weapon = weapon;
      ctx_player->accessory = accessory;
      ctx_player->armor = armor;

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
turn_component_t *init_turn_component(turn_component_t tc, int m, int i, int p)
{
      tc.move = m;
      tc.item = i;
      tc.pass = p;
      return SUCCESS;
}

/* see battle_flow_structs.h */
turn_component_list_t *new_turn_component_list(turn_component_t *t, 
                                                turn_component_list_t *r)
{
      turn_component_list_t *new_tcl = (turn_component_list_t *) 
                                    malloc (sizeof(turn_component_list_t));
      if (new_tcl == NULL){
            perror("Could not allocate memory");
            return NULL;
      }
      new_tcl->current = t;
      new_tcl->next = r;
      return new_tcl;
}

/* see battle_flow_structs.h */
turn_component_list_t *init_turn(turn_component_list_t *tcl, 
                                    turn_component_list_t *r, 
                                    turn_component_t *c)
{
      assert(tcl != NULL);
      tcl->current = c;
      tcl->next = r;
      return SUCCESS;
}





