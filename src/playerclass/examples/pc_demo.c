#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../../battle/examples/battle_move_maker.h"

player_t* player1 =  new_ctx_player("player1", class_t *class, stat_t *stats, move_t *moves, item_t* items);

player1_mod = build_moves(player1);

while (player1_mod->moves) {
  printf("%s,", player1_mod->moves->info);
  player->moves = player->moves->next;
 }
