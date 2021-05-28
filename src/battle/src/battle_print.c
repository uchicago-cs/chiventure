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

    //int rc = print_hp(b, string);
    //assert(rc == SUCCESS);

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

    // n = snprintf(temp, BATTLE_BUFFER_SIZE, "ENEMY HP\n");
    // strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    // slen += n;

    // calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
    // char *player_hp_string;
    // sprintf(player_hp_string,"\n-- Your HP: %d\n", player_hp);
    // strcat(string, player_hp_string);
    // char *enemy_hp = ("ENEMY HP\n");
    // strcat(string, enemy_hp);

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

   // char *movestring = calloc(200,sizeof(char));
    //char *itemstring = calloc(200,sizeof(char));
    //char *movestring = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
   // char *itemstring = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

   // snprintf(string, BATTLE_BUFFER_SIZE, "Your turn!\n\n");

    //print_hp(b, string);

    snprintf(string, BATTLE_BUFFER_SIZE, "\nTo use a Move, type 'Use [insert move name here]'\n\n"
                                         "To use an Item, type 'Consume [insert item name here]'\n");
    print_moves(b,string);
    print_battle_items(b, string);

   // snprintf(movestring, BATTLE_BUFFER_SIZE, "\n\n\n");
   // print_battle_items(b,itemstring);

    // if (((strlen(movestring) + strlen(itemstring)) > 100)) {
    //     string = realloc(string, (250 + strlen(movestring) + strlen(itemstring) * sizeof(char)));
    // }
    //  if (((strlen(itemstring)+ strlen(string)) > 200)) {
    //     string = realloc(string, (250 + strlen(itemstring) + strlen(string)) * sizeof(char));
    // }
    
    //strcat(string, movestring);
    //strcat(string, itemstring);
    
    //free(movestring);
    //free(itemstring);

    return string;
}

/* see battle_print.h */
char *print_moves(battle_t *b, char* moves)
{
    move_t *temp;
    int slen = strnlen(moves, BATTLE_BUFFER_SIZE + 1);
    int n;
    
    char temp2[BATTLE_BUFFER_SIZE + 1];

    n = snprintf(temp2,BATTLE_BUFFER_SIZE,"AVAILABLE MOVES:\n");
    strncat(moves, temp2, BATTLE_BUFFER_SIZE - slen);
    slen += n;

    DL_FOREACH(b->player->moves, temp)
    {
        //char *store = calloc(BATTLE_BUFFER_SIZE, sizeof(char));
        int n = snprintf(temp2, BATTLE_BUFFER_SIZE, "Move Name:%s\nDescription:%s\nAttack:%d\nDamage:%d\nDefense:%d\n",
        temp->name,temp->info, temp->attack, temp->damage, temp->defense);
        strncat(moves, temp2, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }

    n = snprintf(temp2,BATTLE_BUFFER_SIZE,"AVAILABLE BATTLE ITEMS:\n");
    strncat(moves, temp2, BATTLE_BUFFER_SIZE - slen);
    slen += n;

    battle_item_t *temp3;
    DL_FOREACH(b->player->items, temp3)
    {
        //char *store = calloc(BATTLE_BUFFER_SIZE, sizeof(char));
        int n = snprintf(temp2, BATTLE_BUFFER_SIZE, "\nItem Name:%s\nDescription:%s\nAttack:%d\nDefense:%d\nHP:%d\n",
        temp3->name,temp3->description, temp3->attack, temp3->defense, temp3->hp);
        strncat(moves, temp2, BATTLE_BUFFER_SIZE - slen);
        slen += n;
    }
    return moves;
}

/* see battle_print.h */
char *print_battle_items(battle_t *b, char* items)
{
    
    battle_item_t *temp;
    int slen = strnlen(items, BATTLE_BUFFER_SIZE + 1);
    int n;
    
    char temp2[BATTLE_BUFFER_SIZE + 1];

    n = snprintf(temp2,BATTLE_BUFFER_SIZE,"AVAILABLE BATTLE ITEMS:\n");
    strncat(items, temp2, BATTLE_BUFFER_SIZE - slen);
    slen += n;

    DL_FOREACH(b->player->items, temp)
    {
        //char *store = calloc(BATTLE_BUFFER_SIZE, sizeof(char));
        int n = snprintf(temp2, BATTLE_BUFFER_SIZE, "Name: %s\nDescription: %s\nAttack: %d\nDefense: %d\nHP: %d\n",
        temp->name,temp->description, temp->attack, temp->defense, temp->hp);
        strncat(items, temp2, BATTLE_BUFFER_SIZE - slen);
        slen += n;
        // strcat(items, temp->name);
        // strcat(items, "\n");
        // strcat(items, "ID: ");
        // char *id;
        // itoa(temp->id, id, 10);
        // strcat(items, id);
        // strcat(items, "\n");
        // strcat(items, "Description: ");
        // strcat(items, temp->description);
        // strcat(items, "\n");
        // strcat(items, "Description: ");
        // char *quantity;
        // itoa(temp->quantity, id, 10);
        // strcat(items, quantity);
        // strcat(items, "\n");
        // strcat(items, "Attack: ");
        // char *attack;
        // itoa(temp->attack, attack, 10);
        // strcat(items, attack);
        // char *defense;
        // itoa(temp->defense, defense, 10);
        // strcat(items, ", Defense: ");
        // strcat(items, defense);
        // char *hp;
        // itoa(temp->hp, hp, 10);
        // strcat(items, ", HP: ");
        // strcat(items, hp);
    }
    return items;
}