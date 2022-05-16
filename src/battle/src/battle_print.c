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
    char *move_name = move->info;
    int player_hp = b->player->stats->hp;
    int enemy_hp = b->enemy->stats->hp;
    char* enemy_name = b->enemy->name;
    char* combatant_name;
    int dmg;

    if (turn == PLAYER)
    {
        combatant_name = "You";
        dmg = damage(b->enemy, move, b->player);
    } else
    {
        combatant_name = enemy_name;
        dmg = damage(b->player, move, b->enemy);
    }

    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

    snprintf(string, BATTLE_BUFFER_SIZE, "%s used %s! It did %d damage.\n",
             combatant_name, move_name, dmg);

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
        
        int n = snprintf(temp2, BATTLE_BUFFER_SIZE, "Move Name: %s\nDamage: %d\nDefense: %d\n\n",
        temp->info, temp->damage, temp->defense);
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
        int attack = item->attack;
        int defense = item->defense;
        int hp = item->hp;
        int quantity = item->quantity;

        n = snprintf(temp, BATTLE_BUFFER_SIZE, "Name: %s\nAttack: %d\nDefense: %d\nHP: %d\nQuantity: %d\n", name, attack,defense, hp,quantity);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }

    return SUCCESS;
   
}

char *print_battle_action_menu(battle_item_t *items, move_t *moves, char *string) 
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
  char label[] = "M0 - ";
  
  // loop through each move and add an entry to the menu string for each one
  int i;
  for(i=1; i<=moves_count; i++)
  {
    // set label number (the character '0' corrisponds to the int 30 in ascii)
    label[1] = (char)(30+i);
    // add label to the string and account for its length in index
    memcpy(menu+index, label, 6);
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
  char label[] = "I0 - ";
  for(i=1; i<=moves_count; i++)
  {
    // set label number 
    label[1] = (char)(30+i);
    // add label to the string and account for its length in index
    memcpy(menu+index, label, 6);
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
  *(menu+index) = '\0';

  return menu;
}

/* Gets the expected length of a menu of possible actions based on 
 * the given items and moves
 * 
 * Parameters:
 *  - items: a linked list of available items
 *  - moves: a linked list of available items
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
    return buff_len;
  }
}

