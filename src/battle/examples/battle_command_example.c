#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle_move_maker.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"

#define MAX_COMMAND_LINE_LENGTH (100)
#define MAX_COMMAND_LENGTH (100)
#define MAX_ARGS (5)

/* initializes a dummy wizard class */
class_t *make_wizard()
{
    return class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
}

/* initializes a dummy bard class */
class_t *make_bard()
{
    return class_new("Bard", "Cool", "Super Duper and Awesome", NULL, NULL, NULL);
}

/* This ensures that the user's inputted move exists
 * Parameters:
 *  ctx: main structure of the game
 * Returns:
 *  a pointer to the found move or NULL for no move 
 */ 
move_t *find_player_move(chiventure_ctx_battle_t *ctx, char *move_name)
{
    move_t *temp;
    move_t *player_move = NULL;

    DL_FOREACH(ctx->game->battle->player->moves, temp)
    {
        if (strncmp(temp->info, move_name, MAX_MOVE_INFO_LEN) == 0)
        {
            player_move = temp;
            return player_move;
        }
    }
    return NULL;
}

/* Helper function to print the result of a turn
 * Parameters:
 *  ctx: main structure of the game
 *  player_move: the name of the player's move
 * Returns:
 *  Always returns SUCCESS
 */ 
int print_battle_result(chiventure_ctx_battle_t *ctx, move_t *player_move)
{
    char *action_string;
    // everything below allows us to print what just happened
    if (goes_first(ctx->game->battle) == PLAYER)
    {
        printf("goes_first determined the player goes first!\n");
        action_string = print_battle_move(ctx->game->battle,
                                          PLAYER, player_move);
        printf("%s\n", action_string);
        if (ctx->game->battle->enemy->stats->hp <= 0)
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
        printf("goes_first determined the enemy goes first!\n");
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

/* Prints out the avaliable moves for the player
 * Parameter:
 *  ctx: the main structure of the game
 * Returns:
 *  Always SUCCESS
 */ 
int print_moves(chiventure_ctx_battle_t *ctx)
{
    move_t *temp;
    printf("\nMOVES LIST:\n");
    DL_FOREACH(ctx->game->battle->player->moves, temp)
    {
        printf("%s\n", temp->info);
    }
    return SUCCESS;
}

/* this function reads the user's input and converts that into an action
 * Parameters:
 *  args: array of strings that display the user's input
 *  ctx: the main structure of the game
 * Returns:
 *  SUCCESS or FAILURE
 */
int read_move(char **args, chiventure_ctx_battle_t *ctx)
{
    int res;

    // this handles the command MOVE USE <move> ON <enemy_name>
    if ((strncmp(args[0], "MOVE", MAX_COMMAND_LENGTH) == 0) 
        && (strncmp(args[1], "USE", MAX_COMMAND_LENGTH) == 0) 
        && (strncmp(args[3], "ON", MAX_COMMAND_LENGTH) == 0))
    {
        printf("Determined command as MOVE USE, and it using the %s move\n\n",
                args[2]);
        
        move_t *player_move = find_player_move(ctx, args[2]);

        // checks if the player's move is NULL, if so, return FAILURE
        if (player_move == NULL)
        {
            printf("Couldn't find the move you were looking for!\n");
            return FAILURE;
        }

        // call to check_target to ensure that the target exists
        printf("calling check_target...\n");
        if(check_target(ctx->game->battle, args[4]) == NULL)
        {
            printf("Enemy not found!\n");
            return FAILURE;
        }
        printf("target exists!\n");

        printf("\nBeginning call to battle_flow() function\n");
        // calling the function which is the heart of the battle
        res = battle_flow(ctx, player_move, args[4]);

        // prints result of attacks
        int battle_res = print_battle_result(ctx, player_move);
        return battle_res;
    }
    // handles the command MOVE LIST
    else if ((strncmp(args[0], "MOVE", MAX_COMMAND_LENGTH) == 0) 
            && (strncmp(args[1], "LIST", MAX_COMMAND_LENGTH) == 0))
    {
        printf("Determined command as MOVE LIST\n\n");
        res = print_moves(ctx);
        printf("\n");
        return res;
    }
    // handles the command HELP
    else if (strncmp(args[0], "HELP", MAX_COMMAND_LENGTH) == 0)
    {
        // prints out possible commands for the user to use
        printf("Here are the possible commands!\n");
        printf("MOVE USE <move_name> ON <enemy_name>\n");
        printf("MOVE INFO <move_name>\n\n");
        return SUCCESS;
    }
    else
    {
        // this only occurs if the user does not input the correct command
        return FAILURE;
    }
    return res;
}

/* Parses a command into an array of strings
 * Parameters:
 *  out: the array of strings
 *  input: the string containing the whole command
 * Returns:
 *  Array of strings with parsed input
 */ 
int parse_command(char **out, char *input)
{
    for (int i = 0; i < MAX_ARGS; i++)
    {
        out[i] = calloc(MAX_COMMAND_LENGTH + 1, sizeof(char));
    }
    return sscanf(input, " %s %s %s %s %s ", out[0], out[1], out[2], out[3], out[4]);
}

// where everything is called
int main()
{
    printf("\nbeginning to create the player and enemy...\n");
    // this creates the stats of the player to begin the battle
    stat_t *p_stats = (stat_t *)calloc(1, sizeof(stat_t));
    p_stats->hp = 50;
    p_stats->strength = 20;
    p_stats->defense = 12;
    p_stats->xp = 100;
    p_stats->level = 5;
    p_stats->speed = 10;

    // this creates the stats of the enemy to begin the battle
    stat_t *e_stats = (stat_t *)calloc(1, sizeof(stat_t));
    e_stats->hp = 30;
    e_stats->strength = 14;
    e_stats->defense = 9;
    e_stats->xp = 100;
    e_stats->level = 5;
    e_stats->speed = 9;

    // this creates the player and enemy so that they are inside of ctx
    npc_enemy_t *e = NULL;
    DL_APPEND(e, make_npc_enemy("Goblin", make_bard(), e_stats, NULL, NULL, BATTLE_AI_GREEDY));
    printf("enemy created!\n");
    player_t *p = new_ctx_player("John", make_wizard(), p_stats, NULL, NULL);
    printf("player created!\n\n");

    chiventure_ctx_battle_t *ctx =
        (chiventure_ctx_battle_t *)calloc(1, sizeof(chiventure_ctx_battle_t));

    // new_game creates a game that is then attached to ctx
    game_t *g = new_game();
    printf("game has been created folks!\n\n");
    ctx->game = g;

    ctx->game->player = p;

    /* start_battle begins the battle by finalizing 
       all finishing touches for a battle to begin */
    printf("starting battle...\n\n");
    start_battle(ctx, e, ENV_GRASS);

    /* this checks to ensure that the user has moves, if not, 
       the executable will not work since it revolves around moves! */
    if (ctx->game->battle->player->moves == NULL)
    {
        printf("=== oh no! the player's moves do not exist!!! ===\n");
    }

    int turn = 1;
    printf("\nWelcome to the Battle! Let's get this started!\n\n");

    char *start = print_start_battle(ctx->game->battle);
    printf("%s\n", start);
    char buf[MAX_COMMAND_LENGTH + 1] = {0};
    char **args = calloc(MAX_ARGS, sizeof(char *));
    int num_args;
    int res;
    while (ctx != NULL && ctx->status == BATTLE_IN_PROGRESS)
    {
        printf("What will you do?\n");
        // Get the input
        printf("> ");
        if (!fgets(buf, MAX_COMMAND_LENGTH, stdin))
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
