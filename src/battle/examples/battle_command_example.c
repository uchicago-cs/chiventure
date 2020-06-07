#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"

#define MAX_MOVE_NAME_LEN (100)
#define MAX_COMMAND_LINE_LENGTH (100)
#define MAXLEN (100)
#define MAX_ARGS (5)

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

int read_move(char **args, chiventure_ctx_battle_t *ctx)
{
    int res;
    char *action_string;
    if ((strncmp(args[0], "MOVE", MAXLEN) == 0) 
        && (strncmp(args[1], "USE", 4) == 0) 
        && (strncmp(args[3], "ON", 3) == 0))
    {
        printf("Determined command as MOVE USE, and it using the %s move", 
                args[2]);
        move_t *temp;
        move_t *player_move = temp;
        DL_FOREACH(ctx->game->player->moves, temp)
        {
            if (strncmp(temp->name, args[2], MAX_MOVE_NAME_LEN) == 0)
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
        res = battle_flow(ctx, player_move, args[4]);
    }
    else if ((strncmp(args[0], "MOVE", MAXLEN) == 0) 
            && (strncmp(args[1], "LIST", MAXLEN) == 0))
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
    else if ((strncmp(args[0], "MOVE", 5) == 0) && (strncmp(args[1], "INFO", 4) == 0))
    {
        res = print_move_info(ctx, args[2]);
        return res;
    }
    else
    {
        return FAILURE;
    }
    return res;
}

int parse_command(char **out, char *input)
{
    for (int i = 0; i < MAX_ARGS; i++)
    {
        out[i] = calloc(MAXLEN + 1, sizeof(char));
    }
    return sscanf(input, " %s %s %s %s %s ", out[0], out[1], out[2], out[3], out[4]);
}

int main()
{
    stat_t *p_stats = (stat_t *)calloc(1, sizeof(stat_t));
    p_stats->hp = 100;
    p_stats->xp = 10;
    p_stats->speed = 10;

    stat_t *e_stats = (stat_t *)calloc(1, sizeof(stat_t));
    e_stats->hp = 70;
    e_stats->xp = 10;
    e_stats->speed = 9;

    npc_enemy_t *e = NULL;
    DL_APPEND(e, make_npc_enemy("Goblin", NULL, e_stats, NULL, BATTLE_AI_GREEDY));
    player_t *p = new_ctx_player("John", NULL, p_stats, NULL); // need to make moves

    chiventure_ctx_battle_t *ctx =
        (chiventure_ctx_battle_t *)calloc(1, sizeof(chiventure_ctx_battle_t));

    game_t *g = new_game();
    ctx->game = g;

    ctx->game->player = p;

    start_battle(ctx, e, ENV_GRASS);
    int turn = 1;
    printf("\nWelcome to the Battle! Let's get this started!\n\n");
    
    char *hp_string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
    hp_string = print_start_battle(ctx->game->battle);

    char buf[MAXLEN + 1] = {0};
    char **args = calloc(MAX_ARGS, sizeof(char *));
    int num_args;
    int res;
    while (ctx != NULL && ctx->status == BATTLE_IN_PROGRESS)
    {
        printf("Turn %d:\n", turn);
        printf("%s\n", hp_string);
        printf("What will you do?\n");
        while (true)
        {
            // Get the input
            printf("> ");
            if (!fgets(buf, MAXLEN, stdin))
            {
                break;
            }
            // parse the input
            num_args = parse_command(args, buf);
            // ignore empty line
            if (num_args == 0 || buf[0] == '\n')
            {
                continue;
            }
            // otherwise, handle input
            printf("command: %s\n", buf);
            for (int i = 0; i < MAX_ARGS; i++)
            {
                printf("arg %d: %s\n", i, args[i]);
            }
        }
        res = read_move(args, ctx);
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
    for (int i = 0; i < MAX_ARGS; i++)
    {
        free(args[i]);
    }
    free(args);
    return 0;
}
