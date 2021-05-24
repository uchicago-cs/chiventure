#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_state.h"


int main()
{
    stat_t *p_stats = (stat_t*) calloc(1, sizeof(stat_t));
    p_stats->hp = 100;
    p_stats->xp = 10;
    p_stats->speed = 10;
    p_stats->level = 3;
    p_stats->defense = 3;
    p_stats->strength = 80;

    battle_player_t *p = new_ctx_player("John", NULL, p_stats, NULL, NULL);

    stat_t *e_stats = (stat_t*) calloc(1, sizeof(stat_t));
    e_stats->hp = 70;
    e_stats->xp = 10;
    e_stats->speed = 9;
    e_stats->level = 6;
    e_stats->defense = 2;
    e_stats->strength = 70;

    npc_enemy_t *e = NULL;
    DL_APPEND(e, make_npc_enemy("Goblin", NULL, e_stats, NULL, NULL, BATTLE_AI_GREEDY));

    chiventure_ctx_battle_t *ctx = 
        (chiventure_ctx_battle_t*) calloc(1, sizeof(chiventure_ctx_battle_t));

    battle_game_t *g = new_battle_game();
    ctx->game = g;

    ctx->game->player = p;

    start_battle(ctx, e, ENV_GRASS);
    int turn = 1;

    printf("Start of battle: \n");
    printf("    p | hp: %d\n", ctx->game->battle->player->stats->hp);
    printf("    e | hp: %d\n\n", ctx->game->battle->enemy->stats->hp);

    while(ctx != NULL && ctx->status == BATTLE_IN_PROGRESS)
    {

        int res = battle_flow(ctx, test_move_bard(), "Goblin");
        if(res == FAILURE)
        {
            fprintf(stderr, "Uh oh, the battle flow loop had an error\n");
            ctx = NULL;
        }
        else
        {
            printf("Turn %d: \n",turn);
            printf("    p | hp: %d\n", ctx->game->battle->player->stats->hp);
            printf("    e | hp: %d\n\n", ctx->game->battle->enemy->stats->hp);
            turn++;
        }
    }
    battle_status_t winner = battle_over(ctx->game->battle);
    switch (winner) {
        case BATTLE_IN_PROGRESS:
            fprintf(stderr, "Uh oh, the battle flow loop had an error\n");
            break;
        case BATTLE_VICTOR_PLAYER:
            fprintf(stderr, "SUCCESS: battle flow loop exited and player won\n");
            break;
        case BATTLE_VICTOR_ENEMY:
            fprintf(stderr, "SUCCESS: battle flow loop exited and enemy won\n");
            break;
        case NO_BATTLE:
            fprintf(stderr, "ERROR, battle should not return as no_battle");
    }
}

