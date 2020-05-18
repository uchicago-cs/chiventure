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
int battle_setup(game_t *g, npc_t *enemies, combatant_info_t *pinfo, environment_t env)
{
    player_t* p = g->curr_player;
    combatant_t* set_combatants(p,pinfo,enemies);
    set_battle(env);
};

/* see battle_flow.h */
int set_combatants(player_t *p, combatant_info_t *pinfo, npc_t *enemies)
{
  // Set the player


  // Set the enemies

  return FAILURE;
};

combatant_t *set_player(player_t *p, combatant_info_t *pinfo)
{
    char* name = p->player_id;
    char
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
