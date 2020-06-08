#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle_move_maker.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"

#define MAX_MOVE_NAME_LEN (100)
#define MAX_COMMAND_LINE_LENGTH (100)
#define MAXLEN (100)
#define MAX_ARGS (5)

class_t *make_wizard()
{
    return class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
}

class_t *make_bard()
{
    return class_new("Bard", "Cool", "Super Duper and Awesome", NULL, NULL, NULL);
}

// int print_move_info(chiventure_ctx_battle_t *ctx, char *move_name)
// {
//     move_t *temp;
//     DL_FOREACH(ctx->game->player->moves, temp)
//     {
//         if (strncmp(temp->info, move_name, MAX_MOVE_NAME_LEN) == 0)
//         {
//             printf("%s\n", temp->info);
//             printf("\n");
//             return SUCCESS;
//         }
//         printf("Couldn't find the move you were looking for!\n");
//         return FAILURE;
//     }
// }

int read_move(char **args, chiventure_ctx_battle_t *ctx)
{
    int res;
    char *action_string;
    if ((strncmp(args[0], "MOVE", MAXLEN) == 0) 
        && (strncmp(args[1], "USE", MAXLEN) == 0) 
        && (strncmp(args[3], "ON", MAXLEN) == 0))
    {
        printf("\nDetermined command as MOVE USE, and it using the %s move\n",
                args[2]);
        move_t *temp;
        move_t *player_move = temp;

        DL_FOREACH(ctx->game->battle->player->moves, temp)
        {
            if (strncmp(temp->info, args[2], MAX_MOVE_NAME_LEN) == 0)
            {
                player_move = temp;
            }
        }

        if (player_move == NULL)
        {
            printf("Couldn't find the move you were looking for!\n");
            return FAILURE;
        }

        if(check_target(ctx->game->battle, args[4]) == NULL)
        {
            printf("Enemy not found!\n");
            return FAILURE;
        }

        printf("player's move's damage: %d\n", player_move->damage);
        res = battle_flow(ctx, player_move, args[4]);

        // everything bellow allows us to print what just happened
        if (goes_first(ctx->game->battle) == PLAYER)
        {
            action_string = print_battle_move(ctx->game->battle,
                                              PLAYER, player_move);
            printf("%s\n", action_string);
            if(ctx->game->battle->enemy->stats->hp <= 0)
            {
                return SUCCESS;
            }
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
            if (ctx->game->battle->player->stats->hp <= 0)
            {
                return SUCCESS;
            }
            move_t *enemy_move = give_move(ctx->game->battle->player,
                                           ctx->game->battle->enemy,
                                           ctx->game->battle->enemy->ai);
            action_string = print_battle_move(ctx->game->battle, ENEMY, enemy_move);
            printf("%s\n", action_string);
        }
        return SUCCESS;
    }
    else if ((strncmp(args[0], "MOVE", MAXLEN) == 0) 
            && (strncmp(args[1], "LIST", MAXLEN) == 0))
    {
        printf("\nDetermined command as MOVE LIST\n");
        move_t *temp;
        printf("MOVES LIST:\n");
        DL_FOREACH(ctx->game->battle->player->moves, temp)
        {
            printf("%s\n", temp->info);
        }
        printf("\n");
        return SUCCESS;
    }
    // else if ((strncmp(args[0], "MOVE", MAXLEN) == 0) && (strncmp(args[1], "INFO", MAXLEN) == 0))
    // {
    //     res = print_move_info(ctx, args[2]);
    //     return res;
    // }
    else if (strncmp(args[0], "HELP", MAXLEN) == 0)
    {
        printf("Here are the possible commands!\n");
        printf("MOVE USE <move_name> ON <enemy_name>\n");
        printf("MOVE INFO <move_name>\n\n");
        return SUCCESS;
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
    printf("\nbeginning to create the player and enemy...\n");
    stat_t *p_stats = (stat_t *)calloc(1, sizeof(stat_t));
    p_stats->hp = 200;
    p_stats->strength = 20;
    p_stats->defense = 12;
    p_stats->xp = 100;
    p_stats->level = 5;
    p_stats->speed = 10;

    stat_t *e_stats = (stat_t *)calloc(1, sizeof(stat_t));
    e_stats->hp = 150;
    e_stats->strength = 14;
    e_stats->defense = 9;
    e_stats->xp = 100;
    e_stats->level = 5;
    e_stats->speed = 9;

    npc_enemy_t *e = NULL;
    DL_APPEND(e, make_npc_enemy("Goblin", make_bard(), e_stats, NULL, BATTLE_AI_GREEDY));
    printf("enemy created!\n");
    player_t *p = new_ctx_player("John", make_wizard(), p_stats, NULL);
    printf("player created!\n\n");

    chiventure_ctx_battle_t *ctx =
        (chiventure_ctx_battle_t *)calloc(1, sizeof(chiventure_ctx_battle_t));

    game_t *g = new_game();
    printf("game has been created folks!\n\n");
    ctx->game = g;

    ctx->game->player = p;

    printf("starting battle...\n\n");
    start_battle(ctx, e, ENV_GRASS);

    if (ctx->game->battle->player->moves == NULL)
    {
        printf("=== oh no! the player's moves do not exist!!! ===\n");
    }

    int turn = 1;
    printf("\nWelcome to the Battle! Let's get this started!\n\n");

    char buf[MAXLEN + 1] = {0};
    char **args = calloc(MAX_ARGS, sizeof(char *));
    int num_args;
    int res;
    while (ctx != NULL && ctx->status == BATTLE_IN_PROGRESS)
    {
        printf("What will you do?\n");
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
        res = read_move(args, ctx);
        printf("read move returned: %d\n", res);
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
