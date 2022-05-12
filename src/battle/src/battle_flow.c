#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "battle/battle_print.h"

/* see battle_flow.h */
int start_battle(battle_ctx_t *ctx, npc_t *npc_enemy, environment_t env)
{
    battle_game_t *g = ctx->game;
    battle_player_t *player = g->player;
    // Set battle_player, enemies, and battle structs for a new battle
    battle_t *b = set_battle(player, npc_enemy, env);

    g->battle = b;
    ctx->status = BATTLE_IN_PROGRESS;
    return SUCCESS;
}

/* see battle_flow.h */
combatant_t *set_battle_player(battle_player_t *ctx_player)
{
    // Setting up arguments for combatant_new
    char* name = ctx_player->player_id;
    bool is_friendly = true;
    class_t *c_type = ctx_player->class_type;
    stat_t *stats = ctx_player->stats;
    move_t *moves = ctx_player->moves;
    battle_item_t *items = ctx_player->items;

    // Allocating new combatant_t for the player in memory
    combatant_t *comb_player = combatant_new(name, is_friendly, c_type, stats,
                                             moves, items, BATTLE_AI_NONE);

    assert(comb_player != NULL);

    return comb_player;
}

/* see battle_flow.h */
combatant_t *set_enemy(npc_t *npc_enemy)
{
    if (npc_enemy->npc_battle == NULL)
    {
        return NULL;
    }

    combatant_t *comb_enemy;

    char* name = npc_enemy->npc_id;
    bool is_friendly = false;
    class_t *c_type = npc_enemy->class;
    stat_t *stats = npc_enemy->npc_battle->stats;
    move_t *moves = npc_enemy->npc_battle->moves;
    battle_item_t *items = NULL; // TODO: extract battle_item_t from npc's inventory
    difficulty_t ai = npc_enemy->npc_battle->ai;
    
    comb_enemy = combatant_new(name, is_friendly, c_type, stats, moves, items, ai);
    assert(comb_enemy != NULL);

    return comb_enemy;
}

/* see battle_flow.h */
battle_t *set_battle(battle_player_t *ctx_player, npc_t *npc_enemy, environment_t env)
{
    combatant_t *comb_player  = set_battle_player(ctx_player);
    combatant_t *comb_enemies = set_enemy(npc_enemy);

    /* Builds a move list using player class module */
    if (comb_player->moves == NULL)
    {
        build_moves(comb_player);
    }
    if (comb_enemies->moves == NULL)
    {
        build_moves(comb_enemies); // This will have to be updated if multiple enemies are added
    }
    
    turn_t turn = PLAYER;

    battle_t *b = battle_new(comb_player, comb_enemies, env, turn);

    assert(b != NULL);

    return b;
}

/* see battle_flow.h */
char *battle_flow_move(battle_ctx_t *ctx, move_t *move, char* target)
{
    battle_t *b = ctx->game->battle;

    /* the following 3 if statements are stubs, error handling must be clarified
       with custom actions at a later date */
    if (ctx == NULL || move == NULL || target == NULL)
    {
        return "FAILURE";
    }
    combatant_t *enemy = check_target(b, target);
    
    if(enemy == NULL)
    {
        /* print stub: should tell player that their target was invalid
           battle_flow then returns the original, unmodified ctx and waits
           for the next move */
        return "Non-valid enemy chosen";
    }
    
    /* move stub, battle_flow should call either a custom action block or a
       function that works with a move_t struct */
    /* additionally, a check must be performed here to see if player has
       this move, currently not implemented, waiting for player class
       to resolve move_lists() */
    int dmg, rc;
    char *string;

    /* Calculates to see if the move will miss */
    if (!calculate_accuracy(b->player->stats->accuracy, move->accuracy))
    {
        string = print_battle_miss(b, b->turn, move);
    }
    else
    {
        string = print_battle_move(b, b->turn, move);
        if (move->dmg_type != NO_DAMAGE)
        {
            dmg = damage(b->enemy, move, b->player);
            enemy->stats->hp -= dmg;
            //print_battle_move needs to be changed
            rc = print_battle_damage(b, b->turn, move, string);
            assert(rc == SUCCESS);
        }
        if (move->stat_mods != NO_TARGET)
        {
            use_stat_change_move(b->enemy, move, b->player);
            rc = print_stat_changes(b, b->turn, move, string);
            assert(rc == SUCCESS);

        }
        if (move->effects != NO_TARGET)
        {
            //to be implemented in the future
        }
    }
    

    if(battle_over(b) == BATTLE_VICTOR_PLAYER)
    {
        /* print stub: should tel player they won */
        award_xp(b->player->stats, 2.0);
        ctx->status = BATTLE_VICTOR_PLAYER;
    }
    
    if(battle_over(b) == BATTLE_IN_PROGRESS)
    {
        char *res = enemy_make_move(ctx);
        strncat(string, res, 150);
        free(res);
    }

    return string;
}

