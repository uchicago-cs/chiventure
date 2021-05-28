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

    char *battle_begin = ("You have encountered %s!\n\n 
                        Let the battle begin!\n",
                    enemy_name);
    strcat(string, battle_begin);

    int rc = print_hp(b, string);
    assert(rc == SUCCESS);

    return string;
}

/* see battle_print.h */
int print_hp(battle_t* b, char* string)
{
    int player_hp = b->player->stats->hp;

    /* int slen = strnlen(string, BATTLE_BUFFER_SIZE + 1);
    int n;

    char temp[BATTLE_BUFFER_SIZE + 1];
    
    n = snprintf(temp, BATTLE_BUFFER_SIZE, "-- Your HP: %d\n", player_hp);
    strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    slen += n;

    n = snprintf(temp, BATTLE_BUFFER_SIZE, "ENEMY HP\n");
    strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
    slen += n; */

    calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
    char *player_hp_string;
    sprintf(player_hp_string,"\n-- Your HP: %d\n", player_hp);
    strcat(string, player_hp_string);
    char *enemy_hp = ("ENEMY HP\n");
    strcat(string, enemy_hp);

    combatant_t *enemies = b->enemy;
    combatant_t *enemy_elt;
    DL_FOREACH(enemies, enemy_elt)
    {
        char* name = enemy_elt->name;
        int enemy_hp = enemy_elt->stats->hp;

        enemy_hp = ("-- %s's HP: %d\n", name, enemy_hp);
        strcat(string, enemy_hp);
        /* n = snprintf(temp, BATTLE_BUFFER_SIZE, "-- %s's HP: %d\n", name, enemy_hp);
        strncat(string, temp, BATTLE_BUFFER_SIZE - slen);
        slen += n; */
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

    /* snprintf(string, BATTLE_BUFFER_SIZE, "%s used %s! It did %d damage.\n",
             combatant_name, move_name, dmg); */

    char *enemey_damage = ("%s used %s! It did %d damage.\n",
             combatant_name, move_name, dmg);
    strcat(string, enemy_damage);

    int rc = print_hp(b, string);
    assert(rc == SUCCESS);

    return string;
}

/* see battle_print.h */
char *print_battle_winner(battle_status_t status, int xp)
{
    char *string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
    char *winner;

    if (status == BATTLE_VICTOR_PLAYER)
    {
        //snprintf(string, BATTLE_BUFFER_SIZE, "You've won! You gain %d XP!\n",xp);
        winner = ("You've won! You gain %d XP!\n",xp);
        strcat(string, winner);
    } else if (status == BATTLE_VICTOR_ENEMY)
    {
        //snprintf(string, BATTLE_BUFFER_SIZE, "You have been defeated!\n");
        winner = ("You have been defeated!\n");
        strcat(string, winner);
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

    //snprintf(string, BATTLE_BUFFER_SIZE, "Your turn!\n\n");
    strcat(string, "Your turn!\n\n")

    print_hp(b, string);

    snprintf(string, BATTLE_BUFFER_SIZE, "To use a Move, type 'Use [insert move name here]'\n");
    print_moves(b,string);

    snprintf(string, BATTLE_BUFFER_SIZE, "\nTo use an Item, type 'Consume [insert item name here]'\n");
    print_battle_items(b,string);

    return string;
}

/* see battle_print.h */
char *print_moves(battle_t *b, char* moves)
{
    move_t *temp;
    
    strcat(moves,"\nMOVES LIST:\n");
    DL_FOREACH(b->player->moves, temp)
    {
        strcat(moves, temp->info);
        strcat(moves, "\n");
    }
    return moves;
}

/* see battle_print.h */
char *print_battle_items(battle_t *b, char* items)
{
    char *store = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));
    battle_item_t *temp;
    strcat(items,"\nAVAILABLE BATTLE ITEMS LIST:\n");
    DL_FOREACH(b->player->items, temp)
    {
        sprintf(store,"Name: %s\n, Description: %s\n, Attack: %d\n , Defense: %d, HP: %d\n",
        temp->name,temp->description, temp->attack, temp->defense, temp->hp);
        strcat(items,store );
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