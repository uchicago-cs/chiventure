#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_move_maker.h"
#include "battle/battle_moves.h"
#include "battle/battle_print.h"
#include "battle/battle_state.h"
#include "battle/battle_logic.h"
#include "battle/battle_default_objects.h"
#include "npc/npc.h"
#include "npc/npc_battle.h"
#include "move_demo.c"
#include "demo_items_and_equipment.c"
#include <time.h>

#define MAX_COMMAND_LINE_LENGTH (100)
#define MAX_COMMAND_LENGTH (100)
#define MAX_ARGS (5)

/* Makes a dumby sorcerer class */
class_t *make_sorcerer()
{
    return class_new("Sorcerer", "Wise", "Old and wise with crazy magecraft ability", NULL, NULL, NULL);
}

/* Makes a dumby minion class */
class_t *make_minion()
{
    return class_new("Minion", "Stupid", "Unintelligent, but very strong", NULL, NULL, NULL);
}

/* Prints out the avaliable moves for the player
 * Parameter:
 *  ctx: the main structure of the battle
 * Returns:
 *  Always SUCCESS
 */
int print_moves2(battle_ctx_t *ctx)
{
    move_t *temp;
    printf("\nMOVES LIST:\n");
    DL_FOREACH(ctx->game->battle->player->moves, temp)
    {
        printf("%s\n", temp->name);
    }
    return SUCCESS;
}

/* Prints out the avaliable battle_items for the player
 * Parameter:
 *  ctx: the main structure of the battle
 * Returns:
 *  Always SUCCESS
 */ 
int print_battle_items2(battle_ctx_t *ctx)
{
    battle_item_t *temp;
    printf("\nAVAILABLE BATTLE ITEMS LIST:\n");
    DL_FOREACH(ctx->game->battle->player->items, temp)
    {
        printf("Name: %s\n", temp->name);
        printf("ID: %d\n", temp->id);
        printf("Description: %s\n", temp->description);
        printf("Quantity: %d\n", temp->quantity);
    }
    return SUCCESS;
}

/* Reads the user's input and converts that into an action
 * Parameters:
 *  args: array of strings that display the user's input
 *  ctx: the main structure of the battle
 * Returns:
 *  SUCCESS or FAILURE
 */