char *battle_flow_item(battle_ctx_t *ctx, battle_item_t *item)
{
    battle_t *b = ctx->game->battle;
    char *string = calloc(150, sizeof(char));

    if (ctx == NULL)
    {
        snprintf(string, 150, "FAILURE\n");
        return string;
    }
    if (item == NULL)
    {
        snprintf(string, 150, "FAILURE\n");
        return string;
    }
    if (item->quantity <= 0){
       snprintf(string, 150, "FAILURE\n");
        return string;
    }

    char *item_name;
    strcpy(item_name, item->name);

    int usage = use_battle_item(ctx->game->battle->player, ctx->game->battle, item->name);
    snprintf(string, 150, "You used the %s\n", item_name);

    if (usage == FAILURE) 
    {
        snprintf(string, 150, "That item is Unavailable.\n");
        return string;
    } 

    if(battle_over(b) == BATTLE_IN_PROGRESS)
    {
        char *res = enemy_make_move(ctx);
        strncat(string, res, 150);
        free(res);
    }

    return string;
}

/* see battle_flow.h */
char *battle_flow_list(battle_ctx_t *ctx, char* label)
{
    if (strcmp(label, "items") == 0) 
    {
        battle_t *b = ctx->game->battle;

        char *string = calloc(500, sizeof(char));
        print_battle_items(b, string);

        return string;
    } if (strcmp(label, "moves") == 0) 
    {
        battle_t *b = ctx->game->battle;

        char *string = calloc(500, sizeof(char));
        print_moves(b, string);

        return string;
    } else 
    {
             
        char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
        snprintf(string, BATTLE_BUFFER_SIZE, "Please enter a valid battle command!");
        
        return string;
    }
}

/* see battle_flow.h */
char *enemy_make_move(battle_ctx_t *ctx) 
{
    battle_t *b = ctx->game->battle;
    b->turn = ENEMY;

    /* move stub, battle_flow should call either a custom action block or a
       function that works with a move_t struct */
    move_t *enemy_move = give_move(b->player, b->enemy, b->enemy->ai);
    int dmg, rc;
    char *string = calloc(100, sizeof(char));

    if(enemy_move != NULL)
    {
        /* Calculates to see if the move will miss */
        if(!calculate_accuracy(b->enemy->stats->accuracy, enemy_move->accuracy)){
            dmg = 0;
            b->player->stats->hp -= dmg;
            string = print_battle_miss(b, b->turn, enemy_move);
        }else{
            string = print_battle_move(b, b->turn, enemy_move);
            if (enemy_move->dmg_type != NO_DAMAGE)
            {
                dmg = damage(b->player, enemy_move, b->enemy);
                b->player->stats->hp -= dmg;
                rc = print_battle_damage(b, b->turn, enemy_move, string);
                assert(rc == SUCCESS);
            }
            if (enemy_move->stat_mods != NO_TARGET)
            {
                use_stat_change_move(b->player, enemy_move, b->enemy);
                rc = print_stat_changes(b, b->turn, enemy_move, string);
                assert(rc == SUCCESS);
            }
            if (enemy_move->effects != NO_TARGET)
            {
                //to be implemented in the future
            }
        }
        
    }
    
    if(battle_over(b) == BATTLE_VICTOR_ENEMY)
    {
        /* print stub: should tell player they lost */
        ctx->status = BATTLE_VICTOR_ENEMY;
    }

    b->turn = PLAYER;

    return string;
}

int apply_stat_changes(stat_changes_t* changes, stat_t* target_stats)
{
    target_stats->speed += changes->speed;
    target_stats->max_sp += changes->max_sp;
    target_stats->sp += changes->sp;
    target_stats->phys_atk += changes->phys_atk;
    target_stats->mag_atk += changes->mag_atk;
    target_stats->phys_def += changes->phys_def;
    target_stats->mag_def += changes->mag_def;
    target_stats->crit += changes->crit;
    target_stats->accuracy += changes->accuracy;
    target_stats->hp += changes->hp;
    target_stats->max_hp += changes->max_hp;
    return SUCCESS;
}

int use_stat_change_move(combatant_t* target, move_t* move, combatant_t* source)
{
    stat_t* user_stats = source->stats;
    stat_t* target_stats = target->stats;
    if ((move->user_mods == NULL) || (move->opponent_mods == NULL))
    {
        return FAILURE;
    }
    switch(move->stat_mods)
    {
        case USER:
            apply_stat_changes(user_stats, move->user_mods);
            break;
        case TARGET:
            apply_stat_changes(target_stats, move->opponent_mods);
            break;
        case BOTH:
            apply_stat_changes(user_stats, move->user_mods);
            apply_stat_changes(target_stats, move->opponent_mods);
            break;
        default:
            return FAILURE;
            break;
    }
    return SUCCESS;   
}


/* see battle_flow.h */
int calculate_accuracy(int user_accuracy, int move_accuracy)
{
    int chance = randnum(0, 100);
    if(chance <= (user_accuracy * move_accuracy)){
        return 1;
    }else{
        return 0;
    }
}
