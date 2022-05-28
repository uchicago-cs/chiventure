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
int print_battle_damage(battle_t *b, turn_t turn, move_t *move, double crit, char *string)
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
    dmg *= crit;
    char temp[BATTLE_BUFFER_SIZE + 1];
    if (crit == 1.5)
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "It was a critical hit! It did %d damage.\n", dmg);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    else
    {
        n = snprintf(temp, BATTLE_BUFFER_SIZE, "It did %d damage.\n", dmg);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
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
char *print_battle_item(battle_t *b, turn_t turn, battle_item_t *item)
{
  char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
  snprintf(string, BATTLE_BUFFER_SIZE, "you used %s", item->name);
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
    } else if (status == BATTLE_ENEMY_SURRENDER)
    {
	snprintf(string, BATTLE_BUFFER_SIZE, "Your opponent has surrendered!\n");
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
    int hp = changes->hp;
    int crit = changes->crit;
    int accuracy = changes->accuracy;
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
                max_sp, sp, max_hp, hp, crit, accuracy, quantity);

    strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    slen += n;
    return SUCCESS;
}

/* Gets the expected length of a menu of possible actions based on 
 * the given items and moves
 * 
 * Parameters:
 *  - items: a linked list of available items
 *  - moves: a linked list of available moves
 * Returns:
 *  The expected length of the menu
 */ 
int action_menu_buffer_length(battle_item_t *items, move_t *moves) {
  int buff_len = 2; // leave space for the null terminator and an extra newline between items and moves
  //loop until all moves and all items have been accounted for
  while(moves || items) 
  {
    //account for a move
    if(moves) 
    {
      buff_len += strlen(moves->name) + 6; //6 adds space for the newline and label (e.g. "M1 - ")
      moves = moves->next;
    //account for an item
    } else if(items)
    // if all moves are accounted for, account for an item
    {
      buff_len += strlen(items->name) + 6;
      items = items->next;
    }
    // account for "D - Do nothing"
    return buff_len + 15;
  }
}

/* see battle_print.h */
char *print_battle_action_menu(battle_item_t *items, move_t *moves)
{
  
  // get the number of moves and number of items
  int moves_count = num_moves(moves);
  int items_count = num_items(items);

  // get the length of the full menu string
  int buff_len = action_menu_buffer_length(items, moves);
  // allocate the empty string
  char *menu = malloc(buff_len);

  // int to keep track of the size of the string as it is built
  int index = 0;
  // int representing the length of each move name
  int name_len;
  // string representing the menu label for each item
  char move_label[] = "M0 - ";
  
  // loop through each move and add an entry to the menu string for each one
  int i;
  for(i = 1; i <= moves_count; i++)
  {
    // set label number (the character '0' corrisponds to the int 30 in ascii)
    move_label[1] = (char)(30+i);
    // add label to the string and account for its length in index
    memcpy(menu+index, move_label, 6);
    index += 5;
    
    // get the length of the move name
    name_len = strlen(moves->name);
    // add the move name to the menu and account for its length in index
    memcpy(menu+index, moves->name, name_len);
    index += name_len;
    // add a newline character to the string
    *(menu+index) = '\n';
    index++;
    // go to the next move
    moves = moves->next;
  }

  // add a newline character between moves and items
    *(menu+index) = '\n';
    index++;

  // loop through each item and add an entry to the menu string for each one
  char item_label[] = "I0 - ";
  for(i = 1; i <= moves_count; i++)
  {
    // set label number 
    item_label[1] = (char)(30+i);
    // add label to the string and account for its length in index
    memcpy(menu+index, item_label, 6);
    index += 5;
    
    // get the length of the item name
    name_len = strlen(items->name);
    // add the item name to the menu and account for its length in index
    memcpy(menu+index, items->name, name_len);
    index += name_len+1;
    // add a newline character to the string
    *(menu+index) = '\n';
    index++;

    // go to the next item
    items = items->next;
  }

  // add do nothing option (including null terminator)
  char do_nothing_option[] = "D - Do nothing";
  memcpy(menu+index, do_nothing_option, 15);

  return menu;
}