int read_move(char **args, battle_ctx_t *ctx)
{
    int res;

    // this handles the command MOVE USE <move> ON <enemy_name>
    if ((strncmp(args[0], "MOVE", MAX_COMMAND_LENGTH) == 0) 
        && (strncmp(args[1], "USE", MAX_COMMAND_LENGTH) == 0) 
        && (strncmp(args[3], "ON", MAX_COMMAND_LENGTH) == 0))
    {
        printf("Determined command as MOVE USE, and using the move %s\n\n",
                args[2]);
        
        move_t *player_move = find_player_move(ctx, args[2]);

        // checks if the player's move is NULL, if so, return FAILURE
        if (player_move == NULL)
        {
            printf("Couldn't find the move you were looking for!\n");
            return FAILURE;
        }

        // call to check_target to ensure that the target exists
        printf("Calling check_target...\n");
        if(check_target(ctx->game->battle, args[4]) == NULL)
        {
            printf("%s\n", ctx->game->battle->enemy->name);
            printf("%s\n", args[4]);
            printf("Enemy not found!\n");
            return FAILURE;
        }
        printf("target exists!\n");

        printf("\nBeginning call to battle_flow() function\n");
        // calling the function which is the heart of the battle
        char *rs = battle_flow_move(ctx, player_move, args[4]);
        printf("%s", rs);
        // prints result of attacks
        int battle_res = print_battle_result(ctx, player_move);
        if (ctx->game->battle->enemy->stats->hp > 0) 
        {
            char *enemy_rs = enemy_make_move(ctx);
            printf("%s",enemy_rs);
        }
        
        return battle_res;
    }
    // handles the command MOVE LIST
    else if ((strncmp(args[0], "MOVE", MAX_COMMAND_LENGTH) == 0) 
            && (strncmp(args[1], "LIST", MAX_COMMAND_LENGTH) == 0))
    {
        printf("Determined command as MOVE LIST\n\n");
        res = print_moves2(ctx);
        printf("\n");
        return res;
    }
    // handles the command ITEM LIST
    else if ((strncmp(args[0], "ITEM", MAX_COMMAND_LENGTH) == 0) 
            && (strncmp(args[1], "LIST", MAX_COMMAND_LENGTH) == 0))
    {
        printf("Determined command as ITEM LIST\n\n");
        res = print_battle_items2(ctx);
        printf("\n");
        return res;
    }
    // handles the command HELP
    else if (strncmp(args[0], "HELP", MAX_COMMAND_LENGTH) == 0)
    {
        // prints out possible commands for the user to use
        printf("Here are the possible commands!\n");
        printf("MOVE USE <move_name> ON <enemy_name>\n");
        printf("MOVE LIST\n");
        printf("ITEM LIST\n");
        printf("USE <item_id>\n\n");
        return SUCCESS;
    }
    // handles the command USE <battle_item>
    else if (strncmp(args[0], "USE", MAX_COMMAND_LENGTH) == 0) 
    {
        battle_item_t *item = find_battle_item(ctx->game->battle->player->items, args[1]);
        
        if (item == NULL)
        {
            printf("Couldn't find the battle item you were looking for!\n");
            return FAILURE;
        }
        if (item->quantity <= 0)
        {
            printf("Sorry, you don't have any more of that battle item!\n");
            return FAILURE;
        }
        printf("Determined command as USE %s\n\n", item->name);
        char *res_str = battle_flow_item(ctx, item);
        if (!strcmp(res_str, "FAILURE\n"))
        {
            printf("Failure\n");
            return FAILURE;
        } 
        else 
        {
            stat_t *player_stats = ctx->game->battle->player->stats;
            
            printf("%s\n", res_str);
            if (ctx->game->battle->enemy->stats->hp > 0) 
            {
                char *enemy_rs = enemy_make_move(ctx);
                printf("%s",enemy_rs);
            }
        }

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

/* Allows a battle to continue with taking input from the user via command line
 * Parameter:
 *  ctx: main structure of the battle
 * Returns:
 *  Always SUCCESS
 */ 
int continue_battle(battle_ctx_t *ctx)
{
    char buf[MAX_COMMAND_LENGTH + 1] = {0};
    char **args = calloc(MAX_ARGS, sizeof(char *));
    int num_args;
    int res;
    while (ctx != NULL && ctx->status == BATTLE_IN_PROGRESS)
    {
        printf("What will you do?\n");
        // Get the input
        printf("> ");
        char **args = calloc(MAX_ARGS, sizeof(char *));
        if (!fgets(buf, MAX_COMMAND_LENGTH, stdin))
        {
            break;
        }
        // parse the input
        num_args = parse_command(args, buf);
        // ignore empty line
        if (num_args == 0 || buf[0] == '\n')
        {
            printf("Num args is 0\n");
            continue;
        }
    }
    return SUCCESS;
}

//where everything is called
int main()
{
    srand(time(0)); // sets seed
    printf("\nbeginning to create the player and enemy...\n");
    // creates the stats of the player to begin the battle
    stat_t *p_stats = (stat_t*) calloc(1, sizeof(stat_t));
    p_stats->hp = 100;
    p_stats->max_hp = 100;
    p_stats->xp = 10;
    p_stats->speed = 10;
    p_stats->level = 3;
    p_stats->phys_def = 30;
    p_stats->mag_def = 30;
    p_stats->phys_atk = 80;
    p_stats->mag_atk = 80;
    p_stats->sp = 100;
    p_stats->max_sp = 100;
    p_stats->crit = 25;
    p_stats->accuracy = 100;
    move_t *user_moves = generate_moves_user_one();
    battle_player_t *p = new_ctx_player("Sorcerer John", make_sorcerer(), p_stats, user_moves, make_items(), 
                                        make_lunar_wand(), make_omni_crown(), make_cape_of_wisdom());
    printf("player created!\n\n");
    printf("\nPlayer stats:\n");
    printf("HP: %d\n", p_stats->hp);
    printf("SP: %d\n", p_stats->sp);
    printf("Physical Defense: %d\n", p_stats->phys_def);
    printf("Physical Attack: %d\n", p_stats->phys_atk);
    printf("Magical Defense: %d\n", p_stats->mag_def);
    printf("Magical Attack: %d\n", p_stats->mag_atk);
    printf("XP: %d\n", p_stats->xp);
    printf("Level: %d\n", p_stats->level);
    printf("Speed: %d\n", p_stats->speed);
    printf("Accuracy: %d\n", p_stats->accuracy);
    printf("Crit: %d\n", p_stats->crit);
    

    // creates the stats of the enemy to begin the battle
    stat_t *e_stats = (stat_t*) calloc(1, sizeof(stat_t));
    e_stats->hp = 70;
    e_stats->max_hp = 70;
    e_stats->xp = 10;
    e_stats->speed = 9;
    e_stats->level = 6;
    e_stats->phys_def = 30;
    e_stats->mag_def = 30;
    e_stats->phys_atk = 70;
    e_stats->mag_atk = 70;
    e_stats->sp = 100;
    e_stats->max_sp = 100;
    e_stats->crit = 25;
    e_stats->accuracy = 100;


    move_t *e_moves = generate_moves_enemy_one();
    npc_t *e = npc_new("Minion", "Enemy minion!", "Enemy minion!", make_minion(), NULL, HOSTILE);
    npc_battle_t *npc_b = npc_battle_new(e_stats, e_moves, BATTLE_AI_GREEDY, HOSTILE, make_minion(), 
                                        make_items(), NULL, NULL, NULL);
    printf("item created for the player!\n");
    e->npc_battle = npc_b;
    printf("enemy created!\n");
    printf("\nEnemy stats:\n");
    printf("HP: %d\n", e_stats->hp);
    printf("SP: %d\n", e_stats->sp);
    printf("Physical Defense: %d\n", e_stats->phys_def);
    printf("Physical Attack: %d\n", e_stats->phys_atk);
    printf("Magical Defense: %d\n", e_stats->mag_def);
    printf("Magical Attack: %d\n", e_stats->mag_atk);
    printf("XP: %d\n", e_stats->xp);
    printf("Level: %d\n", e_stats->level);
    printf("Speed: %d\n", e_stats->speed);
    printf("Accuracy: %d\n", e_stats->accuracy);
    printf("Crit: %d\n", e_stats->crit);

    battle_ctx_t *ctx = (battle_ctx_t *) calloc(1, sizeof(battle_ctx_t));

    // new_game creates a game that is then attached to ctx
    battle_game_t *g = new_battle_game();
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

    printf("\nWelcome to the Battle! Let's get this started!\n\n");

    // prints the beginning of the battle 
    char *start = print_start_battle(ctx->game->battle);
    printf("%s\n", start);
    // begins call to loop battle
    int res = continue_battle(ctx);
    // declares a winner for the battle if it is deemed as over
    battle_status_t winner = battle_over(ctx->game->battle);

    // prints who won the battle
    char *win_string = print_battle_winner(ctx->status, 20);
    printf("%s\n", win_string);

    // this confirms with us that the victor should be the player
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

    return 0;
}
