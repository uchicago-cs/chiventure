#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_print.h"

/* see battle_print.h */
char *print_start_battle(battle_t *b)
{
    char *enemy_name = b->enemy->name;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;

    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

    snprintf(string, BATTLE_BUFFER_SIZE, "You have encountered %s!\n\n"
                    "Let the battle begin!\n",
                    enemy_name);

    return string;
}

/* see battle_print.h */
int print_hp(battle_t* b, char* string)
{
    int player_hp = b->player->stats->hp;

    int slen = strnlen(string, BATTLE_BUFFER_SIZE + 1);
    int n;

    char temp[BATTLE_BUFFER_SIZE + 1];

    n = snprintf(temp, BATTLE_BUFFER_SIZE, "-- Your HP: %d\n", player_hp);
    strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    slen += n;


    combatant_t *enemies = b->enemy;
    combatant_t *enemy_elt;
    DL_FOREACH(enemies, enemy_elt)
    {
        char* name = enemy_elt->name;
        int enemy_hp = enemy_elt->stats->hp;

        n = snprintf(temp, BATTLE_BUFFER_SIZE, "-- %s's HP: %d\n", name, enemy_hp);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }

    return SUCCESS;
}

/* see battle_print.h */
char *print_battle_move(battle_t *b, turn_t turn, move_t *move)
{
    char *move_name = move->name;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;
    char* enemy_name = b->enemy->name;
    char* combatant_name;

    if (turn == PLAYER)
    {
        combatant_name = "You";
    } else
    {
        combatant_name = enemy_name;
    }

    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

    snprintf(string, BATTLE_BUFFER_SIZE, "%s used %s! ",
             combatant_name, move_name);

    return string;
}

/* see battle_print.h */
int print_battle_damage(battle_t *b, turn_t turn, move_t *move, char *string)
{
    char *move_name = move->name;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;
    int dmg;

    if (turn == PLAYER)
    {
        dmg = damage(b->enemy, move, b->player);
    } else
    {
        dmg = damage(b->player, move, b->enemy);
    }
    int slen = strnlen(string, BATTLE_BUFFER_SIZE + 1);
    int n;

    char temp[BATTLE_BUFFER_SIZE + 1];
    n = snprintf(temp, BATTLE_BUFFER_SIZE, "It did %d damage.\n", dmg);
    strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    slen += n;
    int rc = print_hp(b, string);
    assert(rc == SUCCESS);
    return SUCCESS;
}

/* see battle_print.h */
int print_stat_changes(battle_t *b, turn_t turn, stat_changes_t* changes, char *string)
{
    char* combatant_name;
    if (turn == PLAYER)
    {
        combatant_name = "Your";
    } else
    {
        combatant_name = strcat(b->enemy->name, "\'s");
    }

    int slen = strnlen(string, BATTLE_BUFFER_SIZE + 1);
    int n;

    char temp[BATTLE_BUFFER_SIZE + 1];
    if (changes->speed != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s speed changed by %d\n", combatant_name, 
                    changes->speed);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->max_sp != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s Max SP changed by %d\n", combatant_name, 
                    changes->max_sp);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->sp != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s SP changed by %d\n", combatant_name, 
                    changes->sp);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->phys_atk != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s physical attack"
                " changed by %d\n", combatant_name, changes->phys_atk);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->mag_atk != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s magical attack"
                " changed by %d\n", combatant_name, changes->mag_atk);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->phys_def != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s physical defense"
                " changed by %d\n", combatant_name, changes->phys_def);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->mag_def != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s magical defense"
                " changed by %d\n", combatant_name, changes->mag_def);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->crit != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s crit changed by %d\n", 
                    combatant_name, changes->crit);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->accuracy != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s accuracy changed by %d\n", 
                    combatant_name, changes->accuracy);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->hp != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s HP changed by %d\n", 
                    combatant_name, changes->hp);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    if (changes->max_hp != 0)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "%s Max HP changed by %d\n", 
                    combatant_name, changes->max_hp);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    return SUCCESS;
}

/* see battle_print.h */
int print_stat_changes_move(battle_t *b, turn_t turn, move_t *move, char *string)
{
    char *move_name = move->name;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;
    int rc;
    if (turn == PLAYER)
    {
        switch(move->stat_mods)
        {
            case USER:
                rc = print_stat_changes(b, PLAYER, move->user_mods, string);
                break;
            case TARGET:
                rc = print_stat_changes(b, TARGET, move->opponent_mods, string);
                break;
            case BOTH:
                rc = print_stat_changes(b, PLAYER, move->user_mods, string);
                assert(rc == SUCCESS);
                rc = print_stat_changes(b, TARGET, move->opponent_mods, string);
                break;
            default:
                return FAILURE;
                break;
        }
    }
    else
    {
        switch(move->stat_mods)
        {
            case USER:
                rc = print_stat_changes(b, TARGET, move->user_mods, string);
                break;
            case TARGET:
                rc = print_stat_changes(b, PLAYER, move->opponent_mods, string);
                break;
            case BOTH:
                rc = print_stat_changes(b, PLAYER, move->opponent_mods, string);
                assert(rc == SUCCESS);
                rc = print_stat_changes(b, TARGET, move->user_mods, string);
                break;
            default:
                return FAILURE;
                break;
        }
    }
    assert(rc == SUCCESS);
    return SUCCESS;
}

