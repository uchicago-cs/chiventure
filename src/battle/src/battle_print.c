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

    int rc = print_hp(b, string);
    assert(rc == SUCCESS);

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

    n = snprintf(temp, BATTLE_BUFFER_SIZE, "ENEMY HP\n");
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

    snprintf(string, BATTLE_BUFFER_SIZE, "Your turn!\n\n");

    print_hp(b, string);

    

    return string;
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

/* Prints out the avaliable battle_items for the player
 * Parameter:
 *  ctx: the main structure of the game
 * Returns:
 *  Always SUCCESS
 */ 
int print_battle_items(chiventure_ctx_battle_t *ctx)
{
    battle_item_t *temp;
    printf("\nAVAILABLE BATTLE ITEMS LIST:\n");
    DL_FOREACH(ctx->game->battle->player->items, temp)
    {
        printf("Name: %s\n", temp->name);
        printf("ID: %d\n", temp->id);
        printf("Description: %s\n", temp->description);
        printf("Quantity: %d\n", temp->quantity);
        printf("Attack: %d, Defense: %d, HP: %d\n", 
                temp->attack, temp->defense, temp->hp);
    }
    return SUCCESS;
}