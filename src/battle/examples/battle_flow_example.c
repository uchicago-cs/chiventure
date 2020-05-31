#include "battle/battle_state.h"
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"


int main()
{
stat_t *p_stats = malloc(sizeof(stat_t));
p_stats->hp = 100;
p_stats->xp = 10;
p_stats->speed = 10;
player_t *p = new_ctx_player("John", NULL, p_stats, NULL, NULL);

stat_t *e_stast = malloc(sizeof(stat_t));
e_stats->hp = 70;
e_stats->xp = 10;
e_stats->speed = 9;
npc_enemy_t *e = make_npc_enemy("Goblin", NULL, e_stats, NULL, NULL);

chiventure_ctx_battle_t ctx = malloc(sizeof(chiventure_ctx_battle_t));
ctx->in_battle = true;
ctx->game = new_game();
ctx->game->player = p;
ctx->game->battle = NULL;

start_battle(ctx, enemy, ENV_GRASS);
int turn = 1;
while(ctx->game->battle != NULL)
{
    ctx = battle_flow(ctx, test_move_bard(), "Goblin");
    fprintf(debug, "Turn %d: \n",turn);
    fprintf(debug, "    p | hp: %d\n", ctx->game->battle->player->stats->hp);
    fprintf(debug, "    e | hp: %d\n\n", ctx->game->battle->enemy->stats->hp);
}
int winner = battle_over(ctx->game->battle)
switch (winner){
    case 0:
        fprintf(debug, "Uh oh, the battle flow loop had an error\n");
        break;
    case 1:
        fprintf(debug, "SUCCESS: battle flow loop exited and player won\n");
        break;
    case 2:
        fprintf(debug, "SUCCESS: battle flow loop exited and enemy won\n");
        break;
}

}