/* see battle_print.h */
char *print_battle_miss(battle_t *b, turn_t turn, move_t *move)
{
    char *move_name = move->name;
    char *enemy_name = b->enemy->name;
    char *combatant_name;

    if (turn == PLAYER)
    {
        combatant_name = "You";
    } 
    else
    {
        combatant_name = enemy_name;
    }

    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

    snprintf(string, BATTLE_BUFFER_SIZE, "%s used %s, but it missed!\n",
             combatant_name, move_name);

    int rc = print_hp(b, string);
    assert(rc == SUCCESS);

    return string;
}

/* see battle_print.h */
char *print_battle_winner(battle_status_t status, int xp)
{
    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

    if (status == BATTLE_VICTOR_PLAYER)
    {
        snprintf(string, BATTLE_BUFFER_SIZE, "You've won! You gain %d XP!\n",xp);
    } else if (status == BATTLE_VICTOR_ENEMY)
    {
        snprintf(string, BATTLE_BUFFER_SIZE, "You have been defeated!\n");
    }

    return string;
}

/* see battle_print.h */
char *print_start_turn(battle_t *b)
{
    char *enemy_name = b->enemy->name;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;

    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));



    snprintf(string, BATTLE_BUFFER_SIZE, "\nTo use a Move, type 'Use [insert move name here]'\n\n"
                                         "To use an Item, type 'Consume [insert item name here]'\n\n"
                                         "To see the list available moves, type 'List Moves'\n\n"
                                         "To see the list available items, type 'List Items'\n");

    return string;
}

/* see battle_print.h */
char *print_moves(battle_t *b, char* moves)
{
    move_t *temp;
    int slen = strnlen(moves, BATTLE_BUFFER_SIZE + 1);
    int n;
    
    char temp2[BATTLE_BUFFER_SIZE + 1];

    n = snprintf(temp2,BATTLE_BUFFER_SIZE,"\nAVAILABLE MOVES:\n");
    strncat(moves, temp2, BATTLE_BUFFER_SIZE - slen);
    slen += n;

    DL_FOREACH(b->player->moves, temp)
    {
        
        int n = snprintf(temp2, BATTLE_BUFFER_SIZE, "Move Name: %s\nDamage: %d\n",
        temp->info, temp->damage);
        strncat(moves, temp2, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    return moves;
}

/* see battle_print.h */
int *print_battle_items(battle_t *b, char *string)
{
    battle_item_t *player_items = b->player->items;

    int slen = strnlen(string, BATTLE_BUFFER_SIZE + 1);
    int n;

    char temp[BATTLE_BUFFER_SIZE + 1];
    

    n = snprintf(temp,BATTLE_BUFFER_SIZE,"\nAVAILABLE ITEMS:\n");
    strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    slen += n;
    
    battle_item_t *item;
    DL_FOREACH(player_items, item)
    {
        char* name = item->name;
        int quantity = item->quantity;

        n = snprintf(temp, BATTLE_BUFFER_SIZE, "Name: %s\nQuantity: %d\n", name, quantity);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }

    return SUCCESS;
   
}
/* THIS PR NEEDS TO ACCOUNT FOR THE print_battle_action_menu()
    from a non merged PR.  */

/* see battle_print.h */
int *print_battle_item_details(battle_item_t *item, char *string)
{
    int slen = strnlen(string, BATTLE_BUFFER_SIZE + 1);
    int n;
    char temp[BATTLE_BUFFER_SIZE + 1];

    char* name = item->name;
    char* description = item->description;
    stat_changes_t *changes = item->attributes;
    int phys_atk = changes->phys_atk;
    int mag_atk = changes->mag_atk;
    int phys_def = changes->phys_def;
    int mag_def = changes->mag_def;
    int max_sp = changes->max_sp;
    int sp = changes->sp;
    int max_hp = changes->max_hp;
    int hp = item->hp;
    int crit = item->crit;
    int accuracy = item->accuracy;
    int quantity = item->quantity;

    n = snprintf(temp, BATTLE_BUFFER_SIZE, "Name: %s\n"
                "Description: %s\nStat Changes:\n"
                "\tPhysical Attack: %d\n\tMagical Attack: %d\n"
                "\tPhysical Defense: %d\n\tMagical Defense: %d\n"
                "\tMax_SP: %d\n\tSP: %d\n"
                "\tMax_HP: %d\n\tSP: %d\n"
                "\tCritical Rate: %d\n\tAccuracy: %d\n"
                "\nQuantity: %d\n", 
                name, description, phys_atk, mag_atk, phys_def, mag_def,
                max_sp, sp, max_hp, hp, crit, accuracy);

    strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    slen += n;
    return SUCCESS;
}

 
