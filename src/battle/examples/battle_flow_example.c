#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_state.h"
#include "npc/npc.h"
#include "npc/npc_battle.h"
#include "move_demo.c"
#include "demo_items_and_equipment.c"

class_t *make_sorcerer()
{
    return class_new("Sorcerer", "Wise", "Old and wise with crazy magecraft ability", NULL, NULL, NULL);
}

class_t *make_minion()
{
    return class_new("Minion", "Stupid", "Unintelligent, but very strong", NULL, NULL, NULL);
}

int main()
{
    
    stat_t *p_stats = (stat_t*) calloc(1, sizeof(stat_t));
    p_stats->hp = 100;
    p_stats->max_hp = 100;
    p_stats->xp = 10;
    p_stats->speed = 10;
    p_stats->level = 3;
    p_stats->phys_def = 3;
    p_stats->mag_def = 3;
    p_stats->phys_atk = 80;
    p_stats->mag_atk = 80;
    p_stats->sp = 100;
    p_stats->max_sp = 100;
    p_stats->crit = 25;
    p_stats->accuracy = 100;
    move_t *user_moves = generate_moves_user_one();
    battle_player_t *p = new_ctx_player("Sorcerer John", make_sorcerer(), p_stats, user_moves, NULL, 
                                        make_lunar_wand(), make_omni_crown(), make_cape_of_wisdom());

    stat_t *e_stats = (stat_t*) calloc(1, sizeof(stat_t));
    e_stats->hp = 70;
    e_stats->max_hp = 70;
    e_stats->xp = 10;
    e_stats->speed = 9;
    e_stats->level = 6;
    e_stats->phys_def = 2;
    e_stats->mag_def = 2;
    e_stats->phys_atk = 70;
    e_stats->mag_atk = 70;
    e_stats->sp = 100;
    e_stats->max_sp = 100;
    e_stats->crit = 25;
    p_stats->accuracy = 100;
    move_t *e_moves = generate_moves_enemy_one();
    npc_t *e = npc_new("Minion", "Enemy minion!", "Enemy minion!", make_minion(), NULL, HOSTILE);
    npc_battle_t *npc_b = npc_battle_new(70, e_stats, e_moves, BATTLE_AI_GREEDY, HOSTILE, make_minion(), 
                                        NULL, NULL, NULL, NULL);
    e->npc_battle = npc_b;

    // battle_ctx_t *ctx = 
    //     (battle_ctx_t*) calloc(1, sizeof(battle_ctx_t));

    // battle_game_t *g = new_battle_game();
    // ctx->game = g;

    // ctx->game->player = p;

    // start_battle(ctx, e, ENV_GRASS);
    // int turn = 1;

    // printf("Start of battle: \n");
    // printf("    p | hp: %d\n", ctx->game->battle->player->stats->hp);
    // printf("    e | hp: %d\n\n", ctx->game->battle->enemy->stats->hp);

    // while(ctx != NULL && ctx->status == BATTLE_IN_PROGRESS)
    // {

<<<<<<< HEAD
        char* res = battle_flow_move(ctx, generate_moves_enemy_one(), "Minion");
        if(strcmp(res, "FAILURE") == 0)
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
=======
    //     char* res = battle_flow_move(ctx, test_move_bard(), "Goblin");
    //     if(strcmp(res, "FAILURE") == 0)
    //     {
    //         fprintf(stderr, "Uh oh, the battle flow loop had an error\n");
    //         ctx = NULL;
    //     }
    //     else
    //     {
    //         printf("Turn %d: \n",turn);
    //         printf("    p | hp: %d\n", ctx->game->battle->player->stats->hp);
    //         printf("    e | hp: %d\n\n", ctx->game->battle->enemy->stats->hp);
    //         turn++;
    //     }
    // }
    // battle_status_t winner = battle_over(ctx->game->battle);
    // switch (winner) {
    //     case BATTLE_IN_PROGRESS:
    //         fprintf(stderr, "Uh oh, the battle flow loop had an error\n");
    //         break;
    //     case BATTLE_VICTOR_PLAYER:
    //         fprintf(stderr, "SUCCESS: battle flow loop exited and player won\n");
    //         break;
    //     case BATTLE_VICTOR_ENEMY:
    //         fprintf(stderr, "SUCCESS: battle flow loop exited and enemy won\n");
    //         break;
    //     case NO_BATTLE:
    //         fprintf(stderr, "ERROR, battle should not return as no_battle");
    // }
>>>>>>> 33c160c0c1328ed032048abcc786a2c45cf02e27
    return 0;
}

