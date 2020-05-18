#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "battle/battle_flow.h"

#ifndef BATTLE_FLOW_H
#define BATTLE_FLOW_H

#include "battle_structs.h"
#include "battle_state.h"
#include "common/utlist.h"
#include "common/common.h"
#include <stdbool.h>
#include <string.h>

/* see battle_flow.h */
int start_battle(chiventure_ctx_t *ctx, npc_t *enemies, combatant_info_t *pinfo, environment_t env)
{
      game_t *g = ctx->game;
      player_t *p = g->curr_player;

      combatant_t *player  = set_player(p,pinfo);
      combatant_t *enemies = set_enemies(enemies);
      battle_t *b = set_battle(player,enemies,env);

}

/* see battle_flow.h */
combatant_t *set_enemies(npc_t *enemies)
{
  return FAILURE;
};

/* see battle_flow.h */
combatant_t *set_player(player_t *p, combatant_info_t *pinfo)
{
    char* name = p->player_id;
    combatant_new(name,);
}

/* see battle_flow.h */
int set_battle()
{
  battle_new();
  return FAILURE;
};

int print_battle(combatant_t *enemy)
{
  print_to_cli("You begin a battle with %s",enemy);
  return FAILURE;
};
