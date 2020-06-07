#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"

#define MAX_MOVE_NAME_LEN (100)

int print_move_info(chiventure_ctx_battle_t *ctx, char *move_name)
{
    move_t *temp;
    DL_FOREACH(ctx->game->player->moves, temp)
    {
        if (strncmp(temp->name, move_name, MAX_MOVE_NAME_LEN) == 0)
        {
            printf("%s: %s\n", temp->name, temp->info);
            printf("\n");
            return SUCCESS;
        }
        printf("Couldn't find the move you were looking for!\n");
        return FAILURE;
    }
}

int read_move(char *fst, char *snd, char *move_name, char *act,
              char *enemy_name, chiventure_ctx_battle_t *ctx)
{
    int invalid_move = 1;
    int res;
    char *action_string;
    while (invalid_move)
    {
        if ((strncmp(fst, "MOVE", 5) == 0) && (strncmp(snd, "USE", 4) == 0) && (strncmp(act, "ON", 3) == 0))
        {
            //check if move exists?
            // run below if move exists
            printf("Determined command as MOVE USE, and it using the %s move", 
                    move_name);
            move_t *temp;
            move_t *player_move = temp;
            DL_FOREACH(ctx->game->player->moves, temp)
            {
                if (strncmp(temp->name, move_name, MAX_MOVE_NAME_LEN) == 0)
                {
                    player_move = temp;
                }
                printf("Couldn't find the move you were looking for!\n");
                return FAILURE;
            }
            if (goes_first(ctx->game->battle) == PLAYER)
            {
                action_string = print_battle_move(ctx->game->battle,
                                                  PLAYER, player_move);
                printf("%s\n", action_string);
                move_t *enemy_move = give_move(ctx->game->battle->player, 
                                               ctx->game->battle->enemy, 
                                               ctx->game->battle->enemy->ai);
                action_string = print_battle_move(ctx->game->battle, ENEMY, enemy_move);
                printf("%s\n", action_string);
            }
            else
            {
                action_string = print_battle_move(ctx->game->battle,
                                                  PLAYER, player_move);
                printf("%s\n", action_string);
                move_t *enemy_move = give_move(ctx->game->battle->player,
                                               ctx->game->battle->enemy,
                                               ctx->game->battle->enemy->ai);
                action_string = print_battle_move(ctx->game->battle, ENEMY, enemy_move);
                printf("%s\n", action_string);
            }
            res = battle_flow(ctx, player_move, enemy_name);
            invalid_move = 0;
        }
        else if ((strncmp(fst, "MOVE", 5) == 0) && (strncmp(snd, "LIST", 5) == 0))
        {
            move_t *temp;
            printf("MOVES LIST\n");
            DL_FOREACH(ctx->game->player->moves, temp)
            {
                printf("%s\n", temp->name);
            }
            printf("\n");
            return SUCCESS;
        }
        else if ((strncmp(fst, "MOVE", 5) == 0) && (strncmp(snd, "INFO", 4) == 0))
        {
            res = print_move_info(ctx, move_name);
            return res;
        }
        else
        {
            printf("Invalid Move. Please try again... n");
            int rc = scanf("%s %s %s %s %s", fst, snd, move_name, act, enemy_name);
            printf("\n");
        }
    }
    return res;
}

int main()
{
    stat_t *p_stats = (stat_t *)calloc(1, sizeof(stat_t));
    p_stats->hp = 100;
    p_stats->xp = 10;
    p_stats->speed = 10;

    player_t *p = new_ctx_player("John", NULL, p_stats, NULL, NULL); // need to make moves

    stat_t *e_stats = (stat_t *)calloc(1, sizeof(stat_t));
    e_stats->hp = 70;
    e_stats->xp = 10;
    e_stats->speed = 9;

    move_t *e_moves = NULL;
    move_t *e_move1 = test_move_bard();
    move_t *e_move2 = test_move_cleric();
    DL_APPEND(e_moves, e_move1);
    DL_APPEND(e_moves, e_move2);
    npc_enemy_t *e = NULL;
    DL_APPEND(e, make_npc_enemy("Goblin", NULL, e_stats, e_moves, NULL, BATTLE_AI_GREEDY));

    chiventure_ctx_battle_t *ctx =
        (chiventure_ctx_battle_t *)calloc(1, sizeof(chiventure_ctx_battle_t));

    game_t *g = new_game();
    ctx->game = g;

    ctx->game->player = p;

    start_battle(ctx, e, ENV_GRASS);
    int turn = 1;
    printf("\nWelcome to the Battle! Let's get this started!\n\n");
    char *fst = calloc(strlen("MOVE") + 1, sizeof(char));
    char *snd = calloc(strlen("USE") + 1, sizeof(char));
    char *move_name = calloc(MAX_MOVE_NAME_LEN + 1, sizeof(char));
    char *act = calloc(strlen("ON") + 1, sizeof(char));
    char *enemy_name = calloc(MAX_NAME_LEN + 1, sizeof(char));
    char *hp_string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

    while (ctx != NULL && ctx->status == BATTLE_IN_PROGRESS)
    {
        hp_string = print_start_battle(ctx->game->battle);
        printf("Turn %d:\n", turn);
        printf("%s\n", hp_string);
        printf("What will you do?\n");
        int rc = scanf("%s %s %s %s %s", fst, snd, move_name, act, enemy_name);
        read_move(fst, snd, move_name, act, enemy_name, ctx);
        printf("\n");
    }

    battle_status_t winner = battle_over(ctx->game->battle);

    char *win_string = print_battle_winner(ctx->status, 20);
    printf("%s\n", win_string);
    switch(winner)
    {
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
