#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "battle/battle_print.h"


/* see battle_flow.h */
int start_battle(battle_ctx_t *ctx, npc_t *npc_enemy, environment_t env)
{
    // battle game from the given battle context
    battle_game_t *g = ctx->game;
    // battle player from the given battle game
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
    battle_equipment_t *weapon = ctx_player->weapon; 
    battle_equipment_t *accessory = ctx_player->accessory; 
    battle_equipment_t *armor = ctx_player->armor;
    stat_t *with_equipment = (stat_t *) calloc (1, sizeof(stat_t *));
    with_equipment = stats;
    if (weapon != NULL)
    {
        with_equipment->max_sp+=weapon->attributes->max_sp;
        with_equipment->sp+=weapon->attributes->sp;
        with_equipment->phys_atk+=weapon->attributes->phys_atk;
        with_equipment->mag_atk+=weapon->attributes->mag_atk;
        with_equipment->phys_def+=weapon->attributes->phys_def;
        with_equipment->mag_def+=weapon->attributes->mag_def;
        with_equipment->crit+=weapon->attributes->crit;
        with_equipment->accuracy+=weapon->attributes->accuracy;
        with_equipment->hp+=weapon->attributes->hp;
        with_equipment->max_hp+=weapon->attributes->max_hp;
    }
    if (accessory !=NULL)
    {
        with_equipment->max_sp+=accessory->attributes->max_sp;
        with_equipment->sp+=accessory->attributes->sp;
        with_equipment->phys_atk+=accessory->attributes->phys_atk;
        with_equipment->mag_atk+=accessory->attributes->mag_atk;
        with_equipment->phys_def+=accessory->attributes->phys_def;
        with_equipment->mag_def+=accessory->attributes->mag_def;
        with_equipment->crit+=accessory->attributes->crit;
        with_equipment->accuracy+=accessory->attributes->accuracy;
        with_equipment->hp+=accessory->attributes->hp;
        with_equipment->max_hp+=accessory->attributes->max_hp;
    }
    if (armor != NULL)
    {
        with_equipment->max_sp+=armor->attributes->max_sp;
        with_equipment->sp+=armor->attributes->sp;
        with_equipment->phys_atk+=armor->attributes->phys_atk;
        with_equipment->mag_atk+=armor->attributes->mag_atk;
        with_equipment->phys_def+=armor->attributes->phys_def;
        with_equipment->mag_def+=armor->attributes->mag_def;
        with_equipment->crit+=armor->attributes->crit;
        with_equipment->accuracy+=armor->attributes->accuracy;
        with_equipment->hp+=armor->attributes->hp;
        with_equipment->max_hp+=armor->attributes->max_hp;
    }                                              
    // Allocating new combatant_t for the player in memory
    combatant_t *comb_player = combatant_new(name, is_friendly, c_type, with_equipment,
                                             moves, items, weapon, accessory,
                                             armor, BATTLE_AI_NONE);

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
    battle_equipment_t *weapon = npc_enemy->npc_battle->weapon; 
    battle_equipment_t *accessory = npc_enemy->npc_battle->accessory; 
    battle_equipment_t *armor = npc_enemy->npc_battle->armor;
    // we will need to update npc_battle_t after npc is done with their merge
    stat_t *with_equipment = (stat_t *) calloc (1, sizeof(stat_t *));
    with_equipment = stats;
    if (weapon != NULL)
    {
        with_equipment->max_sp+=weapon->attributes->max_sp;
        with_equipment->sp+=weapon->attributes->sp;
        with_equipment->phys_atk+=weapon->attributes->phys_atk;
        with_equipment->mag_atk+=weapon->attributes->mag_atk;
        with_equipment->phys_def+=weapon->attributes->phys_def;
        with_equipment->mag_def+=weapon->attributes->mag_def;
        with_equipment->crit+=weapon->attributes->crit;
        with_equipment->accuracy+=weapon->attributes->accuracy;
        with_equipment->hp+=weapon->attributes->hp;
        with_equipment->max_hp+=weapon->attributes->max_hp;
    }
    if (accessory !=NULL)
    {
        with_equipment->max_sp+=accessory->attributes->max_sp;
        with_equipment->sp+=accessory->attributes->sp;
        with_equipment->phys_atk+=accessory->attributes->phys_atk;
        with_equipment->mag_atk+=accessory->attributes->mag_atk;
        with_equipment->phys_def+=accessory->attributes->phys_def;
        with_equipment->mag_def+=accessory->attributes->mag_def;
        with_equipment->crit+=accessory->attributes->crit;
        with_equipment->accuracy+=accessory->attributes->accuracy;
        with_equipment->hp+=accessory->attributes->hp;
        with_equipment->max_hp+=accessory->attributes->max_hp;
    }
    if (armor != NULL)
    {
        with_equipment->max_sp+=armor->attributes->max_sp;
        with_equipment->sp+=armor->attributes->sp;
        with_equipment->phys_atk+=armor->attributes->phys_atk;
        with_equipment->mag_atk+=armor->attributes->mag_atk;
        with_equipment->phys_def+=armor->attributes->phys_def;
        with_equipment->mag_def+=armor->attributes->mag_def;
        with_equipment->crit+=armor->attributes->crit;
        with_equipment->accuracy+=armor->attributes->accuracy;
        with_equipment->hp+=armor->attributes->hp;
        with_equipment->max_hp+=armor->attributes->max_hp;
    }
    comb_enemy = combatant_new(name, is_friendly, c_type, with_equipment,
                            moves, items, weapon, accessory, armor, ai);
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
    double crit;
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
            crit = crit_modifier(b->player->stats->crit);
            dmg *= crit;
            //print_battle_move needs to be changed
            rc = print_battle_damage(b, b->turn, move, crit, string);
            assert(rc == SUCCESS);
        }
        if (move->stat_mods != NO_TARGET)
        {
            use_stat_change_move(b->enemy, move, b->player);
            rc = print_stat_changes_move(b, b->turn, move, string);
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
    if(battle_over(b) == BATTLE_ENEMY_SURRENDER)
    {
        /* print stub: should tel player they won */
        award_xp(b->player->stats, 2.0);
        ctx->status = BATTLE_ENEMY_SURRENDER;
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

/* see battle_flow.h*/
char *enemy_run_turn(battle_ctx_t *ctx) 
{
    char *res_string;
    while (ctx->game->battle->current_tc)
    {
        res_string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
        if(ctx->game->battle->current_tc->move) 
        {
            char *enemy_move_report = enemy_make_move(ctx);
            strcat(res_string, enemy_move_report);
        }
  }
  return res_string;
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
    double crit;
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
                crit = crit_modifier(b->enemy->stats->crit);
                dmg *= crit;
                rc = print_battle_damage(b, b->turn, enemy_move, crit, string);
                assert(rc == SUCCESS);
            }
            if (enemy_move->stat_mods != NO_TARGET)
            {
                use_stat_change_move(b->player, enemy_move, b->enemy);
                rc = print_stat_changes_move(b, b->turn, enemy_move, string);
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

/* see battle_flow.h */
char *run_action(char *input, chiventure_ctx_t *ctx)
{
    if (input[0] == 'M' || input[0] == 'm')
    {
        // take the index of the move, under the assumption that the list is less than 10 moves long
        int index = (int) (input[1] - 48);
        for (int k = 0; k < index; k++)
        {
            if (ctx->game->battle_ctx->game->player->moves == NULL)
            {
                return "That move does not exist.";
            }
            if (k == index-1)
            {
                    return battle_flow_move(ctx->game->battle_ctx, 
                                ctx->game->battle_ctx->game->player->moves, 
                                ctx->game->battle_ctx->game->battle->enemy->name);
            }
            else
            {
                ctx->game->battle_ctx->game->player->moves = 
                ctx->game->battle_ctx->game->player->moves->next;
            }
        }
    } 
    else if (input[0] == 'I' || input[0] == 'i')
    {
        int index = (int) (input[1] - 48);
        for (int k = 0; k < index; k++)
        {
            if (ctx->game->battle_ctx->game->player->items == NULL)
            {
                return "That item does not exist.";
            }
            if (k == index-1)
            {
                return battle_flow_item(ctx->game->battle_ctx, 
                                ctx->game->battle_ctx->game->player->items);
            }
            else 
            {
                ctx->game->battle_ctx->game->player->items = 
                ctx->game->battle_ctx->game->player->items->next;
            }
        }
    } 
    else if (input[0] == 'D' || input[0] == 'd') 
    {
        return "You did nothing.";
    } 
    return "That action does not exist.";
}

/* see battle_flow.h */
int use_stat_change_move(combatant_t* target, move_t* move, combatant_t* source)
{
    stat_t* user_stats = source->stats;
    stat_t* target_stats = target->stats;
    if ((move->user_mods == NULL) && (move->opponent_mods == NULL))
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
    if(chance <= ((user_accuracy * move_accuracy) / 100)){
        return 1;
    }else{
        return 0;
    }
}

/* see battle_flow.h */
double crit_modifier(int crit_chance)
{
    int chance = randnum(1, 100);

    if (chance <= crit_chance)
    {
        return 1.5;
    }
    else
    {
        return 1;
    }
}